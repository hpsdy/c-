// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/dimension_doc_manager.h"

#include "gflags/gflags.h"
#include "unise/delay_callback.h"
#include "unise/annotation_schema.pb.h"
#include "unise/util.h"

namespace unise {

// 内部采用数组管理配置，考虑高效，因此数组长度不能太大
DEFINE_int32(dimension_family_max_id, 128, "the max level id of the dimension_doc");
DEFINE_int32(dimensiondoc_hashmap_buckets, 1000000, "the default dimensiondoc_hashmap_buckets"
                                                    "suggest to config in the unise_serve.conf"
                                                    "for each DimensionDoc");

DimensionDocManager::DimensionDocManager() :
    _dimensions(FLAGS_dimension_family_max_id + 1),
    _fact_doc_id(ILLEGAL_LEVEL_ID),
    _need_filter(false) {}

DimensionDocManager::~DimensionDocManager() {
    for (size_t i = 0; i < _d2f_maps.size(); ++i) {
        if (_d2f_maps[i] != NULL) {
            delete _d2f_maps[i];
        }
    }
    // 因为可能有dimension doc还没有延迟删除，在析构dimention_t的时候
    // 需要提前把延迟回调都执行了，否则，factory都没了，如果
    // 延迟回调又得到执行，那么会出core
    Singleton<DelayedEnv>::get()->execute_callback_now();
}

bool DimensionDocManager::dimension_doc_exist(size_t id) const {
    if (id < _dimensions.size()) {
        return _dimensions[id].factory != NULL;
    } else {
        return false;
    }
}

// note: 由于拿不到AnnotationSchema，所以这里没有对非number类型的
// annotation做判断
bool DimensionDocManager::init_filter_relation_ship(const std::string& path) {
    FilterRelationShipConfig config;    ///< 级联过滤规则
    if (!load_protobuf_conf(path, &config)) {
        UFATAL("[FilterRelationShipConfig:%s] illegal", path.c_str());
        return false;
    }
    if (config.filter_relation_ships_size() > 8) {
        UFATAL("[FilterRelationShipConfig:%s] has %d relations > 8",
                    path.c_str(), config.filter_relation_ships_size());
        return false;
    }
    for (int i = 0; i < config.filter_relation_ships_size(); ++i) {
        const FilterRelationShip & p = config.filter_relation_ships(i); 
        // 基量的加载顺序是level id小的在前面，大的在后面
        // 为了保证逻辑正确，只能让fact_doc跟自己或比自己小的level的
        // dimension doc 级联
        if (p.level_id() > get_fact_doc_level_id()) {
            UFATAL("FilterRelationShipConfig:%s] [levelid:%d] > [fact_doc_level_id:%d]",
                        path.c_str(),
                        p.level_id(),
                        get_fact_doc_level_id());
            return false;
        }
        filter_relation_ship_t r;
        r.foreign_key = p.foreign_key();
        r.level_id = p.level_id();
        r.relation_key = p.relation_key();
        for (int j = 0; j < p.filted_values_size(); ++j) {
            r.filted_values.insert(p.filted_values(j));
        }
        _filters.push_back(r);
        if (p.level_id() >= _d2f_maps.size()) {
            // 默认往后面插空指针
            _d2f_maps.resize(p.level_id() + 1, NULL);
        }
        if (_d2f_maps.at(p.level_id()) == NULL) {
            d2f_map_t * tmp_map = new d2f_map_t();
            if (tmp_map == NULL) {
                UFATAL("create d2f_map_t failed");
                return false;
            }
            _d2f_maps.at(p.level_id()) = tmp_map;
        }
    }
    if (_filters.size() <= 0) {
        UNOTICE("[FilterRelationShipConfig:%s] has no relations", path.c_str());
        return true;
    }
    _need_filter = true;
    UNOTICE("init [FilterRelationShipConfig:%s] succ", path.c_str());
    return true;
}

bool DimensionDocManager::init(const comcfg::ConfigUnit& conf) {
    // note: conf is a DimensionDoc array bellow EngineUnit
    std::string dimension_name;
    std::string doc_factory_name;
    size_t id = ILLEGAL_LEVEL_ID;
    try {
        size_t num = static_cast<size_t>(conf.size());
        if (num == 0U) {
            UFATAL("miss dimension doc config array");
            return false;
        }
        UNOTICE("%u types DimensionDoc tobe Inited", num);
        for (size_t i = 0; i < num; ++i) {
            dimension_name.assign(conf[i]["DimensionName"].to_cstr());
            doc_factory_name.assign(conf[i]["DocFactory"].to_cstr());
            id = conf[i]["Id"].to_uint32();
            int32_t hashmap_buckets = FLAGS_dimensiondoc_hashmap_buckets;
            if (id > static_cast<size_t>(FLAGS_dimension_family_max_id)) {
                UFATAL("id:%u great than %d", id, FLAGS_dimension_family_max_id);
                return false;
            }
            // check if the DimensionDoc exist
            if (_family_map.find(dimension_name) != _family_map.end()) {
                UFATAL("DimensionDoc:%s exist", dimension_name.c_str());
                return false;
            }
            // check if the id conflict
            if (_dimensions[id].factory != NULL) {
                UFATAL("DimensionDoc id:%u exist", id);
                return false;
            }
            // check if has hashbuckets
            if (conf[i]["HashmapBuckets"].selfType() != comcfg::CONFIG_ERROR_TYPE) {
                hashmap_buckets = conf[i]["HashmapBuckets"].to_int32();
            }
            UNOTICE("DimensionDoc id:%u hashmap buckets:%d", id, hashmap_buckets);

            // check if the current DimensionDoc is FactDoc
            if (conf[i]["IsFactDoc"].selfType() != comcfg::CONFIG_ERROR_TYPE &&
                strcmp(conf[i]["IsFactDoc"].to_cstr(), "true") == 0) {
                UNOTICE("Find FactDoc level_id:%u, name:%s", id, dimension_name.c_str());
                _fact_doc_id = id;
                _fact_doc_name = dimension_name;
            }

            // check if has FilterRelationShipConfig
            if (conf[i]["FilterRelationShipConfig"].selfType() != comcfg::CONFIG_ERROR_TYPE) {
                if (!init_filter_relation_ship(conf[i]["FilterRelationShipConfig"].to_cstr())) {
                    return false;
                }
            }

            // generate the DocFactory
            DocFactory * factory = DocFactoryFactory::get_instance(
                                   doc_factory_name);
            if (factory == NULL) {
                UFATAL("Generate DocFactory:%s failed", doc_factory_name.c_str());
                return false;
            } else if (factory->init(conf[i]) == false) {
                UFATAL("Init %s failed", doc_factory_name.c_str());
                delete factory;
                factory = NULL;
                return false;
            } else {
                // set the dimension_t to list
                _dimensions[id].id = id;
                _dimensions[id].name = dimension_name;
                // TODO 使用者需要 catch 异常
                _dimensions[id].doc_map = new DimensionDocMap(hashmap_buckets);
                _dimensions[id].factory = factory;
                // set the map k-v
                _family_map.insert(std::make_pair(dimension_name, id));
                UNOTICE("Init DocFactory:%s DimensionDoc:%s succ",
                        dimension_name.c_str(), doc_factory_name.c_str());
            }
        }
    } catch (comcfg::ConfigException & e) {
        UFATAL("Init EngineUnitManager fail:%s", e.what());
        return false;
    }
    if (_fact_doc_id == ILLEGAL_LEVEL_ID) {
        _fact_doc_name = dimension_name;
        _fact_doc_id = id;
        UNOTICE("Not find fact doc, use the last dimension doc as fact doc");
    }
    UNOTICE("Init DimensionDocManager succ");
    return true;
}

void DimensionDocManager::add_relation_ship(uint32_t dim_level_id, DocId dim_id,
            DocId fact_id) {
    if (dim_level_id >= _d2f_maps.size()) {
        return;
    }
    d2f_map_t * d2f_map = _d2f_maps[dim_level_id];
    if (d2f_map == NULL) {
        return;
    }

    d2f_map_t::iterator it = d2f_map->find(dim_id);
    if (it == d2f_map->end()) {
        SkipList<DocId> * list = new SkipList<DocId>();
        list->insert(fact_id);
        d2f_map->insert(std::make_pair(dim_id, list));
    } else {
        it->second->insert(fact_id);
    }
}

void DimensionDocManager::remove_relation_ship(uint32_t dim_level_id, DocId dim_id,
            DocId fact_id) {
    if (dim_level_id >= _d2f_maps.size()) {
        return;
    }
    d2f_map_t * d2f_map = _d2f_maps[dim_level_id];
    if (d2f_map == NULL) {
        return;
    }
    d2f_map_t::iterator it = d2f_map->find(dim_id);
    if (it != d2f_map->end()) {
        it->second->erase(fact_id);
        // 如果等于0，那么清除dimension id对应的map
        if (it->second->size() == 0U) {
            // 首先删除SkipList
            delete it->second;
            // 然后删除hashmap的节点
            d2f_map->erase(it);
        }
    }
}


void DimensionDocManager::remove_fact_doc_filter_relation(const FactDoc& doc) {
    if (!_need_filter) {
        return;
    }
    // 首先获取flag位
    for (size_t i = 0; i < _filters.size(); ++i) {
        const filter_relation_ship_t& r = _filters[i];
        // 只有当非自身级联时，才会有级联关系在map中存储
        if (r.foreign_key != ILLEGAL_ANNOTATION_ID) {
            const Annotation* anno = find_annotation_by_id(r.foreign_key, doc);
            if (anno != NULL) {
                // 只要在FactDoc中找到annotation，那么就应该删除正向级联关系
                remove_relation_ship(r.level_id, anno->number_value, doc.get_doc_id());
            }
        }
    }
}

uint8_t DimensionDocManager::add_fact_doc_filter_relation(const FactDoc& doc) {
    uint8_t flag = 0;
    if (!_need_filter) {
        return flag;
    }
    // 首先获取flag位
    for (size_t i = 0; i < _filters.size(); ++i) {
        const filter_relation_ship_t& r = _filters[i];
        bool pass = false;
        do {
            const DimensionDoc * dim = &doc;
            // 不用fact_doc自身的annotation做过滤，才需要先找到那个dim doc
            if (r.foreign_key != ILLEGAL_ANNOTATION_ID) {
                const Annotation* anno = find_annotation_by_id(r.foreign_key, doc);
                if (anno == NULL) {
                    UDEBUG("filted cause miss [factdoc:%llu] [annotation:%u]",
                                doc.get_doc_id(), r.foreign_key);
                    break;
                }
                // 只要在FactDoc中找到annotation，那么就应该存储正向级联关系
                add_relation_ship(r.level_id, anno->number_value, doc.get_doc_id());
                dim = get_dimension_doc(r.level_id, anno->number_value);
                if (dim == NULL) {
                    UDEBUG("filted cause miss [level_id:%u] [dimdoc:%llu]",
                                r.level_id, anno->number_value);
                    break;
                }
            }
            const Annotation* filter_anno = find_annotation_by_id(r.relation_key, *dim);
            if (filter_anno == NULL) {
                UDEBUG("filted cause miss [dimdoc:%llu] [annotation:%u]",
                            dim->get_doc_id(), r.relation_key);
                break;
            }
            if (r.filted_values.find(filter_anno->number_value) == r.filted_values.end()) {
                pass = true;
            } else {
                pass = false;
                UDEBUG("filted cause value hit "
                            "[factdoc:%llu] [dimdoc:%llu] [annotation:%u] [value:%llu]",
                            doc.get_doc_id(), dim->get_doc_id(),
                            r.relation_key, filter_anno->number_value);
            }
        } while (0);
        if (!pass) {
            flag |= (1 << i);
        }
    }
    return flag;
}




const SkipList<DocId> * DimensionDocManager::get_filt_relation_docids(
            uint8_t * flag,
            uint8_t * mask) const {
    *flag = _relation_flag;
    *mask = _relation_mask;
    return _relation_docids;
}

void DimensionDocManager::relation_ship_filt(
            uint32_t level_id,
            const DimensionDoc& doc,
            bool is_delete) {
    // 首先拿到doc相对fact_doc的过滤位
    for (size_t i = 0; i < _filters.size(); ++i) {
        const filter_relation_ship_t & ship = _filters[i];
        // 如果跟配置中的级联关系不匹配
        if (level_id != ship.level_id) {
            continue;
        }
        // 如果跟配置中的关系匹配上了，那么这个过滤位可能生效
        _relation_mask |= (1 << i);
        // 根据当前dimension doc的annotation取值，判断过滤状态
        if (is_delete) {
            // dimension doc被删除，则一定被过滤掉，不需要判断annotation取值
            _relation_flag |= (1 << i);
            // note: 这里可以break掉，因为doc都被删除了，当然没有判断
            //       的意义了，但是，似乎也就循环最多8次
            //       且删除操作对于一般的业务来讲不会特别多
            //       还是求出完整的mask以及flag吧
        } else {
            const Annotation * relation_anno = find_annotation_by_id(ship.relation_key, doc);
            if (relation_anno == NULL) {
                // WARNING:当缺少annotation的时候，默认做法是不过滤
                // 也许可以有一个开关配置，等需要的时候再说
                continue;
            }
            uint64_t status = static_cast<uint64_t>(relation_anno->number_value);
            // 当前doc的过滤位是否被过滤掉；
            if (ship.filted_values.find(status) != ship.filted_values.end()) {
                _relation_flag |= (1 << i);
            }
        }
    }
    UDEBUG("relation_mask[%u] relation_flag[%u]", _relation_mask, _relation_flag);
    if (_relation_mask == 0) {
        return;
    }

    // 只需要根据level+docid作为节点查到所有的fact_doc即可
    GOOGLE_CHECK_LT(level_id, _d2f_maps.size());
    GOOGLE_CHECK(_d2f_maps.at(level_id));
    d2f_map_t * d2f_map = _d2f_maps[level_id];
    d2f_map_t::iterator it = d2f_map->find(doc.get_doc_id());
    if (it == d2f_map->end()) {
        UDEBUG("not find relation_fact_docs [level:%u] [docid:%llu]",
                    level_id, doc.get_doc_id());
        return;
    }
    _relation_docids = it->second;
}

DimensionDoc * DimensionDocManager::add_dimension_doc(
        size_t id,
        const std::string& str,
        const das_inc_record_t& record) {
    reset_cascade_status();
    // cause this function is used by the framework itself
    // so need not to use the if/else check
    GOOGLE_DCHECK_LT(id, _dimensions.size());
    dimension_t & df = _dimensions[id];
    GOOGLE_DCHECK(df.factory);
    // 记录增量数据信息
    event_info_t event_info;
    event_info.type = INC_DATA;
    event_info.event_id = record.event_id;
    event_info.level_id = record.level_id;
    (df.factory)->set_event_info(event_info);
    DimensionDoc * doc = (df.factory)->produce(str);
    if (doc == NULL) {
        UTRACE("%s parse fail:%s", df.name.c_str(), str.c_str());
        return NULL;
    }
    // 对annotation进行排序
    sort(doc->annotations.begin(), doc->annotations.end());

    // 需要处理插入结果
    int ret = df.doc_map->set(doc->get_doc_id(), doc, 0);
    if (ret != bsl::HASH_INSERT_SEC) {
        // 插入失败的情况，进行析构
        UTRACE("add dimention %u docid:%llu failed[%d]",
                    id, doc->get_doc_id(), ret);
        // 首先通知DocFactory
        (df.factory)->on_delete_event(doc);
        // 最后，延迟删除DimensionDoc
        Singleton<DelayedEnv>::get()->add_callback(
                NewCallback(df.factory,
                        &DocFactory::destroy,
                        doc));
        return NULL;
    }
    // dimension doc插入成功
    UDEBUG("add_dimension_doc docid:%llu dimension_name:%s",
                doc->get_doc_id(),
                doc->get_dimension_name().c_str());
    // 判断级联过滤会影响哪些fact_doc
    if (_need_filter && get_fact_doc_level_id() != record.level_id) {
        relation_ship_filt(record.level_id, *doc, false);
    }
    return doc;
}

void DimensionDocManager::delete_dimension_doc(
        size_t id, 
        DocId docid,
        const das_inc_record_t& record) {
    reset_cascade_status();
    // cause this function is used by the framework itself
    // so need not to use the if/else check
    GOOGLE_DCHECK_LT(id, _dimensions.size());
    dimension_t &df = _dimensions[id];
    GOOGLE_DCHECK(df.factory);
    // 记录增量数据信息
    event_info_t event_info;
    event_info.type = INC_DATA;
    event_info.event_id = record.event_id;
    event_info.level_id = record.level_id;
    (df.factory)->set_event_info(event_info);
    DimensionDoc *res = NULL;
    if (bsl::HASH_EXIST != df.doc_map->get(docid, &res)) {
        UTRACE("can't find the to-be-deleted dimension doc,"
                 "level_id:%u docid:%llu", id, docid);
        return;
    }

    // note: 删除时，只有真正的das增量删除信号，才判断级联
    //       update中的删除行为，以及overwrite中的的删除行为
    //       避免无谓的性能损耗
    if (_need_filter && record.op_id == 1U && get_fact_doc_level_id() != record.level_id) {
        relation_ship_filt(record.level_id, *res, true);
    }

    // 可以删除，首先通知DocFactory
    df.factory->on_delete_event(res);
    // 然后清除doc map中的key-value对
    df.doc_map->erase(docid);
    // 最后，延迟删除DimensionDoc
    Singleton<DelayedEnv>::get()->add_callback(
            NewCallback(df.factory,
                    &DocFactory::destroy,
                    res));
    UTRACE("delete DimensionDoc level_id:%u docid:%llu", id, docid);
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
