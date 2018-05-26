//
// Created by qinhan on 2018/5/14.
//

#ifndef INC_15_ANDQUERY_H
#define INC_15_ANDQUERY_H

#include "BinaryQuery.h"
#include "Query.h"
#include "QueryResult.h"
#include "TextQuery.h"
#include <memory>

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &, const Query &);

    AndQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "&") {}

    QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &l, const Query &r) {
    return std::shared_ptr<query_base>(new AndQuery(l, r));
}

#endif //INC_15_ANDQUERY_H
