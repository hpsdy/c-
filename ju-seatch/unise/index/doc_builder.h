// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_DOC_BUILDER_H
#define  INDEX_DOC_BUILDER_H

#include <vector>
#include <isegment.h>
#include "unise/base.h"
#include "unise/skiplist.h"
#include "index/token_hit.h"

namespace unise {
class QueryNodeValue;
class Annotation;
class AnnotationSchema;
class AnnotationManager;
class FactDoc;
class RepositoryManager;
class DimensionDocManager;

class DocBuilder {
public:
    explicit DocBuilder(RepositoryManager * repository_manager);
    ~DocBuilder();

    /**
     * @breaf 单个FactDoc建正排索引、DocInfo、倒排索引
     *
     * @param [in] : doc, FactDoc的指针
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note 只能单线程调用，整个EngineUnit只能有一个写线程
     *       构建失败，内部打印WARNING LOG
     *       会根据Annotation的类型，建完索引，抛弃部分Annotation
     * @warning 不能重复构建一个doc，内部为了性能考虑，不做重复判断
    **/
    void build(FactDoc * doc);

    /**
     * @breaf 在EngineUnit中删除一个FactDoc的倒排、DocInfo、正排
     *
     * @param [in] : docid, EngineUnit内部唯一的表明该doc的id
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note 只能单线程调用，整个EngineUnit只能有一个写线程
     *       删除失败，内部打印WARNING LOG
    **/
    void remove(DocId docid);

    /**
     * @brief 只有增量构建需要考虑执行级联过滤
     *        该方法在das_inc_builder中调用
     * @retval 多少个doc被影响了
     */
    uint32_t filt_relation_ship(const SkipList<DocId>* docids, uint8_t flag, uint8_t mask);

private:
    void finish_doc();

private:
    RepositoryManager * _repository_manager;
    AnnotationManager * _annotation_manager;
    DimensionDocManager * _dimension_doc_manager;
    // 当前doc的DocInfo
    doc_info_t * _cur_doc_info;
    // 保存当前构建索引的doc待建正排、倒排的token信息
    std::vector<TokenHit> _token_hits;
    // the token id tobe deleted
    std::vector<TokenId> _token_id_list;
    // 全局词典指针，单例，不可释放
    scw_worddict_t * _dict;
    // 线程切词缓冲区，不可释放
    scw_out_t * _handler;
    // the token id tobe 
    std::vector<TokenId> _relation_token_ids;

    uint64_t _doc_count; ///< 计数
    uint64_t _anno_count;
    uint64_t _token_count;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(DocBuilder);
};

}
#endif  // INDEX_DOC_BUILDER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
