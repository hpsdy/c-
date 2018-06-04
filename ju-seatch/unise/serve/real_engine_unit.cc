// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/real_engine_unit.h"
#include "gflags/gflags.h"
#include "unise/factory.h"
#include "unise/base.h"
#include "index/base_builder.h"
#include "retri/result_retrievor.h"

DEFINE_bool(start_serve_after_inc_finished, true,
      "if true, won't serve until the inc finished loading");

namespace unise {

RealEngineUnit::RealEngineUnit() :
        _name("NoName"),
        _type("NoType"),
        _retrievor_number(0) {}

RealEngineUnit::~RealEngineUnit() {
    // 首先保证没有检索资源了，不会调用检索逻辑
    ResultRetrievor * retrievor = NULL;
    if (_result_retrievor_queue.get()) {
        while (_result_retrievor_queue->pop(retrievor)) {
            delete retrievor;
        }
    }
    // 停止das loader，这样子，就不会再有新的回调发生
    if (_das_loader.get()) {
        _das_loader->stop();
        _das_loader->join();
    }
}

bool RealEngineUnit::init(const comcfg::ConfigUnit& conf) {
    try {
        _name.assign(conf["EngineUnitName"].to_cstr());
        _type.assign(conf["EngineUnitType"].to_cstr());
        _retrievor_number = conf["RetrievorNumber"].to_int32();
        _info_file_name = conf["InfoFileName"].to_cstr();
        _inc_doc_path = conf["IncDocPath"].to_cstr();
        _inc_doc_name_prefix = conf["IncDocNamePrefix"].to_cstr();
        UNOTICE("InfoFileName:%s IncDocPath:%s IncDocNamePrefix:%s",
                _info_file_name.c_str(),
                _inc_doc_path.c_str(),
                _inc_doc_name_prefix.c_str());
    } catch (comcfg::ConfigException e) {
        UFATAL("Configure for %s illegal:%s", get_name().c_str(), e.what());
        return false;
    }
    // init the BaseBuilder and build the base
    BaseBuilder base_builder;
    if (false == base_builder.init(conf)) {
        UFATAL("base builder init fail");
        return false;
    }
    if (false == base_builder.build_concurrency()) {
        UFATAL("build base fail");
        // TODO(wangguangyuan) : base failed condition should be accepted-able?
        return false;
    }
    _repository_manager = base_builder.get_repository_manager();
    _dimension_doc_manager = base_builder.get_dimension_doc_manager();
    _result_retrievor_queue.reset(new RetrievorQueue(_retrievor_number));
    for (int32_t i = 0; i < _retrievor_number; ++i) {
        ResultRetrievor * retrievor = new ResultRetrievor(*_repository_manager.get());
        if (false == retrievor->init(conf)) {
            delete retrievor;
            UFATAL("Init retrievor failed");
            return false;
        }
        if (_result_retrievor_queue->push(retrievor)) {
            UNOTICE("Generate the %dth ResultRetrievor for %s",
                    i + 1, _name.c_str());
        } else {
            delete retrievor;
            UFATAL("push ResultRetrievor To queue failed");
            return false;
        }
    }
    GetMemInfo mem_info;
    mem_info.get_proc_mem_info();
    UNOTICE("After building base, proc_virt=%llu kb proc_res=%llu kb",mem_info._proc_virt, mem_info._proc_res);
    // finaly init the DasIncBuilder and DasLoader
    _das_inc_builder.reset(new DasIncBuilder(_repository_manager.get()));
    if (!_das_inc_builder->init(conf)) {
        UFATAL("init das inc builder failed");
        return false;
    }
    boost::shared_ptr<DasCbClosure> das_cb(NewPermanentDasCallback(
            _das_inc_builder.get(),
            &DasIncBuilder::process_one_line));
    _das_callbacks.push_back(das_cb);
    // finally start the das_loader
    _das_loader.reset(new DasLoader(_info_file_name,
            _inc_doc_path,
            _inc_doc_name_prefix,
            _das_callbacks));
    _das_loader->start();
    return true;
}

bool RealEngineUnit::is_initing() const {
    if (FLAGS_start_serve_after_inc_finished) {
        if (!_das_loader->inited() && _das_loader->is_stop()) {
            return false;
        } else if (!_das_loader->inited() && !_das_loader->is_stop()) {
            return true;
        }
    }
    return false;
}

bool RealEngineUnit::inited() const {
    if (FLAGS_start_serve_after_inc_finished) {
        return _das_loader->inited();
    }
    return true;
}

bool RealEngineUnit::init_for_search() {
    return true;
}

void RealEngineUnit::search(GeneralSearchRequest* request,
                            GeneralSearchResponse* response) {
    // get the retrievor first
    ResultRetrievor * retrievor;
    if (false == _result_retrievor_queue->pop(retrievor)) {
        UWARNING("[\tlvl=FOLLOW\t] pop result retrievor failed");
        return;
    }
    // retrieve
    GOOGLE_DCHECK(retrievor);
    retrievor->retrieve(*request, response);
    response->set_name(get_name());
    response->set_type(get_type());
    // return the retrievor
    if (false == _result_retrievor_queue->push(retrievor)) {
        UWARNING("[\tlvl=FOLLOW\t] after search, push retrievor failed");
    }
}


const ForwardIndex * RealEngineUnit::get_forward_index(DocId docid) const {
    const doc_info_t * doc_info = _repository_manager->get_doc_info(docid);
    if (doc_info == NULL) {
        return NULL;
    }
    return doc_info->forward_index;
}

REGISTER_ENGINEUNIT(RealEngineUnit);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
