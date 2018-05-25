//
// Created by qinhan on 2018/5/24.
//
#include "../include/AndQuery.h"
#include "../include/QueryResult.h"
#include <set>
#include <vector>
#include <string>
#include <algorithm>

QueryResult AndQuery::eval(const TextQuery &text) const {
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_scores_left = std::set<int>((left->scores).begin(), (left->scores).end());
    auto ret_scores_right = std::set<int>((right->scores).begin(), (right->scores).end());
    auto ret_scores = std::set<int>();
    std::set_intersection(ret_scores_left.begin(), ret_scores_left.end(), ret_scores_right.begin(),
                          ret_scores_right.end(), std::inserter(ret_scores, ret_scores.begin()));
    auto ret_lines = std::vector<int>();
    for (auto &c:ret_scores) {
        ret_lines.push_back((text.text)->at(c));
    }
    return {req(), ret_scores, ret_lines};
}
