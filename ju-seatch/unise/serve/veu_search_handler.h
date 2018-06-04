/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file veu_search_handler.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/12 17:18:47
 * @version $Revision$
 * @brief VeuSearchHandler类
 *
 **/

#ifndef  __VEU_SEARCH_HANDLER_H_
#define  __VEU_SEARCH_HANDLER_H_

#include "unise/search_handler.h"
#include "unise/general_servlet.pb.h"
#include "unise/pbrpc_client.h"
#include "util/queue.h"
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <Configure.h>
#include <string>
#include <vector>

namespace unise {

void rpc_callback(const GeneralSearchRequest* request, GeneralSearchResponse* response, 
            baidu::rpc::Controller* cntl);

class VeuChannelPool {
public:
    VeuChannelPool() : _inited(false) {}
    ~VeuChannelPool();
    bool init(const std::vector<std::string> & service_names,
                const std::string & load_balancer_name,
                const baidu::rpc::ChannelOptions& options);
    baidu::rpc::Channel * get_channel_by_index(size_t i);

private:
    bool _inited;
    std::vector<baidu::rpc::Channel *> _rpc_channel_pool;
};

class VeuSearchHandler : public SearchHandler
{
public:
    VeuSearchHandler();

    virtual ~VeuSearchHandler() {}

    /**
     * @brief 初始化
     *
     * @param [in] conf   : VEU conf unit
     * @return  bool true 成功，false 失败
     * @retval
     * @see
     * @note
    **/
    virtual bool my_init(const comcfg::ConfigUnit& conf, 
            std::vector<std::string>& service_names);

    /**
     * @brief search过程
     *
     * @param [in] request   : 请求
     * @param [out] responses   : 响应
     * @return  void
     * @retval
     * @see
     * @note
    **/
    virtual void search_internal(const GeneralSearchRequest* request,
            std::vector<GeneralSearchResponse*>* responses);

    /**
     * @brief 获取名字
     *
     * @return  const std::string 主机名
     * @retval
     * @see
     * @note
    **/
    const std::string get_name() const {
        return _hostname;
    }

    /**
     * @brief 获取类型
     *
     * @return  const std::string "VeuSearchHandler"
     * @retval
     * @see
     * @note
    **/
    const std::string get_type() const {
        return "VeuSearchHandler";
    }

private:
    std::string _hostname;        /**< 主机名       */
    std::vector<std::string> _service_names;          /**< 下游service的名字       */
    VeuChannelPool * _channel_pool;
    struct RpcContext {
        boost::shared_ptr<UniseService_Stub> unise_service_stub;         /**< service stub       */
        GeneralSearchResponse* response;          /**< response       */
        baidu::rpc::Controller cntl;
        baidu::rpc::CallId call_id;
    };
    boost::shared_array<RpcContext> _rpc_contexts;        /**< rpc上下文       */
    int32_t _result_num_eu;
};



REGISTER_FACTORY(VeuSearchHandler);
#define REGISTER_VEU_SEARCH_HANDLER(name) REGISTER_CLASS(VeuSearchHandler, name)

}

#endif  //__VEU_SEARCH_HANDLER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
