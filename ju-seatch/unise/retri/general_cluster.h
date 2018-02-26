// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_GENERAL_CLUSTER_H
#define  RETRI_GENERAL_CLUSTER_H

#include <string>
#include <Configure.h>
#include "unise/result_cluster.h"
#include "unise/cluster_template.h"
#include "unise/matched_doc.h"
#include "unise/general_plugin.pb.h"
#include "unise/general_servlet.pb.h"
#include "util/hash_tables.h"

namespace unise
{
class MatchedDoc;
class GeneralSearchRequest;
class SearchContext;

class GeneralCluster : public ResultCluster
{
public:
    typedef ClusterTemplate<std::string, MatchedDoc*, 4> MyClusterInternal;

    ~GeneralCluster();
    virtual bool init(const comcfg::ConfigUnit & conf);
    virtual std::string get_name() const { return "GeneralCluster"; }
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 const Comparator* result_comparator,
                                 SearchContext * context);
    virtual bool need_cluster(MatchedDoc* result) const;

    virtual cluster_status_t cluster_result(MatchedDoc* result,
                                            MatchedDoc** clustered_result);
    virtual void add_info(MatchedDoc* result);
    virtual void remove_info(MatchedDoc* result);
private:
    MyClusterInternal _cluster;
    AnnotationClusterItem _cluster_item;
    bool _need_cluster;
};
}

#endif  // RETRI_GENERAL_CLUSTER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
