// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_RESULT_MANAGER_H_
#define  RETRI_RESULT_MANAGER_H_

#include <set>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <bsl/map.h>
#include "util/masf_mempool.h"
#include "retri/matched_doc_internal.h"
#include "retri/result_filter_handler.h"
#include "retri/result_cluster_handler.h"
#include "retri/scorer_handler.h"
#include "unise/result_filler.h"
#include "unise/comparator.h"
#include "unise/base.h"


namespace comcfg
{
class ConfigUnit;
}

namespace unise
{
class MatchedDoc;
class GeneralSearchRequest;
class GeneralSearchResponse;
class RepositoryManager;
class SearchContext;


// TODO(wangguangyuan) : 夜深人静时，再测试一个具体数据
// #pragma pack(push, 1)
/**
 * @brief hash节点的实际内容，由一个vector来分配
 *        vector初始化一次，构造足够的数据
 * @note 使用字节对齐，约节省300M内存
 *       但是粗略的实验发现，不pack的QPS比pack略高10左右。
 */
struct hash_node_t {
    size_t heap_index;     ///< 堆的下标，正向指针
                           ///< 堆调整的时候，需要维护该结构
    uint8_t stamp;         ///< 循环使用，避免hash的clear操作
};

/**
 * @brief heap节点的实际内容，由vector来分配
 *        vector初始化一次，构造足够的数据
 *        需要保证hash不会再hash
 */
struct heap_node_t {
    MatchedDoc * doc;         ///< 数据域
    hash_node_t * hash_node;  ///< 反向指针，目的减少一次hash
};
// #pragma pack(pop)

class ResultManager {
public:
    ResultManager(const RepositoryManager & repository_manager,
                MasfObjPool<MatchedDocInternal>* result_pool);
    ~ResultManager();

    bool init(const comcfg::ConfigUnit& conf);

    void init_for_search(const GeneralSearchRequest* request,
                GeneralSearchResponse* response,
                SearchContext * search_context);

    bool maybe_add_candidate_result(MatchedDoc* result, int* replace_num, result_status_t* result_status);

    // free up all the memory
    void finish();
private:
    // This function can reject a result without actually needing to
    // build the DocTokenHit info,
    // note: can't access the score and the MatchedNode
    bool early_filter(MatchedDoc* result, result_status_t* result_status);

    // This function be called just before accept the result
    // note: can access the score and the MatchedNode
    bool later_filter(MatchedDoc* result, result_status_t* result_status);

    // This function be called when finished retrieval
    // note: can't access the MatchedNode
    bool final_filter(MatchedDoc* result, result_status_t* result_status);

    bool add_candidate_result(MatchedDoc* result);

    void remove_candidate_result(MatchedDoc* result);

private:
    bool init_result_filler(const comcfg::ConfigUnit& conf);
    bool init_comparator(const comcfg::ConfigUnit& conf);

    /**
     * @brief 删除p位置的节点
     *        p指向的节点是无用节点，从p节点开始，向下调整堆
     * @note 堆的大小会减1
     */
    inline void down_adjust_heap(size_t p) {
        // 首先把堆的最后一个元素放到哨兵位
        heap_node_t * tmp = _accepted_results_heap[_heap_size];
        // 减小堆的大小
        --_heap_size;
        // 然后从上至下找到tmp应该的位置
        size_t i = p << 1; ///< 左孩子
        while (i <= _heap_size) {
            size_t j = i < _heap_size ? i + 1 : i; ///< 右孩子
            // up为最小的孩子
            size_t up = (*_cur_comparator)(_accepted_results_heap[i]->doc,
                        _accepted_results_heap[j]->doc) ? j : i;
            // 如果最小的孩子比tmp质量高，那么tmp可以放在p处
            if ((*_cur_comparator)(_accepted_results_heap[up]->doc, tmp->doc)) {
                break;
            }
            // 否则，最小的孩子上升
            _accepted_results_heap[p] = _accepted_results_heap[up];
            // 调整堆的同时，维护hash的数据
            _accepted_results_heap[p]->hash_node->heap_index = p;
            p = up;
            i = p << 1;
        }
        // 将tmp放到位置p
        _accepted_results_heap[p] = tmp;
        tmp->hash_node->heap_index = p;
    }

private:
    const RepositoryManager & _repository_manager;
    MasfObjPool<MatchedDocInternal>* _result_pool;
    const GeneralSearchRequest* _request;
    GeneralSearchResponse* _response;
    size_t _num_results_requested;
    size_t _result_manager_capacity;

    typedef bsl::hashmap<uint64_t, hash_node_t*> HeapHash;
    // 支持随机查找MatchedDoc*在堆中的下标
    boost::scoped_ptr<HeapHash> _heap_hash; 
    uint8_t _hash_clear_count;              ///< 用来定期清空hash
    uint8_t _hash_stamp;                    ///< 用来区分不同的检索
    std::vector<hash_node_t> _hash_nodes;   ///< 为hash分配节点使用
    size_t _hash_nodes_index;               ///< 游标

    // 调整堆时，需要操作元素，所以自己实现
    heap_node_t ** _accepted_results_heap;  ///< 小顶堆，最坏的元素在头部
                                            ///< 头部从下标1开始
    size_t _heap_size;                      ///< 堆的当前大小
    std::vector<heap_node_t> _heap_nodes;   ///< 为heap分配节点使用
    size_t _heap_nodes_index;               ///< 游标

    boost::scoped_ptr<ResultFilterHandler> _result_filter_handler;
    boost::scoped_ptr<ResultClusterHandler> _result_cluster_handler;
    boost::scoped_ptr<ScorerHandler> _scorer_handler;
    std::set<MatchedDoc*> _clustered_results;

    typedef std::map<uint64_t, boost::shared_ptr<ResultFiller> > UniseFillersMap;
    
    UniseFillersMap _fillers_map;            ///< ResultFiller插件管理容器
    ResultFiller * _cur_result_filler;       ///< 当前search过程的result_filter

    typedef std::map<uint64_t, boost::shared_ptr<Comparator> > UniseComparatorMap;
    UniseComparatorMap _comparators_map;     ///< Comparator插件管理容器
    Comparator * _cur_comparator;            ///< 当前search过程的comparator

    // 每次检索时的检索上下文
    SearchContext * _search_context;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ResultManager);
};

}

#endif  // RETRI_RESULT_MANAGER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
