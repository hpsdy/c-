// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_RESULT_RETRIEVOR_H_
#define  RETRI_RESULT_RETRIEVOR_H_

#include <boost/scoped_ptr.hpp>
#include <vector>
#include "Configure.h"
#include "unise/search_context.h"
#include "util/masf_mempool.h"
#include "retri/matched_doc_internal.h"
#include "retri/doc_match_info_proxy.h"
#include "index/index.h"

namespace unise {
class GeneralSearchRequest;
class GeneralSearchResponse;
class QueryNode;
class RepositoryManager;
class ForwardIterator;
class MatchedDoc;
class ResultManager;

class ResultRetrievor {
public:
    explicit ResultRetrievor(const RepositoryManager & repository_manager);
    ~ResultRetrievor();
    bool init(const comcfg::ConfigUnit& conf);

    /**
     * @brief 针对request做检索，将结果放到response中
     * @param [in] : request
     * @param [out] : response
     * @return none
     * @retval none
     * @see 
     * @note
     */
    void retrieve(const GeneralSearchRequest & request, GeneralSearchResponse * response);

private:
    /**
     * @brief 获取迭代树
     * @note 如果迭代树内部包含非法子树，那么非法子树被empty_node节点代替
     *       请注意内部WARNING LOG
     */
    ForwardIterator * construct_retrieve_tree(const QueryNode & query_node);

    /**
     * @brief 根据已有迭代树，获取具备范围约束的新的迭代树
     *        返回的it为新的迭代树，root_iterator成为新迭代树的孩子
     */
    ForwardIterator * construct_range_restriction(
            const GeneralSearchRequest& request,
            ForwardIterator * root_iterator);

    /**
     * @brief 一次检索结束，资源回收
     */
    void finish_retrieve();

    uint64_t get_estimated_num(
                uint64_t tree_num,
                float progress,
                int64_t retrieve_num,
                int64_t recall_docs);

private:
    // 当前EU的存储管理器
    const RepositoryManager & _repository_manager;
    // 存储每次检索申请的迭代器
    std::vector<ForwardIterator*> _forward_iterators;
    // doc命中详细信息代理
    DocMatchInfoProxy _doc_match_info_proxy;
    // MatchedDoc资源池
    boost::scoped_ptr<MasfObjPool<MatchedDocInternal> > _matched_doc_pool;
    // 结果管理器
    boost::scoped_ptr<ResultManager> _result_manager;
    // 生成检索上下文的工厂
    boost::scoped_ptr<SearchContextFactory> _search_context_factory;
    // 一次检索的检索上下文句柄，可供不同插件传递数据
    // 需要由工厂析构，因此不使用scoped_ptr
    SearchContext * _search_context;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ResultRetrievor);
};

}

#endif  // RETRI_RESULT_RETRIEVOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
