//
// Created by qinhan on 2018/5/16.
//

#ifndef C_PLUS_TEXTQUERY_H
#define C_PLUS_TEXTQUERY_H

#include <memory>
#include <map>
#include <string>
#include <vector>
#include "QueryResult.h"

using namespace std;

class TextQuery {
public:
    typedef shared_ptr <vector<string>> lineList;
    typedef map <string, set<int>> keyNumMap;

    TextQuery(string filename);

    QueryResult query(string key);

    ~textquery() {
    }

private:
    lineList text;
    keyNumMap keymap;


};

#endif //C_PLUS_TEXTQUERY_H
