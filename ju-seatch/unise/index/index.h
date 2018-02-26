// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_INDEX_H_
#define  INDEX_INDEX_H_

#include <stdint.h>
#include <algorithm>
#include <string>
#include <vector>
#include "Configure.h"
#include "isegment.h"
#include "ucode.h"
#include "ul_string_i18n_codetype.h"
#include "unise/base.h"
#include "util/util.h"
#include "unise/asl_wordseg.h"
#include "unise/fact_doc.h"
#include "unise/annotation_schema.pb.h"
#include "index/repository_manager.h"
#include "index/annotation_manager.h"
#include "index/doc_builder.h"
#include "index/token_hit.h"
#include "index/token_list.h"
#include "index/doc_hit_list.h"

DECLARE_string(wordseg_flags);
DECLARE_bool(use_trans_word);
namespace unise
{

struct dimension_doc_config_t {
    std::string name;
    uint32_t id;
};

/**
* @brief 获取DimensionDoc的配置信息
*
*/
inline std::vector<dimension_doc_config_t> get_dimension_doc_configs(
        const comcfg::ConfigUnit & dimension_conf)
{
    /*{{{*/
    std::vector<dimension_doc_config_t> dimension_doc_configs;
    size_t num = dimension_conf.size();
    for (size_t i = 0; i < num; ++i) {
        std::string dimension_doc_name(dimension_conf[i]["DimensionName"].to_cstr());
        uint32_t id = dimension_conf[i]["Id"].to_uint32();
        dimension_doc_config_t config = {dimension_doc_name, id};
        dimension_doc_configs.push_back(config);
    }
    return dimension_doc_configs;
}/*}}}*/

/**
 * @warning 调用该方法时，请确保已经调用了AslWordseg的init函数
 * @note 如果某转换失败，那么会跳过该转换
 */
inline void trans_word(const std::string& org, std::string * dst)
{
    char * buf = new char[ANNOTATION_SIZE_MAX + 1];
    char * out_buf = new char[ANNOTATION_SIZE_MAX + 1];
    int l = std::min(ANNOTATION_SIZE_MAX, static_cast<uint32_t>(org.length()));

    // 进行大写到小写的转换
    if (NULL == ul_to_lower(org.c_str(), l, buf, ANNOTATION_SIZE_MAX,
                CODETYPE_UTF8, LANGTYPE_GLOBAL)) {
        UWARNING("ul_to_lower[%s] failed", org.c_str());
        strncpy(buf, org.c_str(), l);
    }
    buf[l] = '\0';

    // 进行全角到半角的转换
    if (NULL == ul_to_half(buf, l, out_buf, ANNOTATION_SIZE_MAX, CODETYPE_UTF8)) {
        UWARNING("ul_to_half[%s] failed", buf);
        strncpy(out_buf, buf, l);
    }
    out_buf[l] = '\0';

    // 进行繁体到简体的转换
    int ret = uln_utf8_trans2simplified(out_buf, l, buf, ANNOTATION_SIZE_MAX);
    if (ret <= 0) {
        UWARNING("trans2simplified[%s] failed ret[%d]", buf, ret);
        strncpy(buf, out_buf, l);
    } else {
        l = ret;
    }
    buf[l] = '\0';
    dst->assign(buf);
    delete []buf;
    delete []out_buf;
}

inline void get_prefixs_from_string(const std::string& value,
                                    std::vector<std::string> * prefixs,
                                    const std::string& sep = "-")
{
    std::vector<std::string> kvs;
    string_split(value, sep, &kvs);

    // build prefix
    std::string str;
    for (size_t j = 0; j < kvs.size(); ++j) {
        if (j == 0) {
            str.assign(kvs.at(j));
        } else {
            str.append("-" + kvs.at(j));
        }
        prefixs->push_back(str);
    }
}

/**
 * @brief 64位的无符号数至少需要几个二进制位数来存储
 *        如4，需要3个二进制位；3，需要2个二进制位
 * @note  注意0需要1个二进制位；1需要1个二进制位
 */
inline int32_t get_value_size(uint64_t value) {
    int32_t val_size = 0;
    do {
        ++val_size;
        value = value >> 1;
    } while (value);
    return val_size;
}

/**
 * @brief 将min和max都向右移位shift，然后，枚举min到max，并恢复原值存储
 *        e.g. min:0x13, max:0x34, shift:4
 *             输出有：0x20, 0x30
 */
inline void get_range_sequence(
            int64_t min,
            int64_t max,
            int32_t shift,
            std::vector<std::pair<int64_t, int32_t> > * pairs) {
    min = min >> shift;
    max = max >> shift;
    while (min <= max) {
        pairs->push_back(std::make_pair(min << shift, shift));
        ++min;
    }
}

/**
 * @brief 根据查询区间，返回能精确覆盖该查询区间的多个区间
 * @params [in] min_bound, 查询的下界，闭区间
 * @params [in] max_bound, 查询的上界，闭区间
 * @params [in] min, 当前查询字段的配置下界
 * @params [in] max, 当前查询字段的配置上界
 * @params [in] precision_step，步长精度，几个二进制位
 * @params [in] pairs，输出，根据输出的多个区间，构造OR查询
 * @note  参考Lucene对NumberRangeQuery的实现
 *        org.apache.lucene.util.NumericUtils类的splitRange()
 */
inline void get_proper_range_pairs(
            int64_t min_bound,
            int64_t max_bound,
            int64_t min,
            int64_t max,
            int32_t precision_step,
            std::vector<std::pair<int64_t, int32_t> > * pairs) {
    GOOGLE_DCHECK_LE(precision_step, 8);
    GOOGLE_DCHECK_GE(precision_step, 1);
    if (min_bound > max_bound) {
        return;
    }
    if (min_bound == 0) {
        pairs->push_back(std::make_pair(0LL, 0));
        min_bound = 1;
    }

    // 根据max的二进制位数，以及步长精度，决定最终trie树有几层
    // e.g. 如果max有9位，精度为8，那么有两层
    int32_t val_size = get_value_size(max);

    for (int32_t shift = 0; ; shift += precision_step) {
        int64_t diff = 1LL << (shift + precision_step);
        int64_t mask = ((1LL << precision_step) - 1LL) << shift;
        bool has_lower = (min_bound & mask) != 0LL;
        bool has_upper = (max_bound & mask) != mask;
        int64_t next_min_bound = (has_lower ? (min_bound + diff) : min_bound) & ~mask;
        int64_t next_max_bound = (has_upper ? (max_bound - diff) : max_bound) & ~mask;
        if (shift + precision_step >= val_size ||
            next_min_bound > next_max_bound ||
            next_min_bound < min_bound ||
            next_max_bound > max_bound) {
            get_range_sequence(min_bound, max_bound, shift, pairs);

#ifndef NDEBUG
            for (size_t i = 0; i < pairs->size(); ++i) {
                UNOTICE("NumberRangeQuery idx[%d] term[%lld] shift[%d]",
                            i, pairs->at(i).first, pairs->at(i).second);
            }
#endif
            break;
        }
        if (has_lower) {
            get_range_sequence(min_bound, min_bound | mask, shift, pairs);
        }
        if (has_upper) {
            get_range_sequence(max_bound & ~mask, max_bound, shift, pairs);
        }
        min_bound = next_min_bound;
        max_bound = next_max_bound;
    }
}

/**
 * @brief 根据指定的区间，生成value在该区间的所有trie区间
 *        如果precision_step=4，那么从最低位，每次将mask移动4bit作为term
 *        结合shift，作为一个token
 * @note  max如果有12个bit，那么会生成2个token
 *        e.g. 0x234, token: 0x200, 0x230, 0x234
 * @warning 需要根据max的位数，而不是实际value的位数
 */
inline void get_number_range_pairs(int64_t value, int32_t precision_step,
        int64_t min, int64_t max, std::vector<std::pair<int64_t, int32_t> > * pairs) {
    GOOGLE_DCHECK_LE(precision_step, 8);
    GOOGLE_DCHECK_GE(precision_step, 1);
    // warning: 注意，必须用max的，不能用value的位数
    // note: 尝试用value的位数，不生成无谓的0
    int32_t val_size = get_value_size(value);
    for (int32_t shift = 0; shift < val_size; shift += precision_step) {
        int64_t mask = (1LL << shift) - 1LL;
        pairs->push_back(std::make_pair(value & ~mask, shift));
    }
}

/**
 * @brief 检查anno的取值是否合法
 *        调用前需要保证schema的name与anno的name一致
 *        id一致
 */
inline bool check_annotation(const Annotation& anno, const AnnotationSchema& schema)
{
    GOOGLE_DCHECK_EQ(anno.id, schema.id());
    // 字符串类型的annotation，需要检查是否有字符串取值，没有则不建索引
    if (schema.annotation_type() == TEXT &&
        anno.text_value == "") {
        UTRACE("annotation [%s] missing text_value", schema.annotation_name().c_str());
        return false;
    }
    // 数字类型的annotation，需要检查是否在schema范围内，不在，则不建索引
    if (schema.annotation_type() == NUMBER &&
        (anno.number_value < schema.number_schema().min() ||
         anno.number_value > schema.number_schema().max())) {
        UWARNING("annotation [%s] number_value [%lld] not in range [%lld,%lld]",
                 schema.annotation_name().c_str(),
                 anno.number_value,
                 schema.number_schema().min(),
                 schema.number_schema().max());
        return false;
    }
    return true;
}

/**
 * @brief 对长文本获取TokenHit列表
 */
void get_token_hit_list_by_seg(
            const doc_info_t & doc_info,
            const Annotation & annotation,
            const AnnotationSchema& schema,
            std::vector<TokenHit> &token_hit_list,
            scw_worddict_t * dict,
            scw_out_t * handler);

/**
 * @brief 通过Annotation获取TokenHit列表
 *
 */
void get_token_hit_list_from_annotation(
            const doc_info_t & doc_info,
            const Annotation & annotation,
            const AnnotationSchema& schema,
            std::vector<TokenHit> &token_hit_list,
            scw_worddict_t * dict,
            scw_out_t * handler);

inline int WriteVint32(int32_t value, char* buf, int buf_len)
{
    /*{{{*/
    uint8_t bytes[5];
    int size = 0;
    while (value > 0x7F) {
        bytes[size++] = (static_cast<uint8_t>(value) & 0x7F) | 0x80;
        value >>= 7;
    }
    bytes[size++] = static_cast<uint8_t>(value) & 0x7F;
    if (buf_len < size) {
        return -1;
    }
    memcpy(buf, bytes, size);
    return size;
}/*}}}*/

inline int ReadVint32(const char* buf, int32_t &value)
{
    /*{{{*/
    value = 0;
    int rlen = 0;
    const uint8_t *bytes = (const uint8_t*)buf;
    int left_move = 0;
    while (true) {
        uint32_t num = *bytes & 0x80;
        value += (num << left_move);
        rlen++;
        left_move += 7;
        if (0 == *bytes & 0x80) {
            break;
        }
        bytes++;
    }
    return rlen;
}/*}}}*/

}

#endif  // INDEX_INDEX_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=80: */
