// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_RESULT_CLUSTER_HANDLER_H_
#define  RETRI_RESULT_CLUSTER_HANDLER_H_

#include <vector>
#include <set>
#include <map>
#include "unise/result_cluster.h"

namespace comcfg
{
class ConfigUnit;
}

namespace unise
{
class GeneralSearchRequest;
class GeneralSearchResponse;
class Comparator;
class MatchedDoc;
class SearchResult;
class RepositoryManager;

class ResultClusterHandler
{
public:
    ResultClusterHandler(const RepositoryManager& rm);
    virtual ~ResultClusterHandler();

    bool init(const comcfg::ConfigUnit& conf);
    void init_for_search(const GeneralSearchRequest* request,
                         const Comparator* result_comparator,
                         SearchContext * context);
    void end_for_search(GeneralSearchResponse * response);

    cluster_status_t cluster(MatchedDoc* result,
                             std::set<MatchedDoc*>* clustered_result);

    void add_cluster_info(MatchedDoc* result);
    void remove_cluster_info(MatchedDoc* result);
    void fill_result_cluster_info(MatchedDoc* doc,
                                  SearchResult* search_result);

private:
    typedef std::map<uint64_t, std::vector<ResultCluster*> > UniseClustersMap;
    UniseClustersMap _clusters_map;
    std::vector<ResultCluster*> * _cur_clusters;
    std::vector<uint32_t> _cluster_counters;

    const RepositoryManager& _repository_manager;
};

}

#endif  // RETRI_RESULT_CLUSTER_HANDLER_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
