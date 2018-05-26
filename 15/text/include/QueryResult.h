//
// Created by qinhan on 2018/5/16.
//

#ifndef C_PLUS_QUERYRESULT_H
#define C_PLUS_QUERYRESULT_H

#include <set>
#include <vector>
#include <string>

struct QueryResult {
    std::string key;
    std::set<int> scores;
    std::vector <string> lines;
};
#endif //C_PLUS_QUERYRESULT_H
