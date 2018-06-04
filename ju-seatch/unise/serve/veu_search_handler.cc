/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file veu_search_handler.cc
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/12 17:23:34
 * @version $Revision$
 * @brief VeuSearchHandler类的实现
 *
 **/

#include <unistd.h>
#include <exception>
#include <climits>
#include "util/util.h"
#include "unise/base.h"
#include "boost/lexical_cast.hpp"
#include "serve/veu_search_handler.h"

DEFINE_int64(communicate_timeout, 5, "communicate timeout");
DECLARE_double(retrieve_timeout);
DEFINE_double(veu_result_number_scale, 1.5, "the scale of result_number each VEU to get");
DECLARE_int32(exact_num_results);

namespace unise
{

void rpc_callback(const GeneralSearchRequest* request, GeneralSearchResponse* response, 
            baidu::rpc::Controller* cntl) {
}

VeuChannelPool::~VeuChannelPool() {
    for (size_t i = 0; i < _rpc_channel_pool.size(); ++i) {
        delete _rpc_channel_pool.at(i);
    }
}

bool VeuChannelPool::init(const std::vector<std::string> & service_names,
            const std::string & load_balancer_name,
            const baidu::rpc::ChannelOptions& options) {
    if (_inited) {
        UTRACE("veuChannelPool already inited");
        return true;
    }
    for (size_t i = 0; i < service_names.size(); ++i) {
        baidu::rpc::Channel * channel = new(std::nothrow) baidu::rpc::Channel();
        if (channel == NULL) {
            UFATAL("init channel failed");
            return false;
        }
        _rpc_channel_pool.push_back(channel);

        int ret = channel->Init(service_names.at(i).c_str(),
                    load_balancer_name.c_str(),
                    &options);
        if (ret != 0) {
            UFATAL("init Channel failed!");
            return false;
        }
    }
    _inited = true;
    return true;
}
baidu::rpc::Channel * VeuChannelPool::get_channel_by_index(size_t i) {
    if (i < _rpc_channel_pool.size()) {
        return _rpc_channel_pool.at(i);
    } else {
        return NULL;
    }
}

VeuSearchHandler::VeuSearchHandler() : _channel_pool(NULL) {}

bool VeuSearchHandler::my_init(const comcfg::ConfigUnit& conf,
        std::vector<std::string>& service_names) {
    if (!SearchHandler::init(conf)) {
        UFATAL("Failed to init SearchHandler");
        return false;
    }
    _channel_pool = Singleton<VeuChannelPool>::get();
    if (_channel_pool == NULL) {
        UFATAL("Failed to get VeuChannelPool from Singleton");
        return false;
    }
    try {
        // 获取主机名
        if (!get_host_name(_hostname)) {
            UWARNING("[\tlvl=FOLLOW\t] Failed to get host name");
            _hostname.assign("Unknown");
        }
        _service_names = service_names;
        std::string load_balancer_name = conf["ClientConfig"]["Client"]["LoadBalancerName"].to_cstr();
        size_t service_num = _service_names.size();
        _rpc_contexts.reset(new RpcContext [service_num]);

        // 设置默认的超时时间
        baidu::rpc::ChannelOptions t_options;
        uint32_t time_out = static_cast<uint32_t>(FLAGS_retrieve_timeout + FLAGS_communicate_timeout);
        t_options.connect_timeout_ms = time_out; 
        t_options.timeout_ms = time_out;
        if (false == _channel_pool->init(_service_names, load_balancer_name, t_options)) {
            UFATAL("Failed to init channel_pool in VeuSearchHandler");
            return false;
        }
        UNOTICE("Init VEU search handler done, [service_num:%u]", service_num);
    } catch (comcfg::ConfigException &e) {
        UFATAL("Failed to init VEU search handler, err_msg:%s", e.what());
        return false;
    } catch (std::exception &e) {
        UFATAL("Failed to init VEU search handler, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to init VEU search handler, unknown exception");
        return false;
    }
    _result_num_eu = std::min(static_cast<int32_t>(FLAGS_exact_num_results *
                    FLAGS_veu_result_number_scale /
                    _service_names.size()),
                FLAGS_exact_num_results);
    return true;
}

void VeuSearchHandler::search_internal(const GeneralSearchRequest* request,
        std::vector<GeneralSearchResponse*>* responses) {
    // 发送请求
    size_t service_num = _service_names.size();
    // 改写结果获取个数
    GeneralSearchRequest my_request(*request);
    my_request.set_num_results(_result_num_eu);
    if (request->has_search_params()) {
        int32_t exact_num_results = 0; 
        int32_t result_num_eu = 0;
        const SearchParams & tmp_sp = request->search_params();
        if (tmp_sp.has_exact_num_results()) {
            exact_num_results = tmp_sp.exact_num_results(); 
            if (exact_num_results != 0) {
                // 根据后端配置的EngineUnit个数和比例，决定每个EngineUnit返回多少结果
                result_num_eu = std::min(static_cast<int32_t>(exact_num_results *
                            FLAGS_veu_result_number_scale /
                            service_num),
                        exact_num_results);
                my_request.set_num_results(result_num_eu);
            }
        }
    }
    // 获取检索的超时时间
    double retrieve_timeout = FLAGS_retrieve_timeout;
    if (request->has_search_params()) {
        const SearchParams & search_para = request->search_params();
        if (search_para.has_retrieve_timeout() && search_para.retrieve_timeout() > 0) {
            retrieve_timeout = search_para.retrieve_timeout();
        }
    }
    for (size_t serv_id = 0; serv_id < service_num; ++serv_id) {
        // 获取response结构
        GeneralSearchResponse* response = get_response();
        if (!response) {
            UWARNING("[\tlvl=COUNT\t] Failed to get response instance");
            return;
        }
        baidu::rpc::Channel * channel = _channel_pool->get_channel_by_index(serv_id);
        if (channel == NULL) {
            UWARNING("[\tlvl=FOLLOW\t] Failed to get channel for serv_id[%u]", serv_id);
            return;
        }
        _rpc_contexts[serv_id].response = response;
        // 设置超时时间
        uint32_t time_out = static_cast<uint32_t>(retrieve_timeout + FLAGS_communicate_timeout);
        _rpc_contexts[serv_id].cntl.set_timeout_ms(time_out);
        _rpc_contexts[serv_id].call_id = _rpc_contexts[serv_id].cntl.call_id();
        // 发送请求
        _rpc_contexts[serv_id].unise_service_stub.reset(new unise::UniseService_Stub(channel));
        _rpc_contexts[serv_id].unise_service_stub->Search(
                    &_rpc_contexts[serv_id].cntl,
                    static_cast<const GeneralSearchRequest *>(&my_request),
                    _rpc_contexts[serv_id].response, 
                    google::protobuf::NewCallback(
                        rpc_callback,
                        static_cast<const GeneralSearchRequest *>(&my_request),
                        response,
                        &_rpc_contexts[serv_id].cntl));
        UDEBUG("Finish sending request, [name:%s], [type:%s], [serv_id:%u]",
                get_name().c_str(), get_type().c_str(), serv_id);
    }

    for (size_t serv_id = 0; serv_id < service_num; ++serv_id) {
        // baidu-rpc的接口变更，因此这里做改动
        baidu::rpc::Join(_rpc_contexts[serv_id].call_id);
    }
    for (size_t serv_id = 0; serv_id < service_num; ++serv_id) {
        if (!_rpc_contexts[serv_id].cntl.Failed()) {
            responses->push_back(_rpc_contexts[serv_id].response);
            UDEBUG("Received one service response done, serv_id[%u], PeerAddress[%s]",
                    serv_id, endpoint2str(_rpc_contexts[serv_id].cntl.remote_side()).c_str());
        } else {
            // 归还response结构
            return_response(_rpc_contexts[serv_id].response);
            UWARNING("[\tlvl=MONITOR\t] Rpc failed, serv_id[%u],PeerAddress[%s], ErrorText[%s]", serv_id, 
                    endpoint2str(_rpc_contexts[serv_id].cntl.remote_side()).c_str(),
                    _rpc_contexts[serv_id].cntl.ErrorText().c_str());
        }
    }

    // 重置RpcClientContext
    for (size_t serv_idx = 0; serv_idx < _service_names.size(); ++serv_idx) {
        _rpc_contexts[serv_idx].cntl.Reset();
    }
}

REGISTER_VEU_SEARCH_HANDLER(VeuSearchHandler);

}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
