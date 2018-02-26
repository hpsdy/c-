/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/


/**
 * @file virtual_engine_unit.cc
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/11/29 14:27:11
 * @version $Revision$
 * @brief VEU的实现
 *
 **/


#include "serve/virtual_engine_unit.h"
#include "util/util.h"
#include "unise/base.h"
#include "Configure.h"
#include <sys/time.h>
#include <exception>
#include <algorithm>

namespace unise
{

VirtualEngineUnit::VirtualEngineUnit() :
    _inited(false),
    _veu_search_handler_num(0) {}

bool VirtualEngineUnit::init(const comcfg::ConfigUnit& conf)
{/*{{{*/
    try {
        // 初始化Client
        if (conf["ClientConfig"].selfType() == comcfg::CONFIG_ERROR_TYPE) {
            UFATAL("Invalid Client Conf");
            return false;
        }

        // 获取服务个数
        const comcfg::ConfigUnit &client_conf = conf["ClientConfig"];
        size_t service_num = client_conf["Client"]["Service"].size();
        for (size_t serv_idx = 0; serv_idx < service_num; ++serv_idx) {
            _service_names.push_back(
                    client_conf["Client"]["Service"][serv_idx]["ServiceName"].to_cstr());
        }

        // 初始化queue
        _veu_search_handler_queue.reset(new Queue(_veu_search_handler_num));
        
        // 初始化veu_search_handler
        _eu_type.assign(conf["EngineUnitType"].to_cstr());
        _eu_name.assign(conf["EngineUnitName"].to_cstr());
        _veu_search_handler_name.assign(conf["VeuSearchHandlerName"].to_cstr());
        _veu_search_handler_num = conf["VeuSearchHandlerNumber"].to_uint32();
        for (uint32_t i = 0; i < _veu_search_handler_num; ++i) {
            VeuSearchHandler* search_handler =
                VeuSearchHandlerFactory::get_instance(_veu_search_handler_name);
            if (!search_handler) {
                UFATAL("Failed to get VeuSearchHandler");
                return false;
            }
            if (!search_handler->my_init(conf, _service_names)) {
                UFATAL("Failed to init search handler");
                delete search_handler;
                return false;
            }
            if (!_veu_search_handler_queue->push(search_handler)) {
                UFATAL("Failed to push VeuSearchHandler into queue");
                delete search_handler;
                return false;
            }
        }
        UNOTICE("Init virtual engine unit done, [type:%s], [name:%s]",
                _eu_type.c_str(), _eu_name.c_str());
    } catch (comcfg::ConfigException &e) {
        UFATAL("Failed to init virtual engine unit, err_msg:%s", e.what());
        return false;
    } catch (std::exception &e) {
        UFATAL("Failed to init virtual engine unit, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to init virtual engine unit, unknown exception");
        return false;
    }
    _inited = true;
    return true;
}/*}}}*/

bool VirtualEngineUnit::init_for_search()
{/*{{{*/
    return true;
}/*}}}*/

void VirtualEngineUnit::search(GeneralSearchRequest* request, 
        GeneralSearchResponse* response)
{/*{{{*/
    VeuSearchHandler* search_handler = NULL;
    if (!_veu_search_handler_queue->pop(search_handler)) {
        UFATAL("Failed to pop VeuSearchHandler from queue");
        return;
    }
    search_handler->search(request, response);
    if (!_veu_search_handler_queue->push(search_handler)) {
        UFATAL("Failed to push VeuSearchHandler into queue");
    }
}/*}}}*/

REGISTER_ENGINEUNIT(VirtualEngineUnit);
}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
