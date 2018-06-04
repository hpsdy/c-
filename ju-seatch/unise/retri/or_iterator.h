// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_OR_ITERATOR_H_
#define  RETRI_OR_ITERATOR_H_

#include <vector>
#include <queue>
#include "retri/forward_iterator.h"
#include "unise/base.h"

namespace unise {

/**
 * @brief return true if a<b，priority_queue中b位于top
 * @note pair的first代表数组的下标
 */
struct ForwardItComp {
    bool operator()(const std::pair<size_t, doc_hit_t>& a,
            const std::pair<size_t, doc_hit_t>& b) {
        if (a.second == b.second) {
            return b.first < a.first;
        } else {
            return b.second < a.second;
        }
    }
};

/**
 * @brief Or迭代器，下面可以挂1+个节点，每次Or会给出当前所有
 *        子节点中最大score的结果
 * @see 相关函数接口说明，请见ForwardIterator的定义
 */
class OrIterator : public ForwardIterator {
public:
    /**
     * @brief 根据迭代器指针，构造一个Or迭代器
     * @param [in] : 迭代器指针列表
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note
     */
    explicit OrIterator(const std::vector<ForwardIterator *> & it_list);

    virtual ~OrIterator() {}
    virtual void next();
    virtual bool done() const;
    virtual void jump_to(DocId docid, int32_t score);
    virtual const doc_hit_t & get_cur_doc_hit() const;
    virtual bool post_retrieval_check_internal();
    virtual void get_hit_list(std::stack<TokenId> * hits) const;
    virtual float get_progress() const;
    virtual uint64_t get_estimated_num() const;

private:
    /**
     * @brief 调整孩子，使至少一个孩子指向比当前Or小的值
     * @param [in] : none
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note
     */
    void get_match();

private:
    // or迭代器的所有孩子
    std::vector<ForwardIterator *> _it_list;
    // or迭代器当前指向的节点
    doc_hit_t _cur_doc_hit;
    // or迭代器的所有孩子的当前节点构成的大顶堆
    std::priority_queue <std::pair<size_t, doc_hit_t>,
                         std::vector< std::pair<size_t, doc_hit_t> >,
                         ForwardItComp > _heap;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(OrIterator);
};

}

#endif  // RETRI_OR_ITERATOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
