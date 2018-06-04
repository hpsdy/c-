/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file default_result_adapter.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/23 11:59:08
 * @version $Revision$
 * @brief 默认结果调整器类
 *
 **/


#ifndef  __DEFAULT_RESULT_ADAPTER_H_
#define  __DEFAULT_RESULT_ADAPTER_H_

#include "unise/result_adapter.h"
#include "retri/default_comparator.h"

namespace unise
{
class DefaultResultAdapter : public ResultAdapter
{
public:
    DefaultResultAdapter() {}

    virtual ~DefaultResultAdapter() {}

    virtual bool init(const comcfg::ConfigUnit & conf)
    {
        (void)(conf);
        return true;
    }

    /**
     * @brief 每次search前的初始化
     *
     * @param [in] request   : 请求
     * @return  void
     * @retval
     * @see
     * @note
    **/
    virtual void init_for_search(const GeneralSearchRequest* request,
                GeneralSearchResponse* response);

    /**
     * @brief 调整检索结果
     *
     * @param [in] results   : 检索结果
     * @param [out] selected_results   : 选中的检索结果
     * @param [out] dropped_results   : 丢弃的检索结果
     * @return  void
     * @retval
     * @see
     * @note
    **/
    virtual void adapt(const std::vector<SearchResult*> &results,
            std::vector<const SearchResult*>* selected_results,
            std::vector<const SearchResult*>* dropped_results);

    /**
     * @brief 获取Adapter的名字
     * @return  std::string 名字
     * @retval
     * @see
     * @note
    **/
    virtual std::string get_name() const 
    {
        return "DefaultResultAdapter";
    }

    virtual void ultimatum(const GeneralSearchRequest& request,
                           GeneralSearchResponse* response_ptr) {
        (void)(request);
        (void)(response_ptr);
    }
private:
    SearchResultComparator _comparator;
};

}

#endif  //__DEFAULT_RESULT_ADAPTER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
