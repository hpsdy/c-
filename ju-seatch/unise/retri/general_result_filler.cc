// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "retri/general_result_filler.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "unise/matched_doc.h"
#include "unise/dimension_doc.h"
#include "unise/base.h"
#include "unise/util.h"

namespace unise
{

GeneralResultFiller::GeneralResultFiller()
{
    _filler_items.resize(ANNOTATION_ID_MAX + 1);
}

bool GeneralResultFiller::init(const comcfg::ConfigUnit & conf)
{
    try {
        string filler_file_path(conf["GeneralFillerConfig"].to_cstr());
        int fd = open(filler_file_path.c_str(), O_RDONLY);
        if (fd == -1) {
          UFATAL("GeneralFillerConfig File not exist:%s", filler_file_path.c_str());
          return false;
        }
        google::protobuf::io::FileInputStream ins(fd);
        bool init_succ = google::protobuf::TextFormat::Parse(&ins, &_filler_config);
        ins.Close();
        close(fd);

        if (!init_succ) {
          UFATAL("GeneralFillerConfig illegal:%s", filler_file_path.c_str());
          return false;
        }
    } catch (comcfg::ConfigException& e) {
        // 如果没有配置文件，那么，采用空配置
        UNOTICE("illegal Configure for GeneralResultFiller:%s, use empty config", e.what());
    }
    for (int i = 0; i < _filler_config.annotation_items_size(); ++i) {
        const AnnotationFillerItem * item = &(_filler_config.annotation_items(i));
        if (item->annotation_id() > ANNOTATION_ID_MAX) {
            UFATAL("annotation_id [%u] bigger than [%u]",
                  item->annotation_id(),
                  static_cast<uint32_t>(ANNOTATION_ID_MAX));
            return false;
        }
        // 不去重，采用最后覆盖的
        _filler_items.at(item->annotation_id()) = item;
    }
    return true;
}

void GeneralResultFiller::fill_search_result(MatchedDoc * doc,
        SearchResult* search_result) const
{
    const FactDoc & fact_doc = doc->get_fact_doc();
    GOOGLE_CHECK_EQ(fact_doc.get_doc_id(), doc->get_doc_id());
    for (size_t i = 0; i < fact_doc.annotations.size(); ++i) {
      const Annotation & anno = fact_doc.annotations.at(i);
      const AnnotationFillerItem * item = _filler_items.at(anno.id);
      if (item == NULL) {
        continue;
      }

      Snippet * snippet = search_result->add_snippets();
      snippet->set_key(item->snippet_key());
      if (item->type() == TEXT) {
        snippet->set_value(anno.text_value);
      } else if (item->type() == NUMBER) {
        snippet->set_value(Int64ToString(anno.number_value));
      } else {
        UWARNING("[\tlvl=FOLLOW\t] not support annotation [%u] type [%d]",
              static_cast<uint32_t>(anno.id), item->type());
        snippet->set_value("NULL");
      }
    }
}

REGISTER_RESULT_FILLER(GeneralResultFiller);
REGISTER_RESULT_FILLER(DefaultResultFiller);
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
