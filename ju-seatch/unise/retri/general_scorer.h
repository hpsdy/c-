// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_GENERAL_SCORER_H_
#define  RETRI_GENERAL_SCORER_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <ext/hash_map>
#include <algorithm>
#include "Configure.h"
#include "unise/search_context.h"
#include "unise/fact_doc.h"
#include "unise/matched_doc.h"
#include "unise/matched_node.h"
#include "unise/general_servlet.pb.h"
#include "unise/base.h"
#include "unise/util.h"
#include "unise/scorer.h"
#include "retri/backend_query_builder.h"

namespace unise {
class SearchContext;

class GeneralScorer : public Scorer {
public:
    GeneralScorer();
    virtual ~GeneralScorer() {}

    virtual bool init(const comcfg::ConfigUnit& conf);
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context);
    virtual bool score(MatchedDoc * doc, dynamic_score_t * score);
    virtual std::string get_name() const {
        return "GeneralScorer";
    }
private:
    void build_token_info_hashmap(const QueryNode * root);

private:
    typedef __gnu_cxx::hash_map<TokenId, const QueryNodeValue *> QueryNodeMap;
    // tokenid映射到哪个查询节点上
    QueryNodeMap query_node_map_;
    GeneralScorerConfig scorer_config_;
    std::vector<const AnnotationScorerItem *> anno_scorer_items_;
    BackendQueryBuilder query_builder_;
    QueryNode query_node_;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(GeneralScorer);
};

/**
 * @brief 压测使用，采用doc的静态得分
 */
class DefaultScorer : public Scorer {
public:
    DefaultScorer() {}
    virtual ~DefaultScorer() {}

    virtual bool init(const comcfg::ConfigUnit& conf) {
        (void)(&conf);
        return true;
    }

    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) {
        (void)(request);
        (void)(context);
    }

    virtual bool score(MatchedDoc * doc, dynamic_score_t * score) {
        *score = static_cast<dynamic_score_t>(doc->get_doc_info().score);
        return true;
    }

    virtual std::string get_name() const {
        return "DefaultScorer";
    }

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(DefaultScorer);
};

}

#endif  // RETRI_GENERAL_SCORER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
