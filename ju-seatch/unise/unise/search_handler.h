// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  CS_VS_CROSS_UNISE_SRC_UNISE_SEARCH_HANDLER_H
#define  CS_VS_CROSS_UNISE_SRC_UNISE_SEARCH_HANDLER_H

#include <string>
#include <vector>
#include <map>
#include "unise/factory.h"
#include "unise/result_adapter.h"

namespace comcfg {
class ConfigUnit;
}

namespace unise {
class EngineUnit;
class EngineUnitManager;
class SearchEngine;
class GeneralSearchRequest;
class GeneralSearchResponse;
class SearchResult;
class SearchHandlerHelper;
class QueryRewriter;

const uint32_t DEFAULT_SH_HELPER_RESPONSE_QUEUE_SIZE = 32;

/// @brief SearchHandler插件完成对多个REU和VEU的检索过程，然后合并形成最终结果
class SearchHandler {
public:
    SearchHandler();

    virtual ~SearchHandler();

    /**
     * @brief 初始化
     *
     * @param [in] conf   : [SearchEngine] conf
     * @return  bool 
     * @retval   true 成功，false 失败
     * @see 
     * @note 
    **/
    virtual bool init(const comcfg::ConfigUnit& conf);

    /**
     * @brief 检索结果
     *
     * @param [in] request   : 请求
     * @param [out] response   : 回复
     * @return  void 
     * @retval   
     * @see 
     * @note 此函数内部会调用SearchInternal，此函数不开放给用户
    **/
    void search(const GeneralSearchRequest* request,
                GeneralSearchResponse* response);

    /**
     * @brief 向多个REU和VEU检索结果
     *
     * @param [in] request   : 请求
     * @param [out] response   : 回复
     * @return  void 
     * @retval   
     * @see 
     * @note 此函数开放给用户，用户可以通过覆盖该函数定制自己的检索过程
     * @warning response通过get_response函数获取，如果将response
     *          push到responses中，那么不需要再调用return_response，
     *          否则需要用户主动调用return_response
    **/
    virtual void search_internal(const GeneralSearchRequest* request,
                                 std::vector<GeneralSearchResponse*>* responses) = 0;

    EngineUnit * get_engine_unit(const std::string& name) const;

    virtual const std::string get_name() const = 0;

    virtual const std::string get_type() const = 0;

protected:
    /**
    * @brief 获得一个GeneralSearchResponse对象
    */
    GeneralSearchResponse* get_response();

    /**
    * @brief 归还一个GeneralSearchResponse对象
    * @note 可以用delete的方式释放resp占用的空间，如果你这样做了，请再new一个对象
    */
    virtual void return_response(GeneralSearchResponse* resp);

    /**
     * @brief 将多个EU的结果合并到一起
     *
     * @param [in] org_responses   : 多个EU的回复
     * @param [out] results   : 合并后的SearchResult
     * @param [out] response   : 合并后的response
     * @return  void 
     * @retval   
     * @see 
     * @note
    **/
    void merge(const std::vector<GeneralSearchResponse*> &org_responses,
               std::vector<SearchResult*>* results,
               GeneralSearchResponse* response);

    /**
     * @brief 翻页
     *
     * @param [in] request   : 请求
     * @param [out] selected_results   : 选中的SearchResult
     * @param [out] response   : 翻页后的response
     * @return  void 
     * @retval   
     * @see 
     * @note 
    **/
    void page_turn(const GeneralSearchRequest* request,
                   const std::vector<const SearchResult*> &selected_results,
                   GeneralSearchResponse* response);

private:
    bool init_result_adapter(const comcfg::ConfigUnit& conf);
    bool init_query_rewriter(const comcfg::ConfigUnit& conf);
    QueryRewriter * get_query_rewriter(uint64_t sample_id);
    ResultAdapter * get_result_adapter(uint64_t sample_id);

protected:
    SearchHandlerHelper * _search_handler_helper;

private:
    typedef std::map<uint64_t, ResultAdapter*> ResultAdapterMap;
    typedef std::map<uint64_t, QueryRewriter*> QueryRewriterMap;
    EngineUnitManager * _engine_unit_manager;
    ResultAdapterMap _result_adapter_map;     /**< 存储多个adapter插件的map       */
    QueryRewriterMap _query_rewriter_map;   ///< 存储query rewriter插件的map

    friend class SearchEngine;
};

class ResultLess {
public:
    bool operator()(const SearchResult* a, const  SearchResult* b) const;
};

}

#endif  // CS_VS_CROSS_UNISE_SRC_UNISE_SEARCH_HANDLER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
