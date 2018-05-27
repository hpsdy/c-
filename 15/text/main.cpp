//
// Created by hupose on 2018/5/27.
//
#include<cstdio>
#include <unistd.h>
#include "include/AndQuery.h"
#include "include/BinaryQuery.h"
#include "include/NotQuery.h"
#include "include/OrQuery.h"
#include "include/Query.h"
#include "include/query_base.h"
#include "include/QueryResult.h"
#include "include/TextQuery.h"
#include "include/WordQuery.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

void print(shared_ptr <QueryResult> &p) {
    cout << "key:" << p->key << endl;
    auto begin = p->lines.begin();
    auto srend = p->lines.end();
    for (auto &c:p->scores) {
        cout << "i:" << c << '\t';
        cout << "line:" << *begin << endl;
        ++begin;
    }
}

void print(const QueryResult &p) {
    cout << "key:" << p.key << endl;
    auto begin = p.lines.begin();
    auto srend = p.lines.end();
    for (auto &c:p.scores) {
        cout << "i:" << c << '\t';
        cout << "line:" << *begin << endl;
        ++begin;
    }
}

int main(int argc, char *argv[]) {
    char opt = '\0';
    string filename = "default.text";
    while (((opt = getopt(argc, argv, "f")) != -1)) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            default:
                printf("defalut:%s\n", optarg);
                break;
        }
    }
    cout << "filename:" << filename << endl;
    TextQuery tq(filename);
    Query q("hello");
    auto ret = q.eval(tq);
    print(ret);
    return 0;
}
