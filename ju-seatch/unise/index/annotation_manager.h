// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_ANNOTATION_MANAGER_H
#define  INDEX_ANNOTATION_MANAGER_H

#include <string>
#include <map>
#include "unise/base.h"
#include "unise/annotation_schema.pb.h"
#include "util/hash_tables.h"

namespace unise
{
class AnnotationManager
{
public:
    AnnotationManager() {}
    ~AnnotationManager() {}
    /**
     * @brief path为AnnotationSchemaConfig的取值
     */
    bool init(const std::string& path);
    const AnnotationSchema * get_annotation_schema(const std::string & name) const
    {
        SchemaMap::const_iterator it = _schema_map.find(name);
        if (it == _schema_map.end()) {
            return NULL;
        } else {
            return it->second;
        }
    }

    const AnnotationSchema * get_annotation_schema(AnnotationId id) const
    {
        return _schema_list.at(id);
    }

    /**
     * @brief 获取所有的schema配置
     */
    const std::vector<const AnnotationSchema*> & get_annotation_schemas() const
    {
        return _schema_list;
    }

private:
    AnnotationSchemaConfig _schema_config;
    typedef __gnu_cxx::hash_map<std::string, const AnnotationSchema*> SchemaMap;
    SchemaMap _schema_map;
    std::vector<const AnnotationSchema*> _schema_list;
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(AnnotationManager);
};

}

#endif  // ANNOTATION_MANAGER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
