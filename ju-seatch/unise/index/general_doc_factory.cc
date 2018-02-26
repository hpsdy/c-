// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/general_doc_factory.h"
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "unise/dimension_doc.h"
#include "index/general_fact_doc.h"
#include "util/util.h"
#include "unise/base.h"

using namespace std;

namespace unise
{

bool GeneralDocFactory::init(const comcfg::ConfigUnit& conf)
{
    try {
        string format_file_path(conf["FormatFile"].to_cstr());
        int fd = open(format_file_path.c_str(), O_RDONLY);
        if (fd == -1) {
          UFATAL("FormatFile not exist:%s", format_file_path.c_str());
          return false;
        }
        google::protobuf::io::FileInputStream ins(fd);
        bool init_succ = google::protobuf::TextFormat::Parse(&ins, &_format_config);
        ins.Close();
        close(fd);

        if (!init_succ) {
          UFATAL("FormatFile illegal:%s", format_file_path.c_str());
          return false;
        }
    } catch (comcfg::ConfigException& e) {
        UFATAL("illegal Configure for ClusterHandler:%s", e.what());
        return false;
    }
    return true;
}

DimensionDoc * GeneralDocFactory::produce(const std::string & line)
{
  GeneralFactDoc * doc = new GeneralFactDoc();

  std::vector<std::string> terms;
  string_split(line, "\t", &terms);
  for (size_t i = 0; i < terms.size(); ++i) {
    string_trim(&terms.at(i), " \t");
  }
  bool init_succ = false;
  do {
    // set the basic terms
    if (terms.size() < 2U) {
      break;
    }
    if (!StringToUint64(terms.at(0), &doc->docid)) {
      break;
    }
    if (!StringToInt(terms.at(1), &doc->score)) {
      break;
    }

    // then set the annotation
    for (int i = 0; i < _format_config.index_field_formats_size(); ++i) {
      const IndexFieldFormat & index_field_format = _format_config.index_field_formats(i);
      if (index_field_format.index() < terms.size()) {
        generate_annotations_from_field(terms.at(index_field_format.index()),
              index_field_format,
              &(doc->annotations));
      }
    }

    init_succ = true;
  } while (0);

  if (init_succ) {
    return doc;
  } else {
    delete doc;
    return NULL;
  }
}

void GeneralDocFactory::destroy(DimensionDoc * doc)
{
    delete down_cast<GeneralFactDoc*>(doc);
}


void GeneralDocFactory::on_delete_event(DimensionDoc * doc)
{
    UTRACE("delete dimension_doc[%s] docid[%llu]", doc->get_dimension_name().c_str(),
          doc->get_doc_id());
}

REGISTER_DOC_FACTORY(GeneralDocFactory);
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
