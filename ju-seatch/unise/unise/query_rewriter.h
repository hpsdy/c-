// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  CS_VS_CROSS_UNISE_UNISE_QUERY_REWRITER_H
#define  CS_VS_CROSS_UNISE_UNISE_QUERY_REWRITER_H

#include <string>
#include "unise/factory.h"

namespace comcfg {
class ConfigUnit;
}

namespace unise {
class GeneralSearchRequest;
class QueryNode;

class QueryRewriter {
public:
    QueryRewriter() {}
    virtual ~QueryRewriter() {}
    virtual bool init(const comcfg::ConfigUnit& conf) = 0;
    /**
     * @brief 对raw进行改写，结果放到req中
     * @note req默认是raw的拷贝
     */
    void rewrite(const GeneralSearchRequest * raw, GeneralSearchRequest * req);
    /**
     * @brief 对req进行改写
     * @note req原始的request经过标准的一些改写后形成的req
     *       用户可继承，对req进行进一步的改写
     *       为了避免使用错误，这里直接对req进行写操作
     */
    virtual void rewrite_internal(GeneralSearchRequest * req) = 0;
    virtual std::string get_name() const = 0;

private:
    void trans_query_node(QueryNode * query_node);
    void merge_search_params_from_exp(
                const GeneralSearchRequest * raw,
                GeneralSearchRequest * req);
};

REGISTER_FACTORY(QueryRewriter);
#define REGISTER_QUERY_REWRITER(name) REGISTER_CLASS(QueryRewriter, name)
}

#endif  // CS_VS_CROSS_UNISE_UNISE_QUERY_REWRITER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
