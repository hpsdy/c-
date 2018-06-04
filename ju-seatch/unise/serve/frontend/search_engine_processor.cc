// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/frontend/search_engine_processor.h"
#include <map>
#include "google/protobuf/text_format.h"
#include "serve/frontend/ctpl/search_engine.ctpl.h"
#include "ctemplate/template.h"
#include "ctemplate/template_modifiers.h"
#include "util/util.h"
#include "unise/base.h"
#include "retri/backend_query_builder.h"
#include "Configure.h"

DECLARE_int32(retrieve_max_depth);
DECLARE_int32(recall_max_docs);
DECLARE_string(conf_fpath);
DECLARE_string(conf_fname);
DECLARE_int64(communicate_timeout);

namespace unise {

using ctemplate::TemplateDictionary;
using ctemplate::Template;
using std::vector;
using std::string;
using std::map;

bool SearchEngineProcessor::Init() {
    comcfg::Configure conf;
    std::string server_address;
    std::string port_str;
    if (conf.load(FLAGS_conf_fpath.c_str(), FLAGS_conf_fname.c_str()) != 0) {
        UWARNING("[\tlvl=FOLLOW\t] Failed to load conf file: %s/%s.", FLAGS_conf_fpath.c_str(),FLAGS_conf_fname.c_str());
        return false;
    }
    // 读取unise的server配置，获取rpc端口  
    try {
        server_address = conf["RpcServer"]["ServerAddress"].to_cstr();
    } catch (comcfg::ConfigException & e) {
        UWARNING("[\tlvl=FOLLOW\t] illegal Configure for SearchEngineProcessor:%s, skip it", e.what());
        return false;
    }
    size_t pos = server_address.find(":", 0);
    if (pos == std::string::npos || pos == server_address.size() - 1) {
        UWARNING("[\tlvl=FOLLOW\t] illegal Configure for SearchEngineProcessor, skip it");
        return false;
    }
    port_str = server_address.substr(pos + 1); 
    server_address = "127.0.0.1:";
    server_address += port_str;
    _server_address=server_address;

    bhp::Controller* rpc_controller = new (std::nothrow) bhp::Controller();
    if (rpc_controller) {
        _controller.reset(rpc_controller);
    } else {
        UWARNING("[\tlvl=FOLLOW\t] allocate Controlrpc_channel failed!");
        return false;
    }

    return true;
}

bool SearchEngineProcessor::HandleHttpRequest(const Request& request, Respond *respond) {
    GeneralSearchRequest srequest;
    TemplateDictionary dict("PAGE");
    RenderScript(&dict);
    RenderInput(request, &dict, &srequest);
    // Search here
    GeneralSearchResponse sresponse;
    // get_retrieve_timeout
    int32_t retrieve_timeout = GetIntUrlParameter(request, "retrieve_timeout", 100);
    int32_t time_out = retrieve_timeout + FLAGS_communicate_timeout;
    // set timeout
    bhp::ChannelOptions t_options;
    t_options.connect_timeout_ms = time_out; 
    t_options.timeout_ms = time_out;
    // malloc rpc_channel
    bhp::Channel* rpc_channel = new (std::nothrow) bhp::Channel();
    if (rpc_channel) {
        _channel.reset(rpc_channel);
    } else {
        UWARNING("[\tlvl=FOLLOW\t] allocate Channel failed!");
        return false;
    }
    if (0 != _channel->Init(_server_address.c_str(), &t_options)) {
        UWARNING("[\tlvl=FOLLOW\t] init Channel failed!");
        return false;
    }
    UniseService_Stub* srv_stub = new (std::nothrow) UniseService_Stub(_channel.get());
    if (srv_stub) {
        _stub.reset(srv_stub);
    } else {
        UWARNING("[\tlvl=FOLLOW\t] allocate UniseService_Stub failed!");
        return false;
    }
    // ToDo improve this later
    sresponse.set_status_code(unise::kStatusError);
    sresponse.set_status_msg("Rpc failed.");
    _stub->Search((google::protobuf::RpcController*)_controller.get(), &srequest, &sresponse, NULL);
    if (_controller->Failed()) {
        std::string ErrorStr = "failed[RpcErrorText:";
        ErrorStr += _controller->ErrorText();
        ErrorStr += "]";
        dict.SetValue("RPC_INFO",ErrorStr);
    } else {
        dict.SetValue("RPC_INFO","succ");
    }
    dict.SetValue("STATUS_CODE",IntToString(sresponse.status_code()));
    dict.SetValue("STATUS_MSG",sresponse.status_msg());
    _controller->Reset();
    RenderResultOutput(&dict, sresponse);
    // send the http respond
    string output;
    GetTemplate()->Expand(&output, &dict);
    respond->AddContent(output);
    return true;
}

const Template* SearchEngineProcessor::GetTemplate() const {
    Template::StringToTemplateCache("search-engine-ctpl",
            search_engine_ctpl);
    return Template::GetTemplate("search-engine-ctpl",
            ::ctemplate::DO_NOT_STRIP);
}

void SearchEngineProcessor::RenderScript(TemplateDictionary* dict) {
    dict->ShowSection("SCRIPT");
}

void SearchEngineProcessor::set_experiments(const std::string& exp, SearchParams * sp) {
    if (!exp.length()) {
        return;
    }
    UNOTICE("experiments:%s", exp.c_str());
    vector<string> kv_list;
    string kv_pair_sep(",");
    string kv_sep(":");
    string experiments(exp);
    // 判断是否有定义KV对和KV之间的分隔符
    // 如果定义格式非法，那么就当作没有定义
    if (exp.length() > 3 && exp[0] == '-') {
        kv_pair_sep = exp.substr(1, 1);
        kv_sep = exp.substr(2, 1);
        experiments = exp.substr(3);
        UNOTICE("kv_pair_sep[%s] kv_sep[%s] experiments[%s]",
                 kv_pair_sep.c_str(), kv_sep.c_str(), experiments.c_str());
    }
    string_split(experiments, kv_pair_sep, &kv_list);
    for (size_t i = 0; i < kv_list.size(); ++i) {
        vector<string> kv_pair;
        string_split(kv_list.at(i), kv_sep, &kv_pair);
        Experiment * ep = sp->add_experiments();
        if (kv_pair.size() > 0) {
            ep->set_key(kv_pair.at(0));
        }
        if (kv_pair.size() > 1) {
            ep->set_value(kv_pair.at(1));
        }
    }
}

void SearchEngineProcessor::set_sort_params(const std::string& sort_params,
                                            SearchParams * search_params) {

    if (!sort_params.length()) {
        return;
    }
    vector<string> kv_list;
    string_split(sort_params, ",", &kv_list);
    for (size_t i = 0; i < kv_list.size(); ++i) {
        vector<string> kv_pair;
        string_split(kv_list.at(i), ":", &kv_pair);
        SortParam * sort_param = search_params->add_sort_params();
        if (kv_pair.size() > 0) {
            sort_param->set_annotation_name(kv_pair.at(0));
        }
        bool asc = true;
        if (kv_pair.size() > 1) {
            asc = kv_pair.at(1) == "true" ? true : false;
        }
        sort_param->set_ascending(asc);
    }
}




bool SearchEngineProcessor::RenderInput(const Request& request,
        TemplateDictionary* dict, GeneralSearchRequest* srequest) {
    dict->ShowSection("INPUT");
    // get parameters first
    string query = GetUrlParameter(request, "query", "");
    string experiments = GetUrlParameter(request, "experiments", "");
    string raw_query = GetUrlParameter(request, "raw_query", "");
    int num_results = GetIntUrlParameter(request, "num_results", 10);
    int32_t start_result = GetIntUrlParameter(request, "start_result", 1);
    uint64_t start_docid = GetUint64UrlParameter(request, "start_docid", 0ULL);
    int32_t retrieve_timeout = GetIntUrlParameter(request, "retrieve_timeout", 100);
    int32_t retrieve_depth = GetIntUrlParameter(request, "retrieve_depth",
                FLAGS_retrieve_max_depth);
    int32_t recall_docs = GetIntUrlParameter(request, "recall_docs",
                FLAGS_recall_max_docs);
    uint64_t session_id = GetUint64UrlParameter(request, "session_id", 0ULL);
    uint64_t business_id = GetUint64UrlParameter(request, "business_id", 0ULL);
    uint64_t sample_id = GetUint64UrlParameter(request, "sample_id", 0ULL);
    string sort_params = GetUrlParameter(request, "sort_params", "");
    string range_restriction_annotation = GetUrlParameter(request, "range_restriction_annotation", "");
    int64_t range_min = GetInt64UrlParameter(request, "range_min", 0);
    int64_t range_max = GetInt64UrlParameter(request, "range_max", 0);

    // decode the query
    string decoded;
    if (false == Request::url_decode(query, decoded)) {
        return false;
    }
    query.swap(decoded);

    // decode the raw_query
    if (false == Request::url_decode(raw_query, decoded)) {
        return false;
    }
    raw_query.swap(decoded);

    // decode the experiments
    decoded.clear();
    if (false == Request::url_decode(experiments, decoded)) {
        return false;
    }
    experiments.swap(decoded);

    // decode the sort_params
    decoded.clear();
    if (false == Request::url_decode(sort_params, decoded)) {
        return false;
    }
    sort_params.swap(decoded);


    // construct the GeneralServletRequest
    if (query != "") {
        // 如果没有赋值query，那么不设置query
        srequest->set_query(query);
    }
    if (raw_query != "") {
        srequest->set_raw_query(raw_query);
    }
    // build the query tree
    bool query_build_ret = false;
    QueryNode * query_tree = srequest->mutable_query_tree();
    if (query.size() > 0 && query[0] == 'P') {
        query_build_ret = google::protobuf::TextFormat::ParseFromString(query.substr(1),
                                                                        query_tree);
    } else {
        BackendQueryBuilder builder;
        query_build_ret = builder.build(query, query_tree);
    }
    if (query_build_ret == false) {
        UNOTICE("Build QueryTree from query fail:%s", query.c_str());
        // 如果构造查询树失败，那么，清空，由检索底层决定如何处理
        // 这里仅仅是debug功能
        srequest->clear_query_tree();
    }
    srequest->clear_query();
    srequest->set_num_results(num_results);
    srequest->set_start_result(start_result);
    srequest->set_start_docid(start_docid);
    srequest->set_session_id(session_id);
    srequest->set_business_id(business_id);
    srequest->set_sample_id(sample_id);

    SearchParams * search_params = srequest->mutable_search_params();

    // 设置experiments
    set_experiments(experiments, search_params);
    
    // 构建restriction annotation
    // TODO(wangguangyuan) : 支持多个range
    if (range_restriction_annotation != "") {
        UNOTICE("range_restriction: annotation[%s] min[%lld] max[%lld]",
                    range_restriction_annotation.c_str(), range_min, range_max);
        RangeRestriction * rr = search_params->add_range_restrictions();
        rr->set_annotation_name(range_restriction_annotation);
        NumberSpec * ns = rr->mutable_number_spec();
        ns->set_min(range_min);
        ns->set_max(range_max);
    }

    // 构建sort params
    set_sort_params(sort_params, search_params);

    search_params->set_retrieve_timeout(retrieve_timeout);
    search_params->set_retrieve_depth(retrieve_depth);
    search_params->set_recall_docs(recall_docs);
    // render the input, so respond contains the query parameters also
    dict->SetValue("LAST_QUERY", query);
    dict->SetValue("LAST_NUM_RESULTS", IntToString(num_results));
    dict->SetValue("LAST_RAW_QUERY", raw_query);
    dict->SetValue("LAST_EXPERIMENTS", experiments);
    dict->SetValue("LAST_START_RESULT", IntToString(start_result));
    dict->SetValue("LAST_START_DOCID", Uint64ToString(start_docid));
    dict->SetValue("LAST_SESSION_ID", Uint64ToString(session_id));
    dict->SetValue("LAST_BUSINESS_ID", Uint64ToString(business_id));
    dict->SetValue("LAST_SAMPLE_ID", Uint64ToString(sample_id));
    dict->SetValue("LAST_RETRIEVE_TIMEOUT", IntToString(retrieve_timeout));
    dict->SetValue("LAST_RETRIEVE_DEPTH", IntToString(retrieve_depth));
    dict->SetValue("LAST_RECALL_DOCS", IntToString(recall_docs));
    dict->SetValue("LAST_SORT_PARAMS", sort_params);
    dict->SetValue("LAST_RANGE_RESTRICTION_ANNOTATION", range_restriction_annotation);
    dict->SetValue("LAST_RANGE_MIN", Int64ToString(range_min));
    dict->SetValue("LAST_RANGE_MAX", Int64ToString(range_max));
    return true;
}

bool SearchEngineProcessor::RenderResultOutput(
        TemplateDictionary* dict, const GeneralSearchResponse& sresponse) {
    // add SearchEngine stat info
    dict->ShowSection("RESULT_OUTPUT");
    dict->SetValue("NUM_RESULTS",
                IntToString(sresponse.search_results_size()));
    dict->SetValue("EXACT_NUM_RESULTS",
                UintToString(sresponse.exact_num_results()));
    dict->SetValue("EST_NUM_RESULTS",
                Int64ToString(sresponse.estimated_num_results()));
    dict->SetValue("DOCS_RETRIEVED",
                Int64ToString(sresponse.docs_retrieved()));
    dict->SetValue("DOCS_RECALLED",
                Int64ToString(sresponse.docs_recalled()));
    dict->SetValue("SEARCH_TIME",
                Int64ToString(sresponse.search_time()));
    // TODO (wangguangyuan) : recurse show all the EUR in frontend
    // add PluginResponse
    for (int i = 0; i < sresponse.plugin_responses_size(); ++i) {
        const PluginResponse& pr = sresponse.plugin_responses(i);
        TemplateDictionary* pr_dict = dict->AddSectionDictionary("SE_PLUGIN_RESPONSE");
        pr_dict->SetValue("SE_PLUGIN_NAME", pr.name());
        pr_dict->SetValue("SE_PLUGIN_ENABLE", BoolToString(pr.enable()));
        pr_dict->SetValue("SE_PLUGIN_INFORMATION", pr.information());
    }

    // add EngineUnit stat info
    for (int i = 0; i < sresponse.engine_unit_responses_size(); ++i) {
        const EngineUnitResponse& eur = sresponse.engine_unit_responses(i);
        TemplateDictionary* result_dict =
            dict->AddSectionDictionary("ENGINE_UNIT_RESPONSE");
        result_dict->SetValue("ENGINE_UNIT_NAME", eur.name());
        result_dict->SetValue("ENGINE_UNIT_TYPE", eur.type());
        result_dict->SetIntValue("ENGINE_UNIT_NUM_RESULTS",
                    eur.num_results());
        result_dict->SetValue("ENGINE_UNIT_EST_NUM_RESULTS",
                    Int64ToString(eur.estimated_num_results()));
        result_dict->SetValue("ENGINE_UNIT_DOCS_RETRIEVED",
                    Int64ToString(eur.docs_retrieved()));
        result_dict->SetValue("ENGINE_UNIT_DOCS_RECALLED",
                    Int64ToString(eur.docs_recalled()));
        result_dict->SetIntValue("ENGINE_UNIT_SEARCH_TIME", eur.search_time());
        for (int j = 0; j < eur.plugin_responses_size(); ++j) {
            const PluginResponse& pr = eur.plugin_responses(j);
            TemplateDictionary* pr_dict =
                result_dict->AddSectionDictionary("PLUGIN_RESPONSE");
            pr_dict->SetValue("PLUGIN_NAME", pr.name());
            pr_dict->SetValue("PLUGIN_ENABLE", BoolToString(pr.enable()));
            pr_dict->SetValue("PLUGIN_INFORMATION", pr.information());
        }
    }
    // add result
    for (int i = 0; i < sresponse.search_results_size(); ++i) {
        const SearchResult& result = sresponse.search_results(i);
        TemplateDictionary* result_dict =
            dict->AddSectionDictionary("ONE_RESULT");
        result_dict->SetValue("RESULT_ID", IntToString(i + 1));
        result_dict->SetValue("RESULT_DOCID", Uint64ToString(result.docid()));
        result_dict->SetValue("RESULT_SCORE", Int64ToString(result.score()));
        string snippet = "";
        for (int j = 0; j < result.snippets_size(); ++j) {
            const Snippet & snip = result.snippets(j);
            snippet += "Snippet[" + snip.key() + "]:" + snip.value() + "<br>";
        }
        result_dict->SetValue("RESULT_SNIPPET", snippet);
    }
    
    // 导航栏
    TemplateDictionary* result_dict = dict->AddSectionDictionary("ONE_PAGE_INFO_LEAD");
    std::string page_name_link = "";
    for (uint32_t i = 0; i < _unise_frontend_proc.size(); ++i) {
        if (_unise_frontend_proc[i].second == "search") {
            page_name_link += "<li class='active'><a href='" + _unise_frontend_proc[i].second + "' style='color:#01184A'>"
                + _unise_frontend_proc[i].first + "</a></li>";
        } else {
            page_name_link += "<li><a href='" + _unise_frontend_proc[i].second + "' style='color:#FFF'>"
                + _unise_frontend_proc[i].first + "</a></li>";
        }
    }
    result_dict->SetValue("PAGE_LEAD", page_name_link); 
    return true;
}

REGISTER_PAGEPROCESSOR(SearchEngineProcessor);
}  // namespace unise
