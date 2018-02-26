// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#ifndef UNISE_SERVE_FRONTEND_INDEX_PROCESSOR_H
#define UNISE_SERVE_FRONTEND_INDEX_PROCESSOR_H

#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "serve/frontend/unise_frontend.h"
#include "serve/search_engine.h"
#include "unise/singleton.h"

namespace ctemplate {
class Template;
class TemplateDictionary;
}

namespace unise{

class IndexProcessor : public PageProcessor {
public:
    IndexProcessor();
    virtual ~IndexProcessor();

    virtual bool HandleHttpRequest(const Request& request, Respond *respond);
    virtual bool Init();
    virtual std::string GetName() const { return "IndexProcessor"; }
    virtual std::string GetPath() const { return "index"; }
    virtual std::string GetDescription() const { return "Unise Index Frontend"; }

private:
    const ctemplate::Template* GetTemplate() const;
    void RenderScript(ctemplate::TemplateDictionary* dict);
    bool RenderInput(const Request& request, ctemplate::TemplateDictionary* dict);
    bool RenderResultOutput(ctemplate::TemplateDictionary* dict);

private:
    DocId _docid;
    std::string _engine_name;
    std::vector<TokenId> _token_id_list;
    SearchEngine * _search_engine;
};

}  // namespace unise

#endif  // UNISE_SERVE_FRONTEND_INDEX_PROCESSOR_H
