// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/frontend/monitor_processor.h"
#include <map>
#include "ctemplate/template.h"
#include "ctemplate/template_modifiers.h"
#include "unise/util.h"
#include "unise/base.h"
#include "serve/frontend/ctpl/monitor.ctpl.h"
#include "retri/backend_query_builder.h"

DECLARE_int32(monitor_record_queue_size);
DEFINE_string(monitor_number_state_keys, "search_time,docs_recalled,docs_retrieved",
            "the keys of the text_state_message to monitor");
DEFINE_string(monitor_text_state_keys, "start_date,proc_res,sys_free",
            "the keys of the number_state_message to monitor");

namespace unise {

using ctemplate::TemplateDictionary;
using ctemplate::Template;
using std::vector;
using std::string;
using std::map;

MonitorProcessor::MonitorProcessor() : _state_monitor(NULL) {
    _records.reset(new std::vector<tens_record_t>());
    _records->reserve(FLAGS_monitor_record_queue_size);
}

bool MonitorProcessor::Init() {
    // 只显示FLAGS指定的key的监控项
    string_split(FLAGS_monitor_number_state_keys, ",", &_number_keys);
    string_split(FLAGS_monitor_text_state_keys, ",", &_text_keys);
    _state_monitor = Singleton<StateMonitor>::get();
    if (_state_monitor == NULL) {
        return false;
    } else {
        return true;
    }
}

bool MonitorProcessor::HandleHttpRequest(const Request& request, Respond *respond) {
    _mem_info.get_proc_mem_info();
    Singleton<StateMonitor>::get()->add_text_state_message("proc_res",
            Uint64ToString(_mem_info._proc_res));
    _mem_info.get_sys_mem_info();
    Singleton<StateMonitor>::get()->add_text_state_message("sys_free",
            Uint64ToString(_mem_info._sys_free));
    GeneralSearchRequest srequest;
    TemplateDictionary dict("PAGE");
    RenderScript(&dict);
    RenderInput(request, &dict);
    RenderResultOutput(&dict);
    // send the http respond
    string output;
    GetTemplate()->Expand(&output, &dict);
    respond->AddContent(output);
    return true;
}

const Template* MonitorProcessor::GetTemplate() const {
    Template::StringToTemplateCache("monitor-ctpl",
            monitor_ctpl);
    return Template::GetTemplate("monitor-ctpl",
            ::ctemplate::DO_NOT_STRIP);
}

void MonitorProcessor::RenderScript(TemplateDictionary* dict) {
    dict->ShowSection("SCRIPT");

    // 构造所有number统计的chart的js对象
    std::string charts_js;
    for (size_t i = 0; i < _number_keys.size(); ++i) {
        charts_js.append("{"
                    "id:'chart_" + _number_keys[i] + "',"
                    "title:'" + _number_keys[i] + "',");

        _records->clear();
        _state_monitor->get_number_state_message(
                    _number_keys[i],
                    FLAGS_monitor_record_queue_size,
                    _records.get());

        std::string x_l("x_l:[");
        std::string min_l("min_l:[");
        std::string max_l("max_l:[");
        std::string avg_l("avg_l:[");
        std::string cnt_l("cnt_l:[");
        for (size_t i = 0; i < _records->size(); ++i) {
            const tens_record_t & r = _records->at(i);
            x_l.append("'" + get_date(r.timestamp) + "',");
            min_l.append(Uint64ToString(r.min) + ",");
            max_l.append(Uint64ToString(r.max) + ",");
            avg_l.append(Uint64ToString(static_cast<uint64_t>(r.avg)) + ",");
            cnt_l.append(Uint64ToString(r.count) + ",");
        }
        x_l.append("],");
        min_l.append("],");
        max_l.append("],");
        avg_l.append("],");
        cnt_l.append("]");
        charts_js.append(x_l + min_l + max_l + avg_l + cnt_l + "},");
    }
    dict->SetValue("VAR_JS", "var charts=[" + charts_js + "];");
}

bool MonitorProcessor::RenderInput(
            const Request& request,
            TemplateDictionary* dict) {
    dict->ShowSection("INPUT");
    return true;
}


bool MonitorProcessor::RenderResultOutput(TemplateDictionary* dict) {
    dict->ShowSection("RESULT_OUTPUT");
    dict->SetValue("START_DATE", _state_monitor->get_text_state_message("start_date"));
    std::string host_name;
    get_host_name(host_name);
    dict->SetValue("IP", host_name);

    // 填充所有的key-value 信息
    for (size_t i = 0; i < _text_keys.size(); ++i) {
        TemplateDictionary* result_dict =
            dict->AddSectionDictionary("MESSAGE_LIST");
        result_dict->SetValue("MESSAGE_KEY", _text_keys[i]);
        result_dict->SetValue(
                    "MESSAGE_VALUE",
                    _state_monitor->get_text_state_message(_text_keys[i]));
    }

    // 获取所有的number统计的key名称
    for (size_t i = 0; i < _number_keys.size(); ++i) {
        TemplateDictionary* result_dict = dict->AddSectionDictionary("CHART_LIST");
        result_dict->SetValue("CHART_ID", "chart_" + _number_keys[i]);
    }
    
    // 导航栏
    TemplateDictionary* result_dict = dict->AddSectionDictionary("ONE_PAGE_INFO_LEAD");
    std::string page_name_link = "";
    for (uint32_t i = 0; i < _unise_frontend_proc.size(); ++i) {
        if (_unise_frontend_proc[i].second == "monitor") {
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

REGISTER_PAGEPROCESSOR(MonitorProcessor);
}  // namespace unise
