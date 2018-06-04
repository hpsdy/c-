// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_DIMENSION_DOC_H_
#define  UNISE_DIMENSION_DOC_H_

#include <string>
#include <vector>
#include "unise/factory.h"
#include "unise/base.h"

namespace unise {
/**
 * @brief Annotation的取值
 * @note id为对应的AnnotationSchema的Id，AnnotationSchema见unise/annotation_schema.proto
 *       text_value，如果为字符串类型，填写这里
 *       number_value,如果为数字类型，填写这里
 */
struct Annotation {
    AnnotationId id;        ///< 取值范围，参见unise/base.h的类型定义
    std::string text_value; ///< 注意编码必须是UTF-8
    int64_t number_value;   ///< 数字类型，只支持int64类型
    bool operator<(const Annotation & b) const {
        return id < b.id;
    }
    bool operator==(const Annotation & b) const {
        return id == b.id;
    }
    template<class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & id;
            ar & text_value;
            ar & number_value;
        }
};
/**
 * @brief 维度文档基类
 *        内存中的索引使用dimension_name和docid进行的，因此
 *        需要每个dimension doc都具备dimension_name和docid的get方法
 */
class DimensionDoc {
public:
    DimensionDoc() {}
    virtual ~DimensionDoc() {}

    /**
     * @breaf 每个DimensionDoc对象，都需要具备DimensionName空间下
     *        全局唯一的DocId
     *        本函数返回其docid
     *
     * @param [in] : none
     * @param [out] : none
     * @return DocId
     * @retval 当前doc的docid
     * @see
     * @note 
    **/
    virtual DocId get_doc_id() const = 0;

    /**
     * @breaf 每种派生的DimensionDoc,都应该有DimensionName
     *        这个DimensionName同类名一致，在配置文件中，
     *        是DimensionDoc的取值
     *
     * @param [in] : none
     * @param [out] : none
     * @return std::string
     * @retval 当前doc的dimension name
     * @see
     * @note 
    **/
    virtual std::string get_dimension_name() const = 0;

public:
    // 需要建索引的内容，放到这里面
    std::vector<Annotation> annotations;   ///< 为了使用方便，采用public
private: 
    friend class boost::serialization::access; 
    template <typename Archive> 
        void serialize(Archive &ar, const unsigned int version) { 
            ar & annotations; 
        } 
};
}

#endif  // DIMENSION_DOC_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
