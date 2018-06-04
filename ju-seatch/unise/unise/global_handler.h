// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_GLOBAL_HANDLER_H
#define  UNISE_GLOBAL_HANDLER_H

#include <string>
#include "bthread_unstable.h"
#include "unise/factory.h"
#include "unise/base.h"

namespace comcfg {
class ConfigUnit;
}

namespace unise {

/**
 * @brief 全局初始化插件，在网络框架启动后，该插件被调用
 *
 */
class GlobalHandler {
public:
    GlobalHandler() {}
    virtual ~GlobalHandler() {}

    /**
     * @breaf 全局初始化接口
     *
     * @param [in] : 
     * @param [out] : 
     * @return  bool
     * @retval 目前框架未判断返回值
     * @see
     * @note 
     *
    **/
    virtual bool init(const comcfg::ConfigUnit& conf) = 0;

    virtual std::string get_name() = 0;

    /**
     * @breaf 基本的初始化接口
     *
     * @param [in] : none
     * @param [out] : none
     * @return  none
     * @retval none
     * @see
     * @note  用户请勿调用该接口 
    **/
    bool init_basic(const comcfg::ConfigUnit& conf) {
        return init(conf);
    }
};

REGISTER_FACTORY(GlobalHandler);
#define REGISTER_GLOBAL_HANDLER(name) REGISTER_CLASS(GlobalHandler, name)

}

#endif  // UNISE_GLOBAL_HANDLER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
