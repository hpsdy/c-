/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/


/**
 * @file virtual_engine_unit.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/11/29 14:58:25
 * @version $Revision$
 * @brief VEU的声明
 *
 **/


#ifndef  __VIRTUAL_ENGINE_UNIT_H_
#define  __VIRTUAL_ENGINE_UNIT_H_

#include "unise/base.h"
#include <boost/lockfree/queue.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>
#include "Configure.h"
#include "unise/engine_unit.h"
#include "unise/general_servlet.pb.h"
#include "serve/veu_search_handler.h"

namespace unise
{

class VirtualEngineUnit : public EngineUnit
{
public:
    VirtualEngineUnit();

    virtual ~VirtualEngineUnit() 
    {
        // 首先保证没有检索资源了，不会调用检索逻辑
        VeuSearchHandler* search_handler = NULL;
        if (_veu_search_handler_queue.get()) {
            while (_veu_search_handler_queue->pop(search_handler)) {
                delete search_handler;
            }
        }
        UFATAL("destroy VirtualEngineUnit");
    }

    /**
     * @brief 初始化
     *
     * @param [in] conf   : VEU conf unit
     * @return  bool true 成功，false 失败
     * @retval
     * @see
     * @note
    **/
    virtual bool init(const comcfg::ConfigUnit& conf);

    virtual bool inited() const {
        return _inited;
    }

    /**
     * @brief 获取名字
     *
     * @return  const std::string&
     * @retval
     * @see
     * @note
    **/
    virtual const std::string& get_name() const {
        return _eu_name;
    }

    /**
     * @brief 获取类型
     *
     * @return  const std::string&
     * @retval
     * @see
     * @note
    **/
    virtual const std::string& get_type() const {
        return _eu_type;
    }

    /**
     * @brief 每次search前的初始化
     *
     * @return  bool true 成功，false 失败
     * @retval
     * @see
     * @note
    **/
    virtual bool init_for_search();

    /**
     * @brief Search过程
     *
     * @param [in] request   : 请求pb结构体
     * @param [out] response   : 响应pb结构体
     * @return  void
     * @retval
     * @see
     * @note
    **/
    virtual void search(GeneralSearchRequest* request, GeneralSearchResponse* response);

private:
    bool        _inited;        ///< 是否已经完成初始化
    std::string _eu_name;        /**< EU的名字       */
    std::string _eu_type;        /**< EU的类型       */
    std::string _veu_search_handler_name;          /**< 所使用的VeuSearchHandler的名字       */
    uint32_t _veu_search_handler_num;         /**< SearchHandler的个数       */

    std::vector<std::string> _service_names;          /**< 下游service的名字       */
    typedef boost::lockfree::queue<VeuSearchHandler*> Queue;
    boost::scoped_ptr<Queue> _veu_search_handler_queue;  /**< SerachHandler队列       */
};

}

#endif  //__VIRTUAL_ENGINE_UNIT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
