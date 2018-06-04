// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/empty_iterator.h"

namespace unise
{
EmptyIterator::EmptyIterator()
{
    _illegal_doc_hit.docid = ILLEGAL_DOCID;
    _illegal_doc_hit.score = ILLEGAL_SCORE;
}

}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
