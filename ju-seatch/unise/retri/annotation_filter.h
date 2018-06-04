// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_ANNOTATION_FILTER_H_
#define  RETRI_ANNOTATION_FILTER_H_

#include <vector>
#include <Configure.h>
#include "unise/matched_doc.h"
#include "unise/result_filter.h"

namespace unise
{
class GeneralSearchRequest;
class MatchedDoc;
class NumberSpec;
class SearchContext;

// this is a early filter, just for range search
class AnnotationFilter : public ResultFilter
{
public:
    AnnotationFilter() {}
    virtual ~AnnotationFilter() {}

    virtual bool init(const comcfg::ConfigUnit& conf);
    virtual void init_for_search(const GeneralSearchRequest* request, SearchContext * context);
    virtual result_status_t filter(MatchedDoc * result);
    virtual std::string get_name() const {
        return "AnnotationFilter";
    }
private:
    std::vector<const NumberSpec *> _filter_list;
    bool _need_filter;
};

}

#endif  // RETRI_ANNOTATION_FILTER_H_
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
