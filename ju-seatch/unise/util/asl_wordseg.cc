// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "gflags/gflags.h"
#include "unise/util.h"
#include "unise/asl_wordseg.h"

DEFINE_string(worddict_conf_path, "data/worddict/scw.conf",
      "切词字典conf文件的全路径");
DEFINE_string(worddict_path, "data/worddict/",
      "切词字典文件路径");
DEFINE_string(ccode_data_path, "data/",
      "ccode字典文件路径，用于繁体转简体，注意不包含./code/xxx");

using namespace unise;

/// @brief 初始化
bool AslWordseg::init()
{
    bool ret = false;
    pthread_mutex_lock(&_lock);
    do {
        if (NULL != _seg_dict) {
            ret = true;
            break;
        }
        // 加载切词词典conf文件
        pgconf = scw_load_conf(get_file_path(FLAGS_worddict_conf_path).c_str());
        if (NULL == pgconf) {
            UWARNING("[\tlvl=SERIOUS\tdict_conf_file=%s\t] Load wordseg conf failed!",
                        get_file_path(FLAGS_worddict_conf_path).c_str());
            break;
        }
        // 加载切词词典
        _seg_dict = scw_load_worddict(get_file_path(FLAGS_worddict_path).c_str());
        if (NULL == _seg_dict) {
            UWARNING("[\tlvl=SERIOUS\tdict_file=%s\t] Load wordseg dictionary failed!",
                        get_file_path(FLAGS_worddict_path).c_str());
            break;
        }
        // 加载ucode繁体转简体的词典
        if (ULN_UTF8_SUCCESS != uln_utf8_transload(get_file_path(FLAGS_ccode_data_path).c_str())) {
            UWARNING("[\tlvl=SERIOUS\tcode_path=%s\t] Load code for ucode failed!",
                        get_file_path(FLAGS_ccode_data_path).c_str());
            _ucode_init_succ = false;
            break;
        } else {
            _ucode_init_succ = true;
        }
        ret = true;
    } while (0);
    pthread_mutex_unlock(&_lock);
    return ret;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=80: */
