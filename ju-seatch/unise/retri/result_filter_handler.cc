// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/result_filter_handler.h"
#include <string>
#include "Configure.h"
#include "gflags/gflags.h"
#include "unise/matched_doc.h"
#include "unise/result_filter.h"
#include "unise/search_context.h"
#include "index/repository_manager.h"
#include "util/util.h"

DEFINE_bool(enable_result_handler_counter, false, "show the Filter,Cluster counter");

namespace unise
{
using std::string;
using std::vector;

ResultFilterHandler::ResultFilterHandler(const RepositoryManager& rm)
    : _repository_manager(rm)
{
}


void ResultFilterHandler::destroy_filters_map(UniseFiltersMap * filters_map)
{
    for (UniseFiltersMap::iterator it = filters_map->begin();
                it != filters_map->end(); ++it) {
        std::vector<ResultFilter*> & filters = it->second;
        for (size_t i = 0; i < filters.size(); ++i) {
            delete filters.at(i);
        }
    }
}

ResultFilterHandler::~ResultFilterHandler()
{
    destroy_filters_map(&_early_filters_map);
    destroy_filters_map(&_later_filters_map);
    destroy_filters_map(&_final_filters_map);
}

bool ResultFilterHandler::init_handler(const comcfg::ConfigUnit& conf,
        const std::string& conf_item_name,
        UniseFiltersMap * filters_map)
{
    std::vector<std::pair<uint64_t, string> > plugins;
    bool missing_default = true;
    try {
        int num = conf[conf_item_name.c_str()].size();
        for (int i = 0; i < num; ++i) {
            uint64_t sample_id = conf[conf_item_name.c_str()][i]["sample_id"].to_uint64();
            string str(conf[conf_item_name.c_str()][i]["plugin"].to_cstr());
            // 在所有sample下的LaterResultFilters中加入内建Filter
            // TODO(wangguangyuan) : 为内建默认插件找更好的实现方式
            //                       拒绝狗屁膏药
            if (conf_item_name == "LaterResultFilters") {
                str.append(",BuildinFilter");
            }
            plugins.push_back(std::make_pair(sample_id, str));
            UNOTICE("sample_id:%llu %s:%s", sample_id, conf_item_name.c_str(), str.c_str());
            if (sample_id == DEFAULT_SAMPLE_ID) {
                missing_default = false;
            }
        }
    } catch (comcfg::ConfigException & e) {
        UFATAL("illegal Configure for ResultFilterHandler:%s", e.what());
        return false;
    }

    if (missing_default) {
        UFATAL("missing sample_id 0 conf for ResultFilter");
        return false;
    }
    for (size_t idx = 0; idx < plugins.size(); ++idx) {
        vector<string> values;
        uint64_t sample_id = plugins.at(idx).first;
        string & str = plugins.at(idx).second;
        if (filters_map->find(sample_id) != filters_map->end()) {
            UFATAL("sample id:%llu conflict for %s", sample_id, conf_item_name.c_str());
            return false;
        }
        string_split(str, ",", &values);
        vector<ResultFilter*> filters;
        for (size_t i = 0; i < values.size(); ++i) {
            UNOTICE("Init ResultFilter:%s", values.at(i).c_str());
            ResultFilter * filter = ResultFilterFactory::get_instance(values.at(i));
            if (filter == NULL) {
                UFATAL("GetInstance failed:%s", values.at(i).c_str());
                return false;
            } else if (filter->basic_init(&_repository_manager,
                                          conf[conf_item_name.c_str()][idx]) == false) {
                UFATAL("Init failed:%s", values.at(i).c_str());
                delete filter;
                return false;
            } else {
                filters.push_back(filter);
            }
        }
        filters_map->insert(std::make_pair(sample_id, filters));
    }
    return true;
}

bool ResultFilterHandler::init(const comcfg::ConfigUnit& conf)
{
    return init_handler(conf, "EarlyResultFilters", &_early_filters_map) &&
           init_handler(conf, "LaterResultFilters", &_later_filters_map) &&
           init_handler(conf, "FinalResultFilters", &_final_filters_map);
}

bool ResultFilterHandler::init_for_search(const GeneralSearchRequest* request,
                                          SearchContext * context)
{
    uint64_t sample_id = context->get_sample_id();

    UniseFiltersMap::iterator it = _early_filters_map.find(sample_id);
    if (it == _early_filters_map.end()) {
        it = _early_filters_map.find(DEFAULT_SAMPLE_ID);
        GOOGLE_DCHECK(it != _early_filters_map.end());
    }
    _cur_early_filters = &(it->second);

    it = _later_filters_map.find(sample_id);
    if (it == _later_filters_map.end()) {
        it = _later_filters_map.find(DEFAULT_SAMPLE_ID);
        GOOGLE_DCHECK(it != _later_filters_map.end());
    }
    _cur_later_filters = &(it->second);

    it = _final_filters_map.find(sample_id);
    if (it == _final_filters_map.end()) {
        it = _final_filters_map.find(DEFAULT_SAMPLE_ID);
        GOOGLE_DCHECK(it != _final_filters_map.end());
    }
    _cur_final_filters = &(it->second);

    _early_filter_counters.resize(_cur_early_filters->size());
    for (size_t i = 0; i < _cur_early_filters->size(); ++i) {
        _cur_early_filters->at(i)->init_for_search(request, context);
        _early_filter_counters.at(i) = 0U;
    }
    _later_filter_counters.resize(_cur_later_filters->size());
    for (size_t i = 0; i < _cur_later_filters->size(); ++i) {
        _cur_later_filters->at(i)->init_for_search(request, context);
        _later_filter_counters.at(i) = 0U;
    }
    _final_filter_counters.resize(_cur_final_filters->size());
    for (size_t i = 0; i < _cur_final_filters->size(); ++i) {
        _cur_final_filters->at(i)->init_for_search(request, context);
        _final_filter_counters.at(i) = 0U;
    }
    return true;
}

bool ResultFilterHandler::early_filter(MatchedDoc* result,
        result_status_t* result_status)
{
    *result_status = RESULT_ACCEPTED;
    for (size_t i = 0; i < _cur_early_filters->size(); ++i) {
        ResultFilter * filter = _cur_early_filters->at(i);
        *result_status = filter->filter(result);
        if (*result_status != RESULT_ACCEPTED) {
            UDEBUG("early_filter:%s rejected MatchedDoc:%llu",
                    filter->get_name().c_str(), result->get_doc_id());
            *result_status = RESULT_FILTED_EARLY;
            ++(_early_filter_counters.at(i));
            return false;
        }
    }
    return true;
}

bool ResultFilterHandler::later_filter(MatchedDoc* result,
        result_status_t* result_status)
{
    *result_status = RESULT_ACCEPTED;
    for (size_t i = 0; i < _cur_later_filters->size(); ++i) {
        ResultFilter * filter = _cur_later_filters->at(i);
        *result_status = filter->filter(result);
        if (*result_status != RESULT_ACCEPTED) {
            UDEBUG("later_filter:%s rejected MatchedDoc:%llu",
                    filter->get_name().c_str(), result->get_doc_id());
            *result_status = RESULT_FILTED_LATER;
            ++(_later_filter_counters.at(i));
            return false;
        }
    }
    return true;
}

bool ResultFilterHandler::final_filter(MatchedDoc* result,
        result_status_t* result_status)
{
    *result_status = RESULT_ACCEPTED;
    for (size_t i = 0; i < _cur_final_filters->size(); ++i) {
        ResultFilter * filter = _cur_final_filters->at(i);
        *result_status = filter->filter(result);
        if (*result_status != RESULT_ACCEPTED) {
            UDEBUG("final_filter:%s rejected MatchedDoc:%llu",
                    filter->get_name().c_str(), result->get_doc_id());
            *result_status = RESULT_FILTED_FINAL;
            ++(_final_filter_counters.at(i));
            return false;
        }
    }
    return true;
}

void ResultFilterHandler::end_for_search_filters(std::vector<ResultFilter*> * filters,
                                                 GeneralSearchResponse * response)
{
    PluginResponse pr;
    for (size_t i = 0; i < filters->size(); ++i) {
        ResultFilter * filter = filters->at(i);
        pr.Clear();
        pr.set_enable(false);
        filter->end_for_search(&pr);
        if (pr.enable()) {
            response->add_plugin_responses()->CopyFrom(pr);
        }
    }
}

void ResultFilterHandler::end_for_search(GeneralSearchResponse * response)
{
    end_for_search_filters(_cur_early_filters, response);
    end_for_search_filters(_cur_later_filters, response);
    end_for_search_filters(_cur_final_filters, response);
    if (FLAGS_enable_result_handler_counter) {
        // 增加计数的log
        string msg;
        for (size_t i = 0; i < _cur_early_filters->size(); ++i) {
            msg.append(_cur_early_filters->at(i)->get_name() + "[" +
                        UintToString(_early_filter_counters.at(i)) + "] ");
        }
        for (size_t i = 0; i < _cur_later_filters->size(); ++i) {
            msg.append(_cur_later_filters->at(i)->get_name() + "[" +
                        UintToString(_later_filter_counters.at(i)) + "] ");
        }
        for (size_t i = 0; i < _cur_final_filters->size(); ++i) {
            msg.append(_cur_final_filters->at(i)->get_name() + "[" +
                        UintToString(_final_filter_counters.at(i)) + "] ");
        }
        PluginResponse * pr = response->add_plugin_responses();
        pr->set_enable(true);
        pr->set_name("ResultFilterHandler");
        pr->set_information(msg);
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=80: */
