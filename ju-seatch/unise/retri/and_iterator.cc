// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/and_iterator.h"
#include "index/index.h"

namespace unise
{
using std::vector;

AndIterator::AndIterator(const vector<ForwardIterator *> & it_list)
    : ForwardIterator(), _it_list(it_list)
{
    get_match();
}

void AndIterator::get_match()
{
    bool find = false;
    doc_hit_t max_doc_hit;
    max_doc_hit.set_min();
    while (!(done())) {
        for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
                it != _it_list.end(); ++it) {
            if (max_doc_hit < (*it)->get_cur_doc_hit()) {
                max_doc_hit = (*it)->get_cur_doc_hit();
            }
        }
        // check equal
        bool equal = true;
        for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
                it != _it_list.end(); ++it) {
            if (!(max_doc_hit == (*it)->get_cur_doc_hit())) {
                (*it)->jump_to(max_doc_hit.docid, max_doc_hit.score);
                equal = false;
            }
        }
        if (equal) {
            find = true;
            break;
        }
    }
    if (find) {
        _cur_doc_hit = max_doc_hit;
    } else {
        _cur_doc_hit.reset();
    }
}

void AndIterator::next()
{
    if (!done()) {
        for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
                it != _it_list.end(); ++it) {
            (*it)->next();
        }
        get_match();
    }
}

bool AndIterator::done() const
{
    bool is_done = false;
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        if ((*it)->done()) {
            is_done = true;
            break;
        }
    }
    return is_done;
}

void AndIterator::jump_to(DocId docid, int32_t score)
{
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        (*it)->jump_to(docid, score);
    }
    get_match();
}

const doc_hit_t & AndIterator::get_cur_doc_hit() const
{
    return _cur_doc_hit;
}

bool AndIterator::post_retrieval_check_internal()
{
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        if (false == (*it)->post_retrieval_check()) {
            return false;
        }
    }
    return true;
}

void AndIterator::get_hit_list(std::stack<TokenId> * hits) const
{
    GOOGLE_DCHECK(hits);
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        (*it)->get_hit_list(hits);
    }
}

float AndIterator::get_progress() const {
    float max_pro = 0.0;
    float cur_pro = 0.0;
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        cur_pro = (*it)->get_progress();
        if (cur_pro > max_pro) {
            max_pro = cur_pro;
        }
    }
    return max_pro;
}

uint64_t AndIterator::get_estimated_num() const {
    uint64_t min_num = 0xFFFFFFFFFFFFFFFF;
    uint64_t cur_num = 0LLU;
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        cur_num = (*it)->get_estimated_num();
        if (cur_num < min_num) {
            min_num = cur_num;
        }
    }
    return min_num;
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
