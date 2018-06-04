// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_DEMO_SCORER_H
#define  UNISE_DEMO_SCORER_H

#include "unise/general_servlet.pb.h"
#include "unise/util.h"
#include "unise/scorer.h"
#include "Configure.h"
#include "article_doc.h"

namespace unise {
class MatchedDoc;
class GeneralSearchRequest;
class SearchContext;
class PluginResponse;

class ArticleScorer : public Scorer {
public:
    ArticleScorer() {}
    virtual ~ArticleScorer() {}

    virtual bool init(const comcfg::ConfigUnit& conf) {
        (void)(conf);
        return true;
    }
    virtual void init_for_search(const GeneralSearchRequest* request, SearchContext * context);
    virtual bool score(MatchedDoc * doc, dynamic_score_t * score);
    virtual std::string get_name() const { return "ArticleScorer"; }

private:
    void build_token_info_hashmap(const QueryNode * root);
    bool hilight_annotations_score(MatchedDoc* doc, dynamic_score_t* score);

private:
    typedef __gnu_cxx::hash_map<TokenId, const QueryNodeValue *> QueryNodeMap;
    std::map<uint16_t, std::map<uint32_t, uint32_t> > _annotation_id_pos_len;
    QueryNodeMap _query_node_map;
    QueryNode _query_node;
    const GeneralSearchRequest* _request;

    // tokenid映射到哪个查询节点上
    int64_t _doc_factor;
    int64_t _annotation_factor;
    int64_t _hit_factor;
};
}

#endif  // UNISE_DEMO_SCORER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
