// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  SERVE_REAL_ENGINE_UNIT_H_
#define  SERVE_REAL_ENGINE_UNIT_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/lockfree/queue.hpp>
#include "Configure.h"
#include "unise/engine_unit.h"
#include "unise/general_servlet.pb.h"
#include "index/repository_manager.h"
#include "index/dimension_doc_manager.h"
#include "index/das_inc_builder.h"
#include "util/das_loader.h"

namespace unise {
class ResultRetrievor;

class RealEngineUnit : public EngineUnit {
public:
    RealEngineUnit();
    virtual ~RealEngineUnit();

    // conf is-a EngineUnit
    virtual bool init(const comcfg::ConfigUnit& conf);
    virtual const std::string& get_name() const {
        return _name;
    }
    virtual const std::string& get_type() const {
        return _type;
    }
    /**
     * @brief 是否已经启动成功
     */
    virtual bool inited() const;

    /**
     * @brief 是否还在启动中
     * @note 增量是否加载完毕对服务的影响，请参见
     *       FLAGS_start_serve_after_inc_finished
     */
    virtual bool is_initing() const;

    // TODO(wangguangyuan) : add parameters for InitForSearch()
    virtual bool init_for_search();
    virtual void search(GeneralSearchRequest* request, GeneralSearchResponse* response);
    virtual const ForwardIndex * get_forward_index(DocId docid) const;

private:
    // private members for repository, retrieve and indexing
    std::string _name;
    std::string _type;
    int32_t _retrievor_number;
    std::string _info_file_name;            /**< das 的base.n文件的全路径 */
    std::string _inc_doc_path;              /**< 增量文件的路径       */
    std::string _inc_doc_name_prefix;       /**< 增量文件名字的前缀       */

    typedef boost::lockfree::queue<ResultRetrievor*> RetrievorQueue;
    boost::scoped_ptr<RetrievorQueue> _result_retrievor_queue;
    boost::shared_ptr<RepositoryManager> _repository_manager;
    boost::shared_ptr<DimensionDocManager> _dimension_doc_manager;
    boost::scoped_ptr<DasIncBuilder> _das_inc_builder;
    boost::scoped_ptr<DasLoader> _das_loader;
    std::vector<boost::shared_ptr<DasCbClosure> > _das_callbacks;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RealEngineUnit);
};
}

#endif  // SERVE_REAL_ENGINE_UNIT_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
