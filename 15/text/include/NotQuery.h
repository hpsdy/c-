//
// Created by qinhan on 2018/5/14.
//

#ifndef INC_15_NOTQUERY_H
#define INC_15_NOTQUERY_H

#include "query_base.h"
#include "Query.h"
#include <string>
#include "QueryResult.h"
#include "TextQuery.h"
#include <memory>

class NotQuery : public query_base {
    friend Query operator~(const Query &);

    NotQuery(const Query &q) : query(q) {}

    std::string req() const {
        return "~(" + query.req() + ")";
    }

    QueryResult eval(const TextQuery &) const;

    Query query;
};

inline Query operator~(const Query &q) {
    return std::shared_ptr<query_base>(new NotQuery(q));
}

#endif //INC_15_NOTQUERY_H
