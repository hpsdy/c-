// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "article_doc_factory.h"
#include <vector>
#include <string>
#include "unise/dimension_doc.h"
#include "unise/state_monitor.h"
#include "article_doc.h"

namespace unise {
DimensionDoc * ArticleDocFactory::produce(const std::string & line) {
    ArticleDoc * doc = new ArticleDoc();
    // 解析数据文件，建立相应索引
    if (!doc->init(line)) {
        delete doc;
        return NULL;
    }
    {
        Annotation anno;
        anno.id = 0;
        anno.number_value = doc->_resource_id;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 1;
        anno.number_value = doc->_area_id;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 2;
        anno.number_value = doc->_city_id;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 3;
        anno.text_value = doc->_title;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 4;
        anno.text_value = doc->_source;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 5;
        anno.text_value = doc->_image_url;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 6;
        anno.text_value = doc->_content;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 7;
        anno.text_value = doc->_na_redirect_url;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 8;
        anno.text_value = doc->_wap_redirect_url;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 9;
        anno.number_value = doc->_score;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 10;
        anno.number_value = doc->_publish_time;
        doc->annotations.push_back(anno);
    }

    {
        Annotation anno;
        anno.id = 11;
        anno.text_value = doc->_category_id;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 12;
        anno.number_value = doc->_column_id;
        doc->annotations.push_back(anno);
    }
    {
        Annotation anno;
        anno.id = 13;
        anno.text_value = doc->_tags;
        doc->annotations.push_back(anno);
    }

    ++_produce_num;
    Singleton<StateMonitor>::get()->add_number_state_message("article_doc_produce", 1);
    Singleton<StateMonitor>::get()->add_text_state_message("article_doc_num",
          Uint64ToString(_produce_num));
    return doc;
}

void ArticleDocFactory::on_delete_event(DimensionDoc * doc) {
    --_produce_num;
    Singleton<StateMonitor>::get()->add_text_state_message("article_doc_num",
          Uint64ToString(_produce_num));
    Singleton<StateMonitor>::get()->add_number_state_message("article_doc_destroy", 1);

    // get base or inc data event info
    const event_info_t* record = get_event_info();
    UTRACE("[%s] event_id[%u] level_id:%u",
        record->type == BASE_DATA ? "BASE_DATA" : "INC_DATA",
        record->event_id,
        record->level_id);
}

void ArticleDocFactory::destroy(DimensionDoc * doc) {
    delete dynamic_cast<ArticleDoc*>(doc);
}

bool ArticleDocFactory::serialize(const std::vector<const DimensionDoc *> & dimension_docs) {
  return unise::serialize<ArticleDoc>(dimension_docs, _dump_path);
}

bool ArticleDocFactory::deserialize(std::vector<DimensionDoc *> * dimension_docs) {
  return unise::deserialize<ArticleDoc>(dimension_docs, _dump_path);
}

REGISTER_DOC_FACTORY(ArticleDocFactory);
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
