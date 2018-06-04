// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include <boost/lockfree/detail/branch_hints.hpp>

#include "retri/doc_match_info_proxy.h"
#include "unise/matched_node.h"
#include "index/repository_manager.h"
#include "index/forward_index.h"
#include "retri/forward_iterator.h"
#include "util/util.h"
#include "gflags/gflags.h"

using std::vector;

namespace unise
{
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

DocMatchInfoProxy::DocMatchInfoProxy(const RepositoryManager & rm)
    : _repository_manager(rm)
{
    _matched_node_pool.reset(new MasfObjPool<MatchedNode>(32, 0.5, 100));
    _hits_list_pool.reset(new MasfObjPool<vector<doc_token_hit_t*> >(32, 0.5, 100));
    _hit_pool.reset(new MasfObjPool<doc_token_hit_t>(32, 0.5, 100));
}

DocMatchInfoProxy::~DocMatchInfoProxy()
{
    // for safe, in case user forget
    reset();
}

void DocMatchInfoProxy::init_for_search(
        const ForwardIterator* root_it,
        const GeneralSearchRequest* request,
        GeneralSearchResponse* response)
{
    _root_it = root_it;
    _response = response;
    _request = request;
}

// build the doc match info use the current doc which
// root_it is pointing to
bool DocMatchInfoProxy::build_doc_match_info(const ForwardIndex * forward_index)
{
    if (forward_index == NULL) {
        return false;
    }
    DocId docid = _root_it->get_cur_doc_hit().docid;
    GOOGLE_DCHECK_NE(ILLEGAL_DOCID, docid);

    reset_for_scoring();
    _root_it->get_hit_list(&_dochit_tokenids);

    // build the hit info
    while (!_dochit_tokenids.empty()) {
        TokenId token_id = _dochit_tokenids.top();
        _dochit_tokenids.pop();
        // get the size of the doc_token_hit_t for the current token
        size_t hits_list_size = forward_index->get_doc_token_hit_list_size(token_id);
        if (unlikely(hits_list_size == 0U)) {
            UWARNING("[\tlvl=SERIOUS\t] token_id:%llu don't exist in doc:%llu", token_id, docid);
        }
        // alloc object: doc_token_hit_t and hit_list and matched_node
        vector<doc_token_hit_t*> * list = _hits_list_pool->New(hits_list_size);
        for (size_t j = 0; j < hits_list_size; ++j) {
            list->at(j) = _hit_pool->New();
        }
        _matched_nodes.push_back(_matched_node_pool->New(token_id, list));
        // fill the result
        if (unlikely(! forward_index->get_doc_token_hit_list(token_id, *list))) {
            UWARNING("[\tlvl=SERIOUS\t] get_doc_token_hit_list for token_id:%llu fail", token_id);
        }
    }
    return true;
}

// note : when call this function, can't access hit info of one matched doc
void DocMatchInfoProxy::finalize_result(SearchResult * search_result)
{
    return;
}

void DocMatchInfoProxy::reset_for_scoring()
{
    while (!_matched_nodes.empty()) {
        MatchedNode *node = _matched_nodes.back();
        _matched_nodes.pop_back();

        vector<doc_token_hit_t*> *list = node->get_hits_p();
        while (likely(NULL != list) && (!list->empty())) {
            _hit_pool->Delete(list->back());
            list->pop_back();
        }
        _hits_list_pool->Delete(list);
        _matched_node_pool->Delete(node);
    }
}

void DocMatchInfoProxy::reset()
{
    reset_for_scoring();
    _matched_node_pool->Recycle();
    _hits_list_pool->Recycle();
    _hit_pool->Recycle();
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
