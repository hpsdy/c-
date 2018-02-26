// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_ENGINE_UNIT_H_
#define  UNISE_ENGINE_UNIT_H_

#include <string>
#include "unise/factory.h"
// TODO(wangguangyuan):mv forward_index.h to unise
#include "index/forward_index.h"

namespace comcfg {
class ConfigUnit;
}

namespace unise {
class GeneralSearchRequest;
class GeneralSearchResponse;

/**
 * @brief EngineUnit是一个引擎单元，内部有一种类别的FactDoc
 *        SearchEngine的检索逻辑，是对EngineUnit的Search函数的
 *        调用
 */
class EngineUnit {
public:
    EngineUnit() {}
    virtual ~EngineUnit() {}

    /**
     * @breaf 根据配置文件，初始化
     *
     * @param [in] : const ConfigUnit&, 是配置文件中的EngineUnit配置单元
     * @param [out] : none
     * @return bool
     * @retval true 初始化成功；否则，服务退出
     * @see
     * @note 
    **/
    virtual bool init(const comcfg::ConfigUnit&) = 0;

    /**
     * @breaf 获取当前EngineUnit的名字
     *
     * @param [in] : none
     * @param [out] : none
     * @return const std::string&
     * @retval 名字的引用
     * @see
     * @note 这里的名字是配置文件中[EngineUnit]["EngineUnitName"]的取值
    **/
    virtual const std::string& get_name() const = 0;

    /**
     * @breaf 获取当前EngineUnit的类型，就是类名
     *
     * @param [in] : none
     * @param [out] : none
     * @return const std::string&
     * @retval 类名的应用
     * @see
     * @note 这里的类型，就是配置文件中[EngineUnit]["EngineUnitType"]的取值
     *       目前，框架只支持2种type：RealEngineUnit和VirtualEngineUnit
     *       
     *       RealEngineUnit，数据就在本地存储
     *       VirtualEngineUnit，数据在远程存储，VirtualEngineUnit下面可以连接
     *         多个Unise
     *       每个Unise内部可以有多个EngineUnit，一般一个EngineUnit用来存储一种
     *         FactDoc的数据和相关的DimensionDoc
    **/
    virtual const std::string& get_type() const = 0;

    /**
     * @breaf 一次检索前的初始化工作
     *
     * @param [in] : none TODO:添加参数
     * @param [out] : none
     * @return bool
     * @retval true代表初始化成功
     * @see
     * @note 一般，如果初始化失败，那么这次检索最好跳过这个EngineUnit
    **/
    virtual bool init_for_search() = 0;

    /**
     * @breaf 在EngineUnit中检索
     *
     * @param [in] : GeneralSearchRequest*, 请求
     * @param [out] : GneralSearchResponse*, 相应
     * @return none
     * @retval none
     * @see unise/general_servlet.proto
     * @note RealEngineUnit和VirtualEngineUnit有不同的检索逻辑实现，但是
     *       对上层调用方是透明的，遵循general_servlet.proto协议
     *       SearchEngine也要遵循该proto协议
    **/
    virtual void search(GeneralSearchRequest*, GeneralSearchResponse*) = 0;

    /**
     * @brief 引擎是否已经初始化完成
     */
    virtual bool inited() const = 0;

    /**
     * @brief 是否还在启动中
     *        如果init函数会创建额外的线程，并且需要等待线程的初始化状态
     *        那么就需要实现该函数
     */
    virtual bool is_initing() const {
        return false;
    }

    /**
     * @brief 获取一个doc的正排
     * TODO:对于VEU需要特殊实现
     */
    virtual const ForwardIndex * get_forward_index(DocId docid) const {
        return NULL;
    }
};

REGISTER_FACTORY(EngineUnit);
#define REGISTER_ENGINEUNIT(name) REGISTER_CLASS(EngineUnit, name)
}

#endif  // UNISE_ENGINE_UNIT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
