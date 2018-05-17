//
// Created by qinhan on 2018/5/14.
//

#ifndef INC_15_WORDQUERY_H
#define INC_15_WORDQUERY_H

#include "query_base.h"
#include "QueryResult.h"
#include "TextQuery.h"
#include <string>

class WordQuery : public query_base {
    friend class Query;

    WordQuery(const std::string &s) : query_word(s) {}

    QueryResult eval(const TextQuery &t) const {
        return t.query(query_word);
    }

    std::string req() const {
        return query_word;
    }

    std::string query_word;

};

#endif //INC_15_WORDQUERY_H
