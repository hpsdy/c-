// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/search_handler_helper.h"

namespace unise
{

SearchHandlerHelper::~SearchHandlerHelper()
{/*{{{*/
    while (!_responses.empty()) {
        delete _responses.front();
        _responses.pop();
    }
}/*}}}*/

bool SearchHandlerHelper::init(uint32_t num)
{/*{{{*/
    _org_size = num;
    for (uint32_t i = 0; i < _org_size; ++i) {
        _responses.push(new GeneralSearchResponse());
    }
    return true;
}/*}}}*/

}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
