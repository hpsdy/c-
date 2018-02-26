/***************************************************************************
 *
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/

#include "util/das_loader.h"
#include "unise/base.h"
#include "util/util.h"
#include "util/file.h"
#include <Configure.h>
#include <boost/lexical_cast.hpp>
#include <iostream>

namespace unise
{

DasLoader::DasLoader(const std::string &info_file_name,
        const std::string &inc_dir,
        const std::string &inc_file_name_prefix,
        std::vector<boost::shared_ptr<DasCbClosure> > &callbacks,
        FileMonitor *file_monitor,
        char delim) :
    Thread(DAS_INC_LOADER_THREAD_NAME),
    _stopped(false),
    _updated(0),
    _inited(false),
    _info_file_name(info_file_name),
    _inc_dir(inc_dir),
    _inc_file_name_prefix(inc_file_name_prefix),
    _begin_file_id(INVALID_NUMBER),
    _begin_file_line(INVALID_NUMBER),
    _cur_line_head_offset(0),
    _callbacks(callbacks),
    _file_monitor(file_monitor),
    _DELIM(delim)
{/*{{{*/
    pthread_mutex_init(&_mutex, NULL);
    pthread_cond_init(&_cond, NULL);
}/*}}}*/

DasLoader::~DasLoader()
{/*{{{*/
    //取消增量目录更新的回调函数
    _file_monitor->remove_fcb(_inc_dir);
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
}/*}}}*/

int DasLoader::run() {
    do {
        //获取增量读取的起始信息
        if (!get_begin_info()) {
            UFATAL("Failed to get das begin info");
            break;
        }
        //注册增量目录更新的回调函数
        if(!_file_monitor->register_fcb(_inc_dir,
                        NewPermanentCallback(this, &DasLoader::raise))) {
            UFATAL("Failed to register file monitor callback function");
            break;
        }
        //加载增量文件
        if (!load_inc_files()) {
            UFATAL("Failed to load inc files");
            break;
        }
    } while (0);
    _stopped = true;
    return 0;
}

const std::string DasLoader::inc_file_name(uint32_t id)
{/*{{{*/
    return _inc_dir + "/" + _inc_file_name_prefix +
           boost::lexical_cast<std::string>(id);
}/*}}}*/

bool DasLoader::get_begin_info()
{/*{{{*/
    comcfg::Configure das_base_info;
    if (0 != das_base_info.load("", _info_file_name.c_str())) {
        UFATAL("Failed to load das info file: %s.", _info_file_name.c_str());
        return false; 
    } 
    try {
        _begin_file_id = das_base_info["idx"].to_uint32();
        _begin_file_line = das_base_info["line"].to_uint32();
    } catch (comcfg::ConfigException &e) {
        UFATAL("Failed to get das inc begin info, err_msg:%s", e.what());
        return false;
    }
    UDEBUG("Das begin info: file id %u, file line %u", _begin_file_id, 
            _begin_file_line);
    return true;
}/*}}}*/

bool DasLoader::is_id_file_exist(uint32_t id)
{/*{{{*/
    return FileSystem::is_file_exist(inc_file_name(id));
}/*}}}*/

bool DasLoader::load_inc_files()
{/*{{{*/
    //打开起始文件
    _cur_file_id = _begin_file_id;
    while (!is_id_file_exist(_cur_file_id)) {
        wait();
    }
    UNOTICE("Begin to load das inc file %s",
            inc_file_name(_cur_file_id).c_str());
    StopWatch load_stop_watch;
    uint32_t cnt = 0;
    char ch;
    uint64_t cur_idx = 0;
    std::string line[2]; //一个用于存储当前处理的记录，一个用来存储之前处理过的记录
    line[0].reserve(MAX_RECORD_LINE_LEN);
    line[1].reserve(MAX_RECORD_LINE_LEN);
    int see_new_cnt = 0;
    while (!_stopped) {
        //打开当前文件，读指针移动到上次读取的行的末尾处
        if (_cur_in_stream.is_open()) {
            _cur_in_stream.close();
        }
        _cur_in_stream.clear();
        _cur_in_stream.open(inc_file_name(_cur_file_id).c_str(), std::ios::in);
        _cur_in_stream.seekg(_cur_line_head_offset);
        line[cur_idx].clear();
        UDEBUG("(Re)Open file %s, offset:%u",
                inc_file_name(_cur_file_id).c_str(), _cur_line_head_offset);
        //读当前文件
        while (_cur_in_stream.get(ch)) {
            if (_DELIM == ch) {
                cnt++;
                //对于起始文件需要跳过起始行之前的记录
                // 这里修复一个bug, _begin_file_line是需要被处理的line
                // 之前的逻辑认为_begin_file_line是从0开始的，实际das是从1开始
                if (_cur_file_id != _begin_file_id || cnt >= _begin_file_line) {
                    if (line[cur_idx].size() > 0) {
                        process_line(line[cur_idx]);
                    }
                    UDEBUG("Process file %s %dst line, line:%s",
                            inc_file_name(_cur_file_id).c_str(), cnt, line[cur_idx].c_str());
                }
                cur_idx = (cur_idx + 1) % 2;
                line[cur_idx].clear();
                _cur_line_head_offset = _cur_in_stream.tellg();
            } else {
                line[cur_idx].push_back(ch);
            }
        }
        if (_cur_in_stream.bad()) {
            UFATAL("Failed to read das inc file %s",
                    inc_file_name(_cur_file_id).c_str());
            return false;
        }
        _cur_line_head_offset = 0;
        UTRACE("Das events before %lu (included) has been processed", 
                get_event_id(line[(cur_idx + 1) % 2]));
        wait();
        // 目前ju-search只需要一个增量文件即可
        /*
        //读到文件尾部了，此时有两种情况
        if (!is_id_file_exist(_cur_file_id + 1)) {
            //新文件还没有产生，当前文件可能还没有写完，等待
            //打印当前读取到的增量事件ID到日志
            UTRACE("Das events before %lu (included) has been processed", 
                    get_event_id(line[(cur_idx + 1) % 2]));
            wait();
        } else {
            //新文件已经生成
            if (0 == see_new_cnt) {
                //若之前未看到过新文件，则此时存在着旧文件未被读取完全的可能，
                //需要重新读取旧文件
                see_new_cnt++;
            } else {
                see_new_cnt = 0;
                //若之前看到过新文件，则此时旧文件必然已经读取完全，
                //关闭当前文件，开始读取新文件
                if (line[cur_idx].size() > 0) {
                    process_line(line[cur_idx]);
                    UDEBUG("Process file %s %dst line, line:%s",
                            inc_file_name(_cur_file_id).c_str(), cnt, line[cur_idx].c_str());
                    cur_idx = (cur_idx + 1) % 2;
                }
                UNOTICE("Finish loading das inc file %s, totally %u lines in %0.1f ms",
                        inc_file_name(_cur_file_id).c_str(), cnt, load_stop_watch.read());
                load_stop_watch.reset();
                _cur_file_id++;
                _cur_line_head_offset = 0;
                cnt = 0;
                UNOTICE("Begin to load das inc file %s",
                        inc_file_name(_cur_file_id).c_str());
            }
        }*/
    }
    //关闭当前文件
    if (_cur_in_stream.is_open()) {
        _cur_in_stream.close();
    }
    return true;
}/*}}}*/

}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
