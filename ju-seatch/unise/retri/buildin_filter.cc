// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#include <gflags/gflags.h>
#include <boost/lockfree/detail/branch_hints.hpp>
#include "retri/buildin_filter.h"

DEFINE_bool(filter_doc_missing_sort_annotation, false, "whether filter the doc "
                                                       "missing sort annotation");
using std::vector;
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

namespace unise
{
bool BuildinFilter::init(const comcfg::ConfigUnit& conf)
{
    (void)(conf);
    UDEBUG("init BuildinFilter Succ");
    return true;
}

void BuildinFilter::init_for_search(const GeneralSearchRequest* request, SearchContext * context)
{
    (void)(context);
    _sort_schemas.clear();
    // 从request读取sort信息，记录需要sort的annotation的schema和升降序
    if (request->has_search_params()) {
        const SearchParams & sp = request->search_params();
        for (int i = 0; i < sp.sort_params_size(); ++i) {
            _sort_schemas.push_back(get_annotation_schema(sp.sort_params(i).annotation_name()));
        }
    }
    UDEBUG("init_for_search BuildinFilter Succ");
}

result_status_t BuildinFilter::filter(MatchedDoc * doc)
{
    // 首先判断是否需要过滤，如果不需要，那么直接返回
    size_t sort_schemas_size = _sort_schemas.size();
    if (sort_schemas_size == 0U) {
        return RESULT_ACCEPTED;
    }
    // 获取annotation，并赋值到SearchResult中的values数组中，用来做比较
    // 注意，这里会首先清空MatchedDoc中的SearchResult的values数组
    SearchResult * search_result = doc->get_search_result();
    search_result->clear_values();

    const FactDoc & fact_doc = doc->get_fact_doc();
    Annotation to_find;
    // 遍历所有排序需要的annotation，填充到SearchResult中
    for (size_t i = 0; i < sort_schemas_size; ++i) {
        const AnnotationSchema * schema = _sort_schemas[i];
        if (unlikely(schema == NULL)) {
            Value * value = search_result->add_values();
            value->set_id(ILLEGAL_ANNOTATION_ID);
            UNOTICE("doc[%llu] miss anno_schema for sort-annotation[%d]", doc->get_doc_id(), i);
            continue;
        }
        to_find.id = schema->id();
        
        const vector<Annotation> & annos = fact_doc.annotations;
        vector<Annotation>::const_iterator it = find(annos.begin(), annos.end(), to_find);
        if (likely(it != annos.end())) {
            // 找到了对应的annotation，那么填充到SearchResult中，用来排序
            UDEBUG("get doc[%llu] with sort-annotation[%d]", doc->get_doc_id(), i);
            Value * value = search_result->add_values();
            value->set_id(it->id);
            // 根据schema的不同类型进行赋值
            if (likely(schema->annotation_type() == NUMBER)) {
                value->set_number_value(it->number_value);
            } else {
                GOOGLE_DCHECK_EQ(schema->annotation_type(), TEXT);
                value->set_text_value(it->text_value);
            }
        } else if (FLAGS_filter_doc_missing_sort_annotation) {
            // 没有找到对应的annotation，且需要过滤缺失排序参数的doc
            UDEBUG("pass doc[%llu] miss sort-annotation[%d]", doc->get_doc_id(), i);
            return RESULT_INVALID;
        } else {
            // 没有找到对应的annotation，填充默认非法值
            UDEBUG("get doc[%llu] miss sort-annotation[%d]", doc->get_doc_id(), i);
            Value * value = search_result->add_values();
            value->set_id(ILLEGAL_ANNOTATION_ID);
        }
    }
    return RESULT_ACCEPTED;
}

REGISTER_RESULT_FILTER(BuildinFilter);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
