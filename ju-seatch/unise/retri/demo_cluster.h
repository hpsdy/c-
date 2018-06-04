// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_DEMO_CLUSTER_H_
#define  RETRI_DEMO_CLUSTER_H_

#include <string>
#include <Configure.h>
#include "unise/result_cluster.h"
#include "unise/cluster_template.h"
#include "unise/matched_doc.h"

namespace unise
{
class MatchedDoc;
class GeneralSearchRequest;

class DemoCluster : public ResultCluster
{
public:
    typedef ClusterTemplate<dynamic_score_t, MatchedDoc*, 4> MyClusterInternal;

    std::string get_name() const { return "DemoCluster"; }
    bool init(const comcfg::ConfigUnit& conf) { return true; }
    void init_for_search(const GeneralSearchRequest* request,
            const Comparator* result_comparator,
            SearchContext * context);
    bool need_cluster(MatchedDoc* result) const;

    cluster_status_t cluster_result(MatchedDoc* result,
            MatchedDoc** clustered_result);
    void add_info(MatchedDoc* result);
    void remove_info(MatchedDoc* result);
private:
    MyClusterInternal cluster_;
};
}

#endif  // RETRI_DEMO_CLUSTER_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
