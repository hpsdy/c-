// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  SERVE_SEARCH_ENGINE_H_
#define  SERVE_SEARCH_ENGINE_H_

#include <boost/lockfree/queue.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include "Configure.h"
#include "serve/engine_unit_manager.h"
#include "serve/default_search_handler.h"
#include "unise/general_servlet.pb.h"

namespace unise {
class SearchHandler;
class StateMonitor;

class SearchEngine {
public:
    SearchEngine();
    ~SearchEngine();

    // conf is-a [SearchEngine]
    bool init_search_handler(const comcfg::ConfigUnit&);

    // conf is-a [SearchEngine]
    bool init(const comcfg::ConfigUnit&);

    void search(const GeneralSearchRequest* request,
            GeneralSearchResponse* response);

    /**
     * @brief 为了debug功能增加的函数，返回的指针，可能是空指针
     * @warning 返回的指针，可能若干时间后就失效了
     * @param engine_name [in] 代表EU的名称
     * @param docid [in] 要找的FactDoc的docid
     */
    const ForwardIndex * get_forward_index(const std::string& engine_name, DocId docid);

private:
    /**
     * @brief 做一些search结束后的统计工作
     */
    void finish_search(const GeneralSearchRequest& request,
          const GeneralSearchResponse& response);

private:
    typedef boost::shared_ptr<boost::lockfree::queue<DefaultSearchHandler*> > search_handler_queue;
    typedef std::map<uint64_t, search_handler_queue> search_handler_map;
    // 每个SearchEngine下面，可能有多个EngineUnit
    // 使用EngineUnitManager进行抽象管理
    EngineUnitManager _engine_unit_manager;
    search_handler_map _search_handler_map;     /**< bid->search_handler的map       */
    int32_t _handler_number;
    uint8_t * _base64_buf;   ///< base64结果
    uint8_t * _proto_buf; ///< protobuf序列化buffer
    StateMonitor * _state_monitor;    ///< 状态监控模块的指针，避免每次获取

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(SearchEngine);
};
}

#endif  // SERVE_SEARCH_ENGINE_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
