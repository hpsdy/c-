// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_BASE_H
#define  UNISE_BASE_H

#include <string>
#include <iostream>
#include <com_log.h>
#include <google/protobuf/stubs/common.h>
#include "boost/serialization/vector.hpp"
#include "boost/archive/binary_iarchive.hpp" 
#include "boost/archive/binary_oarchive.hpp" 
#include "boost/serialization/string.hpp" 
#include "boost/serialization/hash_map.hpp"
#include "unise/basictypes.h"

namespace unise
{
#pragma pack(push, 1)

class ForwardIndex;
class FactDoc;

// 所有需要程序自动处理分析(如MapRed)的关键业务日志，打印到自定义的I等级上，
// 独立一个文件可以减少无谓的数据传输和计算，所以这个宏的使用应该受到严格限制
#define UINFO(fmt, arg...) \
    com_writelog("I", __FILE__":"UL_LOGLINE(__LINE__)"] "fmt, ##arg)

// 以下内容与 comlog.h 中宏基本相对应，主要是在格式上的变动，新的日志格式
// 参照 glog，配合 comlog 的自定义前缀，能达到与 glog 基本一致。
#define UFATAL(fmt, arg...) \
    com_writelog(COMLOG_FATAL, __FILE__":"UL_LOGLINE(__LINE__)"] "fmt, ##arg)

#define UWARNING(fmt, arg...) \
    com_writelog(COMLOG_WARNING, __FILE__":"UL_LOGLINE(__LINE__)"] "fmt, ##arg)

#define UNOTICE(fmt, arg...) \
    com_writelog(COMLOG_NOTICE, __FILE__":"UL_LOGLINE(__LINE__)"] "fmt, ##arg)

#define UTRACE(fmt, arg...) \
    com_writelog(COMLOG_TRACE, __FILE__":"UL_LOGLINE(__LINE__)"] "fmt, ##arg)

#ifdef NDEBUG
#define UDEBUG(fmt, arg...) static_cast<void>(0)
#else
#define UDEBUG(fmt, arg...) \
    com_writelog(COMLOG_DEBUG, __FILE__":"UL_LOGLINE(__LINE__)"] "fmt, ##arg)
#endif


// 构造token字面的时候，annotation名或section名与token取值的连接符
const std::string TOKEN_SEP = "__";
// 不使用分词算法，采用哪些符号对annotation的text value进行切分
const std::string WORD_SEP = " .,:;[]{}_!";
// 使用分词算法时，过滤header和tailer的哪些字符
const std::string TRIM_LETTERS = " .,:;[]{}_!";
// DAS增量数据的分隔符
const char DAS_SEP = '\t'; // TODO: 使用das的info信息，自动获取分隔符

// AnnotationId的定义，如果有需要，可以改为更大的uint16,uint32类型
typedef uint16_t AnnotationId;
// 最大的annotation id
const AnnotationId ANNOTATION_ID_MAX = static_cast<AnnotationId>(-1) - 1;
// 非法annotation id
const AnnotationId ILLEGAL_ANNOTATION_ID = static_cast<AnnotationId>(-1);

// SectionId的定义，如果有需要，可以改为更大的uint16,uint32类型
typedef uint8_t SectionId;
const SectionId SECTION_ID_MAX = static_cast<SectionId>(-1) - 1;
// 非法section id
const SectionId ILLEGAL_SECTION_ID = static_cast<SectionId>(-1);

// TokenId的定义
typedef uint64_t TokenId;
const TokenId ILLEGAL_TOKEN_ID = static_cast<TokenId>(-1);

// token出现的位置非法
const int32_t ILLEGAL_POS = 0x7fffffff;

// docid类型的定义
typedef uint64_t DocId;
// 非法docid
const DocId ILLEGAL_DOCID = static_cast<DocId>(-1);
// 最小的docid
const DocId DOCID_MIN = 0;

// 非法score
const int32_t ILLEGAL_SCORE = -1;
// 最大的分数
const int32_t SCORE_MAX = 0x7fffffff;

// 打分插件的分数类型
typedef int64_t dynamic_score_t;


// 默认流量实验id,DEFAULT_SAMPLE_ID在插件的配置中必须存在
const uint64_t DEFAULT_SAMPLE_ID = 0ULL;

// annotation需要切词时，最多保留多少个切词token
const uint32_t ANNOTATION_SIZE_MAX = 409600;

// 非法的das层级ID
const size_t ILLEGAL_LEVEL_ID = 0x7fffffff;

const uint32_t FORWARD_MAGIC = 0x19860630;
const uint32_t INVERTED_MAGIC = 0x20120706;

// 最大的uint32_t, 最大的event_id
const uint32_t MAX_EVENT_ID = static_cast<uint32_t>(-1);

/// @brief 一个doc内，某一个token的命中信息
struct doc_token_hit_t {
    SectionId section_id;
    AnnotationId annotation_id;
    int32_t pos;
};

/// @brief 一个doc的全局信息
struct doc_info_t {
    DocId docid;                   ///< 检索到的fact doc的docid
    int32_t score;                 ///< 当前doc的分数
    ForwardIndex * forward_index;  ///< 当前doc的正排指针
    // 使用const修饰
    const FactDoc * fact_doc;      ///< 当前doc的fact_doc指针
    uint8_t filter_flag;           ///< 过滤位，表示FilterRelationShip的状态

    bool operator<(const doc_info_t & b) const {
        if (score > b.score ||
            score == b.score && docid < b.docid) {
            return true;
        } else {
            return false;
        }
    }

    bool operator==(const doc_info_t & b) const {
        return (score == b.score && docid == b.docid);
    }
};

/// @brief 倒排链基本单元
struct doc_hit_t {
    DocId docid;  // second rank
    int32_t score;  // first rank

    bool operator<(const doc_hit_t & b) const {
        return (score > b.score ||
                score == b.score && docid < b.docid);
    }

    bool operator==(const doc_hit_t & b) const {
        return (score == b.score && docid == b.docid);
    }

    void reset() {
        docid = ILLEGAL_DOCID;
        score = ILLEGAL_SCORE;
    }
    /**
     * @brief 代表这个doc hit应该在倒排链的最后面
     *        需要分数最小(ILLEGAL_SCORE)，docid最大(ILLEGAL_DOCID)
     */
    void set_max() {
        docid = ILLEGAL_DOCID;
        score = ILLEGAL_SCORE;
    }

    /**
     * @brief 代表这个doc hit排在倒排链的最前面
     *        需要分数最大(SCORE_MAX),docid最小(DOCID_MIN)
     */
    void set_min() {
        docid = DOCID_MIN;
        score = SCORE_MAX;
    }
};

/// @brief 检索插件的返回值
enum result_status_t {
    RESULT_ACCEPTED = 0,           // accepted currently
    RESULT_REPLACE = 1,            // replace others
    RESULT_REJECTED_LOW_SCORE = 2,
    RESULT_REJECTED_DUPLICATE = 3, // replaced by others
    RESULT_INVALID = 4,            // invalid result
    RESULT_FILTED_EARLY = 5,       // filted by ealry filter
    RESULT_FILTED_LATER = 6,       // filted by later filter
    RESULT_FILTED_FINAL = 7,       // filted by final filter
};

/// @brief 描述das增量的一行数据
///   其中event_id不能跟上一行event_id重复
///   op_id取值只能是0,1,2
///   level_id跟配置文件中DimensionDoc的Id配置项对应
///      如果没有对应的，不处理改行
///   other是这一行增量数据的除去前4个数字之外的字符串表示
struct das_inc_record_t {
    uint32_t event_id;             // the event id of das inc
    uint32_t op_id;                // 0-add, 1-delete, 2-delete-and-add
    uint32_t level_id;             // the das level
    uint32_t from_id;              // the record's source, from das, not use here
    std::string other;             // other info of the line, useful to add operation
};

/// @brief 定义基量,增量数据类型
enum data_t { BASE_DATA = 0, INC_DATA };

/// @brief 定义基量,增量数据信息
struct event_info_t {
    event_info_t() : type(BASE_DATA), event_id(MAX_EVENT_ID), level_id(ILLEGAL_LEVEL_ID) {}
    data_t type;
    uint32_t event_id;
    uint32_t level_id;
};

#pragma pack(pop)
}

#endif  // UNISE_BASE_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
