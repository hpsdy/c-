// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/default_comparator.h"

namespace unise {

bool DefaultComparator::operator()(const MatchedDoc* a, const MatchedDoc* b) const
{
    return _comparator.operator()(a->get_search_result(), b->get_search_result());
}

REGISTER_COMPARATOR(DefaultComparator);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
