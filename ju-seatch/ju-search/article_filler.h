// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_DEMO_FILLER_H
#define  UNISE_DEMO_FILLER_H

#include <string>
#include <string.h>
#include <boost/algorithm/string.hpp>

#include "Configure.h"
#include "ucode.h"

#include "unise/matched_doc.h"
#include "unise/util.h"
#include "unise/search_context.h"
#include "unise/result_filler.h"

#include "article_doc.h"

namespace unise {
class ArticleFiller : public ResultFiller {
public:
    ArticleFiller() {}
    virtual ~ArticleFiller() {}

    virtual bool init(const comcfg::ConfigUnit& conf) {
        (void)(conf);
        return true;
    }

    virtual void init_for_search(const GeneralSearchRequest* request, SearchContext * context) {
        _request = request;
        (void)(context);
    }

    virtual void fill_search_result(MatchedDoc * result, SearchResult* search_result) const;

    virtual void end_for_search(PluginResponse * plugin_response);

    virtual std::string get_name() const { return "ArticleFiller"; }

private:

    int highlight_string(std::string& annotation, std::string query); 

private:
    GeneralSearchRequest* _request;

};

}

#endif  // UNISE_DEMO_FILLER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
