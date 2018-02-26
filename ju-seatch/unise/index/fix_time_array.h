// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_FIX_TIME_ARRAY_H
#define  INDEX_FIX_TIME_ARRAY_H

#include <vector>
#include <string>
#include "index/doc_hit_list.h"

namespace unise
{
#pragma pack(push, 1)
/**
 * @breaf 固定大小的倒排链实现
 * @note 由于是在一个时刻，进行倒排链合并生成一个该类的对象，之后的时间内，
 *       该倒排只能做删除标记，不能有增加操作，所以名字起为FixTimeArray
**/
class FixTimeArray : public DocHitList
{
public:
    friend class FixTimeArrayIterator;

    explicit FixTimeArray(TokenId token_id)
        : _token_id(token_id)
    {
        // 删除map至少要有一个元素
        _delete_map.push_back(0);
    }

    FixTimeArray(TokenId token_id, std::vector<doc_hit_t> * array)
        : _token_id(token_id)
    {
        _array.swap(*array);
        // 为删除位设置大小
        _delete_map.resize((_array.size() >> 3) + 1);
    }

    virtual ~FixTimeArray() {}
    virtual bool add(const doc_hit_t & doc_hit)
    {
        _array.push_back(doc_hit);
        // 判断删除map是否需要扩容
        if ((_array.size() >> 3) + 1 > _delete_map.size()) {
            _delete_map.resize((_array.size() >> 3) + 1);
        }
        return true;
    }
    virtual void remove(const doc_hit_t & doc_hit);
    /**
     * @note 这个size不是精确的个数
     */
    virtual size_t size() const
    {
        return _array.size();
    }

    // must call this method to reserve enough space
    virtual void reserve(size_t s)
    {
        // note: only reserve
        _array.reserve(s);
        // note: resize the map
        _delete_map.resize((s >> 3) + 1);
    }
    virtual std::string get_name() const
    {
        return "FixTimeArray";
    }
    virtual TokenId get_token_id() const
    {
        return _token_id;
    }

private:
    std::vector<doc_hit_t> _array;
    std::vector<uint8_t> _delete_map;
    TokenId _token_id;

    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FixTimeArray);
};

class FixTimeArrayIterator : public DocHitListIterator
{
public:
    explicit FixTimeArrayIterator(const DocHitList & list);
    virtual ~FixTimeArrayIterator() {}
    virtual bool done() const;
    virtual void next();
    virtual const doc_hit_t & get_current_value() const;
    virtual void jump_to(const doc_hit_t & doc_hit);
    virtual float get_progress() const {
        // TODO:这个类不用了，最好删除了
        // 暂时不做实现
        return 1.0;
    }

private:
    void get_match();

    doc_hit_t _illegal_doc_hit;
    const std::vector<doc_hit_t> & _array;
    std::vector<doc_hit_t>::const_iterator _iterator;
    // 用一个字节标识8个doc的删除状态，置位标识被删除
    const std::vector<uint8_t> & _delete_map;
    std::vector<uint8_t>::const_iterator _delete_it; 
    uint8_t _cur_delete_mask;
    int32_t _count; ///< 字节内偏移
};

#pragma pack(pop)
}

#endif  // INDEX_FIX_TIME_ARRAY_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
