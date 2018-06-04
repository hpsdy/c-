// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/backend_query_builder.h"
#include <vector>
#include <string>
#include "unise/util.h"
#include "unise/general_servlet.pb.h"
#include "unise/base.h"

namespace unise {

void find_sep(const std::string &str, std::vector<size_t> *pos_list) {
    size_t i = 0;
    int32_t cnt = 0;
    for (i = 0; i < str.size(); ++i) {
        if (str.at(i) == '(') {
            cnt++;
        } else if (str.at(i) == ')') {
            cnt--;
        } else if (str.at(i) == ',' && cnt == 0) {
            pos_list->push_back(i);
        }
    }
}

bool BackendQueryBuilder::build(const std::string &str, QueryNode *root) {
    UNOTICE("build QueryTree from str:%s", str.c_str());
    std::string buf(str);
    string_trim(&buf, " ");
    if (buf == "" || buf.size() <= 3) {
        return false;
    }
    std::string tmp(buf);
    std::string sep = " ";
    std::string prefix_sep = "";
    // 自定义分隔符模式
    // query : -&V(&hello world& ANNOTATION keyword)
    if (buf.at(0) == '-') {
        if (buf.size() <= 5) {
            return false;
        }
        // 获取分隔符
        sep.assign(1, buf.at(1));
        prefix_sep = buf.substr(0, 2);
        tmp = buf.substr(2, buf.size() - 2);
    }    
    if (tmp.at(1) != '(' || tmp.at(tmp.size() - 1) != ')') {
        return false;
    }
    if (tmp.at(0) == 'V') {
        // remove V ( ), only the left middle string
        std::vector<std::string> tmp_str;
        string_split(tmp, "V()", &tmp_str);        
        if (tmp_str.size() != 1) {
            UWARNING("[\tlvl=COUNT\t] query tree string:%s", tmp.c_str());
            return false;
        }
        // 解析检索query
        std::string text_value = "";
        std::vector<std::string> strs;
        std::vector<std::string> query_str;
        if (sep != " ") {
            // 使用自定义分隔符            
            string_split(tmp_str.at(0), sep, &query_str);
            if (query_str.size() != 2) {
                UWARNING("[\tlvl=COUNT\t] query tree string:%s", tmp_str.at(0).c_str());
                return false;
            }
            text_value = query_str.at(0);
            string_split("DUMMYSTR " + query_str.at(1), " ", &strs);
        } else {
            string_split(tmp_str.at(0), " ", &strs);
            text_value = strs.at(0);
        }
        if (strs.size() < 3) {
            UWARNING("[\tlvl=COUNT\t] V should be: value SECTION/ANNOTATION "
                     "name [weight] [match_type]");
            return false;
        }
        root->set_type(VALUE);
        QueryNodeValue *value = root->mutable_value();
        if (strs.at(1) == "SECTION") {
            value->set_section_name(strs.at(2));
        } else if (strs.at(1) == "ANNOTATION") {
            value->set_annotation_name(strs.at(2));
        } else {
            UWARNING("[\tlvl=COUNT\t] V should be: value SECTION/ANNOTATION name");
            return false;
        }
        value->set_text_value(text_value);
        if (strs.size() > 3) {
            uint32_t weight = 0;
            if (StringToUint(strs.at(3), &weight)) {
                value->set_weight(weight);
            } else {
                UWARNING("[\tlvl=COUNT\t] weight is not uint32_t:%s", strs.at(3).c_str());
                return false;
            }
        }
        if (strs.size() > 4) {
            uint32_t match_type = 0;
            if (StringToUint(strs.at(4), &match_type)) {
                value->set_match_type(match_type);
            } else {
                UWARNING("[\tlvl=COUNT\t] match_type is not uint32_t:%s", strs.at(4).c_str());
                return false;
            }
        }
        return true;
    } else if (tmp.at(0) == 'A') {
        tmp = tmp.substr(2, tmp.size() - 3);
        std::vector<size_t> sep_list;
        find_sep(tmp, &sep_list);
        root->set_type(AND);
        size_t last_p = 0;
        for (size_t i = 0; i < sep_list.size(); ++i) {
            QueryNode *child = root->add_children();
            if (!build(prefix_sep + tmp.substr(last_p, sep_list.at(i) - last_p), child)) {
                return false;
            }
            last_p = sep_list.at(i) + 1;
        }
        QueryNode *child = root->add_children();
        return build(prefix_sep + tmp.substr(last_p), child);
    } else if (tmp.at(0) == 'O') {
        tmp = tmp.substr(2, tmp.size() - 3);
        std::vector<size_t> sep_list;
        find_sep(tmp, &sep_list);
        root->set_type(OR);
        size_t last_p = 0;
        for (size_t i = 0; i < sep_list.size(); ++i) {
            QueryNode *child = root->add_children();
            if (!build(prefix_sep + tmp.substr(last_p, sep_list.at(i) - last_p), child)) {
                return false;
            }
            last_p = sep_list.at(i) + 1;
        }
        QueryNode *child = root->add_children();
        return build(prefix_sep + tmp.substr(last_p), child);
    } else if (tmp.at(0) == 'N') {
        tmp = tmp.substr(2, tmp.size() - 3);
        root->set_type(NOT);
        QueryNode *left = root->add_children();
        return build(prefix_sep + tmp, left);
    } else if (tmp.at(0) == 'B') {
        tmp = tmp.substr(2, tmp.size() - 3);
        std::vector<size_t> sep_list;
        find_sep(tmp, &sep_list);
        root->set_type(BRANCH);
        size_t last_p = 0;
        for (size_t i = 0; i < sep_list.size(); ++i) {
            QueryNode *child = root->add_children();
            if (!build(prefix_sep + tmp.substr(last_p, sep_list.at(i) - last_p), child)) {
                return false;
            }
            last_p = sep_list.at(i) + 1;
        }
        QueryNode *child = root->add_children();
        return build(prefix_sep + tmp.substr(last_p), child);
    } else {
        return false;
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
