/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file dimension_doc_base_builder.cc
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/26 16:27:55
 * @version $Revision$
 * @brief DimensionDoc基量构建类的实现
 *
 **/

#include "dimension_doc_base_builder.h"
#include "util/util.h"

DECLARE_bool(load_base_index_from_dump);
DECLARE_bool(dump_base_index);
namespace unise
{

DimensionDocBaseBuilder::DimensionDocBaseBuilder(const std::string &name,
        const DocFileInfo &doc_file_info,
        DimensionDocManager::dimension_t *dimension,
        boost::shared_ptr<DimensionDocManager> &dimension_doc_manager) :
    DocBaseBuilder(name, doc_file_info),
    _dimension(dimension),
    _dimension_doc_manager(dimension_doc_manager) {}

DimensionDocBaseBuilder::~DimensionDocBaseBuilder() {}

bool DimensionDocBaseBuilder::load_dimension_doc() {
    StopWatch build_stop_watch;
    UNOTICE("Begin to load dimension doc file %s", get_name().c_str());
    std::vector<DimensionDoc *> dimension_docs;
    if (!_dimension->factory->deserialize(&dimension_docs)) {
        UFATAL("Failed to get dimension from file");
        return false;
    }
    int cnt = 0;
    DimensionDoc* doc = NULL;
    for (size_t i = 0; i < dimension_docs.size(); i++) {
        doc = dimension_docs[i];
        if (doc) {
            _dimension->doc_map->set(doc->get_doc_id(), doc, 0);
        } else {
            UFATAL("Failed to get dimension[level:%s] [idx:%u] from vector",
                        get_name().c_str(), i);
            return false;
        }
        ++cnt;
    }
    UNOTICE("Finish load %d dimension doc file in %0.1f ms %s",
                cnt, build_stop_watch.read(), get_name().c_str());
    return true;
}

bool DimensionDocBaseBuilder::build()
{/*{{{*/
    if (FLAGS_load_base_index_from_dump) {
        return load_dimension_doc();
    }
    StopWatch build_stop_watch;
    int cnt = 0;
    UNOTICE("Begin to load dimension doc file %s:%s",
            get_file_name().c_str(), get_name().c_str());
    DimensionDoc* doc = NULL;
    std::vector<const DimensionDoc* > dimension_docs;
    bool has_next = true;
    while (true) {
        if (!get_next_doc(&doc, &has_next)) {
            UFATAL("Failed to get doc from file %s",
                    get_file_name().c_str());
            return false;
        }
        if (doc) {
            if (FLAGS_dump_base_index) {
                // 收集dimensionDoc  
                dimension_docs.push_back(doc);
            }
            _dimension->doc_map->set(doc->get_doc_id(), doc, 0);
            cnt++;
        }
        if (!has_next) {
            break;
        }
    }
    if (FLAGS_dump_base_index) {
        // 序列化 dimension_docs
        if (!_dimension->factory->serialize(dimension_docs)) {
            UFATAL("Failed to serialize DimensionDoc from file");
            return false;
        }
    }
    UNOTICE("Finish loading dimension doc file %s:%s in %0.1f ms, %d docs added",
            get_file_name().c_str(), get_name().c_str(), build_stop_watch.read(), cnt);
    return true;
}/*}}}*/

}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
