// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#ifndef SERVE_FRONTEND_MONITOR_PROCESSOR_H
#define SERVE_FRONTEND_MONITOR_PROCESSOR_H

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

namespace unise {

class MonitorProcessor : public PageProcessor {
public:
    MonitorProcessor();
    virtual ~MonitorProcessor() {}

    virtual bool HandleHttpRequest(const Request& request, Respond *respond);
    virtual bool Init();
    virtual std::string GetName() const { return "MonitorProcessor"; }
    virtual std::string GetPath() const { return "monitor"; }
    virtual std::string GetDescription() const { return "Unise Monitor Frontend"; }

private:
    const ctemplate::Template* GetTemplate() const;
    void RenderScript(ctemplate::TemplateDictionary* dict);
    bool RenderInput(const Request& request, ctemplate::TemplateDictionary* dict);
    bool RenderResultOutput(ctemplate::TemplateDictionary* dict);

private:
    StateMonitor * _state_monitor;
    std::vector<std::string> _text_keys;
    std::vector<std::string> _number_keys;
    boost::scoped_ptr<std::vector<tens_record_t> > _records;
    GetMemInfo _mem_info; 
};

}  // namespace unise

#endif  // SERVE_FRONTEND_MONITOR_PROCESSOR_H
