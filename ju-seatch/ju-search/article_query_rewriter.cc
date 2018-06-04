// Copyright 2017 Baidu.com  All Rights Reserved.
// Author: lipeng08@baidu.com (lipeng08)

#include <vector>
#include "unise/matched_node.h"
#include "unise/matched_doc.h"
#include "unise/fact_doc.h"
#include "unise/general_servlet.pb.h"
#include "gflags/gflags.h"
#include "unise/base.h"
#include "unise/singleton.h"
#include "index/index.h"
#include "article_query_rewriter.h"

namespace unise {
    
    ArticleQueryRewriter::ArticleQueryRewriter() : _dict(NULL), _handler(NULL), _tokens(NULL) {
    }

    ArticleQueryRewriter::~ArticleQueryRewriter() {
        // note: 不要析构_dict和_handler
        if (_tokens != NULL) {
            delete[] _tokens;
        }
        _stop_words.clear();
    }

    bool ArticleQueryRewriter::init(const comcfg::ConfigUnit& conf) {
        std::string stopword_dict = conf["stopword_dict"].to_cstr();
        UWARNING("stopword_dict path is %s", stopword_dict.c_str());
        std::ifstream in(stopword_dict.c_str(), std::ios::in);
        if (in.fail()) {
            UWARNING("no stopword dict");
        }

        std::string stop_word;
        while(getline(in, stop_word)) {
            UDEBUG("stop_word(%s) add to dict", stop_word.c_str());
           _stop_words.insert(stop_word); 
        }
        in.close();

        // 从全局单例中初始化词典和切词缓冲区（封装为handler）
        _dict = Singleton<AslWordseg>::get()->get_dict();
        if (_dict == NULL) {
            UWARNING("[\tlvl=SERIOUS\t] get dict in ArticleQueryRewriter failed");
            return false;
        }
        
        return true;
    }

    void ArticleQueryRewriter::build_query_tree(GeneralSearchRequest * req) {
        std::string raw_query = req->raw_query();
        if (raw_query.size() == 0) {
            if (!get_string_experiment_value(*req, "raw_query", &raw_query)) {
                return;
            }
            req->set_raw_query(raw_query);
        }
        const std::string trans_raw_query;
        trans_word(raw_query, &trans_raw_query);
        raw_query = trans_raw_query;

        // int dyn_flag = SCW_OUT_BASIC | SCW_OUT_WPCOMP;
        int dyn_flag = SCW_OUT_WPCOMP;

        if (scw_segment_words(_dict,
                    _handler,
                    raw_query.c_str(),
                    raw_query.length(),
                    LANGTYPE_SIMP_CHINESE,
                    &dyn_flag) != 1) {
            UWARNING("[\tlvl=FOLLOW\t] value[%s] seg fail", raw_query.c_str());
            return;
        }

        UDEBUG("seg article in ArticleQueryRewriter, raw_query:%s, seg_type:%d", raw_query.c_str(), dyn_flag);
        std::vector<std::string> annotation_query_strs;
        std::vector<std::string> phrase_words;
        SearchParams * sp = req->mutable_search_params();

        for (int flag = SCW_OUT_DISAMB; flag >= SCW_OUT_BASIC; flag = flag >> 1) {
            if ((flag & dyn_flag) == 0) {
                continue;
            }
        
            int count = scw_get_token_1(_handler,
                    flag,
                    _tokens,
                    ANNOTATION_SIZE_MAX);

            for (int i = 0; i < count; ++i) {
                const token_t& token = _tokens[i];
                UDEBUG("token[%s] length[%u] offset[%u] type[%u] weight[%u]",
                        token.buffer, token.length, token.offset, token.type, token.weight);
                if (std::find(phrase_words.begin(), phrase_words.end(), token.buffer) == phrase_words.end()) {

                        /*Experiment * ep = sp->add_experiments();
                        ep->set_key(token.buffer);
                        ep->set_value("true");*/
                        phrase_words.push_back(token.buffer);
                }
            }
        }

        std::string query_tree_str;
        std::string phrase_node_strs;

        for (size_t i = 0; i < phrase_words.size(); i++) {
            if (phrase_words.at(i).find_first_of(",\t .!") != std::string::npos) {
                continue;
            }
            std::string phrase_node = StringPrintf("V(%s SECTION text_section_tc),",
                    phrase_words.at(i).c_str());
            phrase_node_strs += phrase_node;
        }
        string_trim(&phrase_node_strs, ",");
        phrase_node_strs = StringPrintf("A(%s)", phrase_node_strs.c_str());

        if (phrase_words.size() == 0) {
            query_tree_str = StringPrintf("V(%s SECTION text_section_tc)",
                    INVALID_QUERY.c_str());
        } else {
            query_tree_str = phrase_node_strs;
        }
        UWARNING("query_tree_str is %s", query_tree_str.c_str());

        QueryNode * query_tree = req->mutable_query_tree();
        BackendQueryBuilder builder;
        if (!builder.build(query_tree_str, query_tree)) {
            UWARNING("Build QueryTree from query fail:%s", query_tree_str.c_str());
            req->clear_query_tree();
        }
    }

    void ArticleQueryRewriter::rewrite_internal(GeneralSearchRequest * req) {
        UDEBUG("use article_query_rewriter");
        _handler = Singleton<AslWordseg>::get()->get_handle(1024); 
        if (_handler == NULL) {
            UWARNING("[\tlvl=SERIOUS\t] get dict_handler in ArticleQueryRewriter failed");
            return;
        }
        _tokens = new(std::nothrow) token_t[ANNOTATION_SIZE_MAX];
        if (_tokens == NULL) {
            UWARNING("[\tlvl=SERIOUS\t] init tokens in ArticleQueryRewriter failed");
            return;
        }
        build_query_tree(req);
        if (_tokens != NULL) {
            delete[] _tokens;
        }
    }

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
