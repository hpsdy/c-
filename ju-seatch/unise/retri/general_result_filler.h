// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_GENERAL_RESULT_FILLER_H_
#define  RETRI_GENERAL_RESULT_FILLER_H_

#include <Configure.h>
#include "unise/result_filler.h"
#include "unise/general_plugin.pb.h"
#include "unise/search_context.h"

namespace unise
{
class GeneralSearchRequest;
class SearchResult;
class MatchedDoc;

class GeneralResultFiller : public ResultFiller
{
public:
    GeneralResultFiller();
    virtual ~GeneralResultFiller() {}

    virtual bool init(const comcfg::ConfigUnit & conf);
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) {}
    virtual void fill_search_result(MatchedDoc * doc,
            SearchResult* search_result) const;
    virtual std::string get_name() const {
        return "GeneralResultFiller";
    }
private:
    GeneralFillerConfig _filler_config;
    std::vector<const AnnotationFillerItem *> _filler_items;
};

class DefaultResultFiller : public ResultFiller
{
public:
    DefaultResultFiller() {}
    virtual ~DefaultResultFiller() {}

    virtual bool init(const comcfg::ConfigUnit & conf) { return true; }
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) {}
    virtual void fill_search_result(MatchedDoc * doc,
            SearchResult* search_result) const {}
    virtual std::string get_name() const {
        return "DefaultResultFiller";
    }
};
}

#endif  // RETRI_GENERAL_RESULT_FILLER_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
