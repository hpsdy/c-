// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include <boost/locale.hpp>
#include "index/index.h"

DEFINE_string(text_seg_sep, unise::WORD_SEP, "the seg sep chars");
DECLARE_int32(max_wordseg_buffer_size);

namespace unise {

///< 切词缓冲buffer，全局变量，防止栈溢出
token_t g_tokens[ANNOTATION_SIZE_MAX];

/**
 * @brief 对长文本annotation进行切词，生成token
 * @warning 如果切词方式只为BASIC或WPCOMP，pos才有效
 *          对其他切词方式，生成的pos不代表真实的offset
 */
void get_token_hit_list_by_seg(
            const doc_info_t & doc_info,
            const Annotation & annotation,
            const AnnotationSchema& schema,
            std::vector<TokenHit> &token_hit_list,
            scw_worddict_t * dict,
            scw_out_t * handler) {
    // 首先根据schema进行各种配置初始化
    bool build_section = schema.section_name() != "" ? true : false;
    bool trans_conv = false;
    const TextSchema & text_schema = schema.text_schema();
    // 大写转小写、繁体转简体、全角转半角
    // warning: has_xxx mean to Backwards Compatibility
    if (!text_schema.has_trans_conversion() || text_schema.trans_conversion()) {
        trans_conv = true;
    }
    // 读取切词方式配置
    int type = 0;
    // warning: has_xxx mean to Backwards Compatibility
    if (!text_schema.has_scw_out_flags()) {
        // 未设置，采用默认配置
        type = SCW_OUT_WPCOMP;
    } else {
        type = text_schema.scw_out_flags();
    }
    // 根据schema决定切词的配置
    int dyn_flag = 0;
    if (text_schema.has_scw_lang_para()) {
        dyn_flag = text_schema.scw_lang_para();
    } else if (type | SCW_OUT_DISAMB) {
        // 如果有使用消歧义切词，那么这里自作主张打开一些开关
        dyn_flag = SCW_CRF | SCW_DISAMB;
    }
    // 根据schema决定切词的语言
    int lang_flag = -1;
    if (text_schema.has_scw_seg_lang()) {
        lang_flag = text_schema.scw_seg_lang();
    } else {
        // 默认使用中文切词
        lang_flag = LANGTYPE_SIMP_CHINESE;
    }
    // 根据FLAGS定义和默认的最大缓冲长度，确定当前切词缓冲区长度
    uint32_t max_wordseg_buffer_size =
        std::min(ANNOTATION_SIZE_MAX,
                    static_cast<uint32_t>(FLAGS_max_wordseg_buffer_size));

    // 计算当前分段的起始偏移量
    std::string text_value(annotation.text_value);

    // 开始处理
    if (trans_conv) {
        trans_word(annotation.text_value, &text_value);
        annotation.text_value = text_value;
    }
    // 进行切词
    if (scw_segment_words(dict,
                    handler,
                    text_value.c_str(),
                    text_value.length(),
                    lang_flag,
                    &dyn_flag) != 1) {
        UWARNING("[\tlvl=FOLLOW\t] annotation[%s] value[%s] seg fail",
                    schema.annotation_name().c_str(),
                    text_value.c_str());
        return;
    }
    // 根据配置取切词结果，并转化为token
    for (int f = SCW_OUT_BASIC; f <= SCW_OUT_DISAMB; f = f << 1) {
        // not set
        if (0 == (f & type)) {
            continue;
        }
        UDEBUG("word segment type:%d", f);
        int count = scw_get_token_1(handler,
                    f,
                    g_tokens,
                    max_wordseg_buffer_size);
        int32_t cur_token_offset = 0;
        for (int i = 0; i < count; ++i) {
            const token_t & token = g_tokens[i];
            // 在索引中，pos从1开始
            int32_t cur_pos = cur_token_offset + 1;
            cur_token_offset += token.length;
            UDEBUG("token[%s] length[%u] offset[%u] type[%u] weight[%u]",
                        token.buffer, token.length, cur_pos, token.type, token.weight);
            // trim the header and tailer
            // 更好是采用停用词，或者更多过滤算法
            // 不一定对所有的词建索引
            std::string value;
            TrimString(token.buffer, TRIM_LETTERS.c_str(), &value);
            if (value == "") {
                continue;
            }

            // note: pos start from 1
            TokenHit token_hit(doc_info.score,
                        doc_info.docid,
                        schema,
                        value,
                        cur_pos);
            // TODO(wangguangyuan) : use more token propertys
            token_hit_list.push_back(token_hit);
            if (build_section) {
                TokenHit token_hit(doc_info.score,
                            doc_info.docid,
                            schema,
                            value,
                            cur_pos,
                            true);
                token_hit_list.push_back(token_hit);
            }
        }
    }
}

/**
 * @note 内部不需要判断schema的合法性，外层有校验
 */
void get_token_hit_list_from_annotation(
            const doc_info_t & doc_info,
            const Annotation & annotation,
            const AnnotationSchema& schema,
            std::vector<TokenHit> &token_hit_list,
            scw_worddict_t * dict,
            scw_out_t * handler)
{
    GOOGLE_DCHECK(handler != NULL);
    if (!check_annotation(annotation, schema)) {
        return;
    }
    
    if (schema.annotation_type() == TEXT) {
        std::string text_value(annotation.text_value);
        bool build_section = schema.section_name() != "" ? true : false;
        bool trans_conv = false;
        // 大写转小写、繁体转简体、全角转半角
        // warning: has_xxx mean to Backwards Compatibility
        if (!schema.text_schema().has_trans_conversion() ||
            schema.text_schema().trans_conversion()) {
            trans_conv = true;
        }
        switch (schema.text_schema().index_type()) {
        case TEXT_FULL: {
            if (trans_conv) {
                trans_word(annotation.text_value, &text_value);
            }
            TokenHit token_hit(doc_info.score,
                        doc_info.docid,
                        schema,
                        text_value,
                        1);
            token_hit_list.push_back(token_hit);
            if (build_section) {
                TokenHit token_hit(doc_info.score,
                            doc_info.docid,
                            schema,
                            text_value,
                            1,
                            true);
                token_hit_list.push_back(token_hit);
            }
            break;
        }
        case PREFIX: {
            if (trans_conv) {
                trans_word(annotation.text_value, &text_value);
            }
            std::vector<std::string> strs;
            get_prefixs_from_string(text_value, &strs, "-");
            size_t strs_size = strs.size();
            for (size_t i = 0; i < strs_size; ++i) {
                // 前缀索引，pos越大，则长度越长，做相关性的时候可以使用
                TokenHit token_hit(doc_info.score,
                            doc_info.docid,
                            schema,
                            strs.at(i),
                            i + 1);
                token_hit_list.push_back(token_hit);
                if (build_section) {
                    TokenHit token_hit(doc_info.score,
                                doc_info.docid,
                                schema,
                                strs.at(i),
                                i + 1,
                                true);
                    token_hit_list.push_back(token_hit);
                }
            }
            break;
        }
        case TEXT_SEG: {
            get_token_hit_list_by_seg(
                        doc_info,
                        annotation,
                        schema,
                        token_hit_list,
                        dict,
                        handler);
            break;
        }
        case TEXT_SEG_BY_SEP: {
            // get segs
            vector<string> seg_strings;
            string_split(annotation.text_value, FLAGS_text_seg_sep, &seg_strings);
            // add token hits
            for (size_t i = 0; i < seg_strings.size(); ++i) {
                string_trim(&seg_strings[i], FLAGS_text_seg_sep);
                const std::string * token_value = &seg_strings[i];
                if (trans_conv) {
                    trans_word(seg_strings.at(i), &text_value);
                    token_value = &text_value;
                }
                // note: pos start from 1
                TokenHit token_hit(doc_info.score,
                            doc_info.docid,
                            schema,
                            *token_value,
                            i + 1);
                token_hit_list.push_back(token_hit);
                if (build_section) {
                    TokenHit token_hit(doc_info.score,
                                doc_info.docid,
                                schema,
                                *token_value,
                                i + 1,
                                true);
                    token_hit_list.push_back(token_hit);
                }
            }
            break;
        }
        case TEXT_WORD: {
            if (trans_conv) {
                trans_word(annotation.text_value, &text_value);
            }
            // TODO(wangguangyuan) : 避免转两次
            // get wchar
            std::wstring words = boost::locale::conv::utf_to_utf<wchar_t>(text_value);
            // add token hits
            for (size_t i = 0; i < words.length(); ++i) {
                std::string token_value = boost::locale::conv::utf_to_utf<char>(
                            &words[i],
                            &words[i] + 1);
                // note: pos start from 1
                TokenHit token_hit(doc_info.score,
                            doc_info.docid,
                            schema,
                            token_value,
                            i + 1);
                token_hit_list.push_back(token_hit);
                if (build_section) {
                    TokenHit token_hit(doc_info.score,
                                doc_info.docid,
                                schema,
                                token_value,
                                i + 1,
                                true);
                    token_hit_list.push_back(token_hit);
                }
            }
            break;
        }
        default:
            UWARNING("[\tlvl=FOLLOW\t] not support Annotation [%s] TextIndexType:%d",
                        schema.annotation_name().c_str(), schema.text_schema().index_type());
        }
    } else if (schema.annotation_type() == NUMBER) {
        vector<std::pair<int64_t, int32_t> > number_pairs;
        get_number_range_pairs(annotation.number_value,
                    schema.number_schema().accuracy(),
                    schema.number_schema().min(),
                    schema.number_schema().max(),
                    &number_pairs);
        for (size_t i = 0; i < number_pairs.size(); ++i) {
            TokenHit token_hit(doc_info.score,
                        doc_info.docid,
                        schema,
                        number_pairs[i].first,
                        number_pairs[i].second);
            token_hit_list.push_back(token_hit);
        }
    } else {
        UWARNING("[\tlvl=FOLLOW\t] not support Annotation [%s] AnnotationType:%d",
                 schema.annotation_name().c_str(), schema.annotation_type());
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=80: */
