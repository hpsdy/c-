// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/result_retrievor.h"
#include <boost/lockfree/detail/branch_hints.hpp>
#include <iostream>
#include "gflags/gflags.h"
#include "google/protobuf/text_format.h"
#include "unise/general_servlet.pb.h"
#include "unise/matched_node.h"
#include "unise/base.h"
#include "unise/fact_doc.h"
#include "util/util.h"
#include "index/dimension_doc_manager.h"
#include "index/forward_index.h"
#include "retri/leaf_iterator.h"
#include "retri/and_iterator.h"
#include "retri/or_iterator.h"
#include "retri/not_iterator.h"
#include "retri/branch_iterator.h"
#include "retri/empty_iterator.h"
#include "retri/backend_query_builder.h"
#include "retri/result_manager.h"

DEFINE_int32(retrieve_max_depth, 10000, "at most how many docs will be retrieved"
                                        " before early filter,"
                                        " the real retrieve_depth won't be great than "
                                        " max_result_manager_capacity");
DEFINE_int32(recall_max_docs, 3000, "at most how many docs will be recalled(after cluster)");
DEFINE_double(retrieve_timeout, 200.0, "at least how many ms will retrieve");
DEFINE_int32(retrieve_count_timing, 500, "retrieve each 500 docs, judge if timeout"
                                         "if 1ms can retrieve n docs, set it n/2 is better");
// TODO：为了向前兼容，后续拿掉这个参数
DEFINE_bool(enable_estimated_num_results, false,
            "use estimated_num_results in proto to estimate num");

