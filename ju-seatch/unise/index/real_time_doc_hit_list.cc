// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/real_time_doc_hit_list.h"
#include <boost/lockfree/detail/branch_hints.hpp>
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

namespace unise
{

bool RealTimeDocHitList::add(const doc_hit_t & doc_hit)
{
    return _list.insert(doc_hit) != _list.end();
}

size_t RealTimeDocHitList::size() const
{
    return _list.size();
}

void RealTimeDocHitList::remove(const doc_hit_t & doc_hit)
{
    if (_list.erase(doc_hit) != 1) {
        UDEBUG("Delete skiplist fail for docid:%llu score:%d",
                doc_hit.docid,
                doc_hit.score);
    }
}

RealTimeDocHitListIterator::RealTimeDocHitListIterator(const DocHitList & list) :
    _list((dynamic_cast<const RealTimeDocHitList &>(list))._list),
    _estimated_idx(0U) {
    _iterator = _list.begin();
    _illegal_doc_hit.docid = ILLEGAL_DOCID;
    _illegal_doc_hit.score = ILLEGAL_SCORE;
}

bool RealTimeDocHitListIterator::done() const
{
    return _iterator == _list.end();
}

void RealTimeDocHitListIterator::next()
{
    if (likely(_iterator != _list.end())) {
        _iterator++;
        ++_estimated_idx;
    } else {
        _estimated_idx = _list.size();
    }
}

const doc_hit_t & RealTimeDocHitListIterator::get_current_value() const
{
    if (unlikely(_iterator == _list.end())) {
        return _illegal_doc_hit;
    } else {
        return *_iterator;
    }
}

void RealTimeDocHitListIterator::jump_to(const doc_hit_t & doc_hit)
{
    _iterator = _list.lower_bound(doc_hit);
    // note: 这里无法获取准确的下标
    // 因此，只要有skip，那么估算的结果一定会非常不准确
    ++_estimated_idx;
}


float RealTimeDocHitListIterator::get_progress() const {
    if (_estimated_idx >= _list.size() || _list.size() == 0U) {
        return 1.0;
    } else {
        return static_cast<float>(_estimated_idx) / _list.size();
    }
}




}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
