// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_BUILDIN_FILTER_H
#define  RETRI_BUILDIN_FILTER_H

#include <Configure.h>
#include <string>
#include <vector>
#include "unise/matched_doc.h"
#include "unise/fact_doc.h"
#include "unise/general_servlet.pb.h"
#include "unise/base.h"
#include "unise/result_filter.h"
#include "unise/search_context.h"

namespace unise
{

/**
 * @brief BuildinFilter是为了配合SortParams使用，为
 *        多级排序提供必要的排序字段，作为LaterFilter使用
 * @note 请参考源代码中的gflags
 */
class BuildinFilter : public ResultFilter
{
public:
    BuildinFilter() {}
    virtual ~BuildinFilter() {}

    virtual bool init(const comcfg::ConfigUnit& conf);
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context);
    /**
     * @brief 过滤以下内容：
     *        1,如果GeneralServletRequest里面有SortParams，那么根据配置
     *          过滤annotation不全的doc;同时，为SearchResult的values字段赋值
     *        2,其他过滤需求，待增加
     */
    virtual result_status_t filter(MatchedDoc * result);
    virtual std::string get_name() const { return "BuildinFilter"; }
private:
    std::vector<const AnnotationSchema * > _sort_schemas;
};

}

#endif  // RETRI_BUILDIN_FILTER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
