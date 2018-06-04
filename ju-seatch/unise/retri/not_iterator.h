// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_NOT_ITERATOR_H_
#define  RETRI_NOT_ITERATOR_H_

#include "retri/forward_iterator.h"
#include "index/index.h"

namespace unise {

class NotIterator : public ForwardIterator {
public:
    NotIterator(const RepositoryManager & repos, ForwardIterator * forward_it);
    virtual ~NotIterator() {}
    virtual void next();
    virtual bool done() const;
    virtual void jump_to(DocId docid, int32_t score);
    virtual const doc_hit_t & get_cur_doc_hit() const;
    virtual float get_progress() const;
    virtual uint64_t get_estimated_num() const;
private:
    void get_match();

private:
    doc_hit_t _cur_doc_hit;
    const RepositoryManager & _repository_manager;
    ForwardIterator * _forward_it;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(NotIterator);
};

}

#endif  // RETRI_NOT_ITERATOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
