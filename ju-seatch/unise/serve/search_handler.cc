// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "unise/search_handler.h"
#include <vector>
#include <algorithm>
#include "gflags/gflags.h"
#include "unise/general_servlet.pb.h"
#include "unise/engine_unit.h"
#include "unise/base.h"
#include "unise/result_adapter.h"
#include "unise/query_rewriter.h"
#include "serve/engine_unit_manager.h"
#include "serve/search_engine.h"
#include "serve/search_handler_helper.h"
#include "util/util.h"

DECLARE_bool(enable_estimated_num_results);

DEFINE_int32(exact_num_results, 3000, "how many result can be showed when paging");

namespace unise {

/**
 * @brief 根据docid进行去重,search result无level id
 * @note 内部使用
 */
class DocIdLess {
public:
    bool operator()(const SearchResult* a, const  SearchResult* b) const {
        // docid相同时，score大的排前面，这样子可以把score小的去重掉
        if (a->docid() == b->docid()) {
            return a->score() > b->score();
        } else {
            return a->docid() < b->docid();
        }
    }
};

/**
 * @brief 根据docid和levelid进行去重
 * @note 内部使用
 */
class DocIdWithLevelidLess {
public:
    bool operator()(const SearchResult* a, const  SearchResult* b) const {
        if (a->docid() == b->docid()) {
            if (a->levelid() == b->levelid()) {
                return a->score() > b->score();
            } else {
                return a->levelid() < b->levelid();
            }
        } else {
            return a->docid() < b->docid();
        }
    }
};

class ResultEqual {
public:
    bool operator()(const SearchResult* a, const SearchResult* b) const {
        return a->docid() == b->docid();
    }
};

class ResultWithLevelidEqual {
public:
    bool operator()(const SearchResult* a, const SearchResult* b) const {
        return a->docid() == b->docid() && a->levelid() == b->levelid();
    }
};

bool ResultLess::operator()(const SearchResult* a, const  SearchResult* b) const {
    if (a->score() == b->score()) {
        if (a->docid() == b->docid()) {
            if (a->has_levelid() && b->has_levelid()) {
                return a->levelid() < b->levelid();
            } else if (!a->has_levelid() && !b->has_levelid()) {
                // 如果都没有，避免随机，采用地址
                return a < b;
            } else {
                // 没有levelid的排在前面
                return b->has_levelid();
            }
        } else {
            return a->docid() < b->docid();
        }
    } else {
        return a->score() > b->score();
    }
}

SearchHandler::SearchHandler() {
    _search_handler_helper = new SearchHandlerHelper();
}

SearchHandler::~SearchHandler() {
    delete _search_handler_helper;
    for (ResultAdapterMap::iterator iter = _result_adapter_map.begin();
                iter != _result_adapter_map.end(); 
                ++iter) {
        delete iter->second;
    }
    for (QueryRewriterMap::iterator iter = _query_rewriter_map.begin(); 
                iter != _query_rewriter_map.end(); 
                ++iter) {
        delete iter->second;
    }
}

/**
 * @note 需要catch exception
 */
bool SearchHandler::init_query_rewriter(const comcfg::ConfigUnit& conf) {
    if (conf["QueryRewriter"].selfType() == comcfg::CONFIG_ERROR_TYPE) {
        // 如果没有配置query rewriter，那么就不走query rewriter的逻辑
        UNOTICE("skip QueryRewriter");
        return true;
    }
    bool has_default = false;
    for (uint32_t i = 0; i < conf["QueryRewriter"].size(); ++i) {
        uint64_t sid = conf["QueryRewriter"][i]["sample_id"].to_uint64();
        std::string plugin(conf["QueryRewriter"][i]["plugin"].to_cstr());
        if (_query_rewriter_map.end() != _query_rewriter_map.find(sid)) {
            UFATAL("conflict QueryRewriter sample_id[%llu]", sid);
            return false;
        }
        QueryRewriter * query_rewriter = QueryRewriterFactory::get_instance(
                    plugin.c_str());
        if (!query_rewriter) {
            UFATAL("Failed to create QueryRewriter[%s]", plugin.c_str());
            return false;
        }
        if (!query_rewriter->init(conf["QueryRewriter"][i])) {
            UFATAL("Failed to init QueryRewriter[%s]", plugin.c_str());
            delete query_rewriter;
            return false;
        }
        _query_rewriter_map.insert(std::make_pair(sid, query_rewriter));
        if (0 == sid) {
            has_default = true;
        }
        UNOTICE("init sid[%llu] QueryRewriter[%s] succ", sid, plugin.c_str());
    }
    if (!has_default) {
        UFATAL("miss default query rewriter");
        return false;
    }
    return true;
}

bool SearchHandler::init_result_adapter(const comcfg::ConfigUnit& conf) {
    if (conf["ResultAdapter"].selfType() == comcfg::CONFIG_ERROR_TYPE) {
        // 必须配置query rewriter
        UFATAL("miss ResultAdapter");
        return false;
    }
    bool has_default = false;
    for (uint32_t i = 0; i < conf["ResultAdapter"].size(); ++i) {
        uint64_t sid = conf["ResultAdapter"][i]["sample_id"].to_uint64();
        std::string plugin(conf["ResultAdapter"][i]["plugin"].to_cstr());
        if (_result_adapter_map.end() != _result_adapter_map.find(sid)) {
            UFATAL("conflict ResultAdapter sample_id[%u]", sid);
            return false;
        }
        ResultAdapter* result_adapter = ResultAdapterFactory::get_instance(
                    plugin.c_str());
        if (!result_adapter) {
            UFATAL("Failed to get ResultAdapter[%s]", plugin.c_str());
            return false;
        }
        if (!result_adapter->init(conf["ResultAdapter"][i])) {
            delete result_adapter;
            UFATAL("Failed to init ResultAdapter[%s]");
            return false;
        }
        _result_adapter_map.insert(std::make_pair(sid, result_adapter));
        if (0 == sid) {
            has_default = true;
        }
        UNOTICE("init sid[%llu] ResultAdapter[%s] succ", sid, plugin.c_str());
    }
    if (!has_default) {
        UFATAL("Failed to init result adapter, "
                    "because there is not a default result adapter");
        return false;
    }
    return true;
}

QueryRewriter * SearchHandler::get_query_rewriter(uint64_t sample_id) {
    if (_query_rewriter_map.empty()) {
        return NULL;
    } else {
        QueryRewriterMap::iterator it = _query_rewriter_map.find(sample_id); 
        if (_query_rewriter_map.end() == it) {
            UTRACE("Failed to find query rewriter, smaple_id:%u, use default", sample_id);
            it = _query_rewriter_map.find(DEFAULT_SAMPLE_ID); 
            GOOGLE_DCHECK(it != _query_rewriter_map.end());
        }
        return it->second;
    }
}

ResultAdapter * SearchHandler::get_result_adapter(uint64_t sample_id) {
    if (_result_adapter_map.empty()) {
        return NULL;
    } else {
        ResultAdapterMap::iterator it = _result_adapter_map.find(sample_id); 
        if (_result_adapter_map.end() == it) {
            UTRACE("Failed to find result adapter, smaple_id:%u, use default", sample_id);
            it = _result_adapter_map.find(DEFAULT_SAMPLE_ID); 
            GOOGLE_DCHECK(it != _result_adapter_map.end());
        }
        return it->second;
    }
}

bool SearchHandler::init(const comcfg::ConfigUnit& conf) {
    try {
        //init search handler helper
        if (!_search_handler_helper->init(DEFAULT_SH_HELPER_RESPONSE_QUEUE_SIZE)) {
            UFATAL("Failed to init search handler helper");
            return false;
        }

        // 初始化query rewriter
        if (!init_query_rewriter(conf)) {
            UFATAL("init query rewriter failed");
            return false;
        }

        // 初始化result adapter
        if (!init_result_adapter(conf)) {
            UFATAL("init result_adapter failed");
            return false;
        }
    } catch(comcfg::ConfigException &e) {
        UFATAL("illegal Configure for SearchHandler:%s", e.what());
        return false;
    }
    return true;
}

void SearchHandler::search(const GeneralSearchRequest* request,
        GeneralSearchResponse* response) {
    StopWatch search_stop_watch;
    uint64_t sample_id = DEFAULT_SAMPLE_ID;
    if (request->has_sample_id()) {
        sample_id = request->sample_id();
    }

    // 调用query rewrite逻辑
    const GeneralSearchRequest * new_request = request;
    GeneralSearchRequest rewrite_request;
    // 根据sample_id，获取QueryRewriter
    // 只有当配置了query rewriter的时候，才进行rewrite
    QueryRewriter * cur_rewriter = get_query_rewriter(sample_id);
    if (cur_rewriter) {
        cur_rewriter->rewrite(request, &rewrite_request);
        new_request = &rewrite_request;
        request->set_raw_query(new_request->raw_query());
    }

    // 检索
    std::vector<GeneralSearchResponse*> responses;
    search_internal(new_request, &responses);
    UDEBUG("Finish SearchInternal, totally %u responses", responses.size());
    //汇总结果，排序，去重
    std::vector<SearchResult*> results;
    merge(responses, &results, response);
    UDEBUG("Finish Merge, totally %u results after merge", results.size());
    //调整结果（选取需要结果，去除不需要结果）
    std::vector<const SearchResult*> selected_results;
    std::vector<const SearchResult*> dropped_results;

    // 根据sample_id，获取ResultAdapter,进行结果调整
    ResultAdapter * cur_adapter = get_result_adapter(sample_id);
    GOOGLE_DCHECK(cur_adapter);
    cur_adapter->init_for_search(new_request, response);
    cur_adapter->adapt(results, &selected_results, &dropped_results);
    PluginResponse pr;
    pr.set_enable(false);
    cur_adapter->end_for_search(&pr);
    if (pr.enable()) {
        response->add_plugin_responses()->CopyFrom(pr);
    }
    size_t selected_results_size = selected_results.size();
    UDEBUG("Finish Adapt, totally %u selected results, %u dropped results",
                selected_results_size, dropped_results.size());

    //翻页
    page_turn(new_request, selected_results, response);
    UDEBUG("Finish PageTurn, totally %u results left", 
        response->search_results_size());

    double search_time = search_stop_watch.read();
    UDEBUG("SearchHandler: search done with %0.3f ms", search_time);

    // 从请求中获取 exact_num_results 参数
    int32_t exact_num_results = 0;
    if (new_request->has_search_params()) {
        const SearchParams & tmp_sp = new_request->search_params();
        if (tmp_sp.has_exact_num_results()) {
            exact_num_results = tmp_sp.exact_num_results(); 
        }
    }
    if (exact_num_results == 0) {
        exact_num_results = FLAGS_exact_num_results;
    }
    // 设置相关参数
    // 最多支持翻页可见的结果数用FLAGS_exact_num_results表示
    if (selected_results_size > static_cast<size_t>(exact_num_results)) {
        response->set_exact_num_results(exact_num_results);
    } else {
        response->set_exact_num_results(selected_results_size);
    }

    if (!FLAGS_enable_estimated_num_results ||
        selected_results_size < static_cast<size_t>(exact_num_results)) {
        response->set_estimated_num_results(selected_results_size);
    } // else 用户无法翻页来校验，直接采用估算结果数

    response->set_search_time(static_cast<int>(search_time));
    response->set_name(get_name());
    response->set_type(get_type());
    //归还临时资源
    for (size_t i = 0; i < responses.size(); ++i) {
        return_response(responses[i]);
    }
    response->set_status_code(unise::kStatusOK);
    response->set_status_msg("Hello, UniSE");

    cur_adapter->ultimatum(*new_request, response);
}

void SearchHandler::merge(const std::vector<GeneralSearchResponse*> &org_responses,
        std::vector<SearchResult*>* results,
        GeneralSearchResponse* response)
{
    response->Clear();
    int64_t estimated_num_results = 0;
    int64_t docs_retrieved = 0;
    int64_t docs_recalled = 0;
    std::vector<SearchResult *> results_with_levelid;
    std::vector<SearchResult *> results_without_levelid;
    for (size_t i = 0; i < org_responses.size(); ++i) {
        //将有levelid和无levelid的results分开
        for (int j = 0; j < org_responses[i]->search_results_size(); ++j) {
            if ((org_responses[i]->search_results(j)).has_levelid()) {
                results_with_levelid.push_back(org_responses[i]->mutable_search_results(j));
            } else {
                results_without_levelid.push_back(org_responses[i]->mutable_search_results(j));
            }
        }
        //附加数据汇总
        estimated_num_results += org_responses[i]->estimated_num_results();
        docs_retrieved += org_responses[i]->docs_retrieved();
        docs_recalled += org_responses[i]->docs_recalled();
        //GSR to EUR, 添加到response中
        EngineUnitResponse *engine_unit_response = response->add_engine_unit_responses();
        engine_unit_response->set_name(org_responses[i]->name());
        engine_unit_response->set_type(org_responses[i]->type());
        engine_unit_response->set_num_results(org_responses[i]->search_results_size());
        engine_unit_response->set_estimated_num_results(org_responses[i]->estimated_num_results());
        engine_unit_response->set_docs_retrieved(org_responses[i]->docs_retrieved());
        engine_unit_response->set_docs_recalled(org_responses[i]->docs_recalled());
        engine_unit_response->set_search_time(org_responses[i]->search_time());
        for (int j = 0; j < org_responses[i]->engine_unit_responses_size(); ++j) {
            EngineUnitResponse *eu_resp = engine_unit_response->add_engine_unit_responses();
            eu_resp->CopyFrom(org_responses[i]->engine_unit_responses(j));
        }
        PluginResponse *parent_response_plug = response->mutable_log_info();
        for (int j = 0; j < org_responses[i]->plugin_responses_size(); ++j)
        {
            PluginResponse *plug_resp = engine_unit_response->add_plugin_responses();
            PluginResponse plug_info = org_responses[i]->plugin_responses(j)；
            for (int k = 0; k < plug_info.trigger_type_size(); ++k)
            {
                Experiment *exper = parent_response_plug->add_trigger_type();
                exper->CopyFrom(plug_info.trigger_type(k));
            }
            plug_info.clear_trigger_type();
            if(!parent_response_plug->has_context_log() && plug_info.has_context_log())
            {
                parent_response_plug->set_context_log(plug_info.context_log());
            }
            plug_info.clear_context_log();
            plug_resp->CopyFrom(plug_info);
            if(!parent_response_plug->has_name())
            {
                parent_response_plug->set_name("log_info");
                parent_response_plug->set_information("log_info");
                parent_response_plug->set_enable(true);
            }    
        }
    }

    UDEBUG("Before uniq, totally %u results", results_with_levelid.size() + 
        results_without_levelid.size());

    //对有levelid的results排序
    sort(results_with_levelid.begin(), results_with_levelid.end(), 
        DocIdWithLevelidLess());
    //对有levelid的results去重
    std::vector<SearchResult*>::iterator end_iter_a = unique(
        results_with_levelid.begin(),
        results_with_levelid.end(), 
        ResultWithLevelidEqual());

    // 对无levelid的results排序
    sort(results_without_levelid.begin(), results_without_levelid.end(), DocIdLess());
    // 对无levelid的results去重
    std::vector<SearchResult*>::iterator end_iter_b = unique(
        results_without_levelid.begin(),
        results_without_levelid.end(), 
        ResultEqual());

    results->reserve(end_iter_a - results_with_levelid.begin() +
                end_iter_b - results_without_levelid.begin());
    results->insert(results->end(), results_with_levelid.begin(), end_iter_a);
    results->insert(results->end(), results_without_levelid.begin(), end_iter_b);
    UDEBUG("After uniq, %u results left", results->size());

    // 归并有levelid和无levelid的results到最终的结果
    sort(results->begin(), results->end(), ResultLess());

    //设置相关参数
    response->set_estimated_num_results(estimated_num_results);
    response->set_docs_retrieved(docs_retrieved);
    response->set_docs_recalled(docs_recalled);
}

void SearchHandler::page_turn(const GeneralSearchRequest* request,
                              const std::vector<const SearchResult*> &selected_results,
                              GeneralSearchResponse* response)
{
    int32_t selected_num = selected_results.size();
    if (selected_num <= 0) {
        return;
    }
    int32_t start_result = request->start_result();
    if (start_result < 1) {
        start_result = 1;
    }
    int32_t num_results = request->num_results();
    int i, j;
    for (i = start_result - 1, j = 0;
                i < selected_num && j < num_results;
                ++i, ++j) {
        SearchResult *result = response->add_search_results();
        result->CopyFrom(*(selected_results[i]));
    }
    UDEBUG("selected_num=%d start_result=%d num_results=%d i=%d j=%d",
                selected_num, start_result, num_results, i, j);
}

EngineUnit * SearchHandler::get_engine_unit(const std::string& name) const
{
    return _engine_unit_manager->get_engine_unit(name);
}

GeneralSearchResponse* SearchHandler::get_response()
{
    return new GeneralSearchResponse();
    // return _search_handler_helper->pop_response();
}

void SearchHandler::return_response(GeneralSearchResponse* resp)
{
    delete resp;
    /*
    resp->Clear();
    _search_handler_helper->push_response(resp);
    */
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
