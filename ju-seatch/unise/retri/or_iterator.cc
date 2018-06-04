// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/or_iterator.h"
#include <boost/lockfree/detail/branch_hints.hpp>

namespace unise {
using std::vector;
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

OrIterator::OrIterator(const vector<ForwardIterator *> & it_list) :
        ForwardIterator(),
        _it_list(it_list) {
    for (size_t i = 0; i < _it_list.size(); ++i) {
        if (!_it_list.at(i)->done()) {
            _heap.push(std::make_pair(i, _it_list.at(i)->get_cur_doc_hit()));
        }
    }
    get_match();
}

void OrIterator::get_match() {
    if (unlikely(_heap.empty())) {
        _cur_doc_hit.reset();
    } else {
        // TODO(wangguangyuan) : 这里是否能够减少赋值
        _cur_doc_hit = _heap.top().second;
    }
}

void OrIterator::next() {
    if (unlikely(done())) {
        return;
    }
    doc_hit_t last_min = _heap.top().second;
    while (!_heap.empty() && last_min == _heap.top().second) {
        size_t last_idx = _heap.top().first;
        ForwardIterator * fi = _it_list.at(last_idx);
        fi->next();
        _heap.pop();
        if (!fi->done()) {
            _heap.push(std::make_pair(last_idx, fi->get_cur_doc_hit()));
        }
    }
    get_match();
}

bool OrIterator::done() const {
    return _cur_doc_hit.docid == ILLEGAL_DOCID || _heap.empty();
}

void OrIterator::jump_to(DocId docid, int32_t score) {
    if (unlikely(done())) {
        return;
    }
    doc_hit_t doc_hit = {docid, score};
    while (!_heap.empty() && _heap.top().second < doc_hit) {
        size_t last_idx = _heap.top().first;
        ForwardIterator * fi = _it_list.at(last_idx);
        fi->jump_to(docid, score);
        _heap.pop();
        if (!fi->done()) {
            _heap.push(std::make_pair(last_idx, fi->get_cur_doc_hit()));
        }
    }
    get_match();
}

const doc_hit_t & OrIterator::get_cur_doc_hit() const {
    return _cur_doc_hit;
}

bool OrIterator::post_retrieval_check_internal() {
    // Or迭代器，只要有任何一个孩子同意当前答案，那么
    // 当前Or节点就同意
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        if ((*it)->get_cur_doc_hit() == _cur_doc_hit &&
                (*it)->post_retrieval_check()) {
            return true;
        }
    }
    return false;
}


void OrIterator::get_hit_list(std::stack<TokenId> * hits) const {
    GOOGLE_DCHECK(hits);
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        if ((*it)->get_cur_doc_hit() == _cur_doc_hit) {
            (*it)->get_hit_list(hits);
        }
    }
}

float OrIterator::get_progress() const {
    float min_pro = 1.0;
    float cur_pro = 0.0;
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        cur_pro = (*it)->get_progress();
        if (cur_pro < min_pro) {
            min_pro = cur_pro;
        }
    }
    return min_pro;
}

uint64_t OrIterator::get_estimated_num() const {
    uint64_t est = 0LLU;
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        est += (*it)->get_estimated_num();
        // FIXME:这里需要判断溢出
    }
    return est;
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
