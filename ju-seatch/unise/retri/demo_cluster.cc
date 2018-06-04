// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/demo_cluster.h"
#include "gflags/gflags.h"
#include "util/util.h"
#include "unise/general_servlet.pb.h"
#include "unise/search_context.h"

DEFINE_int32(demo_cluster_num, 1, "");

namespace unise
{

void DemoCluster::init_for_search(const GeneralSearchRequest* request,
        const Comparator* result_comparator,
        SearchContext * context)
{
    cluster_.reset();
    cluster_.set_comparator(result_comparator);
}

bool DemoCluster::need_cluster(MatchedDoc* result) const
{
    return true;
}

cluster_status_t DemoCluster::cluster_result(MatchedDoc* result,
        MatchedDoc** clustered_result)
{
    return cluster_.cluster_result(result->get_score(),
            result,
            clustered_result);
}

void DemoCluster::add_info(MatchedDoc* result)
{
    cluster_.add(result->get_score(),
            result,
            FLAGS_demo_cluster_num);
}

void DemoCluster::remove_info(MatchedDoc* result)
{
    cluster_.remove(result->get_score(),
                    result);
}

REGISTER_RESULT_CLUSTER(DemoCluster);
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
