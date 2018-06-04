// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_REPOSITORY_MANAGER_H
#define  INDEX_REPOSITORY_MANAGER_H

#include <list>
#include <set>
#include "unise/base.h"
#include "unise/boost_wrap.h"
#include <bsl/containers/hash/bsl_phashmap.h>

namespace unise
{
class QueryNodeValue;
class RangeRestriction;
class TokenList;
class AnnotationManager;
class ForwardIndex;
class DimensionDocManager;

using std::list;
using std::set;

struct DocInfoComp {
    bool operator()(doc_info_t* const & a,
            doc_info_t* const & b) const {
        return (*a) < (*b);
    }
};

/**
 * @breaf 一个EngineUnit具有一个RepositoryManager对象
 *        RepositoryManager负责管理三类数据：
 *        1. 正排，forward index
 *        2. doc info
 *        3. 倒排，inverted index
 *
 *        TODO:其中doc info和正排可以结合起来
 * @note 下面的成员函数，如果没有特别注明多线程安全，
 *       那么就是非安全的
 */
class RepositoryManager
{
public:
    explicit RepositoryManager(DimensionDocManager *);
    ~RepositoryManager();

    /**
     * @brief RepositoryManager需要初始化后才能被检索端和索引端使用
     *        提供的string为临时的参数接口，AnnotationSchema文件的路径
     *        后续改为comcfg
     *
     */
    bool init(const std::string& );

    /**
     * @breaf 根据查询value，获取一个TokenList，TokenList内部包含
     *        实时链和历史链
     *
     * @param [in] : QueryNodeValue
     * @param [out] : none
     * @return const TokenList*
     * @retval 非NULL，为找到；否则，为没有找对对应的token
     * @see
     * @note 多线程安全
    **/
    const TokenList * get_token_list(const QueryNodeValue &) const;

    /**
     * @brief 根据RangeRestriction，获取能涵盖该范围的最小的已有Token的倒排
     * @param [in] : RangeRestriction
     * @param [out] : none
     * @return const TokenList*
     * @retval 非NULL，为找到；否则，为没有找对对应的token
     * @see
     * @note 多线程安全
     */
    const void get_token_list(const RangeRestriction &, std::vector<const TokenList*> *) const;

    /**
     * @breaf 根据token_id，获取一个TokenList，TokenList内部包含
     *        实时链和历史链
     *
     * @param [in] : token_id
     * @param [out] : none
     * @return const TokenList*
     * @retval 非NULL，为找到；否则，为没有找对对应的token
     * @see
     * @note 多线程安全，用于获取实时链和历史链，检索使用
    **/
    const TokenList * get_token_list(TokenId token_id) const {
        TokenList * res = NULL;
        _token_list_map.get(token_id, &res);
        return res;
    }

    /**
     * @breaf 根据token_id，获取一个TokenList，TokenList内部包含
     *        实时链和历史链
     *
     * @param [in] : token_id
     * @param [out] : none
     * @return TokenList*
     * @retval 非NULL，为找到；否则，为没有找对对应的token
     * @see
     * @note 非多线程安全,用于建索引，一写多读安全
    **/
    inline TokenList * get_token_list(TokenId token_id) {
        TokenList * res = NULL;
        _token_list_map.get(token_id, &res);
        return res;
    }

    /**
     * @breaf 根据token_id构造一个token list
     *
     * @param [in] : token_id
     * @param [out] : none
     * @return TokenList*
     * @retval 非NULL的指针
     * @see
     * @note 非多线程安全，一写多读安全，如果已经存在该token id的token list
     *       那么返回已经存在的
    **/
    TokenList * create_token_list_by_id(TokenId token_id);

    /**
     * @breaf 设置一条token list。为基量索引提供的方法
     *        无锁操作
     *
     * @param [in] : token_list指针
     * @param [out] : none
     * @return none
     * @retval none
     * @see
     * @note 如果已经存在该token id的token list，那么忽略当前操作
     *       并打印WARNING LOG
    **/
    void set_token_list(TokenList * token_list);

