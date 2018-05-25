//
// Created by qinhan on 2018/5/24.
//
#include "../include/OrQuery.h"
#include "../include/QueryResult.h"
#include <set>
#include <vector>
#include <string>

QueryResult OrQuery::eval(const TextQuery &text) const {
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_scores = std::set<int>((left->scores).begin(), (left->scores).end());
    ret_scores.insert((right->scores).begin(), (right->scores).end());
    auto ret_lines = std::vector<std::string>(left->lines);
    ret_lines.insert(ret_lines->end(), (right->lines).begin(), (right->lines).end());
    return {req(), ret_scores, ret_lines};
}

