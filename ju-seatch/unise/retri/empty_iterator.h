// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_EMPTY_ITERATOR_H_
#define  RETRI_EMPTY_ITERATOR_H_

#include "retri/forward_iterator.h"
#include "unise/base.h"

namespace unise
{
class EmptyIterator : public ForwardIterator
{
public:
    EmptyIterator();
    virtual ~EmptyIterator() {}

    virtual void next() {}
    virtual bool done() const {
        return true;
    }
    virtual void jump_to(DocId docid, int32_t score)
    {
        UWARNING("[\tlvl=FOLLOW\t] EmptyIterator can't JumpTo");
    }
    virtual const doc_hit_t & get_cur_doc_hit() const {
        return _illegal_doc_hit;
    }
    virtual float get_progress() const {
        return 1.0;
    }
    virtual uint64_t get_estimated_num() const {
        return 0LLU;
    }
private:
    doc_hit_t _illegal_doc_hit;
};
}

#endif  // EMPTY_ITERATOR_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