namespace unise {
using std::vector;
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

ResultRetrievor::ResultRetrievor(const RepositoryManager & repository_manager) :
        _repository_manager(repository_manager),
        _doc_match_info_proxy(repository_manager),
        _search_context(NULL) {}

ResultRetrievor::~ResultRetrievor() {
    if (_search_context_factory.get() != NULL && _search_context != NULL) {
        _search_context_factory->destroy(_search_context);
        _search_context = NULL;
    }
}

bool ResultRetrievor::init(const comcfg::ConfigUnit& conf) {
    // 构造MatchedDoc资源池
    MasfObjPool<MatchedDocInternal> * doc_pool  =
        new(std::nothrow) MasfObjPool<MatchedDocInternal>(256, 0.5, 100);
    if (doc_pool == NULL) {
        UFATAL("construct MatchedDocInternal pool for 256,0.5,100 failed");
        return false;
    }
    _matched_doc_pool.reset(doc_pool);

    // 构造结果管理器
    ResultManager * result_manager =
        new(std::nothrow) ResultManager(_repository_manager, _matched_doc_pool.get());
    if (result_manager == NULL) {
        UFATAL("construct ResultManager failed");
        return false;
    }
    _result_manager.reset(result_manager);

    // 根据配置，构造结果上下文工厂类对象
    string str;
    try {
        str.assign(conf["SearchContextFactory"].to_cstr());
    } catch (comcfg::ConfigException & e) {
        UNOTICE("illegal Configure for SearchContextFactory:%s,"
                "use DefaultSearchContextFactory", e.what());
        str.assign("DefaultSearchContextFactory");
    }
    UNOTICE("Init SearchContextFactory:%s", str.c_str());
    SearchContextFactory * scf = SearchContextFactoryFactory::get_instance(str);
    if (scf == NULL) {
      UFATAL("GetInstance failed:%s", str.c_str());
      return false;
    }
    _search_context_factory.reset(scf);
    if (_search_context_factory->init(conf) == false) {
      UFATAL("Init failed:%s", str.c_str());
      return false;
    }
    _search_context = _search_context_factory->produce();
    if (_search_context == NULL) {
      UFATAL("%s produce SearchContext failed", str.c_str());
      return false;
    }

    // init result_manager
    if (false == _result_manager->init(conf)) {
        return false;
    }
    return true;
}

/**
 * @warning: 内部new不使用nothrow，为了检索性能，避免if分支
 *           如果new失败抛异常，服务core掉即可，即使服务不core，
 *           也没有任何服务能力。一般根据测试大query，可以推测线上
 *           服务需要预留多少内存
 */
ForwardIterator * ResultRetrievor::construct_retrieve_tree(const QueryNode & query_node) {
    int children_size = query_node.children_size();
    switch (query_node.type()) {
    case VALUE: {
        if (unlikely(!query_node.has_value())) {
            UWARNING("[\tlvl=COUNT\t] QueryNode type:VALUE miss value");
            break;
        }
        const TokenList * token_list = _repository_manager.get_token_list(query_node.value());
        if (token_list == NULL) {
            UDEBUG("don't find TokenList, create EmptyIterator instead");
            break;
        }
        vector<ForwardIterator*> it_list;
        ForwardIterator * list_it = new LeafIterator(token_list->get_doc_hit_list(
                        REAL_TIME_LIST));
        ForwardIterator * array_it = new LeafIterator(token_list->get_doc_hit_list(
                        FIX_TIME_ARRAY));
        it_list.push_back(list_it);
        it_list.push_back(array_it);
        ForwardIterator * or_it = new OrIterator(it_list);
        _forward_iterators.push_back(list_it);
        _forward_iterators.push_back(array_it);
        _forward_iterators.push_back(or_it);
        return or_it;
    }
    case OR: {
        if (children_size == 0) {
            UWARNING("[\tlvl=COUNT\t] QueryNode type:OR miss children");
            break;
        }
        vector<ForwardIterator*> it_list;
        for (int i = 0; i < children_size; ++i) {
            it_list.push_back(construct_retrieve_tree(query_node.children(i)));
        }
        ForwardIterator * or_it = new OrIterator(it_list);
        _forward_iterators.push_back(or_it);
        return or_it;
    }
    case AND: {
        if (children_size == 0) {
            UWARNING("[\tlvl=COUNT\t] QueryNode type:AND miss children");
            break;
        }
        vector<ForwardIterator*> it_list;
        for (int i = 0; i < children_size; ++i) {
            it_list.push_back(construct_retrieve_tree(query_node.children(i)));
        }
        ForwardIterator * and_it = new AndIterator(it_list);
        _forward_iterators.push_back(and_it);
        return and_it;
    }
    case NOT: {
        if (children_size != 1) {
            UWARNING("[\tlvl=COUNT\t] QueryNode type:NOT children_size unequal 1");
            break;
        }
        ForwardIterator * only_left_it = construct_retrieve_tree(query_node.children(0));
        ForwardIterator * not_it = new NotIterator(_repository_manager, only_left_it);
        _forward_iterators.push_back(not_it);
        return not_it;
    }
    case BRANCH: {
        if (children_size == 0) {
            UWARNING("[\tlvl=COUNT\t] QueryNode type:NOT miss children");
            break;
        }
        vector<ForwardIterator*> it_list;
        vector<uint32_t> weight_list;
        for (int i = 0; i < children_size; ++i) {
            it_list.push_back(construct_retrieve_tree(query_node.children(i)));
            if (query_node.children(i).has_value() &&
                query_node.children(i).value().has_weight()) {
                // 根据子节点的配置出结果
                weight_list.push_back(query_node.children(i).value().weight());
            } else {
                // 默认权重，以此给1个结果
                weight_list.push_back(1);
            }
        }
        ForwardIterator * branch_it = new BranchIterator(it_list, weight_list);
        _forward_iterators.push_back(branch_it);
        return branch_it;
    }
    default:
        // pass, return empty_it at the end of the function
        break;
    }
    ForwardIterator * empty_it = new EmptyIterator();
    _forward_iterators.push_back(empty_it);
    return empty_it;
}

/**
 * @brief 把参数root_iterator作为AND树的一个孩子节点
 *        把range_restrictions的所有节点作为AND树的孩子节点
 *        返回新的树的根
 */
ForwardIterator* ResultRetrievor::construct_range_restriction(
            const GeneralSearchRequest& request,
            ForwardIterator * root_iterator) {
    // 没有设置范围查询时，直接返回当前迭代树的root
    if (false == request.has_search_params() ||
        request.search_params().range_restrictions_size() == 0) {
        return root_iterator;
    }
    vector<ForwardIterator*> it_list;
    // 首先把root_iterator作为and节点的孩子
    it_list.push_back(root_iterator); 
    for (int i = 0; i < request.search_params().range_restrictions_size(); ++i) {
        const RangeRestriction & rr = request.search_params().range_restrictions(i);
        std::vector<const TokenList*> token_lists;
        _repository_manager.get_token_list(rr, &token_lists);
        if (token_lists.size() == 0U) {
            // 这个整数范围搜索，没有对应的token
            ForwardIterator * empty_it = new EmptyIterator();
            _forward_iterators.push_back(empty_it);
            it_list.push_back(empty_it);
            UNOTICE("don't find TokenList for %s when restrict, create EmptyIterator instead",
                        rr.annotation_name().c_str());
            // 一个范围检索如果没有找到对应的倒排，那么，这次检索肯定没有结果
            // 没有必要再添加其他约束条件了
            break;
        } else {
            vector<ForwardIterator*> or_list;
            // 当前范围查询字段，是有结果的，这里有一个优化
            // 将所有的区间的实时链、历史链，都作为OR节点的孩子
            for (size_t list_idx = 0; list_idx < token_lists.size(); ++list_idx) {
                ForwardIterator * list_it = new LeafIterator(
                            token_lists[list_idx]->get_doc_hit_list(REAL_TIME_LIST));
                ForwardIterator * array_it = new LeafIterator(
                            token_lists[list_idx]->get_doc_hit_list(FIX_TIME_ARRAY));
                or_list.push_back(list_it);
                or_list.push_back(array_it);
                _forward_iterators.push_back(list_it);
                _forward_iterators.push_back(array_it);
            }
            ForwardIterator * or_it = new OrIterator(or_list);
            _forward_iterators.push_back(or_it);
            it_list.push_back(or_it);
        }
    }
    // 构造AND节点，作为新的查询树的根节点
    ForwardIterator * and_it = new AndIterator(it_list);
    _forward_iterators.push_back(and_it); ///< 存储下来，检索完毕进行释放
    return and_it;
}

void ResultRetrievor::retrieve(
            const GeneralSearchRequest & request,
            GeneralSearchResponse * response) {
    StopWatch search_stop_watch;
    // 首先构造查询树
    ForwardIterator * retrieve_root;
    if (likely(request.has_query_tree())) {
        retrieve_root = construct_retrieve_tree(request.query_tree());
        GOOGLE_DCHECK(retrieve_root) << "construct_retrieve_tree from QueryTree fail";
    } else if (request.has_query()) {
        BackendQueryBuilder builder;
        QueryNode query_root;
        if (!builder.build(request.query(), &query_root)) {
            UWARNING("[\tlvl=COUNT\t] build QueryTree from query fail:%s", request.query().c_str());
            return;
        }
        // frontend的debug请求，这里性能不敏感，打印详细query
        std::string str;
        google::protobuf::TextFormat::PrintToString(query_root, &str);
        UNOTICE("QueryTree from string:%s", str.c_str());
        retrieve_root = construct_retrieve_tree(query_root);
        GOOGLE_DCHECK(retrieve_root) << "construct_retrieve_tree from query fail";
    } else {
        // 如果用户没有设置query tree，也没有设置query，那么就是拉全库
        // 通过N(V())实现拉全库
        QueryNode query_root;
        query_root.set_type(NOT);
        QueryNode * empty_node = query_root.add_children();
        empty_node->set_type(VALUE);
        QueryNodeValue * v = empty_node->mutable_value();
        v->set_annotation_name("UNISE_NO_SUCH_ANNOTATION");
        v->set_text_value("UNISE_NO_SUCH_VALUE");
        // 不对empty_node的value赋值，使得构造一个empty retrieve iterator
        retrieve_root = construct_retrieve_tree(query_root);
        GOOGLE_DCHECK(retrieve_root) << "construct_retrieve_tree from N(empty node) fail";
    }

    // 初始化本次查询
    _search_context->init_for_search(&request);
    _result_manager->init_for_search(&request, response, _search_context);
    // 由于正排hit获取逻辑不需要范围检索的信息，这部分信息需要对用户透明
    // 所以，放到构造范围AND分支前操作
    _doc_match_info_proxy.init_for_search(retrieve_root, &request, response);

    // 构造范围查询AND分支
    retrieve_root = construct_range_restriction(request, retrieve_root);

    // the retrieve stop logic
    // TODO(wangguangyuan) : if necessary, use SearchContext to proxy the stop logic
    int64_t retrieve_num = 0;
    int64_t recall_docs = 0;
    double retrieve_timeout = _search_context->get_retrieve_timeout();
    int32_t retrieve_max_depth = _search_context->get_retrieve_depth();
    int32_t recall_max_docs = _search_context->get_recall_docs();

    StopWatch retrieve_stop_watch;
    int32_t cnt = 0;
    while (!retrieve_root->done()) {
        // get one hitted doc
        ++retrieve_num;
        ++cnt;
        const doc_hit_t & doc_hit = retrieve_root->get_cur_doc_hit();
        const doc_info_t * doc_info = _repository_manager.get_doc_info(doc_hit.docid);
        // the doc_info must be valid
        // note: 这里有可能一个doc刚刚被删除，由于倒排、doc_info、dimension_doc
        //       的删除操作并不是一个全局锁，所以，这里需要做一个校验
        //       不处理刚刚被删除的doc
        if (likely(doc_info) && likely(doc_info->fact_doc)) {
            UDEBUG("retrieve doc_hit[score:%d docid:%llu] doc_info[score:%d docid:%llu]",
                    doc_hit.score, doc_hit.docid, doc_info->score, doc_info->docid);
            // alloc the matched_doc
            MatchedDocInternal * matched_doc = _matched_doc_pool->New(
                        *doc_info,
                        &_doc_match_info_proxy);
            GOOGLE_DCHECK(matched_doc);
            // push the matched_doc to result manager
            result_status_t result_status;
            int replace_num = 0; 
            bool result_accepted = _result_manager->maybe_add_candidate_result(
                        matched_doc,
                        &replace_num,
                        &result_status);
            // 更新计数器
            if (unlikely(!result_accepted)) {
                _matched_doc_pool->Delete(matched_doc);
            } else if (result_status == RESULT_ACCEPTED) {
                // 结果被接受
                ++recall_docs;
            } else if (result_status == RESULT_REPLACE) {
                // 结果被替换
                recall_docs = recall_docs - replace_num + 1;
            }
        }

        // 召回结果数目达到，结束倒排检索
        if (unlikely(recall_docs >= recall_max_docs)) {
            UDEBUG("recall enough docs:%d", recall_max_docs);
            break;
        }
        // 检索深度达到，结束倒排检索
        if (unlikely(retrieve_num >= retrieve_max_depth)) {
            UDEBUG("retrieve reach the depth:%d", retrieve_max_depth);
            break;
        }
        // 检索超时达到，结束倒排检索
        if (unlikely(cnt == FLAGS_retrieve_count_timing)) {
            if (retrieve_stop_watch.read() > retrieve_timeout) {
                UDEBUG("retrieve reach the timeout:%d", retrieve_timeout);
                break;
            }
            cnt = 0;
        }
        // get the next matched doc
        retrieve_root->next();
    }

    response->set_estimated_num_results(
                get_estimated_num(
                    retrieve_root->get_estimated_num(),
                    retrieve_root->get_progress(),
                    retrieve_num,
                    recall_docs));
    response->set_docs_retrieved(retrieve_num);
    response->set_docs_recalled(recall_docs);
    finish_retrieve();
    // timing
    double search_time = search_stop_watch.split();
    response->set_search_time(static_cast<int>(search_time));
    UDEBUG("retrieve %lld docs use %0.3f ms", retrieve_num, search_time);
}

uint64_t ResultRetrievor::get_estimated_num(
            uint64_t tree_num,
            float progress,
            int64_t retrieve_num,
            int64_t recall_docs) {
    UTRACE("tree_num[%llu] progress[%.2f] retrieve_num[%lld] recall_docs[%lld]",
                tree_num, progress, retrieve_num, recall_docs);
    if (tree_num <= static_cast<uint64_t>(retrieve_num) ||
                retrieve_num == 0) {
        return recall_docs;
    }
    uint64_t est_num = static_cast<uint64_t>(tree_num * recall_docs / retrieve_num);
    if (est_num <= static_cast<uint64_t>(recall_docs)) {
        return recall_docs;
    } else {
        return est_num;
    }
}

void ResultRetrievor::finish_retrieve() {
    // release resource
    for (size_t i = 0; i < _forward_iterators.size(); ++i) {
        delete _forward_iterators.at(i);
    }
    _forward_iterators.clear();
    _result_manager->finish();
    _matched_doc_pool->Recycle();
    _doc_match_info_proxy.reset();
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
