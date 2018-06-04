// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#include "retri/leaf_iterator.h"
#include <boost/lockfree/detail/branch_hints.hpp>
#include "index/doc_hit_list.h"
#include "index/real_time_doc_hit_list.h"
#include "index/fix_time_array.h"
#include "index/fix_post_list.h"

using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

namespace unise
{
LeafIterator::LeafIterator(const DocHitList & list)
    : ForwardIterator(), _list(list)
{
    if (list.get_name() == "RealTimeDocHitList") {
        _iterator = new RealTimeDocHitListIterator(list);
    } else if (list.get_name() == "FixTimeArray") {
        _iterator = new FixTimeArrayIterator(list);
    } else if (list.get_name() == "FixPostList") {
        _iterator = new FixPostListIterator(list);
    } else {
        GOOGLE_CHECK(false) << "unknow DocHitList type";
    }
}

LeafIterator::~LeafIterator()
{
    delete _iterator;
}

void LeafIterator::next()
{
    _iterator->next();
}

bool LeafIterator::done() const
{
    if (unlikely(_iterator->done())) {
        return true;
    } else {
        return false;
    }
}

void LeafIterator::jump_to(DocId docid, int32_t score)
{
    // TODO(wangguangyuan) : 这里的写操作是否可以优化掉
    doc_hit_t doc_hit;
    doc_hit.docid = docid;
    doc_hit.score = score;
    if (unlikely(!(get_cur_doc_hit() < doc_hit))) {
        return;
    }
    _iterator->jump_to(doc_hit);
}

const doc_hit_t & LeafIterator::get_cur_doc_hit() const
{
    return _iterator->get_current_value();
}

void LeafIterator::get_hit_list(std::stack<TokenId> * hits) const
{
    GOOGLE_DCHECK(hits);
    hits->push(_list.get_token_id());
}

uint64_t LeafIterator::get_estimated_num() const {
    UDEBUG("LeafIterator[%p] token[%llu] estimated_num[%u]",
                this, _list.get_token_id(), _list.size());
    return _list.size();
}

float LeafIterator::get_progress() const {
    UDEBUG("LeafIterator[%p] token[%llu] progress[%f]",
                this, _list.get_token_id(), _iterator->get_progress());
    return _iterator->get_progress();
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
