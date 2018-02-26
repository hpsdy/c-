/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/

#ifndef  UNISE_RESULT_ADAPTER_H_
#define  UNISE_RESULT_ADAPTER_H_

#include "unise/factory.h"
#include "unise/unise_plugin.h"
#include <vector>
#include <string>

namespace comcfg {
class ConfigUnit;
}

namespace unise {
class GeneralSearchRequest;
class GeneralSearchResponse;
class SearchResult;

/// @brief ResultAdapter插件用于在SearchEngine得到检索结果后对结果进行过滤
/// @note 用户需要继承此插件基类，完成定制的Adapt需求
///       该接口在SearchEngine模块生效，不继承自UnisePlugin接口，无法访问
//        DimensionDoc等接口，需要将使用的数据通过SearchResult传递上来
class ResultAdapter {
public:
    ResultAdapter() {}

    virtual ~ResultAdapter() {}

    /**
     * @brief 初始化函数，提供的conf为插件单元的conf
     * @return bool
     * @retval true则初始化成功，否则失败，服务退出
     *
     * @note 注意插件的是SearchEngine模块的插件
     */
    virtual bool init(const comcfg::ConfigUnit&) = 0;

    /**
     * @brief 每次search操作前的初始化
     *
     * @param [in] request   : 请求体
     * @param [in] response  : 结果体
     * @return  void 
     * @retval   
     * @see 
     * @note 
    **/
    virtual void init_for_search(const GeneralSearchRequest* request,
                                GeneralSearchResponse* response) = 0;

    /**
     * @brief Adapt操作
     *
     * @param [in] results   : 所有的SearchResult
     * @param [out] selected_results   : 被选中的SearchResult
     * @param [out] dropped_results   : 被抛弃的SearchResult
     * @return  void 
     * @retval   
     * @see 
     * @note 注意不要析构results中的SearchResult*，可以修改
     *       如果用户需要增加非results中的SearchResult，那么需要自己负责
     *       维护这些新增的SearchResult，不推荐这么做
    **/
    virtual void adapt(const std::vector<SearchResult*> &results,
            std::vector<const SearchResult*>* selected_results,
            std::vector<const SearchResult*>* dropped_results) = 0;

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
     * @brief 最后通牒，告诉adapter，这就是最终的结果了
     * @param [in] const & request
     * @param [in] * response
     * @note 这个接口，主要是为了方便插件做log定制
     *       如无特殊需求，可不实现
     * @note 将接口改成纯虚，只是为了在参数变更后，强制derived class
     *       修改其实现
     */
    virtual void ultimatum(const GeneralSearchRequest& request,
                           GeneralSearchResponse* response_ptr) = 0;
};

REGISTER_FACTORY(ResultAdapter);
#define REGISTER_RESULT_ADAPTER(name) REGISTER_CLASS(ResultAdapter, name)

}

#endif  // UNISE_RESULT_ADAPTER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
