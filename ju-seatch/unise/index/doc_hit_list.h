// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_DOC_HIT_LIST_H
#define  INDEX_DOC_HIT_LIST_H

#include <string>
#include "unise/base.h"

namespace unise
{
class DocHitListIterator;

/**
 * @breaf 一个token的倒排链的接口类。定义了一下主要方法：
 *   1. 往倒排链中插入一个DocHit
 *   2. 从倒排链中删除一个DocHit
 *   3. 获取倒排链的大概长度
 *   4. 获取倒排链的实现类名
 *   5. 获取倒排链所属token的tokenid
 *   6. 为倒排链保留多少空间
 * @note 非多线程安全
**/
class DocHitList
{
public:
    friend class DocHitListIterator;
    DocHitList() {}
    virtual ~DocHitList() {}
    virtual bool add(const doc_hit_t & doc_hit) = 0;
    virtual void remove(const doc_hit_t & doc_hit) = 0;
    virtual size_t size() const = 0;
    virtual std::string get_name() const {
        return "DocHitList";
    }
    virtual TokenId get_token_id() const = 0;
    virtual void reserve(size_t s) {}
};

/**
 * @breaf 一个token的倒排链的迭代器接口类，定义了倒排的遍历方法
 *   1. 查询当前迭代器是否已经指向倒排链的末尾
 *   2. 迭代器往前走一步
 *   3. 迭代器快速跳转到指定位置
 *   4. 查询当前迭代器所指位置的元素
 * @note 多线程安全
 *
**/
class DocHitListIterator
{
public:
    DocHitListIterator() {}
    virtual ~DocHitListIterator() {}
    virtual bool init(const DocHitList & list) {
        UDEBUG("init the DocHitListIterator with list:%s",
                list.get_name().c_str());
        return true;
    }

    /**
     * @breaf 当前迭代器是否已经指向end
     *
     * @param [in] : none
     * @param [out] : none
     * @return bool
     * @retval true 则指向end；
     * @see
     * @note 
    **/
    virtual bool done() const = 0;

    /**
     * @breaf 当前迭代器往前走一步
     *
     * @param [in] : none
     * @param [out] : none
     * @return none
     * @retval none
     * @see
     * @note 如果当前迭代器已经指向end，那么什么也不做
    **/
    virtual void next() = 0;

    /**
     * @breaf 获取当前迭代器所指位置的元素
     *
     * @param [in] : none
     * @param [out] : none
     * @return const DocHit&
     * @retval 当前迭代器所指位置元素
     * @see unise/base.h中对非法Docid和非法Score的定义
     * @note 如果当前迭代器指向end，那么返回的是一个非法DocHit
    **/
    virtual const doc_hit_t & get_current_value() const = 0;

    /**
     * @breaf 当前迭代器快速跳转到所指位置，如果不存在指定位置元素
     *        跳到大于指定元素的最小的位置
     *        假设倒排链后面的元素比前面的元素大
     *
     * @param [in] : 目标DocHit
     * @param [out] : none
     * @return none
     * @retval none
     * @see
     * @note 如果当前迭代器已经指向end，那么什么也不做
     *       提供默认实现，如果派生类不具备jump功能，可不实现该函数
    **/
    virtual void jump_to(const doc_hit_t & doc_hit) {
        while (!done()) {
            if (doc_hit < get_current_value()) {
                next();
            } else {
                break;
            }
        }
    }

    virtual float get_progress() const = 0;
};

}

#endif  // INDEX_DOC_HIT_LIST_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
