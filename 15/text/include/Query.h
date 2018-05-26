//
// Created by qinhan on 2018/5/17.
//

#ifndef C_PLUS_QUERY_H
#define C_PLUS_QUERY_H

#include "QueryResult.h"
#include "TextQuery.h"
#include "query_base.h"
#include <memory>
#include <string>
#include <iostream>

class Query {
    friend Query operator~(const Query &);

    friend Query operator|(const Query &, const Query &);

    friend Query operator&(const Query &, const Query &);

    friend std::ostream &operator<<(std::ostream &os, const Query &);

public:
    Query(const std::string &);

    QueryResult eval(const TextQuery &t) const {
        return q->eval(t);
    }

    std::string req() const {
        return q->req();
    }

private:
    Query(std::shared_ptr <query_base> query) : q(query) {}

    std::shared_ptr <query_base> q;
};

Query operator~(const Query &);

Query operator|(const Query &, const Query &);

Query operator&(const Query &, const Query &);

std::ostream &operator<<(std::ostream &os, const Query &);

#endif //C_PLUS_QUERY_H
