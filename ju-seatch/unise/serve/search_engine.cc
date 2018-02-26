// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/search_engine.h"
#include <boost/lockfree/detail/branch_hints.hpp>
#include "gflags/gflags.h"
#include "unise/search_handler.h"
#include "unise/base.h"
#include "unise/util.h"
#include "unise/singleton.h"
#include "unise/state_monitor.h"

DEFINE_int32(handler_number, 12, "serving thread num");
DEFINE_bool(log_search_info, false, "whether log the protobuf search info,"
                                    "close it to get better performance");
DEFINE_bool(log_format_search_info, true, "whether log the formated search info,"
                                         "include: search_time, retrieve_depth...");
DEFINE_int32(binlog_buffer_size, 1048576, "when print binlog, the buffer size, default:1M");

namespace unise {
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

SearchEngine::SearchEngine() :
        _handler_number(FLAGS_handler_number),
        _base64_buf(NULL),
        _proto_buf(NULL),
        _state_monitor(NULL) {}

SearchEngine::~SearchEngine() {
    for(search_handler_map::iterator iter = _search_handler_map.begin();
            iter != _search_handler_map.end();
            ++iter) {
        while (!(iter->second)->empty()) {
            DefaultSearchHandler *search_handler = NULL;
            if (iter->second->pop(search_handler)) {
                delete search_handler;
                search_handler = NULL;
            } else {
                UWARNING("[\tlvl=FOLLOW\t] when destruct SearchEngine, pop failed");
            }
        }
    }
    if (_base64_buf != NULL) {
        delete []_base64_buf;
        _base64_buf = NULL;
    }
    if (_proto_buf != NULL) {
        delete []_proto_buf;
        _proto_buf = NULL;
    }
}

bool SearchEngine::init(const comcfg::ConfigUnit& conf) {
    try {
        //init engin unit
        if (!_engine_unit_manager.init(conf["EngineUnit"])) {
            UFATAL("Init EngineUnitManager failed");
            return false;
        }

        //init search handler
        _handler_number = conf["HandlerNumber"].to_int32();
        UNOTICE("SearchEngine: HandlerNumber:%d", _handler_number);
        bool has_default = false;
        for (uint32_t i = 0; i < conf["SearchHandler"].size(); ++i) {
            uint64_t sid = conf["SearchHandler"][i]["sample_id"].to_uint32();
            std::string plugin(conf["SearchHandler"][i]["plugin"].to_cstr());
            if (_search_handler_map.end() != _search_handler_map.find(sid)) {
                UFATAL("Unvalid search handler sample_id conf, sid:%u", sid);
                return false;
            }
            search_handler_queue sh_queue(new boost::lockfree::queue<DefaultSearchHandler*>(_handler_number));
            for (int32_t j = 0; j < _handler_number; ++j) {
                DefaultSearchHandler *search_handler =
                    DefaultSearchHandlerFactory::get_instance(plugin);
                if (!search_handler) {
                    return false;
                }
                // TODO(wangguanguan) : delete this
                search_handler->_engine_unit_manager = &_engine_unit_manager;
                // init the SearchHandler
                if (!search_handler->my_init(conf)) {
                    delete search_handler;
                    search_handler = NULL;
                    UFATAL("Init search handler:%s fail", plugin.c_str());
                    return false;
                }
                // push the valid SearchHandler into queue
                if (!sh_queue->push(search_handler)) {
                    UFATAL("push the search handler to queue fail");
                    delete search_handler;
                    search_handler = NULL;
                    return false;
                }
            }
            _search_handler_map.insert(std::make_pair(sid, sh_queue));
            if(0 == sid) {
                has_default = true;
            }
        }
        if(!has_default) {
            UFATAL("Failed to init search handler map, "
                    "because there is not a default search handler");
            return false;
        }
        _state_monitor = Singleton<StateMonitor>::get();
        if (_state_monitor == NULL) {
            UFATAL("Failed to get state monitor");
            return false;
        }
    } catch (comcfg::ConfigException &e) {
        UFATAL("illegal Configure for SearchEngine:%s", e.what());
        return false;
    }

    _base64_buf = new(std::nothrow) uint8_t[FLAGS_binlog_buffer_size];
    if (_base64_buf == NULL) {
        UFATAL("new base_buf failed [size:%u]", FLAGS_binlog_buffer_size);
        return false;
    }
    _proto_buf = new(std::nothrow) uint8_t[FLAGS_binlog_buffer_size];
    if (_proto_buf == NULL) {
        UFATAL("new proto_buf failed [size:%u]", FLAGS_binlog_buffer_size);
        return false;
    }
    return true;
}

void SearchEngine::search(const GeneralSearchRequest* request,
                          GeneralSearchResponse* response) {
    uint64_t sample_id = request->has_sample_id() ? request->sample_id() : DEFAULT_SAMPLE_ID;
    search_handler_map::iterator iter = _search_handler_map.find(sample_id);
    if (_search_handler_map.end() == iter) {
        // 使用NOTICE日志即可，不需要使用WARNING日志
        UNOTICE("[sample_id=%lu] Invalid sample_id", sample_id);
        iter = _search_handler_map.find(DEFAULT_SAMPLE_ID);
    }

    DefaultSearchHandler *search_handler = NULL;
    if (unlikely(!iter->second->pop(search_handler))) {
        UWARNING("[\tlvl=FOLLOW\treq_id=%lu\t] Insufficient search handler",
                 request->request_id());
        response->set_status_code(unise::kStatusRetry);
        response->set_status_msg("Server busy.");
        return;
    }
    search_handler->search(request, response);
    if(unlikely(!iter->second->push(search_handler))) {
        UFATAL("Failed to push search handler into queue");
        // 这里不需要设置response返回码，因为search已经被调用
        return;
    }
    finish_search(*request, *response);
}

void SearchEngine::finish_search(const GeneralSearchRequest& request,
                                 const GeneralSearchResponse& response) {
    // 往lockless-queue里面push一个消息
    int32_t ts = get_timestamp();
    _state_monitor->add_number_state_message(ts, "search_time", response.search_time());
    _state_monitor->add_number_state_message(ts, "docs_retrieved", response.docs_retrieved());
    _state_monitor->add_number_state_message(ts, "docs_recalled", response.docs_recalled());

    // 打印完整的request和response的protobuf，为了支持线上debug或者QA测试
    // 如果为了性能考虑没有打开开关，不打印
    bool print_request_response = FLAGS_log_search_info;
    get_bool_experiment_value(request, "log_search_info", &print_request_response);
    if (print_request_response) {
        do {
            if (1) {
                // Do NOT log request!
                break;
            }
            int proto_size = request.ByteSize();
            if (proto_size >= FLAGS_binlog_buffer_size) {
                UNOTICE("request proto_size[%d]>=binlog_buffer_size[%d]",
                            proto_size,
                            FLAGS_binlog_buffer_size);
                break;
            }
            if (!request.SerializeToArray(_proto_buf, proto_size)) {
                UNOTICE("serialize request protobuf failed");
                break;
            }
            int encode_l = base64_encode(
                        _proto_buf,
                        proto_size,
                        _base64_buf,
                        FLAGS_binlog_buffer_size - 1);
            if (encode_l < 0 || encode_l >= FLAGS_binlog_buffer_size) {
                break;
            }
            _base64_buf[encode_l] = 0;
            UNOTICE("[PROTO-REQUEST-BASE64:%s]", _base64_buf);
        } while (0);
        do {
            int proto_size = response.ByteSize();
            if (proto_size >= FLAGS_binlog_buffer_size) {
                UNOTICE("response proto_size[%d]>=binlog_buffer_size[%d]",
                            proto_size,
                            FLAGS_binlog_buffer_size);
                break;
            }
            if (!response.SerializeToArray(_proto_buf, proto_size)) {
                UNOTICE("serialize response protobuf failed");
                break;
            }
            int encode_l = base64_encode(
                        _proto_buf,
                        proto_size,
                        _base64_buf,
                        FLAGS_binlog_buffer_size - 1);
            if (encode_l < 0 || encode_l >= FLAGS_binlog_buffer_size) {
                break;
            }
            _base64_buf[encode_l] = 0;
            // UNOTICE("[PROTO-RESPONSE-BASE64:%s]", _base64_buf);
        } while (0);
    }

    // 打印格式化的请求和相应信息，便于直接观察日志
    bool log_format_search_info = FLAGS_log_format_search_info;
    get_bool_experiment_value(request, "log_format_search_info", &print_request_response);

    std::string cuid = "";
    get_string_experiment_value(request, "cuid", &cuid);

    int city_id = 0;
    get_int_experiment_value(request, "city_id", &city_id);

    if (log_format_search_info) {
        std::string doc_ids;
        std::vector<std::string> docIdVec;
        for (int i = 0; i < response.search_results_size(); ++i) {
            if (i != 0) {
                doc_ids.append(",");
            }
            std::string tmpDocidStr = Uint64ToString(response.search_results(i).docid());
            doc_ids.append(tmpDocidStr);
            docIdVec.push_back(tmpDocidStr);
        }

        PluginResponse _pluginResp = response.log_info();
        std::string logStr;
        if(_pluginResp.has_context_log())
        {
            logStr = _pluginResp.context_log();
        }
        
        std::string triggerInfo = "[";
        std::vector<std::string>::iterator iterEnd = docIdVec.end();
        std::vector<std::string>::iterator iterBegin = docIdVec.begin();
        for (int i = 0; i < _pluginResp.trigger_type_size(); ++i)
        {
            Experiment tmpExperiment = _pluginResp.trigger_type(i);
            std::string key = tmpExperiment.key();
            std::string value = tmpExperiment.value();
            if(std::find(iterBegin, iterEnd, key) != iterEnd)
            {
                triggerInfo += key + ":" + value + ",";
            }
        }
        if(!triggerInfo.empty())
        {
            triggerInfo = triggerInfo.substr(0, triggerInfo.size() - 1);
        }
        triggerInfo += "]";
        
        UNOTICE("init_params:%s,trigger_info:%s,result:[raw_query:%s] [num_results:%d] [start_result:%d] [session_id:%llu] "
                "[business_id:%llu] [request_id:%llu] [sample_id:%llu] [cuid:%s] [city_id:%d] "
                "[results_num:%d] [estimated_num_results:%lld] [docs_retrieved:%lld] "
                "[docs_recalled:%llu] [search_time:%d] [doc_ids:%s]",
                    logStr.c_str(),
                    triggerInfo.c_str(),
                    request.raw_query().c_str(),
                    request.num_results(),
                    request.start_result(),
                    request.session_id(),
                    request.business_id(),
                    request.request_id(),
                    request.sample_id(),
                    cuid.c_str(),
                    city_id,
                    response.search_results_size(),
                    response.estimated_num_results(),
                    response.docs_retrieved(),
                    response.docs_recalled(),
                    response.search_time(),
                    doc_ids.c_str());
    }
}

const ForwardIndex * SearchEngine::get_forward_index(const std::string& engine_name, DocId docid) {
    EngineUnit * eu = _engine_unit_manager.get_engine_unit(engine_name);
    if (eu == NULL) {
        return NULL;
    }
    return eu->get_forward_index(docid);
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=80: */
