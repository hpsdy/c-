// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#ifndef SERVE_FRONTEND_BINLOG_PROCESSOR_H_
#define SERVE_FRONTEND_BINLOG_PROCESSOR_H_

#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "serve/frontend/unise_frontend.h"
#include "serve/search_engine.h"
#include "unise/singleton.h"
#include "unise/state_monitor.h"

namespace ctemplate {
class Template;
class TemplateDictionary;
}

namespace unise{

class BinlogProcessor : public PageProcessor {
public:
    BinlogProcessor();
    virtual ~BinlogProcessor();

    virtual bool HandleHttpRequest(const Request& request, Respond *respond);
    virtual bool Init();
    virtual std::string GetName() const { return "BinlogProcessor"; }
    virtual std::string GetPath() const { return "binlog"; }
    virtual std::string GetDescription() const { return "Unise Binlog Frontend"; }

private:
    const ctemplate::Template* GetTemplate() const;
    void RenderScript(ctemplate::TemplateDictionary* dict);
    bool RenderInput(const Request& request, ctemplate::TemplateDictionary* dict);
    bool RenderResultOutput(ctemplate::TemplateDictionary* dict);

private:
    uint8_t * _base64_buf;
    uint8_t * _proto_buf;
    std::string _request_text;
    std::string _response_text;
};

}  // namespace unise

#endif  // SERVE_FRONTEND_BINLOG_PROCESSOR_H_
