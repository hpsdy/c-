// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_LEAF_ITERATOR_H_
#define  RETRI_LEAF_ITERATOR_H_

#include "retri/forward_iterator.h"
#include "index/index.h"

namespace unise
{
class DocHitList;
class DocHitListIterator;

class LeafIterator : public ForwardIterator
{
public:
    LeafIterator(const DocHitList & doc_hit_list);
    virtual ~LeafIterator();

    virtual void next();
    virtual bool done() const;
    virtual void jump_to(DocId docid, int32_t score);
    virtual const doc_hit_t & get_cur_doc_hit() const;
    /// @brief 获得命中一个 DOC 的所有 TOKENID
    /// @param hits
    virtual void get_hit_list(std::stack<TokenId> * hits) const;
    virtual float get_progress() const;
    virtual uint64_t get_estimated_num() const;

private:
    const DocHitList & _list;
    DocHitListIterator * _iterator;
};
}
#endif  // RETRI_LEAF_ITERATOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
