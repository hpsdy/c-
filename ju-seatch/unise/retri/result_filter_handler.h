// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_RESULT_FILTER_HANDLER_H_
#define  RETRI_RESULT_FILTER_HANDLER_H_

#include <vector>
#include <map>
#include "unise/base.h"

namespace comcfg
{
class ConfigUnit;
}

namespace unise
{
class GeneralSearchRequest;
class GeneralSearchResponse;
class MatchedDoc;
class ResultFilter;
class RepositoryManager;
class SearchContext;

class ResultFilterHandler
{
public:
    ResultFilterHandler(const RepositoryManager& rm);
    virtual ~ResultFilterHandler();

    // conf is EngineUnit conf
    bool init(const comcfg::ConfigUnit& conf);
    bool init_for_search(const GeneralSearchRequest* request, SearchContext * context);
    void end_for_search(GeneralSearchResponse * response);

    // This function can reject a result without actually needing to
    // build the DocTokenHit info
    bool early_filter(MatchedDoc* result, result_status_t* result_status);
    // This function be called just before accept the result
    bool later_filter(MatchedDoc* result, result_status_t* result_status);
    // This function be called when finished retrieval
    bool final_filter(MatchedDoc* result, result_status_t* result_status);

private:
    typedef std::map<uint64_t, std::vector<ResultFilter*> > UniseFiltersMap;
    bool init_handler(const comcfg::ConfigUnit& conf,
                     const std::string& conf_name,
                     UniseFiltersMap * filters_map);

    void end_for_search_filters(std::vector<ResultFilter*> *,
                                GeneralSearchResponse *);
    void destroy_filters_map(UniseFiltersMap * filters_map);
private:
    const RepositoryManager& _repository_manager;
    UniseFiltersMap _early_filters_map;
    UniseFiltersMap _later_filters_map;
    UniseFiltersMap _final_filters_map;
    std::vector<ResultFilter*> * _cur_early_filters;
    std::vector<ResultFilter*> * _cur_later_filters;
    std::vector<ResultFilter*> * _cur_final_filters;
    std::vector<uint32_t> _early_filter_counters;
    std::vector<uint32_t> _later_filter_counters;
    std::vector<uint32_t> _final_filter_counters;
};
}

#endif  // RETRI_RESULT_FILTER_HANDLER_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
