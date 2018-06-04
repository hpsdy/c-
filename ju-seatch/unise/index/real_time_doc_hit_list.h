// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_REAL_TIME_DOC_HIT_LIST_H
#define  INDEX_REAL_TIME_DOC_HIT_LIST_H

#include <string>
#include "unise/skiplist.h"
#include "index/doc_hit_list.h"

namespace unise
{
#pragma pack(push, 1)
/**
 * @breaf 实时倒排链表的实现
 * @note 采用SkipList作为底层实现，以获取较好的随机插入性能和查询性能
**/
class RealTimeDocHitList : public DocHitList
{
public:
    friend class RealTimeDocHitListIterator;
    explicit RealTimeDocHitList(TokenId token_id)
        : _token_id(token_id) {}
    virtual ~RealTimeDocHitList() {}
    virtual bool add(const doc_hit_t & doc_hit);
    virtual void remove(const doc_hit_t & doc_hit);
    virtual size_t size() const;
    virtual std::string get_name() const
    {
        return "RealTimeDocHitList";
    }
    virtual TokenId get_token_id() const
    {
        return _token_id;
    }

private:
    SkipList<doc_hit_t> _list; ///< 采用SkipList作为底层实现
    TokenId _token_id;

    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RealTimeDocHitList);
};

class RealTimeDocHitListIterator : public DocHitListIterator
{
public:
    explicit RealTimeDocHitListIterator(const DocHitList & list);
    virtual ~RealTimeDocHitListIterator() {}
    virtual bool done() const;
    virtual void next();
    virtual const doc_hit_t & get_current_value() const;
    virtual void jump_to(const doc_hit_t & doc_hit);
    virtual float get_progress() const;

private:
    doc_hit_t _illegal_doc_hit;
    const SkipList<doc_hit_t> & _list;
    _SkipListConstIterator<doc_hit_t> _iterator;
    size_t _estimated_idx;
};

#pragma pack(pop)
}

#endif  // INDEX_REAL_TIME_DOC_HIT_LIST_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
