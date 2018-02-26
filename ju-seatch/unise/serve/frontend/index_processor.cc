// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/frontend/index_processor.h"
#include "ctemplate/template.h"
#include "ctemplate/template_modifiers.h"
#include "gflags/gflags.h"
#include "unise/util.h"
#include "unise/base.h"
#include "unise/singleton.h"
#include "serve/frontend/ctpl/index.ctpl.h"
#include "index/forward_index.h"

namespace unise {
using ctemplate::TemplateDictionary;
using ctemplate::Template;
using std::string;

IndexProcessor::IndexProcessor() {}

IndexProcessor::~IndexProcessor() {}

bool IndexProcessor::Init() {
    _search_engine = Singleton<SearchEngine>::get();
    if (_search_engine == NULL) {
        return false;
    }
    return true;
}

bool IndexProcessor::HandleHttpRequest(const Request& request, Respond *respond) {
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

const Template* IndexProcessor::GetTemplate() const {
    Template::StringToTemplateCache("index-ctpl", index_ctpl);
    return Template::GetTemplate("index-ctpl", ::ctemplate::DO_NOT_STRIP);
}

void IndexProcessor::RenderScript(TemplateDictionary* dict) {}

bool IndexProcessor::RenderInput(const Request& request, TemplateDictionary* dict) {
    dict->ShowSection("INPUT");
    _docid = GetUint64UrlParameter(request, "doc_id", ILLEGAL_DOCID);
    _engine_name = GetUrlParameter(request, "engine_name", "");
    dict->SetValue("LAST_DOC_ID", Uint64ToString(_docid));
    dict->SetValue("LAST_ENGINE_NAME", _engine_name);
    return true;
}

bool IndexProcessor::RenderResultOutput(TemplateDictionary* dict) {
    // 导航栏
    TemplateDictionary* result_dict = dict->AddSectionDictionary("ONE_PAGE_INFO_LEAD");
    std::string page_name_link = "";
    for (uint32_t i = 0; i < _unise_frontend_proc.size(); ++i) {
        if (_unise_frontend_proc[i].second == "index") {
            page_name_link += "<li class='active'><a href='"
                + _unise_frontend_proc[i].second
                + "' style='color:#01184A'>"
                + _unise_frontend_proc[i].first + "</a></li>";
        } else {
            page_name_link += "<li><a href='" + _unise_frontend_proc[i].second
                + "' style='color:#FFF'>"
                + _unise_frontend_proc[i].first + "</a></li>";
        }
    }
    result_dict->SetValue("PAGE_LEAD", page_name_link); 

    dict->ShowSection("RESULT_OUTPUT");
    dict->SetValue("ENGINE_NAME", _engine_name);
    dict->SetValue("DOC_ID", Uint64ToString(_docid));
    const ForwardIndex * forward_index = _search_engine->get_forward_index(_engine_name, _docid);
    if (forward_index == NULL) {
        dict->SetValue("INFO", "not find doc in such EngineName");
        return true;
    }

    size_t token_num = forward_index->get_token_num();
    dict->SetValue("TOKEN_NUMBERS", UintToString(token_num));

    _token_id_list.clear();
    if (false == forward_index->get_token_id_list(&_token_id_list)) {
        dict->SetValue("INFO", "get_token_id_list failed");
        return true;
    }

    for (size_t i = 0; i < _token_id_list.size(); ++i) {
        TokenId token_id = _token_id_list.at(i);
        size_t hit_size = forward_index->get_doc_token_hit_list_size(token_id);
        std::vector<doc_token_hit_t*> token_hits;
        // 记得释放内存
        for (size_t j = 0; j < hit_size; ++j) {
            token_hits.push_back(new doc_token_hit_t());
        }
        forward_index->get_doc_token_hit_list(token_id, token_hits);
        for (size_t j = 0; j < hit_size; ++j) {
            TemplateDictionary* pr_dict = dict->AddSectionDictionary("TOKEN_RESULTS");
            pr_dict->SetValue("TOKEN_ID", Uint64ToString(token_id));
            pr_dict->SetValue("SECTION_ID",
                        UintToString(static_cast<uint32_t>(token_hits.at(j)->section_id)));
            pr_dict->SetValue("ANNOTATION_ID",
                        UintToString(static_cast<uint32_t>(token_hits.at(j)->annotation_id)));
            pr_dict->SetValue("POS", IntToString(token_hits.at(j)->pos));
        }
        // 释放内存
        for (size_t j = 0; j < hit_size; ++j) {
            delete token_hits.at(j);
        }
    }
    dict->SetValue("INFO", "succ");
    return true;
}

REGISTER_PAGEPROCESSOR(IndexProcessor);
}  // namespace unise
