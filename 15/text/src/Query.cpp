//
// Created by qinhan on 2018/5/17.
//
#include "../include/Query.h"
#include "../include/WordQuery.h"

std::ostream &operator<<(const std::ostream &os, const Query &query) {
    return os << query->req();
}

Query::Query(std::string &str) : query(new WordQuery(str)) {

}

