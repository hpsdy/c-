// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/matched_doc_internal.h"
#include "unise/matched_node.h"

namespace unise
{

MatchedDocInternal::MatchedDocInternal(
      const doc_info_t & doc_info,
      DocMatchInfoProxy* proxy) :
    _score(0),
    _docid(doc_info.docid),
    _doc_match_info_proxy(proxy),
    _search_result(new SearchResult()),
    _doc_info(doc_info)
{
    UDEBUG("docinfo [docid:%llu score:%d fact_doc_address:%p] "
           "factdoc [docid:%llu score:%d]",
           _doc_info.docid, _doc_info.score, _doc_info.fact_doc,
           _doc_info.fact_doc->get_doc_id(), _doc_info.fact_doc->get_score());
}

const std::vector<MatchedNode*>& MatchedDocInternal::get_matched_nodes() const
{
    return _doc_match_info_proxy->get_matched_nodes();
}

bool MatchedDocInternal::build_doc_match_info()
{
    return _doc_match_info_proxy->build_doc_match_info(_doc_info.forward_index);
}

void MatchedDocInternal::finalize_result()
{
    // 提前在scorer handler进行score和docid的固化
    // _search_result->set_score(get_score());
    // _search_result->set_docid(get_doc_id());
    _doc_match_info_proxy->finalize_result(_search_result.get());
}

const doc_info_t& MatchedDocInternal::get_doc_info() const
{
    UDEBUG("docinfo [docid:%llu score:%d fact_doc_address:%p] "
           "factdoc [docid:%llu score:%d]",
           _doc_info.docid, _doc_info.score, _doc_info.fact_doc,
           _doc_info.fact_doc->get_doc_id(), _doc_info.fact_doc->get_score());
    return _doc_info;
}

const FactDoc& MatchedDocInternal::get_fact_doc() const
{
    UDEBUG("docinfo [docid:%llu score:%d fact_doc_address:%p] "
           "factdoc [docid:%llu score:%d]",
           _doc_info.docid, _doc_info.score, _doc_info.fact_doc,
           _doc_info.fact_doc->get_doc_id(), _doc_info.fact_doc->get_score());
    return *(_doc_info.fact_doc);
}

}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
