// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "article_scorer.h"
#include <vector>
#include "gflags/gflags.h"
#include "unise/matched_node.h"
#include "unise/matched_doc.h"
#include "unise/fact_doc.h"
#include "unise/general_servlet.pb.h"
#include "unise/base.h"
#include "unise/search_context.h"
#include "serve/frontend/unise_frontend.h"
#include "unise/util.h"

namespace unise {

void ArticleScorer::init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) {
    _request = request;
    _doc_factor = 1;
    _annotation_factor = 0;
    _hit_factor = 1;

    // you can change this factor from request's SearchParams's extensions params
    context->get_experiment_value("doc_factor", &_doc_factor);
    context->get_experiment_value("annotation_factor", &_annotation_factor);
    context->get_experiment_value("hit_factor", &_hit_factor);
    _request = request;

    // clear hash map
    _query_node_map.clear();
    _query_node.Clear();
    // 递归的方法对hash复制
    if (request->has_query_tree()) {
        build_token_info_hashmap(&(request->query_tree()));
    } else {
        UWARNING("request has no query nether query_tree");
    }
}

void ArticleScorer::build_token_info_hashmap(const QueryNode * root) {
    GOOGLE_DCHECK(root);
    if (root->type() == VALUE && root->has_value()) {
        TokenId token_id = get_token_id_from_query_node_value(root->value());
        if (token_id != ILLEGAL_TOKEN_ID) {
            _query_node_map.insert(std::make_pair(token_id, &root->value()));
        }
    } else if (root->type() == AND || root->type() == OR) {
        // Don't handler "NOT"
        // TODO(wangguangyuan) : 改成迭代算法
        for (int i = 0; i < root->children_size(); ++i) {
            build_token_info_hashmap(&(root->children(i)));
        }
    }
}

