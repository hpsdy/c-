// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  BACKEND_QUERY_BUILDER_H_
#define  BACKEND_QUERY_BUILDER_H_

#include <string>
namespace unise {
class QueryNode;

class BackendQueryBuilder {
public:
    BackendQueryBuilder() {}
    ~BackendQueryBuilder() {}

    bool build(const std::string &str, QueryNode *root);
};

}

#endif  // BACKEND_QUERY_BUILDER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
