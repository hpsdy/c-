// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_BLACKLIST_FILTER_H_
#define  RETRI_BLACKLIST_FILTER_H_

#include "unise/matched_doc.h"
#include "unise/result_filter.h"
#include "util/hash_tables.h"
#include "unise/search_context.h"
#include "unise/fact_doc.h"

namespace unise
{
class GeneralSearchRequest;
class MatchedDoc;

// this is a simple early filter, just for demo and test
// use docid to filt matched doc
class BlacklistFilter : public ResultFilter
{
public:
    BlacklistFilter() {}
    virtual ~BlacklistFilter() {}

    virtual bool init(const comcfg::ConfigUnit & conf);

    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) {}
    virtual result_status_t filter(MatchedDoc * result);
    virtual std::string get_name() const {
        return "BlacklistFilter";
    }

private:
    typedef __gnu_cxx::hash_map<DocId, bool> FilterIdMap;
    FilterIdMap filter_id_map_;
};

// this is a simple early filter, just for performance test
// use score to filt matched doc
class PerformanceFilter : public ResultFilter
{
public:
    PerformanceFilter() {}
    virtual ~PerformanceFilter() {}

    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) {}
    virtual result_status_t filter(MatchedDoc * result)
    {
        int32_t score = result->get_fact_doc().get_score();
        // 测试数据的score为1到1000，因此，这里的通过率基本为20%
        // 以实现检索深度10000，召回深度2000
        if ((score & 0x01) || (score & 0x02)) {
            return RESULT_ACCEPTED;
        } else {
            return RESULT_FILTED_EARLY;
        }
    }
    virtual std::string get_name() const {
        return "PerformanceFilter";
    }
};

}

#endif  // RETRI_BLACKLIST_FILTER_H_
/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
