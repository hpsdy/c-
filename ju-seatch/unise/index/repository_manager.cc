// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/repository_manager.h"
#include <cstddef>
#include <uln_sign_murmur.h>

#include "gflags/gflags.h"
#include "unise/general_servlet.pb.h"
#include "unise/annotation_schema.pb.h"
#include "unise/singleton.h"
#include "unise/delay_callback.h"
#include "util/util.h"
#include "index/dimension_doc_manager.h"
#include "index/token_list.h"
#include "index/annotation_manager.h"
#include "index/forward_index.h"
#include "index/index.h"
#include "index/compact_forward_index.h"

// phashmap 当不设置 rwlock 大小时，最大的 rwlock 是 100 个
DEFINE_int32(token_hashmap_buckets, 5000000, "Token hashmap bucket size");
DEFINE_int32(token_hashmap_rwlocks, 1024, "Token hashmap rwlock size");
DEFINE_int32(factdoc_hashmap_buckets, 1000000, "Fact Doc hashmap bucket size");
DEFINE_int32(factdoc_hashmap_rwlocks, 1024, "Fact Doc hashmap rwlock size");
DECLARE_int32(inverted_list_delete_delay);

namespace unise
{

/**
 * @brief 采用全局函数来执行一些延迟回调，是最安全的做法
 *        可以避免当前的类已经被析构掉了
 */
void delay_delete_doc_info(doc_info_t * doc_info) {
    if (doc_info->forward_index != NULL) {
        delete doc_info->forward_index;
    }
    delete doc_info;
}

RepositoryManager::RepositoryManager(
        DimensionDocManager * dimension_doc_manager)
    : _doc_info_list(NULL),
      _annotation_manager(NULL),
      _dimension_doc_manager(dimension_doc_manager) {}

// TODO(wangguangyuan) : 使用configure
bool RepositoryManager::init(const std::string& path)
{
    if (_token_list_map.create(FLAGS_token_hashmap_buckets, FLAGS_token_hashmap_rwlocks) != 0) {
        UFATAL("FLAGS_token_list_map_reserve_size too big, no enough memory");
        return false;
    }
    _doc_info_list = new(std::nothrow) DocInfoList();
    if (_doc_info_list == NULL) {
        UFATAL("create DocInfoList failed, no enough memory");
        return false;
    }
    if (_doc_info_map.create(FLAGS_factdoc_hashmap_buckets, FLAGS_factdoc_hashmap_rwlocks) != 0) {
        UFATAL("FLAGS_doc_reserve_size too big, no enough memory");
        return false;
    }
    _annotation_manager = new(std::nothrow) AnnotationManager();
    if (_annotation_manager == NULL) {
        UFATAL("create AnnotationManager failed, no enough memory");
        return false;
    }
    // add guard
    doc_info_t * guard = new doc_info_t();
    guard->score = ILLEGAL_SCORE;
    guard->docid = ILLEGAL_DOCID;
    guard->forward_index = NULL;
    add_doc_info(guard);
    return _annotation_manager->init(path);
}

RepositoryManager::~RepositoryManager()
{
    size_t token_type_num = 0;
    size_t doc_hit_num = 0;
    for (TokenListMap::iterator it = _token_list_map.begin();
         it != _token_list_map.end(); ++it) {
        ++token_type_num;
        doc_hit_num += it->second->get_length();
        delete it->second;
    }
    if (_annotation_manager != NULL) {
        delete _annotation_manager;
    }
    if (_doc_info_list != NULL) {
        size_t i = 0;
        for (DocInfoList::iterator it = _doc_info_list->begin();
                    it != _doc_info_list->end(); ++it, ++i) {
            UDEBUG("DocInfoList[%u] score:%d docid:%llu",
                        i, (*it)->score, (*it)->docid);
            if ((*it)->forward_index != NULL) {
                delete (*it)->forward_index;
            }
            delete *it;
        }
        delete _doc_info_list;
    }
}

void RepositoryManager::set_token_list(TokenList * token_list)
{
    TokenId token_id = token_list->get_token_id();
    int ret = _token_list_map.set(token_id, token_list, 1);
    if (1 == ret) {
        UWARNING("[\tlvl=SERIOUS\ttoken_id=%lu\ttoken_list_map_size=%zu\t] "
                 "insert token_id fail", token_id, _token_list_map.size());
    } else if (bsl::HASH_OVERWRITE == ret) {
        UWARNING("[\tlvl=MONITOR\ttoken_id=%lu\t] overwrite token_id", token_id);
    }
}

/**
 * @note 只会处理text_value
 *
 */
const TokenList * RepositoryManager::get_token_list(
        const QueryNodeValue & value) const
{
    TokenId token_id = get_token_id_from_query_node_value(value);
    if (token_id == ILLEGAL_TOKEN_ID) {
        return NULL;
    }
    return get_token_list(token_id);
}

/**
 * @brief 范围检索获取TokenList
 */
const void RepositoryManager::get_token_list(const RangeRestriction & rr,
            std::vector<const TokenList*> * lists) const {
    // 目前只支持NumberSpec
    if (rr.has_number_spec() == false ||
        rr.annotation_name() == "") {
        UNOTICE("missing annotation name or number_spec in RangeRestriction");
        return;
    }

    // 通过AnnotationName获取AnnotationSchema
    const AnnotationSchema * schema = _annotation_manager->get_annotation_schema(
                rr.annotation_name());
    if (schema == NULL) {
        UNOTICE("[\tannotation_name=%s\t] get AnnotationSchema fail",
                    rr.annotation_name().c_str());
        return;
    }
    if (schema->annotation_type() != NUMBER) {
        UNOTICE("[\tannotation_name=%s\t] Annotation is not NUMBER type",
                    rr.annotation_name().c_str());
        return;
    }
    int64_t min = rr.number_spec().min();
    int64_t max = rr.number_spec().max();
    // first: number; second: shift
    std::vector<std::pair<int64_t, int32_t> > range_pairs;
    range_pairs.reserve(200U);
    get_proper_range_pairs(
                min,
                max,
                schema->number_schema().min(),
                schema->number_schema().max(),
                schema->number_schema().accuracy(),
                &range_pairs);

    for (size_t i = 0; i < range_pairs.size(); ++i) {
        string token_string(TOKEN_SEP + schema->annotation_name() + TOKEN_SEP +
                    Int64ToString(range_pairs[i].first) + TOKEN_SEP +
                    IntToString(range_pairs[i].second) + TOKEN_SEP);

        TokenId token_id = ILLEGAL_TOKEN_ID;
        // murmur 只有参数为 NULL 时才出错，所以这里不处理返回值
        uln_sign_murmur2_64(token_string.data(), token_string.size(),
                    reinterpret_cast<long long unsigned*>(&token_id));
        UDEBUG("generate token value:%s token_id:%llu", token_string.c_str(), token_id);
        const TokenList * list = get_token_list(token_id);
        if (list != NULL) {
            lists->push_back(list);
        }
    }
}

/**
 * @brief 需要处理一写多读的竞争
 */
TokenList * RepositoryManager::create_token_list_by_id(TokenId token_id)
{
    TokenList * token_list = NULL;
    // 当 token_id 不存在时，新建一个 token list
    if (bsl::HASH_EXIST != _token_list_map.get(token_id, &token_list)) {
        token_list = new TokenList(token_id);
        // 这里 set 时候用 1 flag，为的是返回的 token_list 指针是被使用的指针
        if (1 == _token_list_map.set(token_id, token_list, 1)) {
            UNOTICE("[\ttoken_id=%lu\ttoken_list_map_size=%zu\t] "
                     "insert token_id fail", token_id, _token_list_map.size());
        }
    }
    GOOGLE_CHECK(token_list);
    return token_list;
}

/**
 * @brief 这里的锁，只会影响not逻辑的查询性能
 */
doc_hit_t RepositoryManager::get_next_doc_info(int32_t score, DocId docid) const
{
    doc_info_t doc_info;
    doc_info.docid = docid;
    doc_info.score = score;
    doc_hit_t doc_hit;
    boost::shared_lock<boost::shared_mutex> lock(_doc_info_list_mu);
    DocInfoList::const_iterator it = _doc_info_list->lower_bound(&doc_info);
    if (it == _doc_info_list->end()) {
        UFATAL("the guard not work");
        GOOGLE_DCHECK(false) << "the guard not work";
        doc_hit.docid = ILLEGAL_DOCID;
        doc_hit.score = ILLEGAL_SCORE;
    } else {
        doc_hit.docid = (*it)->docid;
        doc_hit.score = (*it)->score;
    }
    return doc_hit;
}

void RepositoryManager::delete_doc_info(DocId docid)
{
    doc_info_t *res = NULL;
    if (bsl::HASH_EXIST == _doc_info_map.get(docid, &res)) {
        _doc_info_map.erase(docid);
        // BUG FIX: 写_doc_info_list时，需要加写锁
        boost::unique_lock<boost::shared_mutex> lock(_doc_info_list_mu);
        _doc_info_list->erase(res);
        Singleton<DelayedEnv>::get()->add_callback(NewCallback(&delay_delete_doc_info, res));
    } else {
        UTRACE("delete nonexist doc[%llu]", docid);
    }
}

ForwardIndex * RepositoryManager::create_forward_index()
{
    ForwardIndex * fi = new(std::nothrow) CompactForwardIndex();
    GOOGLE_DCHECK(fi);
    return fi;
}


}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
