// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_TOKEN_HIT_H
#define  INDEX_TOKEN_HIT_H

#include <string>
#include "unise/base.h"

namespace unise
{
class AnnotationSchema;

/**
 *  @brief 一个term，命中一个doc的某一个位置，相关信息封装到一起
 *         成为一个token。建倒排的过程，就是将FactDoc的annotation字段先
 *         切词，生成terms，然后，token化，构建倒排、正排，都是针对token
 *         进行的
 */
class TokenHit
{
public:
    /**
     * @brief text类型的annotation生成的TokenHit
     *
     */
    TokenHit(int32_t score,
            DocId docid,
            const AnnotationSchema& schema,
            const std::string & value,
            int32_t pos,
            bool generate_section_token = false);

    /**
     * @brief number类型的annotation生成的TokenHit
     *
     */
    TokenHit(int32_t score,
            DocId docid,
            const AnnotationSchema& schema,
            int64_t value,
            int32_t shift);

    ~TokenHit() {}

    AnnotationId get_annotation_id() const {
        return annotation_id_;
    }
    const std::string & get_token_value() const {
        return value_;
    }
    int32_t get_pos() const {
        return pos_;
    }
    TokenId get_token_id() const {
        return token_id_;
    }
    int32_t get_score() const {
        return score_;
    }
    DocId get_doc_id() const {
        return docid_;
    }
    SectionId get_section_id() const {
        return section_id_;
    }
    void print() const;
    bool operator < (const TokenHit & b) const {
        if (token_id_ < b.get_token_id()) {
            return true;
        } else if (token_id_ > b.get_token_id()) {
            return false;
        } else if (score_ > b.get_score()) {
            return true;
        } else if (score_ < b.get_score()) {
            return false;
        } else if (docid_ < b.get_doc_id()) {
            return true;
        } else if (docid_ > b.get_doc_id()) {
            return false;
        } else if (section_id_ < b.get_section_id()) {
            return true;
        } else if (section_id_ > b.get_section_id()) {
            return false;
        } else if (annotation_id_ < b.get_annotation_id()) {
            return true;
        } else if (annotation_id_ > b.get_annotation_id()) {
            return false;
        } else if (pos_ < b.get_pos()) {
            return true;
        } else {
            return false;
        }
    }

private:
    int32_t score_;     ///< 命中doc的分数
    DocId docid_;     ///< 命中doc的docid
    SectionId section_id_;
    AnnotationId annotation_id_;
    std::string value_;  ///< token的取值，注意，不是term
    int32_t pos_;       ///< term命中annotation的位置，从1开始

    TokenId token_id_;    ///< value_的64位hash
};

// used for create DocHit
bool TokenHitCompare(const TokenHit & a, const TokenHit & b);

}
#endif  // INDEX_TOKEN_HIT_H
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