    /**
     * @breaf 构造一个暂时没有数据的正排，然后调用方调用ForwardIndex的build
     *        接口构造正排数据
     *        该接口的存在意义只是为了统一正排对象构造，作为类的成员函数不是
     *        特别合适
     *
     * @param [in] : none
     * @param [out] : none
     * @return ForwardIndex*
     * @retval 基类指针，实际指向对象是其派生类.如果为NULL，代表构造失败
     * @see
     * @note 非多线程安全，一写多读安全
    **/
    ForwardIndex * create_forward_index();

    /**
     * @breaf 延迟删除docid指定的doc info
     *
     * @param [in] : docid指定的fact doc
     * @param [out] : none
     * @return none
     * @retval none
     * @see
     * @note 如果docid不存在，那么打印WARNING LOG
    **/
    void delete_doc_info(DocId docid);

    /**
     * @breaf 无锁增加doc_info，给基量构建使用
     *
     * @param [in] : doc_info
     * @param [out] : none
     * @return none
     * @retval none
     * @see
     * @note 不关注是否已经存在，如果存在，都插入失败
     *
     */
    inline void add_doc_info(doc_info_t * doc_info)
    {
        // set会做红黑树调整
        _doc_info_list->insert(doc_info);
        _doc_info_map.set(doc_info->docid, doc_info, 1);
    }

    /**
     * @breaf 增加一个doc info，有锁
     *
     * @param [in] : doc_info，代表一个doc的信息
     * @param [out] : none
     * @return none
     * @retval none
     * @see
     * @note 不关注是否已经存在，如果存在，都插入失败
    **/
    void add_doc_info_with_lock(doc_info_t * doc_info)
    {
        boost::unique_lock<boost::shared_mutex> lock(_doc_info_list_mu);
        add_doc_info(doc_info);
    }

    /**
     * @breaf 获取比docid指定doc的分数小、docid大的第一个doc的score和docid
     *
     * @param [in] : score, 标明docid指定doc的score
     * @param [in] : docid, FactDoc的docid
     * @param [out] : none
     * @return DocHit
     * @retval 如果当前doc就是最后一个doc，那么返回一个非法的DocHit
     * @see
     * @note 有设置guarder，因此，返回的DocHit一定是合法的;多线程安全
     * TODO : change the function name
    **/
    doc_hit_t get_next_doc_info(int32_t score, DocId docid) const;

    /**
     * @breaf 获取docid指定FactDoc的DocInfo
     *
     * @param [in] : docid
     * @param [out] : none
     * @return const DocInfo*
     * @retval 如果docid的docinfo不存在，返回NULL
     * @see
     * @note 
     *
    **/
    const doc_info_t * get_doc_info(DocId docid) const {
        doc_info_t *res = NULL;
        _doc_info_map.get(docid, &res);
        return res;
    }

    /**
     * @warning，只有在索引逻辑中可以使用，并且，请勿修改检索会用到的东西
     *           或者，做到原子更新
     */
    doc_info_t * get_doc_info(DocId docid) {
        doc_info_t *res = NULL;
        _doc_info_map.get(docid, &res);
        return res;
    }

    const size_t get_fact_doc_count() const {
        return _doc_info_map.size();
    }

    AnnotationManager * get_annotation_manager() {
        return _annotation_manager;
    }
    const AnnotationManager & get_annotation_manager() const {
        return *_annotation_manager;
    }
    const DimensionDocManager & get_dimension_doc_manager() const {
        return *_dimension_doc_manager;
    }
    DimensionDocManager * get_dimension_doc_manager() {
        return _dimension_doc_manager;
    }

private:
    typedef bsl::phashmap<TokenId, TokenList*>  TokenListMap;   ///< 倒排哈希结构
    typedef bsl::phashmap<DocId, doc_info_t*>   DocInfoMap;     ///< 正排哈希结构
    typedef set<doc_info_t*, DocInfoComp> DocInfoList;

    TokenListMap    _token_list_map;   ///< 倒排哈希表
    DocInfoMap      _doc_info_map;     ///< 正排哈希表

    // 用来维护全局有序的doc
    // TODO(wangguangyuan) : 考虑更高效的数据结构
    DocInfoList * _doc_info_list;
    mutable boost::shared_mutex _doc_info_list_mu;

    AnnotationManager * _annotation_manager;
    DimensionDocManager * _dimension_doc_manager;

    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepositoryManager);
};

}

#endif  // INDEX_REPOSITORY_MANAGER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
