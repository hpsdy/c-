// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include <comlogplugin.h>
#include "unise/base.h"
#include "unise/singleton.h"
#include "unise/delay_callback.h"
#include "unise/asl_wordseg.h"
#include "util/global_init.h"
#include "index/base_builder.h"

DECLARE_string(conf_fpath);
DECLARE_string(conf_fname);

using namespace unise;

int main(int argc, char *argv[])
{
    // 最先应解析 gflags 文件和命令行参数，命令行参数覆盖 gflags 文件设置
    GlobalInit::global_init(argc, argv);

    // 根据 gflags 解析对应的配置文件，这里不使用约束文件，因为很多情形下RD
    // 会忘记更新约束文件，带来的麻烦可能比好处还大。
    comcfg::Configure conf;
    if (conf.load(FLAGS_conf_fpath.c_str(), FLAGS_conf_fname.c_str()) != 0) {
        UFATAL("Failed to load conf file: %s/%s.", FLAGS_conf_fpath.c_str(),
               FLAGS_conf_fname.c_str());
        return -1;
    }
    // 使用 public/comlog-plugin 封装的 comlog 接口初始化 comlog
    if (comlog_init(conf["Log"])) {
        UFATAL("Failed to initialize log module, please check [Log] in file: %s/%s",
               FLAGS_conf_fpath.c_str(), FLAGS_conf_fname.c_str());
        return -1;
    }

    // 初始化unise资源类
    if (false == Singleton<AslWordseg>::get()->init()) {
        UFATAL("Failed to init AslWordseg");
        return -1;
    }
    // 初始化延迟回调线程
    // 因为DimensionDoc的加载过程中，可能用户使用了延迟删除
    DelayCallbackThread delay_callback_thread;
    delay_callback_thread.start();

    int ret = 0;

    try {
        for (size_t i = 0; i < conf["SearchEngine"]["EngineUnit"].size(); ++i) {
            std::string type = conf["SearchEngine"]["EngineUnit"][i]["EngineUnitType"].to_cstr();
            std::string name = conf["SearchEngine"]["EngineUnit"][i]["EngineUnitName"].to_cstr();
            if (type == "RealEngineUnit") {
                // construct BaseBuilder and build
                unise::BaseBuilder base_builder;
                if (false == base_builder.init(conf["SearchEngine"]["EngineUnit"][i])) {
                    UFATAL("base builder init for:%s failed", name.c_str());
                    ret = -1;
                    continue;
                }
                if (false == base_builder.build_concurrency()) {
                    UFATAL("build base index for:%s failed", name.c_str());
                    ret = -1;
                    continue;
                }
                std::cout << "build base index succ for:" << name << std::endl;
            }
        }
    } catch (comcfg::ConfigException e) {
        UFATAL("Configure illegal:%s", e.what());
        return false;
    }
    if (ret == 0) {
        std::cout << "build base index succ for all" << std::endl;
    } else {
        std::cerr << "build base index failed, see log for detail" << std::endl;
    }

    // 建索引完毕，可以执行所有的回调
    delay_callback_thread.stop();
    delay_callback_thread.join();
    return ret;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
