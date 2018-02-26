// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "unise/unise_plugin.h"
#include <Configure.h>
#include "unise/dimension_doc.h"
#include "unise/fact_doc.h"
#include "index/dimension_doc_manager.h"
#include "index/repository_manager.h"
#include "index/annotation_manager.h"
#include "unise/base.h"

namespace unise
{
bool UnisePlugin::basic_init(const RepositoryManager * rm, const comcfg::ConfigUnit& conf)
{
    _repository_manager = rm;
    _dimension_doc_manager = &(rm->get_dimension_doc_manager());
    _annotation_manager = &(rm->get_annotation_manager());
    return init(conf);
}

const DimensionDoc * UnisePlugin::get_dimension_doc(
        const std::string& name,
        DocId docid) const
{
    GOOGLE_DCHECK(_dimension_doc_manager);
    return _dimension_doc_manager->get_dimension_doc(name, docid);
}

const DimensionDoc * UnisePlugin::get_dimension_doc(
        size_t level_id,
        DocId docid) const
{
    GOOGLE_DCHECK(_dimension_doc_manager);
    return _dimension_doc_manager->get_dimension_doc(level_id, docid);
}


const std::string & UnisePlugin::get_fact_doc_dimension_name() const
{
    GOOGLE_DCHECK(_dimension_doc_manager);
    return _dimension_doc_manager->get_fact_doc_dimension_name();
}

size_t UnisePlugin::get_fact_doc_level_id() const
{
    GOOGLE_DCHECK(_dimension_doc_manager);
    return _dimension_doc_manager->get_fact_doc_level_id();
}


const FactDoc * UnisePlugin::get_fact_doc(DocId docid) const
{
    return _dimension_doc_manager->get_fact_doc(docid);
}

const AnnotationSchema * UnisePlugin::get_annotation_schema(AnnotationId id) const
{
    return _annotation_manager->get_annotation_schema(id);
}

const AnnotationSchema * UnisePlugin::get_annotation_schema(const std::string& name) const
{
    return _annotation_manager->get_annotation_schema(name);
}

const std::vector<const AnnotationSchema*> & UnisePlugin::get_annotation_schemas() const
{
    return _annotation_manager->get_annotation_schemas();
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
