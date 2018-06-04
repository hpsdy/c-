// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_DAS_INC_BUILDER_H
#define  INDEX_DAS_INC_BUILDER_H

#include <string>
#include <boost/scoped_ptr.hpp>
#include "index/doc_builder.h"

namespace comcfg
{
class ConfigUnit;
}

namespace unise
{
class RepositoryManager;
class DimensionDocManager;
struct das_inc_record_t;


// load the doc which is a das line
// build 4 data structure:
//   build the dimension doc
//   build the forward index
//   build the doc info
//   build the inverted index
class DasIncBuilder
{
public:
    explicit DasIncBuilder(RepositoryManager * repository_manager);
    ~DasIncBuilder() {}
    // the conf is the real engine unit's conf
    bool init(const comcfg::ConfigUnit& conf);
    void process_one_line(const std::string & line);
    void process_one_record(const das_inc_record_t& record);

private:
    bool format_input(const std::string& line, das_inc_record_t * record);
    void add_record(const das_inc_record_t& record);
    void delete_record(const das_inc_record_t& record);
    /*
     * @brief 进行级联过滤
     * @note 只能在delete_dimension_doc或add_dimension_doc之后运行
     *       运行时刻不对，会把上一次delete或add的影响重复执行一次
     */
    uint32_t cascade_filt();

private:
    RepositoryManager * _repository_manager;
    DimensionDocManager * _dimension_doc_manager;
    boost::scoped_ptr<DocBuilder> _fact_doc_builder;

    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(DasIncBuilder);
};

}

#endif  // INDEX_DAS_INC_BUILDER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
