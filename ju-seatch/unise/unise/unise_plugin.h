// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
//
// Brief: UnisePlugin is the Base Class of all the EngineUnit's plugins' interface
//        用户只关注内部的方法即可，不用关注构造、初始化操作
//        将插件内部可能用到的功能，在UnisePlugin内部暴露方法接口
#ifndef  UNISE_UNISE_PLUGIN_H_
#define  UNISE_UNISE_PLUGIN_H_

#include "unise/dimension_doc.h"
#include "unise/annotation_schema.pb.h"
#include "unise/base.h"

namespace comcfg {
class ConfigUnit;
}

namespace unise {
class DimensionDoc;
class FactDoc;
class RepositoryManager;
class DimensionDocManager;
class AnnotationManager;
class PluginResponse;

class UnisePlugin {
public:
    UnisePlugin() {}
    virtual ~UnisePlugin() {}

    /**
     * @brief 初始化函数，提供的conf为插件单元的conf
     * @return bool
     * @retval true则初始化成功，否则失败，服务退出
     */
    virtual bool init(const comcfg::ConfigUnit& conf) {
        (void)(conf);
        return true;
    }

    /**
     * @brief 获取插件的派生类名
     *
     * @note 所有的检索端插件，都需要实现该方法
     *       这里调用频率极低，忽略性能
     */
    virtual std::string get_name() const = 0;

    /**
     * @brief 各插件的检索过程结束后，该函数被调用
     * @param [in/out] plugin_response
     *        如果给plugin_response中的enable赋值为true，那么会被加入到
     *        GeneralSearchResponse中；否则不会
     * @note 如无特殊需求，可不实现该函数
     *       不能对检索结果有任何改变，但是可以做一些log
     */
    virtual void end_for_search(PluginResponse * plugin_response) {
        (void)(plugin_response);
    }

    /**
     * @brief 插件的公共初始化接口，用户不需要关注
     * @note 用户请勿使用
     */
    bool basic_init(const RepositoryManager *, const comcfg::ConfigUnit&);

    /**
     * @breaf 根据dimension_doc的dimension name和docid获取doc的指针
     *
     * @param [in] : dimension_name，DimensionDoc的类族名，见配置
     * @param [in] : docid,一个DimensionDoc对象的docid
     * @param [out] : none
     * @return const DimensionDoc*
     * @retval 常指针，如果为NULL，代表没有找到当前doc
     * @see
     * @note 1) 没有找到doc，有可能是doc被删除了，删除为延迟生效
     *       2) 业务插件需要谨慎判断返回值，handle可能的情况
     *       3）不推荐在检索逻辑中大量使用此方法
    **/
    const DimensionDoc * get_dimension_doc(const std::string& dimension_name,
            DocId docid) const;

    /**
     * @breaf 根据dimension_doc的level id和docid获取doc的指针
     *
     * @param [in] : level_id，das中的层级概念，参见配置中DimensionDoc的Id
     * @param [in] : docid,一个DimensionDoc对象的docid
     * @param [out] : none
     * @return const DimensionDoc*
     * @retval 常指针，如果为NULL，代表没有找到当前doc
     * @see
     * @note 1) 没有找到doc，有可能是doc被删除了，删除为延迟生效
     *       2) 业务插件需要谨慎判断返回值，handle可能的情况
     *       3）推荐使用此方法
    **/
    const DimensionDoc * get_dimension_doc(size_t level_id, DocId docid) const;

    /**
     * @brief 获取FactDoc的dimension_name，配置中
     *        有且仅有一种DimensionDoc是一种FactDoc
     *
     * @param [in] : none
     * @param [out] : none
     * @return const std::string&
     * @retval FactDoc dimension_name的引用
     * @see
     * @note
    **/
    const std::string & get_fact_doc_dimension_name() const;

    /**
     * @brief 获取FactDoc的level_id
     *
     * @param [in] : none
     * @param [out] : none
     * @return size_t
     * @retval FactDoc的层级id
     * @see
     * @note
    **/
    size_t get_fact_doc_level_id() const;

    /**
     * @brief 根据docid获取FactDoc
     *        尽量使用MatchedDoc::get_fact_doc()接口，这个速度更快
     *        可以避免一次hash查找
     *
     * @param [in] : docid, FactDoc的docid
     * @param [out] : none
     * @return const FactDoc*
     * @retval FactDoc的指针，如果没有找到，返回NULL
     * @see
     * @note 注意，检查返回值
     */
    const FactDoc * get_fact_doc(DocId docid) const;

    /**
     * @brief 根据annotation_id获取对应的AnnotationSchema
     */
    const AnnotationSchema * get_annotation_schema(AnnotationId annotation_id) const;

    /**
     * @brief 根据annotation_name获取对应的AnnotationSchema
     * @note 速度比通过annotation_id获取要慢，需要有一个hash操作
     */
    const AnnotationSchema * get_annotation_schema(const std::string& annotation_name) const;

    /**
     * @brief 获取所有的AnnotationSchema配置
     */
    const std::vector<const AnnotationSchema*> & get_annotation_schemas() const;

private:
    const RepositoryManager * _repository_manager;
    const DimensionDocManager * _dimension_doc_manager;
    const AnnotationManager * _annotation_manager;
};
}

#endif  // UNISE_PLUGIN_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
