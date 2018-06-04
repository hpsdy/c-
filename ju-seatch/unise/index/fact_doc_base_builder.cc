/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file fact_doc_base_builder.cc
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/26 16:52:52
 * @version $Revision$
 * @brief FactDoc基量构建类的实现
 *
 **/
#include "index/fact_doc_base_builder.h"
#include "gflags/gflags.h"
#include "unise/singleton.h"
#include "unise/skiplist.h"
#include "unise/serialization.h"
#include "unise/asl_wordseg.h"
#include "util/util.h"
#include "index/annotation_manager.h"
#include "index/index.h"

DEFINE_int32(fact_doc_base_build_promote_num, 10000, "how many docs build"
        " you want to be noticed");
DEFINE_bool(dump_base_index, false, "global switch, dump base index when building");
DEFINE_bool(load_base_index_from_dump, false, "global switch, load base index from dump file");
DECLARE_int32(max_wordseg_buffer_size);

namespace unise
{

FactDocBaseBuilder::FactDocBaseBuilder(const std::string &name,
        const DocFileInfo &doc_file_info,
        DimensionDocManager::dimension_t *dimension,
        boost::shared_ptr<DimensionDocManager> &dimension_doc_manager,
        boost::shared_ptr<RepositoryManager> &repository_manager) :
    DimensionDocBaseBuilder(name,
            doc_file_info,
            dimension,
            dimension_doc_manager),
    _repository_manager(repository_manager),
    _annotation_manager(repository_manager->get_annotation_manager()),
    _dimension_doc_manager(repository_manager->get_dimension_doc_manager()),
    _dict(NULL),
    _handler(NULL),
    _forward_index_path(doc_file_info.dump_forward_index_path),
    _inverted_index_path(doc_file_info.dump_inverted_index_path),
    _d2f_maps_path(doc_file_info.dump_d2f_maps_path)
{
    _dict = Singleton<AslWordseg>::get()->get_dict();
    GOOGLE_DCHECK(_dict);
    _handler = Singleton<AslWordseg>::get()->get_handle(FLAGS_max_wordseg_buffer_size);
    GOOGLE_DCHECK(_handler);
}

FactDocBaseBuilder::~FactDocBaseBuilder() {}

bool FactDocBaseBuilder::build_dimension_doc() {
    StopWatch build_stop_watch;
    UNOTICE("Begin to load fact doc file %s", get_name().c_str());
    std::vector<DimensionDoc *> dimension_docs;
    if (!_dimension->factory->deserialize(&dimension_docs)) {
        UFATAL("Failed to get FactDoc from file");
        return false;
    }
    int cnt = 0;
    DimensionDoc* doc = NULL;
    for (size_t i = 0; i < dimension_docs.size(); i++) {
        doc = dimension_docs[i];
        if (doc) {
            _dimension->doc_map->set(doc->get_doc_id(), doc, 0);
            if (++cnt % FLAGS_fact_doc_base_build_promote_num == 0) {
                UNOTICE("load %d FactDoc already", cnt);
            } 
        } else {
            UFATAL("Failed to get FactDoc from vector [idx:%u]", i);
            return false;
        }
    }
    UNOTICE("Finish load %d fact doc file in %0.1f ms %s",
                cnt, build_stop_watch.read(), get_name().c_str());
    return true;
}

bool FactDocBaseBuilder::load_d2f_maps() {
    std::ifstream ifs(_d2f_maps_path.c_str());
    if (!ifs.good()) {
        UFATAL("Failed to load file: %s.", _d2f_maps_path.c_str());
        return false;
    }
    try {
        boost::archive::binary_iarchive ia(ifs);
        // 定义要序列化的结构  
        typedef __gnu_cxx::hash_map<DocId, vector<DocId> > ar_d2f_map_t;
        std::vector<ar_d2f_map_t *> ar_d2f_maps;
        ia & ar_d2f_maps; 
        std::vector<DimensionDocManager::d2f_map_t *> d2f_maps;
        size_t vec_size = ar_d2f_maps.size();
        for (size_t i = 0; i < vec_size; ++i) {
            if (ar_d2f_maps[i]) {
                DimensionDocManager::d2f_map_t * tmp_map = new DimensionDocManager::d2f_map_t();
                if (tmp_map == NULL) {
                    UFATAL("create d2f_map_t failed");
                    return false;
                }
                for (ar_d2f_map_t::iterator map_it = ar_d2f_maps[i]->begin(); 
                        map_it != ar_d2f_maps[i]->end(); ++map_it) {
                    std::vector<DocId> doc_ids = map_it->second; 
                    SkipList<DocId> * list = new SkipList<DocId>();
                    if (list == NULL) {
                        UFATAL("create skip_list failed");
                        return false;
                    }
                    UTRACE("key: %lu", map_it->first);
                    size_t doc_id_num = doc_ids.size();
                    for (size_t i = 0; i < doc_id_num; ++i) {
                        list->insert(doc_ids[i]);
                        UTRACE("doc_id: %lu", doc_ids[i]);
                    } 
                    tmp_map->insert(std::make_pair(map_it->first, list));
                }
                d2f_maps.push_back(tmp_map); 
            } else {
                d2f_maps.push_back(NULL); 
            } 
        } 
        _dimension_doc_manager->set_d2f_maps(d2f_maps);
    } catch (std::bad_alloc& e) {
        UFATAL("Failed to deserialize, err_msg:%s", e.what());
        return false;
    } catch (boost::archive::archive_exception& e) {
        UFATAL("Failed to deserialize, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to deserialize");
        return false;
    }
    return true;
}

bool FactDocBaseBuilder::dump_d2f_maps() {
    try {
        std::ofstream ofs(_d2f_maps_path.c_str());
        if (!ofs.good()) {
            UFATAL("Failed to load file: %s.", _d2f_maps_path.c_str());
            return false;
        }
        boost::archive::binary_oarchive oa(ofs);
        std::vector<DimensionDocManager::d2f_map_t *> d2f_maps;
        d2f_maps = _dimension_doc_manager->get_d2f_maps();
        // 定义要序列化的结构  
        typedef __gnu_cxx::hash_map<DocId, vector<DocId> > ar_d2f_map_t;
        std::vector<ar_d2f_map_t *> ar_d2f_maps;
        size_t vec_size = d2f_maps.size();
        for (size_t i = 0; i < vec_size; ++i) {
            if (d2f_maps[i]) {
                ar_d2f_map_t * tmp_map = new ar_d2f_map_t();
                if (tmp_map == NULL) {
                    UFATAL("create d2f_map_t failed");
                    return false;
                }
                for (DimensionDocManager::d2f_map_t::iterator map_it = d2f_maps[i]->begin(); 
                        map_it != d2f_maps[i]->end(); ++map_it) {
                    SkipList<DocId> * skip_list = map_it->second; 
                    _SkipListConstIterator<DocId> iterator = skip_list->begin();
                    std::vector<DocId> doc_ids;
                    UTRACE("key: %lu", map_it->first);
                    for (; iterator != skip_list->end(); ++iterator) {
                        doc_ids.push_back(*iterator);
                        UTRACE("doc_id: %lu", *iterator);
                    } 
                    tmp_map->insert(std::make_pair(map_it->first, doc_ids));
                }
                ar_d2f_maps.push_back(tmp_map); 
            } else {
                ar_d2f_maps.push_back(NULL); 
            } 
        } 
        oa & ar_d2f_maps;
        vec_size = ar_d2f_maps.size();
        for (size_t i = 0; i < vec_size; ++i) {
            if (ar_d2f_maps[i]) {
                delete ar_d2f_maps[i];
            }
        }
    } catch (std::bad_alloc& e) {
        UFATAL("Failed to serialize, err_msg:%s", e.what());
        return false;
    } catch (boost::archive::archive_exception& e) {
        UFATAL("Failed to serialize, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to serialize");
        return false;
    }
    return true;
}

bool FactDocBaseBuilder::build()
{
    if (FLAGS_load_base_index_from_dump) {
        // TODO(wangguangyuan) : 并行化
        return build_dimension_doc() &&
            load_forward_index(_forward_index_path) &&
            load_inverted_index(_inverted_index_path) &&
            load_d2f_maps();
    }
    int fd = -1;
    const size_t BUFFER_SIZE = 1024 * 1024 * 128;
    ZeroCopyOutputStream* raw_output = NULL;
    CodedOutputStream* coded_output = NULL;
    boost::scoped_array<uint8_t> buffer(new uint8_t[BUFFER_SIZE]);

    // dump正排
    if (FLAGS_dump_base_index) {
        fd = open(_forward_index_path.c_str(),
                      O_WRONLY | O_CREAT | O_TRUNC,
                      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if (fd == -1) {
            UFATAL("write to file:%s failed", _forward_index_path.c_str());
            return false;
        }
        raw_output = new FileOutputStream(fd);
        coded_output = new CodedOutputStream(raw_output);
        coded_output->WriteLittleEndian32(FORWARD_MAGIC);
    }

    StopWatch build_stop_watch;
    int cnt = 0;
    UNOTICE("Begin to load fact doc file %s:%s", get_file_name().c_str(), get_name().c_str());
    DimensionDoc* doc = NULL;
    std::vector<const DimensionDoc* > dimension_docs;
    bool has_next = true;
    
    while (has_next) {
        if (!get_next_doc(&doc, &has_next)) {
            UFATAL("Failed to get doc from file %s", get_file_name().c_str());
            return false;
        }
        if (doc == NULL) {
            continue;
        }
        if (FLAGS_dump_base_index) {
            // 收集dimensionDoc  
            dimension_docs.push_back(doc);
        }
        _dimension->doc_map->set(doc->get_doc_id(), doc, 0);
        FactDoc *fact_doc = down_cast<FactDoc*>(doc);

        //添加DocInfo
        doc_info_t * doc_info = new doc_info_t();
        doc_info->docid = fact_doc->get_doc_id();
        doc_info->score = fact_doc->get_score();
        doc_info->fact_doc = fact_doc;
        //构建正排索引
        std::vector<TokenHit> token_hits;
        get_token_hits(fact_doc, *doc_info, &token_hits);
        doc_info->forward_index = _repository_manager->create_forward_index();
        GOOGLE_DCHECK(doc_info->forward_index);
        if (doc_info->forward_index->build(token_hits) == false) {
            UWARNING("Failed to build forward index for doc %llu", doc_info->docid);
            delete doc_info->forward_index;
            delete doc_info;
            continue;
        }
        // 级联更新map，并获取flag
        doc_info->filter_flag = _dimension_doc_manager->add_fact_doc_filter_relation(*fact_doc);
        _repository_manager->add_doc_info(doc_info);

        //将TokenHit链表存储到全局列表中，等待批量构建倒排
        if (doc_info->filter_flag == 0) {
            _token_hit_list.insert(_token_hit_list.end(), token_hits.begin(), token_hits.end());
        }

        // dump正排数据
        if (fd != -1) {
            coded_output->WriteVarint64(doc_info->docid);
            coded_output->WriteVarint32(doc_info->score);
            coded_output->WriteRaw(&(doc_info->filter_flag), 1);
            // note:不需要dump fact_doc，因为fact_doc的指针下次会变
            int length = doc_info->forward_index->get_dump_data(buffer.get(), BUFFER_SIZE);
            GOOGLE_CHECK_NE(length, -1);
            coded_output->WriteVarint32(length);
            coded_output->WriteRaw(buffer.get(), length);
        }
        if (++cnt % FLAGS_fact_doc_base_build_promote_num == 0) {
            UNOTICE("load %d FactDoc already", cnt);
        }
    }

    if (FLAGS_dump_base_index) {
        // 序列化 dimension_docs
        if (!_dimension->factory->serialize(dimension_docs)) {
            UFATAL("Failed to serialize FactDoc from file");
            return false;
        }
        // 序列化 _d2f_maps
        if (!dump_d2f_maps()) {
            UFATAL("Failed to serialize dump_d2f_maps");
            return false;
        }
    }

    if (fd != -1) {
        // 写结束标记
        coded_output->WriteVarint64(ILLEGAL_DOCID);
        coded_output->WriteLittleEndian32(FORWARD_MAGIC);
        delete coded_output;
        delete raw_output;
        UNOTICE("dump forward_index to file:%s succ", _forward_index_path.c_str());
        close(fd);
    }
    //批量构建倒排索引
    UNOTICE("start to sort %u TokenHit", _token_hit_list.size());
    // 排序，并去重一个doc内重复的token，不考虑pos信息
    std::sort(_token_hit_list.begin(), _token_hit_list.end());
    std::vector<TokenHit>::iterator end_iter =
                std::unique(_token_hit_list.begin(), _token_hit_list.end(), TokenHitCompare);
    _token_hit_list.erase(end_iter, _token_hit_list.end());

    UNOTICE("start to build inverted docs for %d FactDocs", cnt);
    if (!batch_build_inverted_index()) {
        UFATAL("Failed to batch build inverted index");
        return false;
    }
    UNOTICE("Finish loading fact doc file %s:%s in %0.1f ms, %d docs added",
            get_file_name().c_str(), get_name().c_str(), build_stop_watch.read(), cnt);
    return true;
}

void FactDocBaseBuilder::get_token_hits(FactDoc * doc,
            const doc_info_t& doc_info,
            std::vector<TokenHit> *token_hits) {
    std::vector<Annotation> new_annos;
    for (size_t i = 0; i < doc->annotations.size(); ++i) {
        //get the annotation schema
        const AnnotationSchema * schema = _annotation_manager->get_annotation_schema(
                    doc->annotations.at(i).id);
        if (schema == NULL) {
            UWARNING("not find AnnotationSchema id[%u] for doc [%llu], egnore",
                     static_cast<AnnotationId>(doc->annotations.at(i).id),
                     doc->get_doc_id());
            continue;
        }
        // 判断是否需要索引
        if (STORE_INDEX & schema->store_type()) {
            // 获取token hits
            get_token_hit_list_from_annotation(doc_info,
                    doc->annotations.at(i),
                    *schema,
                    *token_hits,
                    _dict,
                    _handler);
        }
        // 判断是否需要存储原文
        if ((STORE_MEMORY | STORE_DISK) & schema->store_type()) {
            new_annos.push_back(doc->annotations.at(i));
        }
    }
    // 使用新的annotation
    // 对annotation按照annotation_id排序
    sort(new_annos.begin(), new_annos.end());
    doc->annotations.swap(new_annos);

    //sort & unique
    std::sort(token_hits->begin(), token_hits->end());
}

/**
 * @brief tokenid按照差分压缩，第一个tokenid不压缩
 *               读取到一个ILLEGAL_DOCID后，代表当前倒排结束
 *        读取到一个ILLEGAL_TOKEN_ID后，代表所有的倒排读取完毕
 */
bool FactDocBaseBuilder::batch_build_inverted_index()
{
    uint64_t token_type_num = 0LLU;
    int fd = -1;
    ZeroCopyOutputStream* raw_output = NULL;
    CodedOutputStream* coded_output = NULL;

    // dump倒排
    if (FLAGS_dump_base_index) {
        fd = open(_inverted_index_path.c_str(),
                      O_WRONLY | O_CREAT | O_TRUNC,
                      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if (fd == -1) {
            UFATAL("write to file:%s failed", _inverted_index_path.c_str());
            return false;
        }
        raw_output = new FileOutputStream(fd);
        coded_output = new CodedOutputStream(raw_output);
        coded_output->WriteLittleEndian32(INVERTED_MAGIC);
    }

    if (_token_hit_list.size() > 0) {
        const TokenHit & hit = _token_hit_list.at(0);
        doc_hit_t doc_hit;
        doc_hit.docid = hit.get_doc_id();
        doc_hit.score = hit.get_score();
        std::vector<doc_hit_t> doc_hit_list;
        doc_hit_list.push_back(doc_hit);
        int token_list_size = 1;

        TokenId last_token_id = hit.get_token_id();
        TokenId token_id_off = 0;

        if (fd != -1) {
            // 输出第一个token的信息
            coded_output->WriteVarint64(hit.get_token_id());
            coded_output->WriteVarint64(hit.get_doc_id());
            coded_output->WriteVarint32(hit.get_score());
        }

        for (size_t i = 1; i < _token_hit_list.size(); ++i) {
            const TokenHit & hit = _token_hit_list.at(i);
            TokenId token_id = hit.get_token_id();
            if (last_token_id != token_id) {
                // last_token_id的倒排拉链结束了
                if (token_list_size >= token_list_limit_size) {
                    UWARNING("tokenid:%llu inverted list %d > %d",
                                last_token_id, token_list_size, token_list_limit_size);
                }
                ++token_type_num;
                TokenList *token_list = new TokenList(
                            last_token_id,
                            new FixPostList(last_token_id, &doc_hit_list));
                _repository_manager->set_token_list(token_list);
                // set_token_list will swap, so don't need to clear
                // doc_hit_list.clear();
                doc_hit.docid = hit.get_doc_id();
                doc_hit.score = hit.get_score();
                doc_hit_list.push_back(doc_hit);
                token_list_size = 1;

                // 输出dump
                if (fd != -1) {
                    // 写一个非法的docid作为上一个token拉链的结束
                    coded_output->WriteVarint64(ILLEGAL_DOCID);
                    // 对token id 差分压缩
                    token_id_off = token_id - last_token_id;
                    coded_output->WriteVarint64(token_id_off);
                    coded_output->WriteVarint64(hit.get_doc_id());
                    coded_output->WriteVarint32(hit.get_score());
                }
                last_token_id = token_id;
            } else if (token_list_size++ < token_list_limit_size) {
                // 单个token的倒排长度做截断，检索不可能检索这么深
                // 也是为了保证输出的倒排长度不超过2G
                doc_hit.docid = hit.get_doc_id();
                doc_hit.score = hit.get_score();
                doc_hit_list.push_back(doc_hit);
                // 输出dump
                if (fd != -1) {
                    coded_output->WriteVarint64(hit.get_doc_id());
                    coded_output->WriteVarint32(hit.get_score());
                }
            }
        }
        ++token_type_num;
        TokenList *token_list = new TokenList(last_token_id,
                                              new FixPostList(last_token_id, &doc_hit_list));
        _repository_manager->set_token_list(token_list);
        if (fd != -1) {
            // 最后一个token的结束
            coded_output->WriteVarint64(ILLEGAL_DOCID);
        }
    }
    if (fd != -1) {
        // dump文件的结束标记
        coded_output->WriteVarint64(ILLEGAL_TOKEN_ID);
        coded_output->WriteLittleEndian32(INVERTED_MAGIC);
        delete coded_output;
        delete raw_output;
        close(fd);
        UNOTICE("dump inverted_index to file:%s succ", _inverted_index_path.c_str());
    }
    UNOTICE("base inverted index has %llu token_type", token_type_num);
    return true;
}

}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
