// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_MATCHED_DOC_INTERNAL_H_
#define  RETRI_MATCHED_DOC_INTERNAL_H_

#include <boost/scoped_ptr.hpp>
#include <vector>
#include "unise/matched_doc.h"
#include "unise/general_servlet.pb.h"
#include "unise/fact_doc.h"
#include "retri/doc_match_info_proxy.h"

namespace unise
{
class MatchedNode;

class MatchedDocInternal : public MatchedDoc
{
public:
    MatchedDocInternal(const doc_info_t & doc_info,
                       DocMatchInfoProxy* proxy);

    virtual ~MatchedDocInternal() {}
    virtual dynamic_score_t get_score() const { return _score; }
    virtual DocId get_doc_id() const { return _docid; }
    virtual const std::vector<MatchedNode*>& get_matched_nodes() const;
    virtual const doc_info_t& get_doc_info() const;

    bool build_doc_match_info();

    inline void set_score(dynamic_score_t score)
    {
        _score = score;
        _search_result->set_score(_score);
        _search_result->set_docid(_docid);
    }
    virtual SearchResult * get_search_result() { return _search_result.get(); }
    virtual const SearchResult * get_search_result() const { return _search_result.get(); }
    void finalize_result();

    /**
     * @brief 获取当前MatchedDoc的fact doc引用
     */
    virtual const FactDoc & get_fact_doc() const;

private:
    dynamic_score_t _score;
    DocId _docid;
    DocMatchInfoProxy * _doc_match_info_proxy;
    boost::scoped_ptr<SearchResult> _search_result;
    doc_info_t _doc_info;
};

}

#endif  // RETRI_MATCHED_DOC_INTERNAL_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
