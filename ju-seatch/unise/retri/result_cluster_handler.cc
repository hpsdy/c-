// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/result_cluster_handler.h"
#include <string>
#include "Configure.h"
#include "unise/general_servlet.pb.h"
#include "unise/result_cluster.h"
#include "unise/matched_doc.h"
#include "unise/search_context.h"
#include "index/repository_manager.h"
#include "util/util.h"
#include "unise/base.h"


DECLARE_bool(enable_result_handler_counter);

namespace unise
{
ResultClusterHandler::ResultClusterHandler(const RepositoryManager& rm)
    : _repository_manager(rm)
{
}

ResultClusterHandler::~ResultClusterHandler()
{
    for (UniseClustersMap::iterator it = _clusters_map.begin();
                it != _clusters_map.end(); ++it) {
        std::vector<ResultCluster*> & clusters = it->second;
        for (size_t i = 0; i < clusters.size(); ++i) {
            delete clusters.at(i);
        }
    }
}

bool ResultClusterHandler::init(const comcfg::ConfigUnit& conf)
{
    std::vector<std::pair<uint64_t, string> > plugins;
    bool missing_default = true;
    try {
        int num = conf["ResultClusters"].size();
        for (int i = 0; i < num; ++i) {
            uint64_t sample_id = conf["ResultClusters"][i]["sample_id"].to_uint64();
            string str(conf["ResultClusters"][i]["plugin"].to_cstr());
            plugins.push_back(std::make_pair(sample_id, str));
            UNOTICE("sample_id:%llu ResultClusters:%s", sample_id, str.c_str());
            if (sample_id == DEFAULT_SAMPLE_ID) {
                missing_default = false;
            }
        }
    } catch (comcfg::ConfigException& e) {
        UFATAL("illegal Configure for ClusterHandler:%s", e.what());
        return false;
    }

    if (missing_default) {
        UFATAL("missing sample_id 0 conf for ResultClusters");
        return false;
    }
    for (size_t idx = 0; idx < plugins.size(); ++idx) {
        vector<string> values;
        uint64_t sample_id = plugins.at(idx).first;
        string & str = plugins.at(idx).second;
        if (_clusters_map.find(sample_id) != _clusters_map.end()) {
            UFATAL("sample id:%ull conflict for Clusters", sample_id);
            return false;
        }
        string_split(str, ",", &values);
        vector<ResultCluster*> clusters;
        for (size_t i = 0; i < values.size(); ++i) {
            UNOTICE("init ResultCluster:%s", values.at(i).c_str());
            ResultCluster * cluster = ResultClusterFactory::get_instance(values.at(i));
            if (cluster == NULL) {
                UFATAL("GetInstance failed:%s", values.at(i).c_str());
                return false;
            } else if (cluster->basic_init(&_repository_manager,
                                          conf["ResultClusters"][idx]) == false) {
                UFATAL("init failed:%s", values.at(i).c_str());
                delete cluster;
                return false;
            } else {
                clusters.push_back(cluster);
            }
        }
        _clusters_map.insert(std::make_pair(sample_id, clusters));
    }
    return true;
}

void ResultClusterHandler::init_for_search(const GeneralSearchRequest* request,
                                           const Comparator* result_comparator,
                                           SearchContext * context)
{
    UniseClustersMap::iterator it = _clusters_map.find(context->get_sample_id());
    if (it == _clusters_map.end()) {
        it = _clusters_map.find(DEFAULT_SAMPLE_ID);
        GOOGLE_DCHECK(it != _clusters_map.end());
    }

    _cur_clusters = &(it->second);
    _cluster_counters.resize(_cur_clusters->size());
    for (size_t i = 0; i < _cur_clusters->size(); ++i) {
        ResultCluster * cluster = _cur_clusters->at(i);
        cluster->init_for_search(request, result_comparator, context);
        _cluster_counters.at(i) = 0;
    }
}

cluster_status_t ResultClusterHandler::cluster(MatchedDoc* result,
        std::set<MatchedDoc*>* clustered_results)
{
    cluster_status_t status = CLUSTER_ADD;
    for (size_t i = 0; i < _cur_clusters->size(); ++i) {
        MatchedDoc * clustered_result = NULL;
        ResultCluster * cluster = _cur_clusters->at(i);
        if (!cluster->need_cluster(result)) {
            UDEBUG("skip cluster:%s docid:%llu",
                    cluster->get_name().c_str(),
                    result->get_doc_id());
            continue;
        }
        // Unit Test find a bug here, good
        status = cluster->cluster_result(result, &clustered_result);
        if (status == CLUSTER_SKIP) {
            UDEBUG("finish clustering for one cluster lose: %s"
                    " status:%d"
                    " docid:%llu"
                    " score:%d"
                    " another_docid:%llu"
                    " another_score:%d",
                    cluster->get_name().c_str(),
                    status,
                    result->get_doc_id(),
                    result->get_score(),
                    clustered_result->get_doc_id(),
                    clustered_result->get_score());
            _cluster_counters.at(i)++;
            return CLUSTER_SKIP;
        } else if (status == CLUSTER_REPLACE) {
            UDEBUG("cluster win: %s"
                    " status:%d"
                    " docid:%llu"
                    " score:%d"
                    " another_docid:%llu"
                    " another_score:%d",
                    cluster->get_name().c_str(),
                    status,
                    result->get_doc_id(),
                    result->get_score(),
                    clustered_result->get_doc_id(),
                    clustered_result->get_score());
            clustered_results->insert(clustered_result);
            _cluster_counters.at(i)++;
            status = CLUSTER_REPLACE;
        }
    }
    return status;
}

void ResultClusterHandler::add_cluster_info(MatchedDoc* result)
{
    for (size_t i = 0; i < _cur_clusters->size(); ++i) {
        ResultCluster * cluster = _cur_clusters->at(i);
        if (false == cluster->need_cluster(result)) {
            continue;
        }
        cluster->add_info(result);
    }
}

void ResultClusterHandler::remove_cluster_info(MatchedDoc* result)
{
    for (size_t i = 0; i < _cur_clusters->size(); ++i) {
        ResultCluster * cluster = _cur_clusters->at(i);
        // TODO(wangguangyuan) : NeedCluster's result should be cached
        if (false == cluster->need_cluster(result)) {
            continue;
        }
        cluster->remove_info(result);
    }
}

void ResultClusterHandler::fill_result_cluster_info(MatchedDoc* doc,
        SearchResult* search_result)
{
    for (size_t i = 0; i < _cur_clusters->size(); ++i) {
        ResultCluster * cluster = _cur_clusters->at(i);
        cluster->fill_result_cluster_info(doc, search_result);
    }
}


void ResultClusterHandler::end_for_search(GeneralSearchResponse * response)
{
    PluginResponse pr;
    for (size_t i = 0; i < _cur_clusters->size(); ++i) {
        ResultCluster * cluster = _cur_clusters->at(i);
        pr.Clear();
        pr.set_enable(false);
        cluster->end_for_search(&pr);
        if (pr.enable()) {
            response->add_plugin_responses()->CopyFrom(pr);
        }
    }
    if (FLAGS_enable_result_handler_counter) {
        // 增加计数的log
        string msg;
        for (size_t i = 0; i < _cur_clusters->size(); ++i) {
            msg.append(_cur_clusters->at(i)->get_name() + "[" +
                        UintToString(_cluster_counters.at(i)) + "] ");
        }
        PluginResponse * pr = response->add_plugin_responses();
        pr->set_enable(true);
        pr->set_name("ResultClusterHandler");
        pr->set_information(msg);
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=80: */
