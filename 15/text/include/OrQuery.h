//
// Created by qinhan on 2018/5/14.
//

#ifndef INC_15_ORQUERY_H
#define INC_15_ORQUERY_H

#include "BinaryQuery.h"
#include "QueryResult.h"
#include "Query.h"
#include "TextQuery.h"
#include "query_base.h"
#include <string>
#include <memory>

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &l, const Query &r);

    OrQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "|") {}

    QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &l, const Query &r) {
    return std::shared_ptr<query_base>(new OrQuery(l, r));
}

#endif //INC_15_ORQUERY_H
