// Copyright 2017 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  BAIDU_MMS_UNISE_RETRI_BRANCH_ITERATOR_H
#define  BAIDU_MMS_UNISE_RETRI_BRANCH_ITERATOR_H

#include <vector>
#include <queue>
#include "retri/forward_iterator.h"
#include "unise/base.h"
#include "bsl/containers/hash/bsl_hashset.h"

namespace unise {

struct WeightRoundPair {
    WeightRoundPair(uint32_t w, uint32_t r) : weight(w), round(r) {}
    uint32_t weight;
    uint32_t round;
};

/**
 * @brief return true if a<b，priority_queue中b位于top
 * @note pair的first代表数组的下标
 *       pair的second代表一个权重和轮次二元组
 */
struct ForwardItBranchComp {
    bool operator()(const std::pair<size_t, WeightRoundPair> & a,
                    const std::pair<size_t, WeightRoundPair> & b) {
        // 首先判断轮次，保证优先队列中轮次低的先被pop出来
        // 然后判断权重，保证优先队列中权重高的先被pop出来
        if (a.second.round == b.second.round) {
            if (a.second.weight == b.second.weight) {
                // 无所谓
                return a.first < b.first;
            } else {
                // 如果a的权重小于b，应该让b作为top
                return a.second.weight < b.second.weight;
            }
        }  else {
            // 如果a的轮次小于b，应该让a作为top
            return b.second.round < a.second.round;
        }
    }
};

/**
 * @brief Branch迭代器，下面可以挂1+个节点，每次会按照子节点的weight来依次出结果
 * @warning: branch节点只能位于查询树顶层
 * @see 相关函数接口说明，请见ForwardIterator的定义
 */
class BranchIterator : public ForwardIterator {
public:
    /**
     * @brief 根据迭代器指针，构造一个branch迭代器
     * @param [in] : 子迭代器指针列表
     * @param [in] : 子迭代器权重
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note
     */
    BranchIterator(const std::vector<ForwardIterator *> & it_list,
                   const std::vector<uint32_t> & weight_list);

    virtual ~BranchIterator() {}

    /**
     * @brief 迭代器往后走一步，指向当前可用的节点
     * @param [in] : none
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note 注意判断是否done，为done时当前节点为ILLEGAL_DOC_HIT
     */
    virtual void next();

    /**
     * @brief 判断迭代器是否已经迭代完毕
     * @param [in] : none
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note 为done时当前节点为ILLEGAL_DOC_HIT
     */
    virtual bool done() const;

    /**
     * @brief 迭代器直接跳转到输入参数的下一个dochit，注意判断是否为done
     * @param [in] : DocId, 迭代器跳到大于等于docid的位置
     * @param [in] : int32_t, 迭代器跳到小于等于score的位置
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note 一般branch迭代器不会被调用jump_to，除非一次检索指定从
     *       一个位置开始检索。当调用时，其所有子树都往下跳到对应
     *       位置，并且重新开始计算weight和轮次
     */
    virtual void jump_to(DocId docid, int32_t score);

    /**
     * @brief 返回当前迭代器指向的doc hit
     * @param [in] : none
     * @param [out] : none
     * @return const doc_hit_t &
     * @retval const doc_hit_t &
     * @see 
     * @note 如果迭代器结束，那么返回ILLEGAL_DOC_HIT
     */
    virtual const doc_hit_t & get_cur_doc_hit() const;

    /**
     * @brief branch迭代器跟上层迭代器之间进行二次校验接口
     * @param [in] : none
     * @param [out] : none
     * @return bool
     * @retval true时代表确认当前节点是可接受的；否则不可接受
     * @see ForwardIterator的定义
     * @note 
     */
    virtual bool post_retrieval_check_internal();

    /**
     * @brief branch迭代器跟上层迭代器之间进行二次校验接口
     * @param [in] : none
     * @param [out] : none
     * @return bool
     * @retval true时代表确认当前节点是可接受的；否则不可接受
     * @see ForwardIterator的定义
     * @note 
     */
    virtual void get_hit_list(std::stack<TokenId> * hits) const;

    /**
     * @brief branch迭代器返回当前的迭代进度
     * @param [in] : none
     * @param [out] : none
     * @return float
     * @retval 0~1之间的浮点数，1代表迭代完毕
     * @see ForwardIterator的定义
     * @note 
     */
    virtual float get_progress() const;

    /**
     * @brief 估算还有多少结果没有迭代完毕
     * @param [in] : none
     * @param [out] : none
     * @return uint64_t
     * @retval 估算还剩余多少doc_hit
     * @see ForwardIterator的定义
     * @note branch迭代器与or迭代器类似，将所有子树的估算结果求和
     */
    virtual uint64_t get_estimated_num() const;

private:
    /**
     * @brief 调整孩子，使至少一个孩子指向比当前doc_hit小的值
     * @param [in] : none
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note
     */
    void get_match();

private:
    // branch迭代器的所有孩子
    std::vector<ForwardIterator *> _it_list;
    // branch迭代器的孩子的权重
    std::vector<uint32_t> _weight_list;
    // branch迭代器当前指向的节点
    doc_hit_t _cur_doc_hit;
    // or迭代器的所有孩子的权重作为大顶堆
    // note: <_it_list's index, weight>
    // TODO(wangguangyuan) : 其实用一个数组能更朴素的实现，但是为了保证灵活性
    //                       这里采用优先队列的方式，后续可以加入动态计算
    //                       term-doc相关性权重的因素
    std::priority_queue <std::pair<size_t, WeightRoundPair>,
                         std::vector< std::pair<size_t, WeightRoundPair> >,
                         ForwardItBranchComp > _heap;
    typedef bsl::hashset<DocId>  SelectedSet;
    // 存储已经被挑选过的doc，用来去重，避免迭代器给出相同结果
    SelectedSet _selected_set;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(BranchIterator);
};

}

#endif  // BAIDU_MMS_UNISE_RETRI_BRANCH_ITERATOR_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
