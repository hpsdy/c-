// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_DOC_MATCH_INFO_PROXY_H_
#define  RETRI_DOC_MATCH_INFO_PROXY_H_

#include <stack>
#include <vector>

#include <boost/scoped_ptr.hpp>
#include "unise/base.h"
#include "unise/general_servlet.pb.h"
#include "util/masf_mempool.h"

namespace unise
{
class MatchedNode;
class RepositoryManager;
class ForwardIterator;
class ForwardIndex;

class DocMatchInfoProxy
{
public:
    explicit DocMatchInfoProxy(const RepositoryManager & repository_manager);
    ~DocMatchInfoProxy();

    void init_for_search(const ForwardIterator* root_it,
            const GeneralSearchRequest* request,
            GeneralSearchResponse* response);

    bool build_doc_match_info(const ForwardIndex * forward_index);
    void finalize_result(SearchResult * search_result);

    // call reset to release the resources
    void reset();

    const std::vector<MatchedNode*>& get_matched_nodes() const {
        return _matched_nodes;
    }
private:
    void reset_for_scoring();

private:
    const RepositoryManager & _repository_manager;
    const GeneralSearchRequest * _request;
    const ForwardIterator * _root_it;
    GeneralSearchResponse * _response;

    // note:the matched_node_pool in charge of the new and delete on MatchedNode
    boost::scoped_ptr<MasfObjPool<MatchedNode> > _matched_node_pool;
    std::vector<MatchedNode*>   _matched_nodes; ///< 命中的节点指针

    // note:the hits_list_pool in charge of new and delete on vector<doc_token_hit_t*>
    boost::scoped_ptr<MasfObjPool<std::vector<doc_token_hit_t*> > > _hits_list_pool;
    // note:the hit_pool in charge of new and delete on doc_token_hit_t
    boost::scoped_ptr<MasfObjPool<doc_token_hit_t> > _hit_pool;

    std::stack<TokenId>     _dochit_tokenids;   ///< 一个DOC里命中的TOKENID列表
};

}

#endif  // RETRI_DOC_MATCH_INFO_PROXY_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