bool ArticleScorer::hilight_annotations_score(MatchedDoc* doc, dynamic_score_t* score) {
    if (doc == NULL || doc->get_matched_nodes().size() == 0) {
        return false;
    }

    _annotation_id_pos_len.clear();
    const FactDoc & fact_doc = doc->get_fact_doc();
    const std::vector<MatchedNode*>& nodes = doc->get_matched_nodes();

    for (size_t j = 0; j < nodes.size(); ++j) {
        const MatchedNode* node = nodes.at(j);
        TokenId token_id = node->get_token_id();
        QueryNodeMap::const_iterator it = _query_node_map.find(token_id);
        if (it == _query_node_map.end()) {
            continue;
        }

        std::string query_node_value = it->second->text_value();
        for (size_t k = 0; k < node->get_hits().size(); ++k) {
            const doc_token_hit_t * hit = node->get_hits().at(k);
            if (hit->annotation_id == 6) {
                if (_annotation_id_pos_len[hit->annotation_id].size() < 2) {
                    _annotation_id_pos_len[hit->annotation_id].insert(std::make_pair(hit->pos, query_node_value.size()));
                }
            } else {
                _annotation_id_pos_len[hit->annotation_id].insert(std::make_pair(hit->pos, query_node_value.size()));

            }
        }
    }


    std::map<uint16_t, std::map<uint32_t, uint32_t> >::iterator it = _annotation_id_pos_len.begin();
    double title_hit_score = 0;
    double content_hit_score = 0;

    SearchParams * sp = _request->mutable_search_params();
    while (it != _annotation_id_pos_len.end()) {
        for (size_t k = 0; k < fact_doc.annotations.size(); k++) {

            const Annotation& annotation = fact_doc.annotations.at(k);
            if (it->first == annotation.id) {
                std::string doc_id_annotation_id = StringPrintf("%u_%u",
                        doc->get_doc_id(),
                        annotation.id);
                std::map<uint32_t, uint32_t>::reverse_iterator pos_len_it = it->second.rbegin();

                std::string pos_lens;
                uint32_t last_pos = 0;
                uint32_t last_len = 0;

                while (pos_len_it != it->second.rend()) {
                    uint32_t pos = pos_len_it->first - 1;
                    uint32_t len = pos_len_it->second;

                    std::string query_word = fact_doc.annotations.at(k).text_value.substr(pos, len);
                    std::string is_phrase;
                    get_string_experiment_value(*_request, query_word, &is_phrase);
                    UDEBUG("query_word(%s) and is_phrase(%s)", query_word.c_str(), is_phrase.c_str());
                    /*uint16_t word_factor = 1;
                    if (is_phrase == "true") {
                        word_factor = 3;
                    }*/
                    uint16_t word_factor = 3;
                    if (it->first == 3) {
                        title_hit_score += 100 * word_factor;
                    }
                    if (it->first == 6) {
                        content_hit_score += 10 * word_factor;
                    }
                    // UWARNING("annotation(%s),pos(%u),length(%u)", fact_doc.annotations.at(k).text_value.c_str(), pos_len_it->first, pos_len_it->second);
                    // UWARNING("query_word is %s", query_word.c_str());
                    std::string pos_len = StringPrintf("%u:%u;", pos, len);
                    if (pos <= last_pos && pos + len >= last_pos + last_len) {
                        pos_lens = pos_len;
                    } else {
                        pos_lens += pos_len;
                    }
                    last_pos = pos;
                    last_len = len;

                    pos_len_it++;
                }
                if (pos_lens.size() > 0) {
                    string_trim(&pos_lens, ";");
                    Experiment * ep = sp->add_experiments();
                    ep->set_key(doc_id_annotation_id);
                    ep->set_value(pos_lens);
                    /*UWARNING("doc_id_annotation_id(%s) and pos_lens(%s)",
                            doc_id_annotation_id.c_str(),
                            pos_lens.c_str());*/
                }
            }
        }
        it++;
    }
    if (title_hit_score > 500) {
        title_hit_score = 500;
    }
    if (content_hit_score > 100) {
        content_hit_score = 100;
    }
    *score = title_hit_score + content_hit_score;
    UDEBUG("title_hit_score(%f), content_hit_score(%f)", title_hit_score, content_hit_score);
    return true;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
bool ArticleScorer::score(MatchedDoc * doc, dynamic_score_t * score) {
    hilight_annotations_score(doc, score);
    double hit_score = *score;
    const ArticleDoc* article = dynamic_cast<const ArticleDoc*>(get_dimension_doc(
                "ArticleDoc",
                doc->get_doc_id()));

    if (hit_score > 0) {
        std::string city_id_str;
        int64_t city_id = 0;
        if (
            get_string_experiment_value(*_request, "city_id", &city_id_str)
            && StringToInt64(city_id_str, &city_id)
            && city_id == article->get_city_id()
        ) {
            hit_score += 800;
        }
    }

    // get the static score use docid
    const FactDoc& fact_doc = doc->get_fact_doc();
    double static_score = fact_doc.get_score() * _doc_factor;

    double time_score = 0;
    uint32_t publish_time = article->get_publish_time();
    uint32_t current_time = (uint32_t)get_timestamp();
    int32_t gap_time = current_time - publish_time;

    if (gap_time < 86400) {
        time_score = 200;
    } else if (gap_time < 86400 * 3) {
        time_score = 120;
    } else if (gap_time < 86400 * 7) {
        time_score = 80;
    } else if (gap_time < 86400 * 30) {
        time_score = 40;
    } else if (gap_time < 86400 * 60){
        time_score = 20;
    } else {
        time_score = 10;
    }

    // avoid overflow
    double sum = static_score + hit_score + time_score;
    UDEBUG("static_score(%f) hit_score(%f) time_score(%f)", static_score, hit_score, time_score);
    dynamic_score_t max_score = ~(1LLU << ((sizeof (dynamic_score_t)<<3) - 1));
    if (sum > static_cast<double>(max_score)) {
        *score = max_score;
    } else {
        *score = static_cast<dynamic_score_t>(sum);
    }
    return true;
}

REGISTER_SCORER(ArticleScorer);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
