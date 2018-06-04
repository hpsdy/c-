// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#ifndef  UNISE_DEMO_DOC_H
#define  UNISE_DEMO_DOC_H

#include <string>
#include <set>
#include <fstream>
#include "util/util.h"
#include "unise/asl_wordseg.h"
#include "Configure.h"
#include "unise/query_rewriter.h"
#include "retri/backend_query_builder.h"

namespace unise {

// 查询树构建失败时的查询词，保证检索无结果
const std::string INVALID_QUERY = "invalidforsearch12345678"; 

class ArticleQueryRewriter : public QueryRewriter {

public:
    ArticleQueryRewriter();
    virtual ~ArticleQueryRewriter();

    virtual bool init(const comcfg::ConfigUnit& conf);

    virtual void rewrite_internal(GeneralSearchRequest * req);

    virtual std::string get_name() const {
        return "ArticleQueryRewriter";
    }

private:
    void build_query_tree(GeneralSearchRequest * req);

private:
    // 全局词典指针，单例，不可释放
    scw_worddict_t * _dict;
    // 全局线程拥有的切词缓冲区，不可释放
    scw_out_t * _handler;
    // 切词结果获取的buffer
    token_t * _tokens;
    // stopword 词典
    std::set<std::string> _stop_words;
    
};

REGISTER_QUERY_REWRITER(ArticleQueryRewriter);

}

#endif  // UNISE_DEMO_DOC_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
