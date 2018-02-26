// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#include "serve/frontend/unise_frontend.h"
#include "gflags/gflags.h"
#include "serve/frontend/ctpl/default.ctpl.h"
#include "ctemplate/template.h"
#include "ctemplate/template_modifiers.h"
#include "util/util.h"

DEFINE_int32(unise_frontend_search_port, 8001,
        "the port of the unise frontend");
DEFINE_string(unise_page_processors, "SearchEngineProcessor,MonitorProcessor,BinlogProcessor,IndexProcessor",
        "the processors of the frontend");

using namespace std;

namespace unise {

using ctemplate::TemplateDictionary;
using ctemplate::Template;

void PageProcessor::SetUniseFrontendProc(const UniseFrontendProc& unise_frontend_proc) {
    _unise_frontend_proc = unise_frontend_proc;
}

bool PageProcessor::HasUrlParameter(const Request &request,
        const string& key) {
    return request.url_params().count(key) > 0;
}

const string PageProcessor::GetUrlParameter(const Request &request,
        const string& key,
        const string& default_value) {
    return HasUrlParameter(request, key) ? request.GetUrlParamValue(key) :
           default_value;
}

int PageProcessor::GetIntUrlParameter(const Request &request,
        const string& key,
        int default_value) {
    if (!HasUrlParameter(request, key)) { return default_value; }
    int result;
    if (!StringToInt(request.GetUrlParamValue(key).c_str(), &result)) {
        return default_value;
    }
    return result;
}

int64_t PageProcessor::GetInt64UrlParameter(const Request &request,
        const string& key,
        int64_t default_value) {
    if (!HasUrlParameter(request, key)) { return default_value; }
    int64_t result;
    if (!StringToInt64(request.GetUrlParamValue(key).c_str(), &result)) {
        return default_value;
    }
    return result;
}

uint64_t PageProcessor::GetUint64UrlParameter(const Request &request,
        const string& key,
        uint64_t default_value) {
    if (!HasUrlParameter(request, key)) { return default_value; }
    uint64_t result;
    if (!StringToUint64(request.GetUrlParamValue(key).c_str(), &result)) {
        return default_value;
    }
    return result;
}

void UniseFrontend::Init() {
    int32_t port = FLAGS_unise_frontend_search_port;
    http_server_.reset(new HttpServer(port, 100));
    http_server_->SetDftHandler(this, &UniseFrontend::HandleDefaultRequest);
    http_server_->AddHandler("/", this, &UniseFrontend::HandleDefaultRequest);
    // get PageProcessor from flags
    vector<string> processor_list;
    string_split(FLAGS_unise_page_processors, ",", &processor_list);
    for (size_t i = 0; i < processor_list.size(); i++) {
        PageProcessor * processor = PageProcessorFactory::get_instance(
                                    processor_list.at(i));
        if (processor != NULL && processor->Init()) {
            http_server_->AddHandler(processor->GetPath(), processor,
                    &PageProcessor::HandleHttpRequest);
            processors_.push_back(processor);
            UNOTICE("Init PageProcessor %u path:%s name:%s",
                    i, processor->GetName().c_str(), processor->GetPath().c_str());
        } else {
            UWARNING("[\tlvl=FOLLOW\t] Load PageProcessor:%s fail", processor_list.at(i).c_str());
        }
    }
    http_server_->SetRootPath("./");
    http_server_->start();
    UNOTICE("Frontend is now running on port:%d", port);
}

bool UniseFrontend::HandleDefaultRequest(
    const Request& request,
    Respond *respond) {
    TemplateDictionary dict("PAGE");
    dict.ShowSection("PAGE_LIST_TAG");
    // 导航home
    TemplateDictionary *result_dict
            = dict.AddSectionDictionary("ONE_PAGE_INFO_LEAD");
    std::string home_link = " <li class='active'><a href='/' style='color:#01184A'>Home</a></li>";
    result_dict->SetValue("PAGE_LEAD", home_link);
    dict.ShowSection("ONE_PAGE_INFO_LEAD");
    // all frontend proc
    std::vector<std::pair<std::string, std::string> > unise_frontend_proc;
    unise_frontend_proc.push_back(std::make_pair("Home", "/"));
    for (size_t i = 0; i < processors_.size(); ++i) {
        // 导航栏顶部
        result_dict = dict.AddSectionDictionary("ONE_PAGE_INFO_LEAD");
        std::string page_name_link = "<li><a href='" + processors_[i]->GetPath() + "' style='color:#FFF'>"
                                + processors_[i]->GetName() + "</a></li>";
        result_dict->SetValue("PAGE_LEAD", page_name_link);
        dict.ShowSection("ONE_PAGE_INFO_LEAD");
        
        // 导航表格内容
        result_dict = dict.AddSectionDictionary("ONE_PAGE_INFO");
        result_dict->SetValue("PAGE_ID", UintToString(i + 1));
        page_name_link = "<a href='" + processors_[i]->GetPath() + "'>"
                                + processors_[i]->GetName() + "</a>";
        result_dict->SetValue("PAGE_NAME", page_name_link);
        result_dict->SetValue("PAGE_DIR", processors_[i]->GetPath().c_str());
        result_dict->SetValue(
                "PAGE_INFO", processors_[i]->GetDescription().c_str());
        dict.ShowSection("ONE_PAGE_INFO");
        
        // 保存unise frontend已经启动的信息
        unise_frontend_proc.push_back(std::make_pair(processors_[i]->GetName(),
                                                     processors_[i]->GetPath()));
    }
    // all worker unise frontend proc
    for (size_t i = 0; i < processors_.size(); ++i) {
        processors_[i]->SetUniseFrontendProc(unise_frontend_proc);
    }
    string output;
    GetTemplate()->Expand(&output, &dict);
    respond->AddContent(output);
    return true;
}

const Template* UniseFrontend::GetTemplate() const {
    Template::StringToTemplateCache("default-ctpl",
            default_ctpl);
    return Template::GetTemplate("default-ctpl",
            ::ctemplate::DO_NOT_STRIP);
}

}  // namespace nidx
