// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/general_cluster.h"
#include <gflags/gflags.h>
#include <uln_sign_murmur.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "unise/general_servlet.pb.h"
#include "unise/util.h"
#include "unise/search_context.h"

namespace unise
{

GeneralCluster::~GeneralCluster() {}

bool GeneralCluster::init(const comcfg::ConfigUnit & conf)
{
    try {
        string cluster_file_path(conf["GeneralClusterConfig"].to_cstr());
        int fd = open(cluster_file_path.c_str(), O_RDONLY);
        if (fd == -1) {
          UFATAL("GeneralClusterConfig file not exist:%s", cluster_file_path.c_str());
          return false;
        }
        google::protobuf::io::FileInputStream ins(fd);
        bool init_succ = google::protobuf::TextFormat::Parse(&ins, &_cluster_item);
        ins.Close();
        close(fd);

        if (!init_succ) {
          UFATAL("GeneralClusterConfig illegal:%s", cluster_file_path.c_str());
          return false;
        }
    } catch (comcfg::ConfigException& e) {
        // 如果没有配置文件，那么，强制失败
        UFATAL("illegal Configure for GeneralCluster:%s", e.what());
        return false;
    }
    if (_cluster_item.type() != TEXT && _cluster_item.type() != NUMBER) {
        UFATAL("unknown annotation_type:%d", _cluster_item.type());
        return false;
    }
    return true;
}

void GeneralCluster::init_for_search(const GeneralSearchRequest* request,
                                     const Comparator* result_comparator,
                                     SearchContext * context)
{
    _cluster.reset();
    _cluster.set_comparator(result_comparator);
    _need_cluster = true;
    context->get_experiment_value("general_cluster", &_need_cluster);
}

bool GeneralCluster::need_cluster(MatchedDoc* result) const
{
    return _need_cluster;
}

cluster_status_t GeneralCluster::cluster_result(MatchedDoc* result,
                                             MatchedDoc** clustered_result)
{
    const FactDoc & fact_doc = result->get_fact_doc();
    GOOGLE_CHECK_EQ(fact_doc.get_doc_id(), result->get_doc_id());
    for (size_t i = 0; i < fact_doc.annotations.size(); ++i) {
        const Annotation & anno = fact_doc.annotations.at(i);
        if (anno.id == _cluster_item.annotation_id()) {
            string key;
            if (_cluster_item.type() == TEXT) {
                key.assign(anno.text_value);
            } else {
                key.assign(Int64ToString(anno.number_value));
            }
            return _cluster.cluster_result(key,
                        result,
                        clustered_result);
        }
    }
    return CLUSTER_ADD;
}

void GeneralCluster::add_info(MatchedDoc* result)
{
    const FactDoc & fact_doc = result->get_fact_doc();
    for (size_t i = 0; i < fact_doc.annotations.size(); ++i) {
        const Annotation & anno = fact_doc.annotations.at(i);
        if (anno.id == _cluster_item.annotation_id()) {
            string key;
            if (_cluster_item.type() == TEXT) {
                key = anno.text_value;
            } else {
                key = Int64ToString(anno.number_value);
            }
            _cluster.add(key, result, _cluster_item.number());
            break;
        }
    }
}

void GeneralCluster::remove_info(MatchedDoc* result)
{
    const FactDoc & fact_doc = result->get_fact_doc();
    for (size_t i = 0; i < fact_doc.annotations.size(); ++i) {
        const Annotation & anno = fact_doc.annotations.at(i);
        if (anno.id == _cluster_item.annotation_id()) {
            string key;
            if (_cluster_item.type() == TEXT) {
                key = anno.text_value;
            } else {
                key = Int64ToString(anno.number_value);
            }
            _cluster.remove(key, result);
            break;
        }
    }
}

REGISTER_RESULT_CLUSTER(GeneralCluster);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
