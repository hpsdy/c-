// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_DEMO_GLOBAL_HANDLER_H
#define  UNISE_DEMO_GLOBAL_HANDLER_H

#include "Configure.h"
#include "unise/global_handler.h"

namespace unise {
/**
 * @brief 全局初始化插件，在网络框架启动后，该插件被调用
 *
 */
class ArticleGlobalHandler : public GlobalHandler {
public:
    ArticleGlobalHandler() {}
    virtual ~ArticleGlobalHandler() {}

    virtual bool init(const comcfg::ConfigUnit& conf);

    virtual std::string get_name() {
        return "ArticleGlobalHandler";
    }

    void recall();
};

}
#endif  // UNISE_DEMO_GLOBAL_HANDLER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
