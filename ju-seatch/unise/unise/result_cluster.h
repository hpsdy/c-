// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_RESULT_CLUSTER_H_
#define  UNISE_RESULT_CLUSTER_H_

#include <string>

#include "unise/factory.h"
#include "unise/comparator.h"
#include "unise/matched_doc.h"
#include "unise/unise_plugin.h"

namespace unise
{
class GeneralSearchRequest;
class SearchResult;
class SearchContext;

enum cluster_status_t {
    CLUSTER_ADD = 0,     // the result will be add
    CLUSTER_SKIP = 1,    // the result will be skip
    CLUSTER_REPLACE = 2, // the result will replace many other results
};

/**
 * @brief 聚合插件，一般用来做去重
 *
 * @note 1) 继承自UnisePlugin，可以访问UnisePlugin提供的基本函数
 *       2) 每个检索线程有一个Cluster对象，检索线程启动时，初始化cluster对象 
 *       3) 参见EngineUnit的ResultClusters配置项，多个cluster使用逗号分隔
 *       4）如果配置多个cluster，按照配置顺序调用，依次生效
 *       5) unise会维护结果状态
 */
class ResultCluster : public UnisePlugin
{
public:
    ResultCluster() {}
    virtual ~ResultCluster() {}

    /**
     * @brief 每一个检索请求处理前，会调用该方法
     * @param [in] : request, 检索请求
     * @param [in] : comparator,相等比较器，相等时，进行去重
     * @param [in/out] : context, 检索上下文，用于做插件间的数据互传
     *                   用户可以继承，实现自己的context
     * @param [out] : none
     * @return  none
     * @retval none
     * @see
     * @note 注意，无返回值
     *       纯虚
     */
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 const Comparator* comparator,
                                 SearchContext * context) = 0;

    /**
     * @brief 每召回一个MatchedDoc会调用该方法，用来判断是否进行聚合
     * @return bool
     * @retval true,进行cluster_result调用
     *         false,不进行cluster_result调用
     *
     */
    virtual bool need_cluster(MatchedDoc* result) const = 0;

    /**
     * @brief 当前召回的MatchedDoc为result，进行去重
     * @param [in] : result
     * @param [out] : clustered_result，被当前result干掉的结果的指针
     *                单返回值为CLUSTER_REPLACE时，才进行赋值
     *
     * @return cluster_status_t 参见定义
     * @note 如果没有特殊需求，请试用cluster_template.h完成一般的去重需求
     */
    virtual cluster_status_t cluster_result(MatchedDoc* result,
                                            MatchedDoc** clustered_result) = 0;

    /**
     * @brief 结果result被加入到结果集中
     *        插件应该在这里把sign存储起来
     */
    virtual void add_info(MatchedDoc* result) = 0;

    /**
     * @brief 结果result被干掉，一般这里实现remove sign的工作
     */
    virtual void remove_info(MatchedDoc* result) = 0;

    /**
     * @brief 当前的这个结果，会被返回，在本函数中有机会填充
     *        一些状态信息到search_result中
     */
    virtual bool fill_result_cluster_info(MatchedDoc* doc,
                                          SearchResult* search_result) {
        (void)(doc);
        (void)(search_result);
        return false;
    }
};

REGISTER_FACTORY(ResultCluster);
#define REGISTER_RESULT_CLUSTER(name) REGISTER_CLASS(ResultCluster, name)

}

#endif  // UNISE_RESULT_CLUSTER_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
