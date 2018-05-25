//
// Created by qinhan on 2018/5/14.
//

#ifndef INC_15_BINARYQUERY_H
#define INC_15_BINARYQUERY_H

#include "query_base.h"
#include "Query.h"
#include <string>

class BinaryQuery : public query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s) {};

    std::string req() const {
        return "(" + lhs.req() + " " + opSym + " " + rhs.req() + ")";
    }

    Query lhs, rhs;
    std::string opSym;
};

#endif //INC_15_BINARYQUERY_H
