// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/doc_builder.h"
#include "unise/singleton.h"
#include "unise/asl_wordseg.h"
#include "unise/base.h"
#include "unise/fact_doc.h"
#include "unise/general_servlet.pb.h"
#include "unise/annotation_schema.pb.h"
#include "util/util.h"
#include "index/index.h"
#include "index/repository_manager.h"
#include "index/annotation_manager.h"
#include "index/dimension_doc_manager.h"
#include "index/token_list.h"
#include "index/forward_index.h"

DEFINE_int32(max_wordseg_buffer_size, 10240, "the max buffer size for each-wordseg, \
            should be small than ANNOTATION_SIZE_MAX 409600");

namespace unise {

DocBuilder::DocBuilder(RepositoryManager * repository_manager) :
        _repository_manager(repository_manager),
        _annotation_manager(repository_manager->get_annotation_manager()),
        _dimension_doc_manager(repository_manager->get_dimension_doc_manager()),
        _dict(NULL),
        _handler(NULL),
        _doc_count(0),
        _anno_count(0),
        _token_count(0) {
    _dict = Singleton<AslWordseg>::get()->get_dict();
    GOOGLE_DCHECK(_dict);
    _handler = Singleton<AslWordseg>::get()->get_handle(FLAGS_max_wordseg_buffer_size);
    GOOGLE_DCHECK(_handler);
}

DocBuilder::~DocBuilder() {}

/**
 * warning : the dimension doc should exist already
 */
void DocBuilder::build(FactDoc * doc) {
    // clear the context
    _token_hits.clear();
    DocId docid = doc->get_doc_id();

    // note : 不能重复构建一个doc的倒排和ForwardIndex
    //        由上层调用方保障，为提高性能，这里使用Debug检查
    //        Release版本不会存在该检查
    GOOGLE_DCHECK_EQ(NULL, _repository_manager->get_doc_info(docid));

    // note: build index
    //   first build forward index
    //   then  build inverted index
    _cur_doc_info = new(std::nothrow) doc_info_t();
    if (_cur_doc_info == NULL) {
        // 内存不足，放弃构建
        UWARNING("[\tlvl=SERIOUS\t] contruct doc_info for doc:%llu failed", docid);
        return;
    }
    _cur_doc_info->docid = docid;
    _cur_doc_info->score = doc->get_score();
    _cur_doc_info->fact_doc = doc;
    UDEBUG("doc %llu has %u annotations", docid, doc->annotations.size());

    _anno_count += doc->annotations.size();
    vector<Annotation> new_annos;
    for (size_t i = 0; i < doc->annotations.size(); ++i) {
        // get the annotation schema
        const AnnotationSchema* schema = _annotation_manager->get_annotation_schema(
                    doc->annotations[i].id);
        if (schema == NULL) {
            UWARNING("[\tlvl=COUNT\t] not find AnnotationSchema id[%u] for doc [%llu], ignore",
                     static_cast<AnnotationId>(doc->annotations[i].id),
                     docid);
            continue;
        }
        // 判断是否需要索引
        if (STORE_INDEX & schema->store_type()) {
            // 获取token hits
            get_token_hit_list_from_annotation(
                        *_cur_doc_info,
                        doc->annotations.at(i),
                        *schema,
                        _token_hits,
                        _dict,
                        _handler);
        }
        // 判断是否需要存储原文
        if ((STORE_MEMORY | STORE_DISK) & schema->store_type()) {
            new_annos.push_back(doc->annotations[i]);
        }
    }
    // 使用新的annotation
    doc->annotations.swap(new_annos);
    
    // 根据配置，抽取级联关系，获取flag值
    _cur_doc_info->filter_flag = _dimension_doc_manager->add_fact_doc_filter_relation(*doc);
    UDEBUG("[docid:%llu] [filter_flag:%u]", docid, _cur_doc_info->filter_flag);

    // sort first
    sort(_token_hits.begin(), _token_hits.end());
    UDEBUG("sort done. doc:%llu has %u tokens", docid, _token_hits.size());
    // build forward index first
    ForwardIndex * forward_index = _repository_manager->create_forward_index();
    if (forward_index == NULL || forward_index->build(_token_hits) == false) {
        GOOGLE_DCHECK(0);
        // note: 此时，dimension doc已经存在了，虽然倒排正排不存在
        UFATAL("Build forward index fail for docid:%llu", docid);
        delete forward_index;
        delete _cur_doc_info;
        return;
    }
    _cur_doc_info->forward_index = forward_index;
    // writelock
    _repository_manager->add_doc_info_with_lock(_cur_doc_info);

    // 只有当不被过滤时，才建到索引中
    if (_cur_doc_info->filter_flag == 0) {
        // build inverted index
        // uniq
        // note: only build the DocHit now, ignor the annotation_id and pos info
        vector<TokenHit>::iterator garbage_it = unique(
                    _token_hits.begin(),
                    _token_hits.end(),
                    TokenHitCompare);
        _token_hits.erase(garbage_it, _token_hits.end());
        UDEBUG("unique done. doc:%llu has %u tokens", docid, _token_hits.size());
        for (size_t j = 0; j < _token_hits.size(); ++j) {
            const TokenHit & token_hit = _token_hits.at(j);
            UDEBUG("Get TokenList of token[%s, %llu]",
                        token_hit.get_token_value().c_str(),
                        token_hit.get_token_id());
            // writelock
            TokenList * token_list =
                _repository_manager->create_token_list_by_id(token_hit.get_token_id());
            doc_hit_t doc_hit;
            doc_hit.score = token_hit.get_score();
            doc_hit.docid = token_hit.get_doc_id();
            token_list->insert_doc_hit(doc_hit);
        }
        _token_count += _token_hits.size();
    } else {
        UTRACE("filted [fact_doc:%llu] filter_flag[%u]",
                    _cur_doc_info->docid, _cur_doc_info->filter_flag);
    }
    finish_doc();
}

void DocBuilder::finish_doc() {
    UTRACE("build index for docid:%llu done", _cur_doc_info->docid);
    ++_doc_count;
    if (_doc_count == 5000) {
        UNOTICE("build 5000 docs with %llu annotations, %llu tokens",
                    _anno_count, _token_count);
        _doc_count = 0;
        _anno_count = 0;
        _token_count = 0;
    }
}


void DocBuilder::remove(DocId docid) {
    // note : clean the context
    _token_id_list.clear();

    // get the doc info from the repository manager
    const doc_info_t * doc_info = _repository_manager->get_doc_info(docid);
    if (NULL == doc_info) {
        // 删除doc_info失败是一种常态
        UTRACE("get_doc_info of docid[%llu] fail", docid);
        return;
    }

    // 更新级联map
    _dimension_doc_manager->remove_fact_doc_filter_relation(*(doc_info->fact_doc));

    // get token id list from forward index
    if (doc_info->forward_index == NULL ||
        false == doc_info->forward_index->get_token_id_list(&_token_id_list)) {
        UWARNING("[\tlvl=FOLLOW\tdocid=%llu\t] get_token_id_list fail", docid);
        return;
    }
    
    doc_hit_t doc_hit = {docid, doc_info->score};
    // delete the inverted index
    for (size_t i = 0; i < _token_id_list.size(); ++i) {
        TokenList * list = _repository_manager->get_token_list(_token_id_list.at(i));
        if (list == NULL) {
            UDEBUG("[tokenid=%llu] miss inverted list", _token_id_list.at(i));
            continue;
        }
        list->delete_doc_hit(doc_hit);
    }
    // delete the doc info
    _repository_manager->delete_doc_info(docid);
}

uint32_t DocBuilder::filt_relation_ship(const SkipList<DocId>* docids,
            uint8_t flag,
            uint8_t mask) {
    if (docids == NULL) {
        return 0U;
    }
    doc_hit_t doc_hit;
    uint32_t doc_num = 0;
    uint8_t new_flag = 0;
    uint8_t old_flag = 0;
    for (SkipList<DocId>::const_iterator it = docids->begin();
                it != docids->end(); ++it) {
        doc_hit.docid = *it;
        UDEBUG("check [fact_doc:%llu] whether need to filted", doc_hit.docid);
        doc_info_t * doc_info = _repository_manager->get_doc_info(doc_hit.docid);
        if (doc_info == NULL) {
            UDEBUG("[fact_doc:%llu] docinfo not found", doc_hit.docid);
            continue;
        }
        doc_hit.score = doc_info->score;
        old_flag = doc_info->filter_flag;
        new_flag = (old_flag & ~mask) | flag;
        // 这里就一个uint_8的赋值的，不需要考虑原子操作问题
        doc_info->filter_flag = new_flag;
        if ((new_flag == 0 && old_flag == 0) ||
            (new_flag != 0 && old_flag != 0)) {
            UDEBUG("doc[%llu] flag not change, [old:%u] [new:%u]",
                        doc_hit.docid, old_flag, new_flag);
            continue;
        }

        // 拿到所有的倒排入口，更新对应DocHit的flag
        _relation_token_ids.clear();
        doc_info->forward_index->get_token_id_list(&_relation_token_ids);
        for (size_t j = 0; j < _relation_token_ids.size(); ++j) {
            // 如果不存在倒排链，那么直接新建一个新的
            TokenList * token_list = _repository_manager->create_token_list_by_id(_relation_token_ids[j]);
            token_list->set_filter_flag(doc_hit, new_flag);
            UDEBUG("[fact_doc:%llu] [token_id:%llu] [flag:%u]",
                        doc_hit.docid, _relation_token_ids[j], new_flag);
        }
        // 走到这里，说明更新了一个doc的所有的token，进行计数
        ++doc_num;
    }
    return doc_num;
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
