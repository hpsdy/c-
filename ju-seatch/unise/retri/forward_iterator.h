// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_FORWARD_ITERATOR_H_
#define  RETRI_FORWARD_ITERATOR_H_

#include <stdint.h>
#include <stack>
#include <vector>
#include "unise/base.h"

namespace unise {

class ForwardIterator {
public:
    ForwardIterator() : _last_post_check_docid(ILLEGAL_DOCID) {}
    virtual ~ForwardIterator() {}

    /**
     * @brief 当前迭代器往后走一步
     * @param [in] : none
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note 需要判断是否有合法的取值
     */
    virtual void next() = 0;

    /**
     * @brief 当前迭代器是否已经走到头了
     * @param [in] : none
     * @param [out] : none
     * @return bool
     * @retval true代表已经到终点，无合法取值
     *         false代表未到终点，有合法取值
     * @see 
     * @note
     */
    virtual bool done() const = 0;

    /**
     * @brief 使迭代器快速跳转到docid处，该doc的分数用score指定
     * @param [in] : docid，指定跳转的唯一位置
     * @param [in] : score,跳转位置的分数
     * @param [out] : none
     * @return none
     * @retval none
     * @see 
     * @note 不同实现，效率不同
     */
    virtual void jump_to(DocId docid, int32_t score) = 0;

    /**
     * @brief 获取当前命中doc的基本信息
     * @param [in] : none
     * @param [out] : none
     * @return const doc_hit_t &
     * @retval 常引用，需要判断是否为非法取值
     * @see 
     * @note
     */
    virtual const doc_hit_t & get_cur_doc_hit() const = 0;

    /**
     * @brief 查询迭代是否统一意见，若统一，当前迭代器的结果可用
     * @param [in] : none
     * @param [out] : none
     * @return bool
     * @retval none
     * @see 
     * @note 实现上采用了记录优化
     */
    bool post_retrieval_check() {
        if (_last_post_check_docid == get_cur_doc_hit().docid) {
            return _last_post_check_status;
        }
        _last_post_check_status = post_retrieval_check_internal();
        _last_post_check_docid = get_cur_doc_hit().docid;
        return _last_post_check_status;
    }

    /**
     * @brief 抽象出一个函数，使得派生类只处理检查逻辑
     * @param [in] : none
     * @param [out] : none
     * @return bool
     * @retval 默认都返回true
     * @see 
     * @note
     */
    virtual bool post_retrieval_check_internal() { return true; }

    /**
     * @brief 获取当前命中doc的所有的TokenId
     * @param [in] : none
     * @param [out] : hits
     * @return none
     * @retval none
     * @see 
     * @note
     */
    virtual void get_hit_list(std::stack<TokenId> * hits) const {
        GOOGLE_DCHECK(hits);
        return;
    }

    virtual float get_progress() const = 0;
    virtual uint64_t get_estimated_num() const = 0;

private:
    DocId _last_post_check_docid;    ///< 上一次申请检查的docid
    bool _last_post_check_status;    ///< 上一次申请检查的结果
};

}

#endif  // RETRI_FORWARD_ITERATOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
