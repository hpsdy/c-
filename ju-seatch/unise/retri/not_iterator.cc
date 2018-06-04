// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/not_iterator.h"
#include "index/index.h"

namespace unise
{

NotIterator::NotIterator(const RepositoryManager & repos,
        ForwardIterator * it)
    : ForwardIterator(), _repository_manager(repos), _forward_it(it)
{
    _cur_doc_hit = _repository_manager.get_next_doc_info(SCORE_MAX, DOCID_MIN);
    get_match();
}

void NotIterator::get_match()
{
    while (!_forward_it->done()) {
        GOOGLE_DCHECK(!(_forward_it->get_cur_doc_hit() < _cur_doc_hit)) <<
                "shit[score:" << _forward_it->get_cur_doc_hit().score <<
                ",docid:" << _forward_it->get_cur_doc_hit().docid <<
                "] cur[score:" << _cur_doc_hit.score << ",docid:" << _cur_doc_hit.docid << "]";
        if (_forward_it->get_cur_doc_hit().docid != _cur_doc_hit.docid ||
                !_forward_it->post_retrieval_check()) {
            break;
        }
        UDEBUG("On shit [score:%d docid:%llu], move one step",
                _cur_doc_hit.score,
                _cur_doc_hit.docid);
        _forward_it->next();
        _cur_doc_hit = _repository_manager.get_next_doc_info(
                       _cur_doc_hit.score,
                       _cur_doc_hit.docid + 1);
    }
}

void NotIterator::next()
{
    if (!done()) {
        _cur_doc_hit = _repository_manager.get_next_doc_info(
                       _cur_doc_hit.score,
                       _cur_doc_hit.docid + 1);
        get_match();
    }
}

// TODO : special
bool NotIterator::done() const
{
    return _cur_doc_hit.docid == ILLEGAL_DOCID;
}

void NotIterator::jump_to(DocId docid, int32_t score)
{
    if (score < _forward_it->get_cur_doc_hit().score ||
            (score == _forward_it->get_cur_doc_hit().score &&
                    docid > _forward_it->get_cur_doc_hit().docid)) {
        _forward_it->jump_to(docid, score);
    }
    _cur_doc_hit = _repository_manager.get_next_doc_info(score, docid);
    get_match();
}

const doc_hit_t & NotIterator::get_cur_doc_hit() const
{
    return _cur_doc_hit;
}

// 这里不打印log，因为规则是固定的，可以通过
// LeafIterator的log来推算
float NotIterator::get_progress() const {
    size_t all_count = _repository_manager.get_fact_doc_count();
    if (all_count != 0U) {
        return _forward_it->get_progress() * _forward_it->get_estimated_num() / all_count;
    } else {
        return 1.0;
    }
}

uint64_t NotIterator::get_estimated_num() const {
    return _repository_manager.get_fact_doc_count() - _forward_it->get_estimated_num();
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
