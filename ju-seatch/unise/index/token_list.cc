// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/token_list.h"
#include <vector>
#include "gflags/gflags.h"
#include "unise/base.h"
#include "unise/singleton.h"
#include "unise/delay_callback.h"
#include "util/util.h"
#include "index/fix_time_array.h"
#include "index/fix_post_list.h"
#include "index/real_time_doc_hit_list.h"

DEFINE_int32(buffer_merge_threshold, 10240, "the threshold for buffer list to merge");
DEFINE_int32(inverted_list_delete_delay, 15000, "how many ms to delay");

namespace unise {

/**
 * @brief 采用全局函数来执行延迟回调，比较安全
 */
void release_delay(DocHitList * a, DocHitList * b) {
    UDEBUG("release [%p] [%p]", a, b);
    delete a;
    delete b;
}

TokenList::TokenList(TokenId token_id, DocHitList * fix_list) :
        _token_id(token_id),
        _fix_list(down_cast<FixPostList*>(fix_list)) {
    _buffer_list = new RealTimeDocHitList(_token_id);
    _buffer_merge_threshold = FLAGS_buffer_merge_threshold;
}

TokenList::TokenList(TokenId token_id) : _token_id(token_id) {
    _buffer_list = new RealTimeDocHitList(_token_id);
    _fix_list = new FixPostList(_token_id);
    _buffer_merge_threshold = FLAGS_buffer_merge_threshold;
}

TokenList::~TokenList() {
    if (_buffer_list != NULL) {
        delete _buffer_list;
        _buffer_list = NULL;
    }
    if (_fix_list != NULL) {
        delete _fix_list;
        _fix_list = NULL;
    }
}

void TokenList::push_to_list(const doc_hit_t & doc_hit, DocHitList * list) {
    list->add(doc_hit);
}

void TokenList::merge() {
    // note : use the current thread to merge merge_index
    UTRACE("start merging thread for tokenid:%llu", _token_id);
    // reserve the vector
    DocHitList * new_fix_list = new FixPostList(_token_id);
    new_fix_list->reserve(_fix_list->size() + _buffer_list->size());
    RealTimeDocHitListIterator buffer_it(*_buffer_list);
    FixPostListIterator fix_it(*_fix_list);
    // 归并merge
    while (!buffer_it.done() && !fix_it.done()) {
        if (buffer_it.get_current_value() < fix_it.get_current_value()) {
            push_to_list(buffer_it.get_current_value(), new_fix_list);
            buffer_it.next();
        } else if (fix_it.get_current_value() < buffer_it.get_current_value()) {
            push_to_list(fix_it.get_current_value(), new_fix_list);
            fix_it.next();
        } else {
            // 同一个token出现2次，不影响服务，需要报警排查代码
            UWARNING("[\tlvl=MONITOR\t] same token exist twice");
            push_to_list(fix_it.get_current_value(), new_fix_list);
            buffer_it.next();
            fix_it.next();
        }
    }
    while (!buffer_it.done()) {
        push_to_list(buffer_it.get_current_value(), new_fix_list);
        buffer_it.next();
    }
    while (!fix_it.done()) {
        push_to_list(fix_it.get_current_value(), new_fix_list);
        fix_it.next();
    }
    // now swap the fix_array_, atomic set
    DocHitList * to_del = _fix_list;
    _fix_list = new_fix_list;
    // note: here, may be a new leaf iterator will get both the new fix_time_list
    // and the old real_time_list, but that does not matter
    DocHitList * to_del_buffer = _buffer_list;
    _buffer_list = new RealTimeDocHitList(_token_id);
    Singleton<DelayedEnv>::get()->add_callback(
            NewCallback(
                    &release_delay,
                    to_del,
                    to_del_buffer),
            FLAGS_inverted_list_delete_delay);
}

void TokenList::insert_doc_hit(const doc_hit_t & doc_hit) {
    _buffer_list->add(doc_hit);
    if (_buffer_list->size() >= static_cast<size_t>(_buffer_merge_threshold)) {
        merge();
    }
}

void TokenList::delete_doc_hit(const doc_hit_t & doc_hit) {
    _buffer_list->remove(doc_hit);
    _fix_list->remove(doc_hit);
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
