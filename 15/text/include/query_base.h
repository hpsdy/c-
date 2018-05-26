//
// Created by qinhan on 2018/5/14.
//

#ifndef INC_15_QUERY_BASE_H
#define INC_15_QUERY_BASE_H

#include "include/QueryResult.h"
#include "include/TextQuery.h"
#include <string>

class query_base {
    friend class Query;

protected:
    virtual ~query_base() {}

private:
    virtual QueryResult eval(const TextQuery &) const =0;

    virtual std::string req() const =0;
};

#endif //INC_15_QUERY_BASE_H
