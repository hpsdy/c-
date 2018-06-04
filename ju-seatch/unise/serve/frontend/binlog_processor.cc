// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/frontend/binlog_processor.h"
#include "ctemplate/template.h"
#include "ctemplate/template_modifiers.h"
#include "gflags/gflags.h"
#include "google/protobuf/io/zero_copy_stream_impl_lite.h"
#include "google/protobuf/text_format.h"
#include "unise/util.h"
#include "unise/base.h"
#include "serve/frontend/ctpl/binlog.ctpl.h"

DECLARE_int32(binlog_buffer_size);

namespace unise {
using ctemplate::TemplateDictionary;
using ctemplate::Template;
using std::string;

BinlogProcessor::BinlogProcessor() :
    _base64_buf(NULL),
    _proto_buf(NULL) {}

BinlogProcessor::~BinlogProcessor() {
    if (_base64_buf != NULL) {
        delete []_base64_buf;
        _base64_buf = NULL;
    }
    if (_proto_buf != NULL) {
        delete []_proto_buf;
        _proto_buf = NULL;
    }
}

bool BinlogProcessor::Init() {
    _base64_buf = new(std::nothrow) uint8_t[FLAGS_binlog_buffer_size];
    if (_base64_buf == NULL) {
        UFATAL("new base_buf failed [size:%u]", FLAGS_binlog_buffer_size);
        return false;
    }
    _proto_buf = new(std::nothrow) uint8_t[FLAGS_binlog_buffer_size];
    if (_proto_buf == NULL) {
        UFATAL("new proto_buf failed [size:%u]", FLAGS_binlog_buffer_size);
        return false;
    }
    return true;
}

bool BinlogProcessor::HandleHttpRequest(const Request& request, Respond *respond) {
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

const Template* BinlogProcessor::GetTemplate() const {
    Template::StringToTemplateCache("binlog-ctpl", binlog_ctpl);
    return Template::GetTemplate("binlog-ctpl", ::ctemplate::DO_NOT_STRIP);
}

void BinlogProcessor::RenderScript(TemplateDictionary* dict) {}

bool BinlogProcessor::RenderInput(const Request& request, TemplateDictionary* dict) {
    dict->ShowSection("INPUT");
    string request_base64;
    string response_base64;
    _request_text = "";
    _response_text = "";

    // 转换request
    do {
        request_base64 = GetUrlParameter(request, "request_base64", "");
        string decoded;
        // url编码转换
        if (false == Request::url_decode(request_base64, decoded)) {
            break;
        }
        request_base64.swap(decoded);

        // 进行base64解码
        strncpy(reinterpret_cast<char*>(_base64_buf),
                    request_base64.c_str(),
                    FLAGS_binlog_buffer_size);
        size_t decode_l = base64_decode(
                    _base64_buf,
                    request_base64.length(),
                    _proto_buf,
                    FLAGS_binlog_buffer_size);
        if (decode_l == 0U) {
            break;
        }
        _proto_buf[decode_l] = 0;

        // protobuf反序列化
        GeneralSearchRequest decode_request;
        google::protobuf::io::ArrayInputStream arr_stream(_proto_buf, decode_l);
        decode_request.ParseFromZeroCopyStream(&arr_stream);
        // protobuf text format
        google::protobuf::TextFormat::PrintToString(decode_request, &_request_text);
        _request_text = process_escape_characters(_request_text);
    } while (0);
    // 转换response
    do {
        response_base64 = GetUrlParameter(request, "response_base64", "");
        string decoded;
        if (false == Request::url_decode(response_base64, decoded)) {
            break;
        }
        response_base64.swap(decoded);

        strncpy(reinterpret_cast<char*>(_base64_buf),
                    response_base64.c_str(),
                    FLAGS_binlog_buffer_size);
        size_t decode_l = base64_decode(
                    _base64_buf,
                    response_base64.length(),
                    _proto_buf,
                    FLAGS_binlog_buffer_size);
        if (decode_l == 0U) {
            break;
        }
        _proto_buf[decode_l] = 0;

        GeneralSearchResponse decode_response;
        google::protobuf::io::ArrayInputStream arr_stream(_proto_buf, decode_l);
        decode_response.ParseFromZeroCopyStream(&arr_stream);
        google::protobuf::TextFormat::PrintToString(decode_response, &_response_text);
        _response_text = process_escape_characters(_response_text);
    } while (0);

    dict->SetValue("LAST_REQUEST_BASE64", request_base64);
    dict->SetValue("LAST_RESPONSE_BASE64", response_base64);
    return true;
}

bool BinlogProcessor::RenderResultOutput(TemplateDictionary* dict) {
    dict->ShowSection("RESULT_OUTPUT");
    dict->SetValue("REQUEST_TEXT", _request_text);
    dict->SetValue("RESPONSE_TEXT", _response_text);
    
    // 导航栏
    TemplateDictionary* result_dict = dict->AddSectionDictionary("ONE_PAGE_INFO_LEAD");
    std::string page_name_link = "";
    for (uint32_t i = 0; i < _unise_frontend_proc.size(); ++i) {
        if (_unise_frontend_proc[i].second == "binlog") {
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

REGISTER_PAGEPROCESSOR(BinlogProcessor);
}  // namespace unise
