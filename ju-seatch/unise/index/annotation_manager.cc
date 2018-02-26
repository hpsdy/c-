// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/annotation_manager.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <gflags/gflags.h>
#include <uln_sign_murmur.h>
#include <cstddef>
#include "util/util.h"
#include "unise/base.h"

using std::string;
using std::map;

namespace unise
{

bool AnnotationManager::init(const string& path)
{
    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1) {
        UFATAL("AnnotationSchemaConfig File not exist:%s", path.c_str());
        return false;
    }
    google::protobuf::io::FileInputStream ins(fd);
    bool init_succ = google::protobuf::TextFormat::Parse(&ins, &_schema_config);
    ins.Close();
    close(fd);

    if (!init_succ) {
        UFATAL("AnnotationSchemaConfig illegal:%s", path.c_str());
        return false;
    }
    _schema_list.resize(ANNOTATION_ID_MAX + 1);
    for (size_t i = 0; i <= ANNOTATION_ID_MAX; i++) {
        _schema_list.at(i) = NULL;
    }
    // 检查并初始化
    for (int i = 0; i < _schema_config.annotation_schemas_size(); ++i) {
        // 检查，并进行兼容性修复
        AnnotationSchema * schema = _schema_config.mutable_annotation_schemas(i);
        // 检查schema的annotation的配置
        if (schema->annotation_name() == "") {
            UFATAL("Annotation name should not be empty");
            return false;
        }

        // 如果类型为NUMBER类型，
        if (schema->annotation_type() == NUMBER) {
            // section name需要为空
            if (schema->section_name() != "") {
                UFATAL("Annotation[%s] NUMBER type should not has section name",
                            schema->annotation_name().c_str());
                return false;
            }
            if (!schema->has_number_schema()) {
                UFATAL("Annotation[%s] NUMBER miss number_schema",
                            schema->annotation_name().c_str());
                return false;
            }
            if (schema->number_schema().min() < 0) {
                schema->mutable_number_schema()->set_min(0);
                UWARNING("Annotation[%s] NUMBER min[%d] be changed to 0 by force",
                            schema->annotation_name().c_str());
            }
            if (schema->number_schema().accuracy() < 1 ||
                schema->number_schema().accuracy() > 8) {
                schema->mutable_number_schema()->set_accuracy(4);
                UWARNING("Annotation[%s] NUMBER accuracy[%d] be changed to 4 by force",
                            schema->annotation_name().c_str());
            }
        }
        // 检查schema annotation id的范围是否超过配置值
        if (schema->id() > ANNOTATION_ID_MAX) {
            UFATAL("Annotation[%s] id[%u] bigger than %u",
                        schema->annotation_name().c_str(),
                        static_cast<uint32_t>(schema->id()),
                        ANNOTATION_ID_MAX);
            return false;
        }
        // 检查schema section id的范围是否超过配置值
        if (schema->section_id() > SECTION_ID_MAX) {
            UFATAL("Annotation[%s] section id[%u] bigger than %u",
                        schema->annotation_name().c_str(),
                        static_cast<uint32_t>(schema->section_id()),
                        SECTION_ID_MAX);
            return false;
        }
        // 这里的下标操作是安全的
        GOOGLE_DCHECK_LE(schema->id(), ANNOTATION_ID_MAX);
        if (_schema_list.at(schema->id()) != NULL) {
            UFATAL("AnnotationId [%u] exist already",
                        static_cast<uint32_t>(schema->id()));
            return false;
        }
        _schema_list.at(schema->id()) = schema;
        if (_schema_map.find(schema->annotation_name()) != _schema_map.end()) {
            UFATAL("AnnotationName [%s] exist already",
                        schema->annotation_name().c_str());
            return false;
        }
        _schema_map.insert(std::make_pair(schema->annotation_name(), schema));
    }
    return true;
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
