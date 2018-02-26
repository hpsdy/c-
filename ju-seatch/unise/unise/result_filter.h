// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_RESULT_FILTER_H_
#define  UNISE_RESULT_FILTER_H_

#include "unise/factory.h"
#include "unise/matched_doc.h"
#include "unise/base.h"
#include "unise/unise_plugin.h"

namespace unise
{
class GeneralSearchRequest;
class MatchedDoc;
class SearchContext;

/**
 * @brief 过滤插件，有三类：EarlyResultFilter,LaterResultFilter,FinalResultFilter
 *
 * @note 1) 继承自UnisePlugin，可以访问UnisePlugin提供的基本函数
 *       2) 对象生存空间和作用方式同其他UnisePlugin插件
 *       3) 参见EngineUnit的XXX_ResultFilter配置项，多个filters使用逗号分隔
 *       4）如果配置多个filters，按照配置顺序调用，依次生效
 *       5) unise会维护结果状态
 * @see 设计文档，对三类Filter的定义
 */
class ResultFilter : public UnisePlugin
{
public:
    ResultFilter() {}
    virtual ~ResultFilter() {}

    /**
     * @brief 每一个检索请求处理前，会调用该方法
     * @param [in] : request, 检索请求
     * @param [out] : none
     * @return  none
     * @retval none
     * @see
     * @note 注意，无返回值，无需要可以不实现
     */
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) = 0;

    /**
     * @breaf 每retrieve到一个MatchedDoc，都会调用filter函数
     *
     * @param [in] : doc,命中的MatchedDoc
     * @param [out] : none
     * @return  result_status_t
     * @retval 只有返回RESULT_ACCEPTED的结果被留下
     * @see base.h
     * @note FinalFilter，不会改变检索过程中其他插件(cluster)的状态了
     *       LaterFilter,如果过滤掉了一个doc，那么，cluster是会调用remove
     *       方面的方法，从sign结合中除去它
    **/
    virtual result_status_t filter(MatchedDoc * result) = 0;
};

REGISTER_FACTORY(ResultFilter);
#define REGISTER_RESULT_FILTER(name) REGISTER_CLASS(ResultFilter, name)

}

#endif  // UNISE_RESULT_FILTER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
