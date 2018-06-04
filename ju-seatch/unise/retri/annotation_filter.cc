// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/annotation_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include "gflags/gflags.h"
#include "unise/base.h"
#include "unise/fact_doc.h"
#include "unise/general_servlet.pb.h"
#include "unise/annotation_schema.pb.h"
#include "unise/search_context.h"

namespace unise {

bool AnnotationFilter::init(const comcfg::ConfigUnit& conf) {
    // NumberRangeQuery升级后，不需要再配合使用AnnotationFilter
    // 为了兼容升级，减少影响，这里仅仅打印一个WARNING LOG
    // 后续AnnotationFilter也可能派上用途，比如为了减少OR节点孩子数目
    // 而升级查询区间的范围，不做QueryNode的完全精确的覆盖
    UWARNING("AnnotationFilter should not be used any more, NumberRangeQuery has been upgrade");
    return true;
}
void AnnotationFilter::init_for_search(const GeneralSearchRequest* request,
                                       SearchContext * context)
{
    _filter_list.clear();
    _filter_list.resize(ANNOTATION_ID_MAX + 1);
    _need_filter = false;
    if (request->has_search_params()) {
        for (int i = 0; i < request->search_params().range_restrictions_size(); ++i) {
            const RangeRestriction & rr = request->search_params().range_restrictions(i);
            if (!rr.has_number_spec()) {
                UWARNING("[\tlvl=COUNT\t] restriction anno[%s] missing number_spec",
                            rr.annotation_name().c_str());
                continue;
            }
            const AnnotationSchema * schema = get_annotation_schema(rr.annotation_name());
            if (schema == NULL || schema->annotation_type() != NUMBER) {
                UWARNING("[\tlvl=COUNT\t] restriction anno[%s] get schema failed",
                            rr.annotation_name().c_str());
                continue;
            }
            AnnotationId anno_id = schema->id();
            if (_filter_list.at(anno_id) != NULL) {
                UWARNING("[\tlvl=COUNT\t] exist RangeRestriction for %s",
                            rr.annotation_name().c_str());
            } else {
                _need_filter = true;
                _filter_list.at(anno_id) = &(rr.number_spec());
            }
        }
    }
}

result_status_t AnnotationFilter::filter(MatchedDoc * result)
{
    if (_need_filter == false) {
        return RESULT_ACCEPTED;
    }
    DocId docid = result->get_doc_id();
    const FactDoc & fact_doc = result->get_fact_doc();
    for (size_t i = 0; i < fact_doc.annotations.size(); ++i) {
        const Annotation & anno = fact_doc.annotations.at(i);
        const NumberSpec * spec = _filter_list.at(anno.id);
        if (spec != NULL) {
            if (anno.number_value < spec->min() ||
                anno.number_value > spec->max()) {
                UTRACE("doc %llu filted by anno %u %lld",
                            docid,
                            static_cast<uint32_t>(anno.id),
                            anno.number_value);
                return RESULT_INVALID;
            } else {
                UTRACE("doc %llu accepted by anno %u %lld",
                            docid,
                            static_cast<uint32_t>(anno.id),
                            anno.number_value);
            }
        }
    }
    return RESULT_ACCEPTED;
}

REGISTER_RESULT_FILTER(AnnotationFilter);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
