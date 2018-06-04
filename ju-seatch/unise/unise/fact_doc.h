// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
//
// Brief: 请用户关注FactDoc,重要接口
#ifndef  UNISE_FACT_DOC_H_
#define  UNISE_FACT_DOC_H_

#include <string>
#include <vector>
#include "unise/dimension_doc.h"
#include "unise/factory.h"
#include "unise/base.h"

namespace unise {
/**
 * @brief FactDoc是一种特殊的DimensionDoc，是检索的对象
 *        用户把需要建索引的字段放到FactDoc的annotations中，索引逻辑对
 *        annotation生成token，然后构建倒排和正排，检索时返回的docid就是
 *        FactDoc的id
 *
 * @note 1) 倒排链顺序:一个token的倒排链中,score大的doc最先被检索到,score相同
 *          时，docid小的先被检索到
 *       2) FactDoc对象，也采用DocFactory构造，注意构造时，需要填充需要
 *          建索引的annotation
 *       3) 注意一个EngineUnit内部只能有一种FactDoc，docid不能冲突
 *       4) 注意FactDoc继承DimensionDoc，用户实现自己的FactDoc，需要提供
 *          DimensionDoc的纯虚函数
 *       5) 注意Annotation在检索模型中，只有STORE类型的annotation会被存储
 *          并且，是按照id升序存储的
 *
 */
class FactDoc : public DimensionDoc {
public:
    FactDoc() {}
    virtual ~FactDoc() {}

    /**
     * @breaf 返回fact_doc的score
     *
     * @param [in] : none
     * @param [out] : none
     * @return int32_t
     * @retval 当前doc的score
     * @see
     * @note 
    **/
    virtual int32_t get_score() const = 0;
private: 
    friend class boost::serialization::access; 

    template <typename Archive> 
        void serialize(Archive &ar, const unsigned int version) { 
            ar & boost::serialization::base_object<DimensionDoc>(*this); 
        } 
};

}

#endif  // UNISE_FACT_DOC_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
