/***************************************************************************
 *
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/

#ifndef  UTIL_DAS_LOADER_H_
#define  UTIL_DAS_LOADER_H_

#include "unise/singleton.h"
#include "unise/thread.h"
#include "unise/callback.h"
#include "unise/util.h"
#include "unise/state_monitor.h"
#include "util/file_monitor.h"
#include <pthread.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace unise {
const std::string DAS_INC_LOADER_THREAD_NAME = "DAS_INC_LOADER_THREAD";
const uint32_t INVALID_NUMBER = 0xffffffff;
const uint32_t MAX_RECORD_LINE_LEN = 2048;

/// @brief 简单的对处理一行das增量的回调函数的封装，
//  @note 借鉴google的Closure
class DasCbClosure {
public:
    DasCbClosure() {}
    virtual ~DasCbClosure() {}

    virtual void Process(const std::string &) = 0;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(DasCbClosure);
};

namespace internal {
class DasCbFunctionClosure0 : public DasCbClosure {
public:
    typedef void (*FunctionType)(const std::string &);

    DasCbFunctionClosure0(FunctionType function, bool self_deleting) :
            function_(function),
            self_deleting_(self_deleting)
    {}
    virtual ~DasCbFunctionClosure0() {}

    void Process(const std::string &line) {
        bool needs_delete = self_deleting_;  // read in case callback deletes
        (*function_)(line);
        if (needs_delete) { delete this; }
    }

private:
    FunctionType function_;
    bool self_deleting_;
};

template <typename Class>
class DasCbMethodClosure0 : public DasCbClosure {
public:
    typedef void (Class::*MethodType)(const std::string &);

    DasCbMethodClosure0(Class* object, MethodType method, bool self_deleting)
        : object_(object), method_(method), self_deleting_(self_deleting)
    {}
    virtual ~DasCbMethodClosure0() {}

    void Process(const std::string &line) {
        bool needs_delete = self_deleting_;  // read in case callback deletes
        (object_->*method_)(line);
        if (needs_delete) { delete this; }
    }

private:
    Class* object_;
    MethodType method_;
    bool self_deleting_;
};

}

inline DasCbClosure* NewPermanentDasCallback(void (*function)(const std::string &)) {
    return new internal::DasCbFunctionClosure0(function, false);
}

template <typename Class>
inline DasCbClosure* NewPermanentDasCallback(
                Class* object,
                void (Class::*method)(const std::string &)) {
    return new internal::DasCbMethodClosure0<Class>(object, method, false);
}

/// @brief 用于加载Das增量文件的类
/// @note  该类的实现强依赖于Das产生增量文件的方式，即
///   1. 存在一个信息文件描述增量加载的起始文件ID和起始行数；
///   2. 增量数据的写入严格按照增量事件发生顺序；
///   3. 增量文件的生成严格按照文件名中的ID增序，并且ID是连续的，即：
///      先生成xxx.11，然后xxx.12，然后xxx.13，以此类推；
///   4. 同一增量文件中只能追加写
class DasLoader : public Thread {
public:
    /// @brief 构造函数
    /// @param [in] info_file_name   : das信息文件全路径
    /// @param [in] inc_dir  : das增量目录
    /// @param [in] inc_file_name_prefix   : das增量文件的名字的前缀
    /// @param [in] callbacks : 处理一行das增量的回调函数列表
    DasLoader(const std::string &info_file_name,
            const std::string &inc_dir,
            const std::string &inc_file_name_prefix,
            std::vector<boost::shared_ptr<DasCbClosure> > &callbacks,
            FileMonitor * file_monitor = Singleton<FileMonitor>::get(),
            char delim = '\n');

    virtual ~DasLoader();

    virtual int run();

    /// @brief 停止线程
    void stop() {
        UDEBUG("Stop the das loader thread");
        _stopped = true;
        raise();
    }

    /// @brief 是否已经追上所有增量
    inline bool inited() const {
        return _inited;
    }

    inline bool is_stop() const {
        return _stopped;
    }

private:
    bool _stopped;       /**< 是否退出标志       */
    int _updated;        /**< 记录未响应的更新次数       */
    bool    _inited;        ///< 是否已经追上增量

    const std::string _info_file_name;        /**< 描述增量加载起始位置的文件的名字       */
    const std::string _inc_dir;         /**< 增量文件目录       */
    const std::string _inc_file_name_prefix;          /**< 增量文件名字的前缀       */
    uint32_t _begin_file_id;          /**< 增量的起始加载文件的ID       */
    uint32_t _begin_file_line;        /**< 文件的起始加载行数       */
    uint32_t _cur_file_id;       /**< 当前正在读取的增量文件ID       */
    std::ifstream _cur_in_stream;         /**< 当前的文件输入流       */
    ssize_t _cur_line_head_offset;       /**< 当前的文件输入流上一个记录结尾处的偏移       */
    std::vector<boost::shared_ptr<DasCbClosure> > _callbacks;         /**< 处理一行das增量的回调函数列表       */
    FileMonitor *_file_monitor;       /**< 文件监控类实例指针       */
    const char _DELIM;         /**< das增量记录之间的分隔符       */

    pthread_mutex_t _mutex;
    pthread_cond_t _cond;

    /// @brief 等待更新事件
    /// @note 在das增量加载线程中调用
    void wait() {/*{{{*/
        _inited = true;             // 第一次调用 wait 就代表已经追上所有增量
        UDEBUG("Wait() called");
        pthread_mutex_lock(&_mutex);
        if (_updated <= 0) {
            pthread_cond_wait(&_cond, &_mutex);
        }
        _updated--;
        pthread_mutex_unlock(&_mutex);
    }/*}}}*/

    /// @brief 更新事件发生，唤醒等待线程
    /// @note 在目录监控线程中调用
    void raise() {/*{{{*/
        UDEBUG("Raise() called");
        pthread_mutex_lock(&_mutex);
        _updated++;
        pthread_mutex_unlock(&_mutex);
        pthread_cond_signal(&_cond);
    }/*}}}*/

    /// @brief 根据ID获取增量文件名
    const std::string inc_file_name(uint32_t id);

    /// @brief 获取增量加载起始信息
    bool get_begin_info();

    /// @brief 根据ID判断增量文件是否存在
    bool is_id_file_exist(uint32_t id);

    /// @brief 调用回调函数处理一行das增量数据
    void process_line(const std::string &line) {/*{{{*/
        for (size_t i = 0; i < _callbacks.size(); ++i) {
            _callbacks[i]->Process(line);
        }
    }/*}}}*/

    /// @brief 加载增量文件
    bool load_inc_files();
};

}

#endif  //UTIL_DAS_LOADER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
