// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_MATCHED_DOC_H_
#define  UNISE_MATCHED_DOC_H_

#include <vector>
#include <string>
#include "unise/base.h"

namespace unise {
class MatchedNode;
class SearchResult;
class FactDoc;

/**
 * @brief 命中的doc，检索逻辑中，各个插件处理的对象
 * @note  不要保存MatchedDoc的指针，MatchedDoc的生存空间为
 *        检索到当前doc到检索到下一个doc之前
 *
 */
class MatchedDoc {
public:
    MatchedDoc() {}
    virtual ~MatchedDoc() {}

    /**
     * @breaf 返回当前match_doc的动态打分
     *
     * @param [in] : none
     * @param [out] : none
     * @return dynamic_score_t
     * @retval 当前doc的动态打分
     * @see
     * @note 注意，只有在scorer后面的插件，才可以调用该函数，能够
     *       获取到scorer打的分数
     *       这个的分数，不是FactDoc的静态得分，是动态得分
    **/
    virtual dynamic_score_t get_score() const = 0;

    /**
     * @breaf 返回当前match_doc的docid，即对应的FactDoc的docid
     *
     * @param [in] : none
     * @param [out] : none
     * @return DocId
     * @retval 当前matched_doc的docid
     * @see
     * @note 可以利用这个docid，在各插件中获取FactDoc的指针
    **/
    virtual DocId get_doc_id() const = 0;

    /**
     * @breaf 返回命中节点信息，用于相关性计算
     *
     * @param [in] : none
     * @param [out] : none
     * @return const std::vector<MatchedNode*>&
     * @retval 每个query node的命中信息，如果一个query
     *         node没有命中当前doc，那么数组中不包含这个node
     * @see
     * @note 注意，返回值的生存空间仅在当前MatchedDoc被放到结果池之前
     *       下一个MatchedDoc被retrieve出来后，之前的MatchedDoc都不再被访问
    **/
    virtual const std::vector<MatchedNode*>& get_matched_nodes() const = 0;

    /**
     * @brief 返回当前doc的doc_info_t
     *
     * @param [in] : none
     * @param [out] : none
     * @return 
     * @retval 
     * @see unise/base.h 中doc_info_t的定义
     * @note 
     *
    **/
    virtual const doc_info_t& get_doc_info() const = 0;


    /**
     * @brief 获取与MatchedDoc相关的SearchResult
     *        用户可使用extension来扩展SearchResult这个proto，效率低
     *        该接口为临时接口，后期会使用更高效方式来替换
     */
    virtual SearchResult * get_search_result() = 0;
    virtual const SearchResult * get_search_result() const = 0;

    /**
     * @brief 获取与MatchedDoc对应的FactDoc 
     *        尽量调用本接口，本接口可以避免每次都从phashmap中查询
     * @note  返回引用
     *        是的，是引用，不用再检查是否为NULL
     * @warning 确保15s之后不再使用FactDoc引用
     *          具体有效时间范围请参考FLAGS_inverted_list_delete_delay配置
     */
    virtual const FactDoc & get_fact_doc() const = 0;
};
}

#endif  // UNISE_MATCHED_DOC_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
