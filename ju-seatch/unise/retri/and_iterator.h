// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_AND_ITERATOR_H_
#define  RETRI_AND_ITERATOR_H_

#include <vector>
#include "unise/base.h"
#include "retri/forward_iterator.h"

namespace unise
{
class AndIterator : public ForwardIterator
{
public:
    explicit AndIterator(const std::vector<ForwardIterator *> & it_list);
    virtual ~AndIterator() {}
    virtual void next();
    virtual bool done() const;
    virtual void jump_to(DocId docid, int32_t score);
    virtual const doc_hit_t & get_cur_doc_hit() const;
    virtual bool post_retrieval_check_internal();
    virtual void get_hit_list(std::stack<TokenId> * hits) const;
    virtual float get_progress() const;
    virtual uint64_t get_estimated_num() const;
private:
    void get_match();

private:
    std::vector<ForwardIterator *> _it_list;
    doc_hit_t _cur_doc_hit;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(AndIterator);
};
}

#endif  // RETRI_AND_ITERATOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
