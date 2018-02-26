// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/fix_time_array.h"
#include <boost/lockfree/detail/branch_hints.hpp>
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

namespace unise
{
void FixTimeArray::remove(const doc_hit_t & doc_hit)
{
    std::vector<doc_hit_t>::iterator it = find(_array.begin(),
                                               _array.end(),
                                               doc_hit);
    if (unlikely(it == _array.end())) {
        UDEBUG("remove FixTimeArray fail for docid:%llu score:%d",
                doc_hit.docid,
                doc_hit.score);
        return;
    }
    // 设置删除位
    size_t distance = it - _array.begin();
    size_t delete_idx = distance >> 3;
    uint8_t delete_mask = 1 << (distance % 8U);
    _delete_map.at(delete_idx) = _delete_map.at(delete_idx) | delete_mask;
}

FixTimeArrayIterator::FixTimeArrayIterator(const DocHitList & list)
    : _array((dynamic_cast<const FixTimeArray &>(list))._array),
      _iterator((dynamic_cast<const FixTimeArray &>(list))._array.begin()),
      _delete_map((dynamic_cast<const FixTimeArray &>(list))._delete_map),
      _delete_it((dynamic_cast<const FixTimeArray &>(list))._delete_map.begin()),
      _cur_delete_mask(*_delete_it),
      _count(0)
{
    _illegal_doc_hit.docid = ILLEGAL_DOCID;
    _illegal_doc_hit.score = ILLEGAL_SCORE;
    get_match();
}

void FixTimeArrayIterator::get_match()
{
    while (_iterator != _array.end()) {
        if (likely(0 == (_cur_delete_mask & 0x01))) {
            // 当前节点没有被删除
            break;
        }
        ++_iterator;
        ++_count;
        if (unlikely(_count > 7)) {
            _count = 0;
            _delete_it++;
            _cur_delete_mask = *_delete_it;
        } else {
            _cur_delete_mask = _cur_delete_mask >> 1;
        }
    }
}

bool FixTimeArrayIterator::done() const
{
    if (unlikely(_iterator == _array.end())) {
        return true;
    } else {
        return false;
    }
}

void FixTimeArrayIterator::next()
{
    if (likely(_iterator != _array.end())) {
        ++_iterator;
        ++_count;
        if (unlikely(_count > 7)) {
            _count = 0;
            _delete_it++;
            _cur_delete_mask = *_delete_it;
        } else {
            _cur_delete_mask = _cur_delete_mask >> 1;
        }
        get_match();
    }
}

const doc_hit_t & FixTimeArrayIterator::get_current_value() const
{
    if (unlikely(done())) {
        return _illegal_doc_hit;
    } else {
        return *_iterator;
    }
}

void FixTimeArrayIterator::jump_to(const doc_hit_t & doc_hit)
{
    _iterator = lower_bound(
                _iterator,
                _array.end(),
                doc_hit);
    if (likely(_iterator != _array.end())) {
        size_t distance = _iterator - _array.begin();
        _delete_it = _delete_map.begin() + (distance >> 3);
        // 设置删除位的字节内偏移以及删除掩码
        _count = distance % 8;
        _cur_delete_mask = *_delete_it >> _count;
        get_match();
    }
}

}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
