// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#ifndef SERVE_SEARCH_FRONTEND_H_
#define SERVE_SEARCH_FRONTEND_H_

#include <boost/scoped_ptr.hpp>
#include <string>
#include <vector>
#include "serve/frontend/unise_frontend.h"
#include "serve/search_engine.h"
#include "unise/pbrpc_client.h"

namespace ctemplate
{
class Template;
class TemplateDictionary;
}

namespace unise
{

class SearchEngineProcessor : public PageProcessor
{
public:
    SearchEngineProcessor() {}
    virtual ~SearchEngineProcessor() {}

    virtual bool HandleHttpRequest(const Request& request, Respond *respond);
    virtual bool Init();
    virtual std::string GetName() const { return "SearchEngineProcessor"; }
    virtual std::string GetPath() const { return "search"; }
    virtual std::string GetDescription() const { return "Unise Search Engine Frontend"; }

private:
    const ctemplate::Template* GetTemplate() const;
    void RenderScript(ctemplate::TemplateDictionary* dict);
    bool RenderInput(const Request& request,
            ctemplate::TemplateDictionary* dict,
            GeneralSearchRequest* srequest);
    bool RenderResultOutput(ctemplate::TemplateDictionary* dict,
            const GeneralSearchResponse& sresponse);
    /**
     * @brief 根据exp字符串，解析Experiment，并设置到sp中
     */
    void set_experiments(const std::string& exp, SearchParams * sp);

    /**
     * @brief 根据sort_params字符串，解析SortParam，设置到sp中
     */
    void set_sort_params(const std::string& sort_param, SearchParams * sp);

private:

    boost::scoped_ptr<bhp::Channel> _channel;
    boost::scoped_ptr<UniseService_Stub> _stub;
    boost::scoped_ptr<bhp::Controller> _controller;
    std::string _server_address;
};

}  // namespace unise

#endif  // SERVE_SEARCH_FRONTEND_H_
