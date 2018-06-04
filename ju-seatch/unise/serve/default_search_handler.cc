// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/default_search_handler.h"
#include "gflags/gflags.h"
#include "unise/engine_unit.h"
#include "unise/general_servlet.pb.h"
#include "unise/factory.h"
#include "unise/base.h"
#include "serve/search_handler_helper.h"

DECLARE_int32(exact_num_results);
DEFINE_double(engine_unit_result_number_scale, 1.5, "the scale of result_number each EU to get");

namespace unise
{
using namespace std;

bool DefaultSearchHandler::my_init(const comcfg::ConfigUnit& conf)
{
    if (false == SearchHandler::init(conf)) {
        return false;
    }
    vector<string> engine_units;
    try {
        int num = (int)conf["EngineUnit"].size();
        for (int i = 0; i < num; ++i) {
            string engine_unit_name(conf["EngineUnit"][i]["EngineUnitName"].to_cstr());
            engine_units.push_back(engine_unit_name);
        }
    } catch (comcfg::ConfigException e) {
        UFATAL("%s", e.what());
        return false;
    }
    for (size_t i = 0; i < engine_units.size(); ++i) {
        EngineUnit * engine_unit = get_engine_unit(engine_units.at(i));
        if (engine_unit == NULL) {
            UFATAL("Get %u EngineUnit:%s fail", i + 1, engine_units.at(i).c_str());
            return false;
        } else {
            engine_unit_list_.push_back(engine_unit);
        }
    }
    // 根据配置，决定SearchEngine总共要求多少结果
    _result_num_all = FLAGS_exact_num_results;
    // 根据后端配置的EngineUnit个数和比例，决定每个EngineUnit返回多少结果
    _result_num_eu = std::min(static_cast<int32_t>(_result_num_all *
                    FLAGS_engine_unit_result_number_scale /
                    engine_units.size()),
                FLAGS_exact_num_results);
    UNOTICE("Init DefaultSearchHandler succ");
    return true;
}

void DefaultSearchHandler::search_internal(
        const GeneralSearchRequest* request,
        std::vector<GeneralSearchResponse*>* responses)
{
    for (vector<EngineUnit*>::iterator it = engine_unit_list_.begin();
            it != engine_unit_list_.end();
            ++it) {
        EngineUnit* engine_unit = *it;
        if (false == engine_unit->init_for_search()) {
            UWARNING("[\tlvl=COUNT\t] InitForSearch failed for %s",
                  engine_unit->get_name().c_str());
            continue;
        }
        GeneralSearchResponse * my_response = get_response();
        if (my_response == NULL) {
            UWARNING("[\tlvl=SERIOUS\t] get_response failed, please add resource");
            continue;
        }
        GeneralSearchRequest my_request(*request);

        // EngineUnit should retrieve how many results
        my_request.set_num_results(_result_num_eu);
        // 从请求中获取 exact_num_results 参数
        if (request->has_search_params()) {
            int32_t exact_num_results = 0; 
            int32_t result_num_eu = 0;
            const SearchParams & tmp_sp = request->search_params();
            if (tmp_sp.has_exact_num_results()) {
                exact_num_results = tmp_sp.exact_num_results(); 
                if (exact_num_results != 0) {
                    // 根据后端配置的EngineUnit个数和比例，决定每个EngineUnit返回多少结果
                    result_num_eu = std::min(static_cast<int32_t>(exact_num_results *
                                FLAGS_engine_unit_result_number_scale /
                                engine_unit_list_.size()),
                            exact_num_results);
                    my_request.set_num_results(result_num_eu);
                }
            }
        }
        engine_unit->search(&my_request, my_response);
        UDEBUG("Get %d results from %s",
                my_response->search_results_size(),
                engine_unit->get_name().c_str());
        // push the response to the vector
        responses->push_back(my_response);
    }
}

REGISTER_SEARCH_HANDLER(DefaultSearchHandler);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
