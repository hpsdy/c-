// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "article_global_handler.h"
#include "unise/singleton.h"
#include "unise/delay_callback.h"

#include "topfeed/topfeed_plugin_cityhot.h"

namespace unise {
void ArticleGlobalHandler::recall() {
    // 每5s执行一次回调
    Singleton<DelayedEnv>::get()->add_callback(
                NewCallback(this, &ArticleGlobalHandler::recall),
                5000);
    UTRACE("ArticleGlobalHandler recall finished");
}

bool ArticleGlobalHandler::init(const comcfg::ConfigUnit &conf) {
    // Init cityhot
    Singleton<TopfeedPluginCityhot>::get()->reload();

    UNOTICE("ArticleGlobalHandler init succ");
    // recall();
    return true;
}

REGISTER_GLOBAL_HANDLER(ArticleGlobalHandler);
}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
