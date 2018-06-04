/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file base_builder.cc
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/27 14:18:17
 * @version $Revision$
 * @brief Doc的基量构建类的实现
 *
 **/

#include "index/base_builder.h"
#include "unise/base.h"
#include "unise/util.h"
#include "unise/fact_doc.h"
#include "unise/dimension_doc.h"
#include "index/annotation_manager.h"
#include "index/forward_index.h"
#include "index/fix_time_array.h"
#include "index/token_list.h"
#include "index/dimension_doc_base_builder.h"
#include "index/fact_doc_base_builder.h"
#include <bsl/exception/bsl_exception.h>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <algorithm>
#include <exception>

DECLARE_bool(load_base_index_from_dump);

namespace unise
{

bool BaseBuilder::init(const comcfg::ConfigUnit& conf)
{/*{{{*/
    try {
        //初始化DimensionDocManager
        dimension_doc_manager_.reset(new DimensionDocManager());
        if (false == dimension_doc_manager_->init(conf["DimensionDoc"])) {
            UFATAL("Failed to init dimension doc manager");
            return false;
        }
        //初始化RepositoryManager
        repository_manager_.reset(new RepositoryManager(dimension_doc_manager_.get()));
        if (false == repository_manager_->init(conf["AnnotationSchemaConfig"].to_cstr())) {
            UFATAL("Failed to init repository manager");
            return false;
        }
        //获取DimensionDoc配置信息
        dimension_doc_configs_ = get_dimension_doc_configs(conf["DimensionDoc"]);
        for (size_t i = 0; i < dimension_doc_configs_.size(); ++i) {
            dimension_doc_ids_.insert(dimension_doc_configs_[i].id);
        }
        UDEBUG("Totally %u DimensionDoc to be built", dimension_doc_configs_.size());
        //获取FactDoc名字和Id
        fact_doc_name_ = dimension_doc_manager_->get_fact_doc_dimension_name();
        fact_doc_id_ = dimension_doc_manager_->get_fact_doc_level_id();
        UDEBUG("Fact doc id is %u", fact_doc_id_);
        //获取基量文件名
        base_doc_file_.assign(std::string(conf["BaseDocPath"].to_cstr()) +
                "/" + std::string(conf["BaseDocName"].to_cstr()));
        UDEBUG("Base file is %s", base_doc_file_.c_str());
        // 获取dump正排文件全路径
        if (conf["DumpBaseForwardIndexPath"].selfType() != comcfg::CONFIG_ERROR_TYPE) {
            _dump_base_forward_index_path = conf["DumpBaseForwardIndexPath"].to_cstr();
        } else {
            _dump_base_forward_index_path = base_doc_file_ + ".forward_index_dump";
        }
        UNOTICE("dump base forward_index path:%s", _dump_base_forward_index_path.c_str());
        // 获取dump倒排文件全路径
        if (conf["DumpBaseInvertedIndexPath"].selfType() != comcfg::CONFIG_ERROR_TYPE) {
            _dump_base_inverted_index_path = conf["DumpBaseInvertedIndexPath"].to_cstr();
        } else {
            _dump_base_inverted_index_path = base_doc_file_ + ".inverted_index_dump";
        }
        UNOTICE("dump base inverted_index path:%s", _dump_base_inverted_index_path.c_str());
        // 获取dump级联数据文件全路径
        if (conf["DumpBaseD2fMapsPath"].selfType() != comcfg::CONFIG_ERROR_TYPE) {
            _dump_base_d2f_maps_path = conf["DumpBaseD2fMapsPath"].to_cstr();
        } else {
            _dump_base_d2f_maps_path = base_doc_file_ + ".d2f_maps_dump";
        }
        UNOTICE("dump base d2f_maps_path:%s", _dump_base_d2f_maps_path.c_str());
        UNOTICE("init BaseBuilder done");
    } catch (comcfg::ConfigException &e) {
        UFATAL("Failed to init BaseBuilder, err_msg:%s", e.what());
        return false;
    } catch (std::exception &e) {
        UFATAL("Failed to init BaseBuilder, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to init BaseBuilder, unknown exception");
        return false;
    }
    return true;
}/*}}}*/

bool BaseBuilder::get_dimension_doc_id(const std::string &line,
        uint32_t *doc_id)
{/*{{{*/
    return 1 == sscanf(line.c_str(), "%u", doc_id);
}/*}}}*/

bool BaseBuilder::load_data_from_disk() {
    bool final_status = true;
    try {
        //获取DimensionDoc的相关信息（工厂类指针等）
        std::vector<DimensionDocManager::dimension_t> &dimensions =
            dimension_doc_manager_->_dimensions;
        StopWatch build_stop_watch;
        DocFileInfo doc_file_info;
        doc_file_info.file_name = base_doc_file_;
        doc_file_info.dump_forward_index_path = _dump_base_forward_index_path;
        doc_file_info.dump_inverted_index_path = _dump_base_inverted_index_path;
        doc_file_info.dump_d2f_maps_path = _dump_base_d2f_maps_path;
        UNOTICE("Begin to load base data from disk");
        
        for (std::map<std::string, size_t>::iterator it =
                    dimension_doc_manager_->_family_map.begin();
                    it != dimension_doc_manager_->_family_map.end();
                    ++it) {
            start_builder(it->second, doc_file_info, &dimensions[it->second]);
        }

        //join各个builder线程
        size_t join_num = 0;
        for (size_t i = 0; i < builders_.size(); ++i) {
            if (0 != builders_[i]->join()) {
                UFATAL("Failed to join builder thread, %s",
                        (builders_[i]->get_name()).c_str());
            } else {
                join_num++;
                if (!builders_[i]->status()) {
                    final_status = false;
                }
            }
        }
        if (join_num != builders_.size()) {
            return false;
        }
        UNOTICE("Finish base build in %0.1f ms", build_stop_watch.read());
    } catch (std::exception &e) {
        UFATAL("Failed to base build, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to base build, unknown exception");
        return false;
    }
    return final_status;
}

bool BaseBuilder::build_concurrency()
{/*{{{*/
    if (FLAGS_load_base_index_from_dump) {
        return load_data_from_disk();
    }
    bool final_status = true;
    try {
        //获取DimensionDoc的相关信息（工厂类指针等）
        std::vector<DimensionDocManager::dimension_t> &dimensions =
            dimension_doc_manager_->_dimensions;
        StopWatch build_stop_watch;
        uint32_t last_doc_id = 0xffffffff;
        ssize_t start_offset = 0;
        ssize_t end_offset = 0;
        std::string line;
        // 保存FactDoc在文件中的信息，只能有一种FactDoc
        DocFileInfo fact_doc_file_info;
        DocFileInfo doc_file_info;
        doc_file_info.file_name = base_doc_file_;
        doc_file_info.dump_forward_index_path = _dump_base_forward_index_path;
        doc_file_info.dump_inverted_index_path = _dump_base_inverted_index_path;
        doc_file_info.dump_d2f_maps_path = _dump_base_d2f_maps_path;
        UNOTICE("Begin to base build");
        //读取基量文件，确定每个DimensionDoc数据块的offset和len
        // TODO(wangguangyuan) : 这里不需要真正从头到尾一行一行
        // 得读文件，可以使用文件偏移，二分方法来查找每类DimensionDoc
        // 的起止位置
        std::ifstream in(base_doc_file_.c_str(), std::ios::in);
        if (in.fail()) {
            UFATAL("Failed to read base file %s", base_doc_file_.c_str());
            in.close();
            return false;
        }
        while (getline(in, line)) {
            //获取DimensionDocId，若Id不同于上一行Id，则旧块结束，启动builder线程，
            //记录新块offset
            uint32_t curr_doc_id = 0;
            if (get_dimension_doc_id(line, &curr_doc_id) &&
                    curr_doc_id != last_doc_id) {
                if (end_offset > start_offset &&
                        dimension_doc_ids_.end() !=
                        dimension_doc_ids_.find(last_doc_id)) {
                    doc_file_info.offset = start_offset;
                    doc_file_info.len = end_offset - start_offset;
                    if (last_doc_id != fact_doc_id_) {
                        start_builder(last_doc_id, doc_file_info,
                                &dimensions[last_doc_id]);
                    } else {
                        fact_doc_file_info = doc_file_info;
                    }
                }
                last_doc_id = curr_doc_id;
                start_offset = end_offset;
            }
            end_offset = in.tellg();
        }
        if (end_offset > start_offset &&
                dimension_doc_ids_.end() !=
                dimension_doc_ids_.find(last_doc_id)) {
            doc_file_info.offset = start_offset;
            doc_file_info.len = end_offset - start_offset;
            if (last_doc_id != fact_doc_id_) {
                start_builder(last_doc_id, doc_file_info,
                        &dimensions[last_doc_id]);
            } else {
                fact_doc_file_info = doc_file_info;
            }
        }
        in.close();
        //join各个builder线程
        size_t join_num = 0;

        for (size_t i = 0; i < builders_.size(); ++i) {
            if (0 != builders_[i]->join()) {
                UFATAL("Failed to join builder thread, %s",
                        (builders_[i]->get_name()).c_str());
            } else {
                join_num++;
                if (!builders_[i]->status()) {
                    final_status = false;
                }
            }
        }
        if (join_num != builders_.size()) {
            return false;
        }
        UNOTICE("Begin to build factDocs");
        builders_.clear();
        start_builder(fact_doc_id_, fact_doc_file_info, &dimensions[fact_doc_id_]);
        if (builders_.empty()) {
            UFATAL("Failed to start factDoc builder thread");
            return false;
        }
        if (0 != builders_[0]->join()) {
            UFATAL("Failed to join builder thread, %s",
                    (builders_[0]->get_name()).c_str());
            return false;
        }
        UNOTICE("Finish base build in %0.1f ms", build_stop_watch.read());
    } catch (std::exception &e) {
        UFATAL("Failed to base build, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to base build, unknown exception");
        return false;
    }
    return final_status;
}/*}}}*/

bool BaseBuilder::start_builder(uint32_t doc_id,
        const DocFileInfo &doc_file_info,
        DimensionDocManager::dimension_t *dimension)
{/*{{{*/
    try {
        boost::shared_ptr<DocBaseBuilder> builder;
        std::string thread_name = boost::lexical_cast<string>(doc_id) +
                                  "_DOC_BASE_BUILDER_THREAD";
        if (doc_id == fact_doc_id_) {
            builder.reset(
                    new FactDocBaseBuilder(thread_name,
                            doc_file_info,
                            dimension,
                            dimension_doc_manager_,
                            repository_manager_)
                                                    );
        } else {
            builder.reset(
                    new DimensionDocBaseBuilder(thread_name,
                            doc_file_info,
                            dimension,
                            dimension_doc_manager_)
                                                    );
        }
        if (0 != builder->start()) {
            UFATAL("Failed to start builder thread, %s",
                    (builder->get_name()).c_str());
            return false;
        }
        builders_.push_back(builder);
    } catch (std::exception &e) {
        UFATAL("Failed to start builder, docid:%u, err_msg:%s",
                doc_id, e.what());
        return false;
    }
    return true;
}/*}}}*/

}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
