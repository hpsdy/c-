// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "unise/search_context.h"
#include "unise/general_servlet.pb.h"
#include "unise/base.h"
#include "unise/util.h"

DECLARE_int32(retrieve_max_depth);
DECLARE_int32(recall_max_docs);
DECLARE_double(retrieve_timeout);
DECLARE_int32(max_result_manager_capacity);

namespace unise {
void SearchContext::init_for_search(const GeneralSearchRequest* request)
{
    _experiment_kvs.clear();

    _retrieve_timeout = FLAGS_retrieve_timeout;
    _retrieve_depth = std::max(FLAGS_retrieve_max_depth, request->num_results());
    _recall_docs = FLAGS_recall_max_docs;

    if (request->has_search_params()) {
        const SearchParams & search_params = request->search_params();
        if (search_params.has_retrieve_timeout()) {
            _retrieve_timeout = search_params.retrieve_timeout();
        }
        if (search_params.has_retrieve_depth()) {
            _retrieve_depth = std::max(_retrieve_depth, search_params.retrieve_depth());
        }
        if (search_params.has_recall_docs()) {
            _recall_docs = std::max(_recall_docs, search_params.recall_docs());
        }
        for (int i = 0; i < request->search_params().experiments_size(); ++i) {
            const Experiment & exp = request->search_params().experiments(i);
            if (exp.has_value()) {
                _experiment_kvs.insert(std::make_pair(exp.key(), exp.value()));
            } else {
                _experiment_kvs.insert(std::make_pair(exp.key(), ""));
            }
        }
    }
    // 检索深度不能超过结果收集容器的可用资源最大数目
    _retrieve_depth = std::min(_retrieve_depth, FLAGS_max_result_manager_capacity);

    // 获取request中的sample id
    _sample_id = DEFAULT_SAMPLE_ID;
    if (request->has_sample_id()) {
        _sample_id = request->sample_id();
    }

    // 执行用户继承的虚函数
    init_for_search_internal(request);
}

bool SearchContext::get_experiment_value(const std::string& key, int64_t * value) const
{
    std::map<std::string, std::string>::const_iterator it = _experiment_kvs.find(key);
    if (it != _experiment_kvs.end() &&
        StringToInt64(it->second, value)) {
        return true;
    } else {
        return false;
    }
}
bool SearchContext::get_experiment_value(const std::string& key, uint64_t * value) const
{
    std::map<std::string, std::string>::const_iterator it = _experiment_kvs.find(key);
    if (it != _experiment_kvs.end() &&
        StringToUint64(it->second, value)) {
        return true;
    } else {
        return false;
    }
}
bool SearchContext::get_experiment_value(const std::string& key, bool * value) const
{
    std::map<std::string, std::string>::const_iterator it = _experiment_kvs.find(key);
    if (it != _experiment_kvs.end()) {
        *value = (it->second == "true");
        return true;
    } else {
        return false;
    }
}
bool SearchContext::get_experiment_value(const std::string& key, std::string * value) const
{
    GOOGLE_DCHECK(value);
    std::map<std::string, std::string>::const_iterator it = _experiment_kvs.find(key);
    if (it != _experiment_kvs.end()) {
        value->append(it->second);
        return true;
    } else {
        return false;
    }
}

class DefaultSearchContextFactory : public SearchContextFactory {
public:
    DefaultSearchContextFactory() {}
    ~DefaultSearchContextFactory() {}
    virtual bool init(const comcfg::ConfigUnit & conf) { return true; }
    virtual SearchContext * produce() { return new SearchContext(); }
    virtual void destroy(SearchContext * c) { delete c; }
    virtual std::string get_name() { return "DefaultSearchContextFactory"; }
};
REGISTER_SEARCH_CONTEXT_FACTORY(DefaultSearchContextFactory);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
