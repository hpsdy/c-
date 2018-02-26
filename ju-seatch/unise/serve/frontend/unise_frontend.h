// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef UTIL_FRONTEND_UNISE_FRONTEND_H_
#define UTIL_FRONTEND_UNISE_FRONTEND_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

#include "util/http_server/http_server.h"
#include "unise/factory.h"

namespace ctemplate {
class Template;
}

namespace unise {

class PageProcessor {
public:    
    PageProcessor() {}
    virtual ~PageProcessor() {}
    virtual bool HandleHttpRequest(const Request& request, Respond *respond) = 0;
    virtual bool Init() = 0;
    virtual std::string GetName() const = 0;
    virtual std::string GetPath() const = 0;
    virtual std::string GetDescription() const = 0;
    
public:
    // key -> value : process_name -> process_path
    typedef std::vector<std::pair<std::string, std::string> > UniseFrontendProc;
    void SetUniseFrontendProc(const UniseFrontendProc& unise_frontend_proc);

protected:    
    int GetIntUrlParameter(const Request& request,
            const std::string& key, int default_value);
    int64_t GetInt64UrlParameter(const Request &request,
            const std::string& key,
            int64_t default_value);
    uint64_t GetUint64UrlParameter(const Request &request,
            const std::string& key,
            uint64_t default_value);
    const std::string GetUrlParameter(const Request& request,
            const std::string& key,
            const std::string& default_value);
    bool HasUrlParameter(const Request& request,
            const std::string& key);
protected:
    // all worker processes of unise frontend
    UniseFrontendProc _unise_frontend_proc;
};
REGISTER_FACTORY(PageProcessor);
#define REGISTER_PAGEPROCESSOR(name) REGISTER_CLASS(PageProcessor, name)

class UniseFrontend {
public:
    UniseFrontend() {}
    ~UniseFrontend() {}
    void Init();
    bool HandleDefaultRequest(const Request& request, Respond *respond);

private:
    const ctemplate::Template* GetTemplate() const;
    boost::shared_ptr<HttpServer> http_server_;
    std::vector<PageProcessor*> processors_;
};

}  // namespace unise

#endif  // UTIL_FRONTEND_UNISE_FRONTEND_H_
