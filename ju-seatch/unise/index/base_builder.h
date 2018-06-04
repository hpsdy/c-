/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file base_builder.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/27 15:56:55
 * @version $Revision$
 * @brief Doc的基量构建类，负责构建基量DimensionDoc（包括基量FactDoc），
 * 并且构建基量FactDoc的正排和倒排索引
 *
 **/

#ifndef  __BASE_BUILDER_H_
#define  __BASE_BUILDER_H_

#include "index/index.h"
#include "index/repository_manager.h"
#include "index/dimension_doc_manager.h"
#include "index/doc_base_builder.h"
#include <Configure.h>
#include <boost/shared_ptr.hpp>
#include <set>
#include <string>
#include <vector>

namespace unise
{

class BaseBuilder
{
public:
    BaseBuilder() {}

    ~BaseBuilder() {}

    /**
     * @brief 初始化
     *
     * @param [in] conf   : EngineUnit ConfUnit
     * @return  bool
     * @retval
     * @see
     * @note
    **/
    bool init(const comcfg::ConfigUnit& conf);

    /**
     * @brief 多线程构建
     *
     * @return  bool true 成功，false 失败
     * @retval
     * @see
     * @note
    **/
    bool build_concurrency();

    /**
     * @brief 多线程从磁盘加载数据
     *
     * @return  bool true 成功，false 失败
     * @retval
     * @see
     * @note
    **/
    bool load_data_from_disk();

    boost::shared_ptr<RepositoryManager> get_repository_manager() 
    {
        return repository_manager_;
    }

    boost::shared_ptr<DimensionDocManager> get_dimension_doc_manager() 
    {
        return dimension_doc_manager_;
    }

private:
    /**
     * @brief 获取DimensionDoc的Id
     *
     * @param [in] line   :
     * @param [out] doc_id   :
     * @return  bool
     * @retval
     * @see
     * @note
    **/
    bool get_dimension_doc_id(const std::string &line, uint32_t *doc_id);

    //void GetTokenHitList(const FactDoc &doc, const DocInfo &doc_info,
    //        std::vector<TokenHit> &token_hit_list);

    //bool BuildDocForwardIndex(const DocInfo &doc,
    //        const std::vector<TokenHit> &token_hit_list);

    //bool BatchBuildInvertedIndex(const std::vector<TokenHit> &token_hit_list);

    /**
     * @brief 启动单个DocBuilder线程
     *
     * @param [in] doc_id   : doc id
     * @param [in] doc_file_info   : doc文件信息
     * @param [in] dimension_family   : doc的Dimension信息
     * @return  bool true 成功，false 失败
     * @retval
     * @see
     * @note
    **/
    bool start_builder(uint32_t doc_id,
            const DocFileInfo &doc_file_info,
            DimensionDocManager::dimension_t *dimension);
private:
    boost::shared_ptr<RepositoryManager> repository_manager_;     /**< repository manager    */
    boost::shared_ptr<DimensionDocManager> dimension_doc_manager_;/**< dimension doc manager */

    std::string fact_doc_name_;     /**< FactDoc的名字       */
    uint32_t fact_doc_id_;      /**< FactDoc的ID       */
    std::string base_doc_file_;     /**< 基量文件名       */
    std::vector<dimension_doc_config_t> dimension_doc_configs_;
    std::set<uint32_t> dimension_doc_ids_;         /**< DimensionDoc的Id的集合       */
    std::vector<boost::shared_ptr<DocBaseBuilder> > builders_;      /**< Doc构建器列表       */
    std::string _dump_base_forward_index_path;          /**< dump基量正排文件路径 */
    std::string _dump_base_inverted_index_path;         /**< dump基量倒排文件路径 */
    std::string _dump_base_d2f_maps_path;               /**< dump基量级联数据文件路径 */
};

}

#endif  //__BASE_BUILDER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
