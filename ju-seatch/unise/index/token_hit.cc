// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/token_hit.h"
#include <cstddef>
#include <uln_sign_murmur.h>
#include "unise/base.h"
#include "unise/util.h"
#include "unise/annotation_schema.pb.h"

namespace unise
{

bool TokenHitCompare(const TokenHit & a, const TokenHit & b)
{
    return (a.get_token_id() == b.get_token_id() &&
            a.get_score() == b.get_score() &&
            a.get_doc_id() == b.get_doc_id());
}

TokenHit::TokenHit(int32_t score,
        DocId docid,
        const AnnotationSchema& schema,
        const string & value,
        int32_t pos,
        bool generate_section_token) :
    score_(score),
    docid_(docid),
    section_id_(schema.section_id()),
    annotation_id_(schema.id()),
    value_(value),
    pos_(pos) {
    string token_string;
    // generate the token_string
    if (generate_section_token) {
        token_string.assign("SECT" + TOKEN_SEP + schema.section_name() + TOKEN_SEP +
                value_ + TOKEN_SEP);
    } else {
        token_string.assign("ANNO" + TOKEN_SEP + schema.annotation_name() + TOKEN_SEP +
                value_ + TOKEN_SEP);
        section_id_ = ILLEGAL_SECTION_ID;
        // TODO(wangguangyuan):正排中如section_id非法，不存储sectionid
    }
    
    // get the token_id
    // murmur 只有参数为 NULL 时才出错，所以这里不处理返回值
    uln_sign_murmur2_64(token_string.data(), token_string.size(),
            reinterpret_cast<long long unsigned *>(&token_id_));
    UDEBUG("Token id[%llu] value[%s] anno_id[%u] anno_name[%s] section_id[%u]"
           " section_name[%s] pos[%d] SECTION[%d]",
           token_id_, value_.c_str(), static_cast<uint32_t>(annotation_id_),
           schema.annotation_name().c_str(), static_cast<uint32_t>(section_id_),
           schema.section_name().c_str(), pos_, static_cast<int32_t>(generate_section_token));
}

/**
 * @brief NUMBER类型的Annotation，转换成token的方法
 * @note NUMBER类型的Annotation，不能在Section中检索
 */
TokenHit::TokenHit(int32_t score,
        DocId docid,
        const AnnotationSchema& schema,
        int64_t value,
        int32_t shift) :
    score_(score),
    docid_(docid),
    section_id_(ILLEGAL_SECTION_ID),
    annotation_id_(schema.id()),
    pos_(1) {
    string token_string;
    value_.assign(Int64ToString(value) + TOKEN_SEP + IntToString(shift));
    // generate the token_string
    token_string.assign(TOKEN_SEP + schema.annotation_name() + TOKEN_SEP +
          value_ + TOKEN_SEP);
    // get the token_id
    // murmur 只有参数为 NULL 时才出错，所以这里不处理返回值
    uln_sign_murmur2_64(token_string.data(), token_string.size(),
            reinterpret_cast<long long unsigned *>(&token_id_));
}

void TokenHit::print() const
{
    UTRACE("TokenHit [token_id:%llu "
            " value:%s"
            " score:%d"
            " docid:%llu"
            " section_id:%u"
            " annotation_id:%u"
            " pos:%d",
            token_id_, value_.c_str(), score_, docid_, section_id_, annotation_id_, pos_);
}

}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
