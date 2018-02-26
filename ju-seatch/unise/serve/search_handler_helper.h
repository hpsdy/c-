/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file search_handler_helper.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/12 10:36:58
 * @version $Revision$
 * @brief 用于生成用户扩展的response对象，非线程安全，
 * 一个线程使用一个实例
 *
 **/

#ifndef  __SEARCH_HANDLER_HELPER_H_
#define  __SEARCH_HANDLER_HELPER_H_

#include <stdint.h>
#include <queue>
#include <boost/scoped_ptr.hpp>
#include "unise/general_servlet.pb.h"

namespace unise
{

class SearchHandlerHelper
{
public:
    SearchHandlerHelper() : _org_size(0) {}

    ~SearchHandlerHelper();

    bool init(uint32_t num);

    /**
     * @brief 获取一个response对象
     *
     * @return  GeneralSearchResponse* 
     * @retval   
     * @see 
     * @note 
    **/
    GeneralSearchResponse* pop_response() 
    {/*{{{*/
        if (_responses.size() <= 0) {
            return NULL;
        }
        GeneralSearchResponse* resp = _responses.front();
        _responses.pop();
        return resp;
    }/*}}}*/

    /**
     * @brief 归还一个response对象
     *
     * @param [in] resp   : 
     * @return  void 
     * @retval   
     * @see 
     * @note 
    **/
    void push_response(GeneralSearchResponse* resp) 
    {/*{{{*/
        _responses.push(resp);
    }/*}}}*/

    /**
     * @brief 获取response队列的大小
     *
     * @return  uint32_t 
     * @retval   
     * @see 
     * @note 
    **/
    uint32_t get_org_size() 
    {
        return _org_size;
    }

private:
    uint32_t _org_size;       /**< 队列大小       */
    std::queue<GeneralSearchResponse*> _responses;        /**< response对象队列       */
};

}


#endif  //__SEARCH_HANDLER_HELPER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
