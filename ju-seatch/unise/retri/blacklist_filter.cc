// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/blacklist_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include "gflags/gflags.h"
#include "unise/base.h"

DEFINE_string(blacklist_fullpath, "./data/blacklist.list", "");

namespace unise
{

bool BlacklistFilter::init(const comcfg::ConfigUnit & conf)
{
    FILE * file = fopen(FLAGS_blacklist_fullpath.c_str(), "r");
    if (file == NULL) {
        UFATAL("open file %s fail", FLAGS_blacklist_fullpath.c_str());
        return false;
    }
    DocId docid;
    while (fscanf(file, "%llu", &docid) != EOF) {
        filter_id_map_.insert(std::make_pair(docid, true));
    }
    fclose(file);
    return true;
}

result_status_t BlacklistFilter::filter(MatchedDoc * result)
{
    if (filter_id_map_.find(result->get_doc_id()) == filter_id_map_.end()) {
        return RESULT_ACCEPTED;
    } else {
        return RESULT_INVALID;
    }
}

REGISTER_RESULT_FILTER(BlacklistFilter);
REGISTER_RESULT_FILTER(PerformanceFilter);
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
