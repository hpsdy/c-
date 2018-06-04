// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "Configure.h"
#include "google/protobuf/io/zero_copy_stream_impl_lite.h"
#include "google/protobuf/text_format.h"
#include "gflags/gflags.h"
#include "unise/general_servlet.pb.h"
#include "unise/base.h"
#include "unise/util.h"
#include "unise/query_rewriter.h"
#include "index/index.h"

DEFINE_bool(enable_all_query_trans_conversion, false, "如果为true，那么全部转换，"
            "query中的配置无效"); 

namespace unise {
void QueryRewriter::merge_search_params_from_exp(
            const GeneralSearchRequest * raw,
            GeneralSearchRequest * req) {
    std::string str;
    // -&=search_params=[unise.filter_params] {name: "beds" values: "1" values: "2"
    //    is_bid_tag:false} 
    if (!get_string_experiment_value(*raw, "search_params", &str)) {
        return;
    }
    SearchParams exp_sp;
    google::protobuf::io::ArrayInputStream arr_stream(str.c_str(), str.length());
    if (!google::protobuf::TextFormat::Parse(&arr_stream, &exp_sp)) {
        UNOTICE("parse search_params[%s] to protobuf failed", str.c_str());
        return;
    }
    SearchParams * sp = req->mutable_search_params();
    sp->MergeFrom(exp_sp);
    google::protobuf::TextFormat::PrintToString(*sp, &str);
    UNOTICE("the final search_params:%s", str.c_str());
}

void QueryRewriter::rewrite(const GeneralSearchRequest * raw, GeneralSearchRequest * req) {
    req->CopyFrom(*raw);
    // 将search_params中的experiment中的search_params抽取出来
    // 避免插件不停的做转换
    merge_search_params_from_exp(raw, req);

    // 调用实际的派生类
    rewrite_internal(req);

    // WARNING: 只有当有query tree时，才需要进行rewrite
    if (req->has_query_tree()) {
        trans_query_node(req->mutable_query_tree());
    }
}

// TODO(wangguangyuan):改成迭代的，目前先保证逻辑正确，用最简单的方式实现
void QueryRewriter::trans_query_node(QueryNode * node) {
    QueryNode & query_node = *node;
    int children_size = query_node.children_size();
    switch (query_node.type()) {
    case VALUE: {
        if (query_node.has_value() && query_node.value().has_text_value()) {
           QueryNodeValue * value = query_node.mutable_value();
           if ((value->has_trans_conversion() && value->trans_conversion()) ||
                FLAGS_enable_all_query_trans_conversion) {
               std::string tmp_str;
               trans_word(value->text_value(), &tmp_str);
               UTRACE("trans_word from [%s] to [%s]",
                           value->text_value().c_str(), tmp_str.c_str());
               value->set_text_value(tmp_str);
           }
        }
        break;
    }
    case OR: {
        for (int i = 0; i < children_size; ++i) {
            trans_query_node(query_node.mutable_children(i));
        }
        break;
    }
    case AND: {
        for (int i = 0; i < children_size; ++i) {
            trans_query_node(query_node.mutable_children(i));
        }
        break;
    }
    case NOT: {
        if (children_size == 1) {
            trans_query_node(query_node.mutable_children(0));
        }
        break;
    }
    default:
        // pass
        break;
    }
}

class EmptyQueryRewriter : public QueryRewriter {
public:
    EmptyQueryRewriter() {}
    virtual ~EmptyQueryRewriter() {}
    virtual bool init(const comcfg::ConfigUnit& conf) {
        (void)(conf);
        return true;
    }
    virtual void rewrite_internal(GeneralSearchRequest * req) {
        (void)(req);
    }
    virtual std::string get_name() const {
        return "EmptyQueryRewriter";
    }
};

REGISTER_QUERY_REWRITER(EmptyQueryRewriter);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
