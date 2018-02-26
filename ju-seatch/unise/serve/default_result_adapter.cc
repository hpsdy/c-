/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file default_result_adapter.cc
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/23 12:03:33
 * @version $Revision$
 * @brief 默认结果调整器类的实现
 *
 **/

#include "serve/default_result_adapter.h"
#include "unise/base.h"

namespace unise
{

void DefaultResultAdapter::init_for_search(const GeneralSearchRequest* request,
            GeneralSearchResponse * response)
{
    (void)(response);
    _comparator.reset(request);
}

void DefaultResultAdapter::adapt(const std::vector<SearchResult*> &results,
        std::vector<const SearchResult*>* selected_results,
        std::vector<const SearchResult*>* dropped_results)
{
    for (size_t i = 0; i < results.size(); ++i) {
        selected_results->push_back(results[i]);
    }
    dropped_results->clear();
    if (_comparator.enable()) {
        sort(selected_results->begin(), selected_results->end(), _comparator);
    }
}

REGISTER_RESULT_ADAPTER(DefaultResultAdapter);
}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
