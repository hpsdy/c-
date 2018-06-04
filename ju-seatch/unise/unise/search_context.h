// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_SEARCH_CONTEXT_H_
#define  UNISE_SEARCH_CONTEXT_H_

#include <map>
#include <string>
#include <Configure.h>
#include "unise/factory.h"

namespace unise {
class GeneralSearchRequest;

/**
 * @brief 检索上下文，用于检索插件Filter,Scorer,Cluster,Filler传递数据
 *        每个ResultRetrievor对象具有一个自己的SearchContext
 *        用户可以派生该类
 * @note 由于ResultAdapter的生效位置不在EngineUnit中，因此，ResultAdapter
 *       不能获取到该接口
 */
class SearchContext {
public:
    SearchContext() {}
    virtual ~SearchContext() {}

    /**
     * @brief 每一次检索开始时，都会先调用该接口
     * @note 该接口有内部默认实现，会在最后调用init_for_search_internal
     */
    void init_for_search(const GeneralSearchRequest* request);

    /**
     * @brief 用户可继承该接口，实现自己的逻辑
     */
    virtual void init_for_search_internal(const GeneralSearchRequest* request)
    {
        (void)(request);
    }

    /**
     * @brief 通过该接口，可以获取请求的检索深度
     * @note 检索深度：至少检索到多少个满足查询树的doc
     */
    inline int32_t get_retrieve_depth() const
    {
        return _retrieve_depth;
    }

    /**
     * @brief 通过该接口，获取请求的召回结果数
     * @note 召回结果数：通过early filter,cluster,later filter的doc数目
     */
    inline int32_t get_recall_docs() const
    {
        return _recall_docs;
    }

    /**
     * @brief 获取请求的检索超时时间
     */
    inline double get_retrieve_timeout() const
    {
        return _retrieve_timeout;
    }

    /**
     * @brief 获得当前请求的sample_id
     */
    inline uint64_t get_sample_id() const
    {
        return _sample_id;
    }


    /**
     * @brief 获取key指定的int64_t类型的value
     *        参见general_servlet.proto中Experiment的定义
     * @note 获取失败，返回false，不会操作value
     */
    bool get_experiment_value(const std::string& key, int64_t * value) const;
    bool get_experiment_value(const std::string& key, uint64_t * value) const;
    bool get_experiment_value(const std::string& key, std::string * value) const;
    bool get_experiment_value(const std::string& key, bool * value) const;

private:
    std::map<std::string, std::string> _experiment_kvs;
    int32_t _retrieve_depth;               ///< 停止条件——倒排检索深度
    int32_t _recall_docs;                  ///< 停止条件——召回文档数
    double _retrieve_timeout;              ///< 停止条件——倒排检索超时
    uint64_t _sample_id;                   ///< 流量实验id，默认为0
};

/**
 * @brief 当用户派生自己的SearchContext时，需要同时定义一个工厂类
 *        实现product与destroy方法
 * @note 通过EngineUnit下的配置项SearchContextFactory的取值动态获取工厂
 *       如果没有定义该配置项，那么使用DefaultSearchContextFactory
 */
class SearchContextFactory {
public:
    SearchContextFactory() {}
    virtual ~SearchContextFactory() {}

    /**
     * @brief 传入EngineUnit下的配置
     */
    virtual bool init(const comcfg::ConfigUnit&) = 0;

    /**
     * @brief 构造一个SearchContext
     */
    virtual SearchContext * produce() = 0;

    /**
     * @brief 销毁一个SearchContext
     */
    virtual void destroy(SearchContext *) = 0;

    /**
     * @brief 返回派生类的类名
     */
    virtual std::string get_name() = 0;
};
REGISTER_FACTORY(SearchContextFactory);
#define REGISTER_SEARCH_CONTEXT_FACTORY(name) REGISTER_CLASS(SearchContextFactory, name)
}

#endif  // UNISE_SEARCH_CONTEXT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
