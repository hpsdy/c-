//
// Created by qinhan on 2018/5/24.
//
#include "../include/NotQuery.h"
#include "../include/QueryResult.h"
#include <set>
#include <vector>
#include <string>
#include <algorithm>

QueryResult NotQuery::eval(const TextQuery &text) const {
    auto qr = query.eval(text);
    auto ret_scores = std::set<int>();
    auto ret_lines = std::vector<int>();
    int sizeLen = text.textSize();
    auto beg = qr->scores.begin();
    auto scend = qr->scores.end();
    for (i = 0; i < sizeLen; ++i) {
        if (beg == scend || *beg != i) {
            ret_scores.insert(i);
            ret_lines.push_back((text.text)->at(i));
        } else if (beg != scend) {
            ++beg;
        }
    }
    return {req(), ret_scores, ret_lines};
}

