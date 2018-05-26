//
// Created by qinhan on 2018/5/16.
//
#include "include/TextQuery.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

TextQuery::TextQuery(std::string filename) : text(new std::vector<std::string>()) {
    std::ifstream fn(filename);
    if (fn.fail()) {
        throw runtime_error("open file " + filename + " fail");
    }
    std::string line;
    std::stringstream ss;
    while (fn.peek() != EOF) {
        std::getline(fn, line);
        if (!line) {
            continue;
        }
        text->push_back(line);
        ss.clear();
        ss.ignore(1000, EOF);
        ss.str(line);
        std::string word;
        while (ss >> word) {
            auto &tmp = keymap.find(word);
            if (tmp == keymap.end()) {
                keymap.insert({word, std::set<int>()});
            }
            auto &wordSet = keymap.find(word).second;
            wordSet.insert(text->size() - 1);
        }
    }
    fn.close();
}

QR TextQuery::query(std::string key) {
    auto &findRet = keymap.find(word);
    if (findRet == keymap.end()) {
        return std::make_shared < QueryResult > {"", std::set<int>(), std::vector<std::string>()};
    } else {
        auto &scores = findRet.second;
        std::vector <std::string> tmpVector;
        for (const auto &c:scores) {
            tmpVector.push_back(text->at(c));
        }
        return std::make_shared < QueryResult > {findRet.first, scores, tmpVector};
    }
}
