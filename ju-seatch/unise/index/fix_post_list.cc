// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/fix_post_list.h"
#include "gflags/gflags.h"
#include <boost/lockfree/detail/branch_hints.hpp>
#include <algorithm>

using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

// tcmalloc每个page 8K
// 实用tcmalloc的page free list来管理，避免内存碎片，提高申请速度
// DEFINE_int32(post_block_item_count, 8 * 1024 * 20 / sizeof (unise::post_item_t),
//            "consider tcmalloc page size");
DEFINE_int32(post_block_item_count, 128, "consider tcmalloc page size");

namespace unise {

FixPostList::~FixPostList() {
    size_t block_list_size = _block_list.size();
    for (size_t i = 0; i < block_list_size; ++i) {
        delete [] _block_list[i];
    }
}

FixPostList::FixPostList(TokenId token_id) :
    _token_id(token_id),
    _last_block(NULL),
    _last_block_free_cnt(0U),
    _size(0U) {}

FixPostList::FixPostList(TokenId token_id, std::vector<doc_hit_t> * array) :
    _token_id(token_id),
    _last_block(NULL),
    _last_block_free_cnt(0U),
    _size(0U) {
    size_t array_size = array->size();
    reserve(array_size);
    for (size_t i = 0; i < array_size; ++i) {
        add((*array)[i]);
    }
    // 清空array
    std::vector<doc_hit_t> empty_array;
    empty_array.swap(*array);
}

void FixPostList::reserve(size_t s) {
    size_t block_cnt = (s + FLAGS_post_block_item_count) / FLAGS_post_block_item_count;
    _block_list.reserve(block_cnt);
}

size_t FixPostList::size() const {
    return _size;
}

bool FixPostList::add(const doc_hit_t & doc_hit) {
    if (_last_block_free_cnt == 0U) {
        _last_block = new(std::nothrow) post_item_t[FLAGS_post_block_item_count];
        GOOGLE_CHECK(_last_block);
        post_item_t & item = _last_block[0];
        item.doc_hit.docid = doc_hit.docid;
        item.doc_hit.score = doc_hit.score;
        item.is_delete = 0;
        // item.reserved = 0;
        _block_list.push_back(_last_block);
        _last_block_free_cnt = FLAGS_post_block_item_count - 1U;
    } else {
        GOOGLE_DCHECK(_last_block);
        post_item_t & item = _last_block[FLAGS_post_block_item_count - _last_block_free_cnt];
        item.doc_hit.docid = doc_hit.docid;
        item.doc_hit.score = doc_hit.score;
        item.is_delete = 0;
        // item.reserved = 0;
        --_last_block_free_cnt;
    }
    ++_size;
    return true;
}

void FixPostList::remove(const doc_hit_t & doc_hit) {
    // 首先找到doc_hit所在的block
    if (_block_list.empty()) {
        return;
    }
    post_item_t p = {doc_hit, 0, 0};
    std::vector<post_item_t*>::iterator start = _block_list.begin();
    std::vector<post_item_t*>::iterator upper = std::upper_bound(
                start, _block_list.end(), &p, PostBlockCmp());
    if (upper == start) {
        return;
    }
    post_item_t * block = *(upper - 1);
    size_t count = FLAGS_post_block_item_count;
    if (block == _block_list[_block_list.size() - 1]) {
        count = FLAGS_post_block_item_count - _last_block_free_cnt;
    }
    post_item_t target = {doc_hit, 0, 0};
    post_item_t * hit = std::find(block, block + count, target);
    if (hit == block + count || hit->is_delete == 1) {
        return;
    }
    hit->is_delete = 1;
    --_size;
}

FixPostListIterator::FixPostListIterator(const DocHitList & list) :
    _block_list((static_cast<const FixPostList &>(list))._block_list),
    _last_block_size(FLAGS_post_block_item_count -
                (static_cast<const FixPostList &>(list))._last_block_free_cnt),
    _cur_block_idx(0U),
    _cur_block_size(0U),
    _cur_item_idx(0U),
    _size(list.size()) {
    _illegal_doc_hit.docid = ILLEGAL_DOCID;
    _illegal_doc_hit.score = ILLEGAL_SCORE;
    if (!_block_list.empty()) {
        _cur_block_size = _cur_block_idx == (_block_list.size() - 1) ?
            _last_block_size : FLAGS_post_block_item_count;
    }
    get_match();
}

void FixPostListIterator::get_match() {
    size_t block_list_size = _block_list.size();
    while (_cur_block_idx < block_list_size) {
        for (; _cur_item_idx < _cur_block_size; ++_cur_item_idx) {
            if ((_block_list[_cur_block_idx])[_cur_item_idx].is_delete == 0) {
                break;
            }
        }
        if (_cur_item_idx == _cur_block_size) {
            ++_cur_block_idx;
            _cur_item_idx = 0U;
            _cur_block_size = _cur_block_idx == (block_list_size - 1) ?
                _last_block_size : FLAGS_post_block_item_count;
        } else {
            break;
        }
    }
}

bool FixPostListIterator::done() const {
    return _cur_block_idx >= _block_list.size();
}

void FixPostListIterator::next() {
    if (likely(_cur_block_idx < _block_list.size())) {
        ++_cur_item_idx;
        get_match();
    }
}

const doc_hit_t & FixPostListIterator::get_current_value() const {
    if (unlikely(_cur_block_idx >= _block_list.size())) {
        return _illegal_doc_hit;
    } else {
        return (_block_list[_cur_block_idx])[_cur_item_idx].doc_hit;
    }
}

void FixPostListIterator::jump_to(const doc_hit_t & doc_hit) {
    // 首先找到doc_hit可能所在的block
    if (unlikely(_cur_block_idx >= _block_list.size())) {
        return;
    }
    post_item_t p = {doc_hit, 0, 0};
    std::vector<post_item_t*>::const_iterator start = _block_list.begin() + _cur_block_idx;
    std::vector<post_item_t*>::const_iterator upper = std::upper_bound(
                start, _block_list.end(), &p, PostBlockCmp());
    if (upper == start) {
        // warning:这里不能回溯
        return;
    }
    size_t target_block_idx = upper - 1 - _block_list.begin();
    _cur_item_idx = _cur_block_idx == target_block_idx ? _cur_item_idx : 0U;
    _cur_block_idx = target_block_idx;
    _cur_block_size = _cur_block_idx == _block_list.size() - 1 ?
        _last_block_size : FLAGS_post_block_item_count;
    const post_item_t * block = _block_list[_cur_block_idx];

    // 然后在block中跳到item的位置
    post_item_t target_hit = {doc_hit, 0, 0};
    const post_item_t * target_item = std::lower_bound(
                block + _cur_item_idx, block + _cur_block_size, target_hit);
    _cur_item_idx = target_item - block;
    get_match();
}


float FixPostListIterator::get_progress() const {
    if (_size == 0) {
        return 1.0;
    } else {
        return static_cast<float>(_cur_block_idx * FLAGS_post_block_item_count +
                    _cur_item_idx) / _size;
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
