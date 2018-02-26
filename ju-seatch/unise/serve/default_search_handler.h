// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  DEFAULT_SEARCH_HANDLER_H_
#define  DEFAULT_SEARCH_HANDLER_H_

#include <vector>
#include "unise/search_handler.h"
#include "Configure.h"
#include "serve/engine_unit_manager.h"

namespace unise
{
class EngineUnit;
class GeneralSearchRequest;
class GeneralSearchResponse;
class SearchResult;

class DefaultSearchHandler : public SearchHandler
{
public:
    DefaultSearchHandler() : _result_num_all(0), _result_num_eu(0) {}
    virtual ~DefaultSearchHandler() {}
    virtual bool my_init(const comcfg::ConfigUnit&);
    virtual void search_internal(const GeneralSearchRequest* request,
            std::vector<GeneralSearchResponse*>* responses);

    const std::string get_name() const {
        return "DefaultSearchHandler";
    }
    const std::string get_type() const {
        return "DefaultSearchHandler";
    }
private:
    std::vector<EngineUnit*> engine_unit_list_;
    int32_t _result_num_all;    ///< SE需要收集的结果总数
    int32_t _result_num_eu;     ///< 每个EU需要返回的结果数
};

REGISTER_FACTORY(DefaultSearchHandler);
#define REGISTER_SEARCH_HANDLER(name) REGISTER_CLASS(DefaultSearchHandler, name)

}

#endif  // DEFAULT_SEARCH_HANDLER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
