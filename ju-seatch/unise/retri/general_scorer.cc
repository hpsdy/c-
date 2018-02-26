// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "general_scorer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

namespace unise {
using std::vector;
using boost::shared_ptr;

GeneralScorer::GeneralScorer() {
    anno_scorer_items_.resize(ANNOTATION_ID_MAX + 1);
}

bool GeneralScorer::init(const comcfg::ConfigUnit& conf) {
    try {
        string scorer_file_path(conf["GeneralScorerConfig"].to_cstr());
        int fd = open(scorer_file_path.c_str(), O_RDONLY);
        if (fd == -1) {
          UFATAL("ScorerFile not exist:%s", scorer_file_path.c_str());
          return false;
        }
        google::protobuf::io::FileInputStream ins(fd);
        bool init_succ = google::protobuf::TextFormat::Parse(&ins, &scorer_config_);
        ins.Close();
        close(fd);

        if (!init_succ) {
          UFATAL("ScorerConfig illegal:%s", scorer_file_path.c_str());
          return false;
        }
    } catch (comcfg::ConfigException& e) {
        // 如果没有配置文件，那么，采用空配置
        UWARNING("illegal Configure for GeneralScorer:%s, use empty config", e.what());
    }
    for (int i = 0; i < scorer_config_.annotation_items_size(); ++i) {
        const AnnotationScorerItem * item = &(scorer_config_.annotation_items(i));
        if (item->annotation_id() > ANNOTATION_ID_MAX) {
            UFATAL("GeneralScorerConfig annotation_id [%u] bigger than [%u]",
                        item->annotation_id(),
                        static_cast<uint32_t>(ANNOTATION_ID_MAX));
            return false;
        }
        // 不检查冲突，以最后一个配置为准
        anno_scorer_items_.at(item->annotation_id()) = item;
        UNOTICE("annotation_id [%u] hit_score [%d] token_score [%d]",
                    item->annotation_id(), item->hit_score(), item->token_score());
    }
    return true;
}

void GeneralScorer::build_token_info_hashmap(const QueryNode * root) {
    GOOGLE_DCHECK(root);
    if (root->type() == VALUE && root->has_value()) {
        TokenId token_id = get_token_id_from_query_node_value(root->value());
        if (token_id != ILLEGAL_TOKEN_ID) {
            query_node_map_.insert(std::make_pair(token_id, &root->value()));
        }
    } else if (root->type() == AND || root->type() == OR) {
        // Don't handler "NOT"
        // TODO(wangguangyuan) : 改成迭代算法
        for (int i = 0; i < root->children_size(); ++i) {
            build_token_info_hashmap(&(root->children(i)));
        }
    }
}

void GeneralScorer::init_for_search(const GeneralSearchRequest* request,
                                    SearchContext * context) {
    GOOGLE_DCHECK(request);
    GOOGLE_DCHECK(context);
    // clear hash map
    query_node_map_.clear();
    query_node_.Clear();
    // 递归的方法对hash复制
    if (request->has_query_tree()) {
        build_token_info_hashmap(&(request->query_tree()));
    } else if (request->has_query()) {
        query_builder_.build(request->query(), &query_node_);
        build_token_info_hashmap(&query_node_);
    } else {
        UWARNING("request has no query nether query_tree");
    }
}

bool GeneralScorer::score(MatchedDoc * doc, dynamic_score_t * score) {
    GOOGLE_DCHECK(doc);
    GOOGLE_DCHECK(score);
    GOOGLE_DCHECK_EQ(doc->get_fact_doc().get_doc_id(), doc->get_doc_id());
    dynamic_score_t anno_score = 0;
    // 初始化所有annotation的查询为0
    int32_t annotations_weight[ANNOTATION_ID_MAX + 1] = {0};
    int32_t annotations_hit_times[ANNOTATION_ID_MAX + 1] = {0};

    // get the hit info
    const vector<MatchedNode*>& nodes = doc->get_matched_nodes();
    UDEBUG("this document has [%u] hit nodes", nodes.size());

    // 遍历所有的命中的token
    for (size_t j = 0; j < nodes.size(); ++j) {
        const MatchedNode* node = nodes.at(j);
        GOOGLE_DCHECK(node);
        string debug_str;
        node->to_string(&debug_str);
        UDEBUG("NodeInfo:%s", debug_str.c_str());

        TokenId token_id = node->get_token_id();
        QueryNodeMap::const_iterator it = query_node_map_.find(token_id);
        if (it == query_node_map_.end()) {
            continue;
        }
        int32_t weight = it->second->weight();

        // 遍历当前token命中的所有hit
        for (size_t hit_idx = 0; hit_idx < node->get_hits().size(); ++hit_idx) {
            const doc_token_hit_t * hit = node->get_hits().at(hit_idx);
            if (hit == NULL) {
                UWARNING("get illegal hit");
                continue;
            }
            AnnotationId hit_anno_id = hit->annotation_id;
            GOOGLE_DCHECK_LE(hit_anno_id, ANNOTATION_ID_MAX);
            // 当前hit命中的Annotation的命中次数自增
            annotations_hit_times[hit_anno_id]++;
            // 赋值查询的动态权重，是的，这里是存在重复赋值
            annotations_weight[hit_anno_id] = weight;
        }
    }

    for (AnnotationId idx = 0; idx <= ANNOTATION_ID_MAX; ++idx) {
        if (annotations_hit_times[idx] == 0) {
            // 没有命中这个编号的annotation
            continue;
        }
        const AnnotationScorerItem * item = anno_scorer_items_.at(idx);
        if (item == NULL) {
            // 命中了这个编号的annotation，但是没有配置项
            continue;
        }
        UDEBUG("hit anno[%u] times[%d] weight[%d]", static_cast<uint32_t>(idx),
                    annotations_hit_times[idx], annotations_weight[idx]);
        // 查询动态权重，只能对一个annotation是否命中进行调权
        // 命中次数的调权，需要在配置文件中修改
        anno_score += item->token_score() * annotations_weight[idx];
        anno_score += item->hit_score() * annotations_hit_times[idx];
    }
    UDEBUG("docid [%llu] general_scorer [%lld]", doc->get_doc_id(), anno_score);
    *score = anno_score;
    return true;
}

REGISTER_SCORER(GeneralScorer);
REGISTER_SCORER(DefaultScorer);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
