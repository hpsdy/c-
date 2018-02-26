// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "util/global_init.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include "gflags/gflags.h"

DEFINE_string(conf_fpath, "./conf", "配置文件目录");
DEFINE_string(gflags_fname, "unise_serve.gflags", "gflags文件名");
DEFINE_string(conf_fname, "unise_serve.conf", "配置文件名");
DEFINE_string(signature, "Not Available", "程序摘要特征串");

namespace unise {

void GlobalInit::global_init(int argc, char *argv[]) {
    // 保证用户可以指定 conf_fpath 路径值
    google::ParseCommandLineFlags(&argc, &argv, false);
    std::map<std::string, std::string> version_map;
    version_map["time"] = __DATE__ " " __TIME__;
    version_map["compiler"] = __VERSION__;
#ifdef BUILD_VERSION
    version_map["build version"] = BUILD_VERSION;
    FLAGS_signature = version_map["build version"];
#endif
#ifdef BUILD_SVN_REV
    version_map["revision"] = BUILD_SVN_REV;
#endif
#ifdef BUILD_USER
    version_map["build by"] = BUILD_USER;
    FLAGS_signature += " by " + version_map["build by"];
#endif
#ifdef BUILD_HOST
    version_map["host"] = BUILD_HOST;
    FLAGS_signature += "@" + version_map["host"];
#endif
#ifdef __OPTIMIZE__
    version_map["mode"] = "opt";
#else
    version_map["mode"] = "dbg";
#endif
    FLAGS_signature += " mode(" + version_map["mode"] + ") on " + version_map["time"];
    // 拼接 version str，作为程序版本打印信息
    std::string version_str = "\n";
    size_t max_key_len = 0;
    std::map<std::string, std::string>::iterator it;
    for (it = version_map.begin(); it != version_map.end(); ++it) {
        max_key_len = max_key_len > it->first.size() ? max_key_len : it->first.size();
    }
    for (it = version_map.begin(); it != version_map.end(); ++it) {
        version_str += it->first;
        version_str.append(max_key_len - it->first.size(), ' ');
        version_str += " : " + it->second + "\n";
    }
    google::SetVersionString(version_str);
    google::SetUsageMessage("Run this application in the directory where \""
            + FLAGS_conf_fpath + "\" can be found.\n");
    struct stat finfo;
    std::string flagfile = FLAGS_conf_fpath + "/" + FLAGS_gflags_fname;
    if (stat(flagfile.c_str(), &finfo) == 0) {
        google::SetCommandLineOption("flagfile", flagfile.c_str());
    }
    google::ParseCommandLineFlags(&argc, &argv, true);
    // 程序未接到其它参数时，打印版本信息
    std::cout << google::VersionString() << std::endl;
    // 初始化随机数产生器
    srand(time(NULL) ^ getpid());
}
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
