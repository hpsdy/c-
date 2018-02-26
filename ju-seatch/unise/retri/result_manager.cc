// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/result_manager.h"
#include <boost/lockfree/detail/branch_hints.hpp>
#include <algorithm>
#include "Configure.h"
#include "gflags/gflags.h"
#include "unise/general_servlet.pb.h"
#include "unise/search_context.h"
#include "index/repository_manager.h"
#include "retri/result_filter_handler.h"
#include "util/util.h"

DEFINE_bool(build_matched_info, true, "whether build the hit info of the matched doc");
DEFINE_int32(max_result_manager_capacity, 1000000, "the max result manager capacity");
DEFINE_int32(result_manager_capacity, 3000, "how many results to keep for sorting");

DECLARE_int32(retrieve_max_depth);

using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

namespace unise
{

ResultManager::ResultManager(
        const RepositoryManager & repository_manager,
        MasfObjPool<MatchedDocInternal>* result_pool)
    : _repository_manager(repository_manager),
      _result_pool(result_pool)
{
    _result_filter_handler.reset(new ResultFilterHandler(_repository_manager));
    _result_cluster_handler.reset(new ResultClusterHandler(_repository_manager));
    _scorer_handler.reset(new ScorerHandler(_repository_manager));
    // 初始化分配足够大小的堆，堆从位置1开始使用
    _accepted_results_heap = new heap_node_t*[FLAGS_max_result_manager_capacity + 1];
    // 初始化分配足够数目的heap元素，系统支持的最大检索深度
    _heap_nodes.resize(FLAGS_max_result_manager_capacity);
    // 初始化分配足够数目的hash元素
    _hash_nodes.resize(FLAGS_max_result_manager_capacity);

    // _heap_hash的桶数设置为系统支持的最大检索深度*10
    _heap_hash.reset(new HeapHash());
    _heap_hash->create(FLAGS_max_result_manager_capacity);
    _hash_stamp = 0U;
    _hash_clear_count = 0U;
}

ResultManager::~ResultManager()
{
    if (_accepted_results_heap) {
        delete []_accepted_results_heap;
    }
}


bool ResultManager::init_result_filler(const comcfg::ConfigUnit& conf)
{
    std::vector<std::pair<uint64_t, string> > plugins;
    bool missing_default = true;
    try {
        int num = conf["ResultFiller"].size();
        for (int i = 0; i < num; ++i) {
            uint64_t sample_id = conf["ResultFiller"][i]["sample_id"].to_uint64();
            string str(conf["ResultFiller"][i]["plugin"].to_cstr());
            plugins.push_back(std::make_pair(sample_id, str));
            UNOTICE("sample_id:%llu ResultFiller:%s", sample_id, str.c_str());
            if (sample_id == DEFAULT_SAMPLE_ID) {
                missing_default = false;
            }
        }
    } catch (comcfg::ConfigException & e) {
        UFATAL("illegal Configure for ResultFiller:%s", e.what());
        return false;
    }
    if (missing_default) {
        UFATAL("missing sample_id 0 conf for ResultFiller");
        return false;
    }
    for (size_t idx = 0; idx < plugins.size(); ++idx) {
      uint64_t sample_id = plugins.at(idx).first;
      string & str = plugins.at(idx).second;
      if (_fillers_map.find(sample_id) != _fillers_map.end()) {
          UFATAL("sample id:%ull conflict for ResultFiller", sample_id);
          return false;
      }
      UNOTICE("Init ResultFiller:%s", str.c_str());
      ResultFiller * filler = ResultFillerFactory::get_instance(str);
      if (filler == NULL) {
        UFATAL("GetInstance failed:%s", str.c_str());
        return false;
      } else if (filler->basic_init(&_repository_manager,
                                   conf["ResultFiller"][idx]) == false) {
        UFATAL("Init failed:%s", str.c_str());
        delete filler;
        return false;
      } else {
        _fillers_map.insert(std::make_pair(sample_id, boost::shared_ptr<ResultFiller>(filler)));
      }
    }
    return true;
}

bool ResultManager::init_comparator(const comcfg::ConfigUnit& conf)
{
    std::vector<std::pair<uint64_t, string> > plugins;
    bool missing_default = true;
    try {
        int num = conf["Comparator"].size();
        for (int i = 0; i < num; ++i) {
            uint64_t sample_id = conf["Comparator"][i]["sample_id"].to_uint64();
            string str(conf["Comparator"][i]["plugin"].to_cstr());
            plugins.push_back(std::make_pair(sample_id, str));
            UNOTICE("sample_id:%llu Comparator:%s", sample_id, str.c_str());
            if (sample_id == DEFAULT_SAMPLE_ID) {
                missing_default = false;
            }
        }
        // 如果用户没有配置Comparator，为了向前兼容，这里采用默认的
        // DefaultComparator
        if (num == 0) {
            UNOTICE("missing Comparator conf, use DefaultComparator");
            plugins.push_back(std::make_pair(DEFAULT_SAMPLE_ID, "DefaultComparator"));
            missing_default = false;
        }
    } catch (comcfg::ConfigException & e) {
        UFATAL("illegal Configure for Comparator:%s", e.what());
        return false;
    }
    if (missing_default) {
        UFATAL("missing sample_id 0 conf for Comparator");
        return false;
    }
    for (size_t idx = 0; idx < plugins.size(); ++idx) {
      uint64_t sample_id = plugins.at(idx).first;
      const string & str = plugins.at(idx).second;
      if (_comparators_map.find(sample_id) != _comparators_map.end()) {
          UFATAL("sample id:%ull conflict for Comparator", sample_id);
          return false;
      }
      UNOTICE("Init Comparator:%s", str.c_str());
      Comparator * comparator = ComparatorFactory::get_instance(str);
      if (comparator == NULL) {
        UFATAL("GetInstance failed:%s", str.c_str());
        return false;
      } else if (comparator->basic_init(&_repository_manager,
                                   conf["Comparator"][idx]) == false) {
        UFATAL("Init failed:%s", str.c_str());
        delete comparator;
        return false;
      } else {
        _comparators_map.insert(std::make_pair(sample_id, boost::shared_ptr<Comparator>(comparator)));
      }
    }
    return true;
}

bool ResultManager::init(const comcfg::ConfigUnit& conf)
{
    if (init_comparator(conf) == false) {
        return false;
    }
    if (init_result_filler(conf) == false) {
        return false;
    }
    // init the result_filter_handler
    if (_result_filter_handler->init(conf) == false) {
        return false;
    }
    // init the result_cluster_handler
    if (_result_cluster_handler->init(conf) == false) {
        return false;
    }
    // init the scorer_handler
    if (_scorer_handler->init(conf) == false) {
        return false;
    }
    return true;
}

void ResultManager::init_for_search(const GeneralSearchRequest* request,
                                    GeneralSearchResponse* response,
                                    SearchContext * search_context)
{
    _search_context = search_context;
    _request = request;
    _response = response;
    _num_results_requested = static_cast<size_t>(_request->num_results());
    _result_manager_capacity = std::max(
                               static_cast<size_t>(FLAGS_result_manager_capacity),
                               _num_results_requested);
    // 结果池的容量不能应该大于可分配的堆和hash节点资源数目
    if (unlikely(_result_manager_capacity >
                    static_cast<size_t>(FLAGS_max_result_manager_capacity))) {
        UWARNING("[\tlvl=COUNT\t] result_manager_capacity[%u] > FLAGS_max_result_manager_capacity[%d]",
                    _result_manager_capacity,
                    FLAGS_max_result_manager_capacity);
        _result_manager_capacity = static_cast<size_t>(FLAGS_max_result_manager_capacity);
    }
    // 每次检索前，初始化heap
    _heap_size = 0U;
    _heap_nodes_index = 0U;

    // _heap_hash->clear();
    // 使用stamp，每次检索前，不必清空hash
    // 并且由于对hash的使用，是覆盖原值，因此，也不存在hash
    // 膨胀的问题
    if (unlikely(_hash_stamp == 255)) {
        _hash_stamp = 0;
        // TODO(wangguangyuan):定期清空一下，进行测试
        /*
        ++_hash_clear_count;
        if (unlikely(_hash_clear_count == 255)) {
            _hash_clear_count = 0;
            _heap_hash->clear();
        }
        */
    } else {
        ++_hash_stamp;
    }
    _hash_nodes_index = 0U;

    // 获取当前sample id下的Comparator插件，并init for search
    {
        UniseComparatorMap::iterator it = _comparators_map.find(_search_context->get_sample_id());
        if (unlikely(it == _comparators_map.end())) {
            it = _comparators_map.find(DEFAULT_SAMPLE_ID);
            GOOGLE_DCHECK(it != _comparators_map.end());
        }
        _cur_comparator = it->second.get();
        _cur_comparator->init_for_search(_request, _search_context);
    }

    _result_filter_handler->init_for_search(_request, _search_context);
    _result_cluster_handler->init_for_search(_request, _cur_comparator, _search_context);
    _scorer_handler->init_for_search(_request, _search_context);

    // 获取当前sample id下的ResultFilter插件，并init for search
    {
        UniseFillersMap::iterator it = _fillers_map.find(_search_context->get_sample_id());
        if (unlikely(it == _fillers_map.end())) {
            it = _fillers_map.find(DEFAULT_SAMPLE_ID);
            GOOGLE_DCHECK(it != _fillers_map.end());
        }
        _cur_result_filler = it->second.get();
        _cur_result_filler->init_for_search(_request, _search_context);
    }
}

bool ResultManager::early_filter(MatchedDoc* result, result_status_t* result_status)
{
    GOOGLE_DCHECK_NE(result->get_doc_id(), ILLEGAL_DOCID);
    return _result_filter_handler->early_filter(result, result_status);
}
bool ResultManager::later_filter(MatchedDoc* result, result_status_t* result_status)
{
    return _result_filter_handler->later_filter(result, result_status);
}

bool ResultManager::final_filter(MatchedDoc* result, result_status_t* result_status)
{
    return _result_filter_handler->final_filter(result, result_status);
}

bool ResultManager::maybe_add_candidate_result(MatchedDoc* result, int* replace_num,
        result_status_t* result_status)
{
    // first call early filter
    if (!early_filter(result, result_status)) {
        return false;
    }
    // then build the matched info
    if (FLAGS_build_matched_info) {
        if (unlikely(!(down_cast<MatchedDocInternal*>(result))->build_doc_match_info())) {
            UWARNING("[\tlvl=COUNT\t] skip doc:%llu cause build_doc_match_info fail",
                result->get_doc_id());
            return false;
        }
    }
    // then call the scorer, after that result->GetScore() has true value
    _scorer_handler->score(result);

    // here we apply later filter
    if (!later_filter(result, result_status)) {
        return false;
    }

    cluster_status_t cluster_status = CLUSTER_ADD;
    // TODO(wangguangyuan) : try to design EarlyCluster
    // which don't need DocTokenHit info, will be more quickly
    _clustered_results.clear();
    cluster_status = _result_cluster_handler->cluster(result, &_clustered_results);
    if (unlikely(cluster_status == CLUSTER_SKIP)) {
        *result_status = RESULT_REJECTED_DUPLICATE;
        return false;
    } else if (unlikely(cluster_status == CLUSTER_REPLACE) || 
            (cluster_status == CLUSTER_ADD && !_clustered_results.empty())) {
        // remove all the results those are replaced by the current result
        for (std::set<MatchedDoc*>::const_iterator it = _clustered_results.begin();
                it != _clustered_results.end();
                ++it) {
            remove_candidate_result(*it);
        }
        // there must be space, so the result can be add safely
        if (!add_candidate_result(result)) {
            *result_status = RESULT_REJECTED_DUPLICATE;
            return false;
        }
        *replace_num = static_cast<int>(_clustered_results.size());
        *result_status = RESULT_REPLACE;
        return true;
    }
    // no clustering, just add
    GOOGLE_DCHECK_EQ(cluster_status, CLUSTER_ADD);
    // check if there is enough space
    if (likely(_heap_size >= _result_manager_capacity)) {
        UDEBUG("Heap is full");
        GOOGLE_DCHECK_GT(_heap_size, 0);
        // 小顶堆的最小元素在下标1存储
        MatchedDoc* worst_result = _accepted_results_heap[1]->doc;
        GOOGLE_DCHECK(worst_result);
        if ((*_cur_comparator)(worst_result, result)) {
            // the result is not as good as the worst one we have
            UDEBUG("Skipping the candidate result:%llu", result->get_doc_id());
            *result_status = RESULT_REJECTED_LOW_SCORE;
            return false;
        } else {
            UDEBUG("Popping the worst accepted result:%llu with score:%d",
                    worst_result->get_doc_id(),
                    worst_result->get_score());
            remove_candidate_result(worst_result);
        }
    }
    UDEBUG("Pushing the candidate result docid:%llu score:%d",
            result->get_doc_id(),
            result->get_score());
    if (!add_candidate_result(result)) {
        *result_status = RESULT_REJECTED_DUPLICATE;
        return false;
    }
    *result_status = RESULT_ACCEPTED;
    return true;
}

bool ResultManager::add_candidate_result(MatchedDoc* result)
{
    if (unlikely(_heap_size >= _result_manager_capacity)) {
        // normally, this will not happen
        UFATAL("Insert result to manager failed:%llu", result->get_doc_id());
        return false;
    }
    // 首先调整堆大小，增加一个新空间
    hash_node_t * hash_node = &(_hash_nodes.at(_hash_nodes_index++));
    GOOGLE_DCHECK_LE(_hash_nodes_index, static_cast<size_t>(_search_context->get_retrieve_depth()));
    hash_node->stamp = _hash_stamp;
    // 如果有旧值，直接替换
    _heap_hash->set(reinterpret_cast<uint64_t>(result), hash_node, 1);
    heap_node_t * heap_node = &(_heap_nodes.at(_heap_nodes_index++));
    GOOGLE_DCHECK_LE(_heap_nodes_index, static_cast<size_t>(_search_context->get_retrieve_depth()));
    heap_node->doc = result;
    heap_node->hash_node = hash_node;
    ++_heap_size;
    // 从底至上调整堆，寻找新节点插入位置
    size_t i = _heap_size;
    while (i > 1) {
        size_t p = i >> 1;
        // i节点的兄弟节点一定比p节点要质量高，所以没有必要比较
        // 如果i节点指向的doc的质量比其父亲的质量高，停止上升
        if ((*_cur_comparator)(result, _accepted_results_heap[p]->doc)) {
            break;
        }
        // 进行上升
        _accepted_results_heap[i] = _accepted_results_heap[p];
        // 上升同时，维护堆节点指向hash_node_t的数据
        _accepted_results_heap[i]->hash_node->heap_index = i;
        i = p;
    }
    // 不能再上升了，此时，将新节点赋值到位置i
    _accepted_results_heap[i] = heap_node;
    hash_node->heap_index = i;

    _result_cluster_handler->add_cluster_info(result);
    return true;
}

void ResultManager::remove_candidate_result(MatchedDoc* result)
{
    // 首先从_heap_hash中找到Heap中的index
    hash_node_t * hash_node;
    int ret = _heap_hash->get(reinterpret_cast<uint64_t>(result), &hash_node);
    // 这里对hash_stamp的判断是不严格精确的，但是，有比没有强
    // _heap_hash仅仅为了辅助快速定位heap中的位置，理论上应该一定能找到值的
    // 这里的if判断仅仅是一个弱校验，并不能校验到所有的非法异常
    // 这样子做是为了避免调用hash的clear函数，提高性能
    if (unlikely(ret != bsl::HASH_EXIST ||
                 hash_node->stamp != _hash_stamp ||
                 hash_node->heap_index == 0)) {
        UWARNING("[\tlvl=MONITOR\t] Erase result from manager failed:%llu", result->get_doc_id());
        return;
    }
    size_t p = hash_node->heap_index;
    // 将hash中的元素置为非法
    hash_node->heap_index = 0;
    down_adjust_heap(p);
    _result_cluster_handler->remove_cluster_info(result);
    _result_pool->Delete(down_cast<MatchedDocInternal*>(result));
}

void ResultManager::finish()
{
    // 从堆中把元素降序输出到_accepted_results_heap数组中
    // 之后，heap已经销毁了
    size_t heap_size = _heap_size;
    while(_heap_size > 0) {
        heap_node_t * worst = _accepted_results_heap[1];
        // 删除堆顶元素
        down_adjust_heap(1);
        // _heap_size大小减一，尾部可以放当前堆的最小值
        _accepted_results_heap[_heap_size+1] = worst;
    }
    size_t heap_idx = 1U;
    size_t num_results_accepted = 0U;
    while (heap_idx <= heap_size && num_results_accepted < _num_results_requested) {
        MatchedDoc * doc = _accepted_results_heap[heap_idx]->doc;
        GOOGLE_DCHECK(doc);
        // here we apply the final filter
        result_status_t result_status;
        final_filter(doc, &result_status);
        if (result_status == RESULT_ACCEPTED) {
            MatchedDocInternal * doc_internal = down_cast<MatchedDocInternal*>(doc);
            doc_internal->finalize_result();
            SearchResult* search_result = doc_internal->get_search_result();
            _cur_result_filler->fill_search_result(doc, search_result);
            _result_cluster_handler->fill_result_cluster_info(doc, search_result);
            (_response->add_search_results())->CopyFrom(*search_result);
            UDEBUG("Packing result:%llu with score:%d",
                    doc->get_doc_id(),
                    doc->get_score());
            ++num_results_accepted;
        }
        _result_pool->Delete(down_cast<MatchedDocInternal*>(doc));
        ++heap_idx;
    }
    // delete the following low scorer doc
    while (heap_idx <= heap_size) {
        MatchedDoc* doc = _accepted_results_heap[heap_idx]->doc;
        GOOGLE_DCHECK(doc);
        _result_pool->Delete(down_cast<MatchedDocInternal*>(doc));
        ++heap_idx;
    }

    // 这里调用所有的插件的EndForSearch接口
    // 不能对检索结果有任何改变，但是可以做一些log
    _result_filter_handler->end_for_search(_response);
    _scorer_handler->end_for_search(_response);
    _result_cluster_handler->end_for_search(_response);
    PluginResponse pr;
    pr.set_enable(false);
    _cur_result_filler->end_for_search(&pr);
    if (pr.enable()) {
        _response->add_plugin_responses()->CopyFrom(pr);
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
