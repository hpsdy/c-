#ifndef UNISE_THREAD_H_
#define UNISE_THREAD_H_

#include <cstdlib>
#include <errno.h>
#include <pthread.h>
#include <string>

#include "unise/base.h"

namespace unise
{

/// @brief 简单线程处理逻辑的封装基类，用户仅需要实现 run 接口。
/// @note 支持一些基本的线程操作接口。如果需要对线程运行进行较为复杂的操作，
/// 建议不要直接使用此基类。
class Thread
{
public:
    Thread(const std::string& name):
        _tid(0), _name(name) {
    }

    virtual ~Thread() {
    }

    /// @brief 获取线程名
    /// @return
    const std::string& get_name() {
        return _name;
    }

    /// @brief 获取线程id
    /// @return 线程的 thread id
    pthread_t get_tid() {
        return _tid;
    }

    /// @brief 强制取消线程对象对应的线程的执行
    /// @return 与 pthread_cancel 返回语义相同
    int cancel() {
        int ret = ESRCH;
        if (0 != _tid) {
            ret = pthread_cancel(_tid);
            if (0 != ret) {
                UWARNING("[\tlvl=FOLLOW\t] FAIL: pthread_cancel(name=%s, tid=%d) return %d",
                        get_name().c_str(), _tid, ret);
            } else {
                _tid = 0;
            }
        }
        return ret;
    }

    /// @brief 给线程发送一个信号
    /// @note 这个操作保证信号处理函数在对应线程的上下文中执行，但可能影响整个进程。
    /// @return 与 pthread_kill 返回语义相同
    int kill(int sig = SIGTERM) {
        int ret = ESRCH;
        if (0 != _tid) {
            ret = pthread_kill(_tid, sig);
            if (0 != ret) {
                UWARNING("[\tlvl=FOLLOW\t] FAIL: pthread_kill(name=%s, tid=%d, signal=%d) "
                            "return %d", get_name().c_str(), _tid, sig, ret);
            } else {
                _tid = 0;
            }
        }
        return ret;
    }

    /// @brief 将线程分离，使其自己处理回收资源。
    /// @return
    virtual int detach() {
        int ret = ESRCH;
        if (0 != _tid) {
            ret = pthread_detach(_tid);
            if (0 != ret) {
                UWARNING("[\tlvl=FOLLOW\t] FAIL: pthread_detach(name=%s, tid=%d) return %d",
                        get_name().c_str(), _tid, ret);
            }
        }
        return ret;
    }

    /// @brief 调用该函数join本线程
    /// @return
    virtual int join() {
        int ret = ESRCH;
        if (0 != _tid) {
            ret = pthread_join(_tid, NULL);
            if (0 != ret) {
                UWARNING("[\tlvl=FOLLOW\t] FAIL: pthread_join(name=%s, tid=%d) return %d",
                        get_name().c_str(), _tid, ret);
            } else {
                _tid = 0;
            }
        }
        return ret;
    }

    /// @brief 子类实现该函数以自定义线程函数
    /// @return
    virtual int run() = 0;

    /// @brief 调用该函数启动线程
    /// @return 与 pthread_create 的返回值含义相同
    virtual int start() {
        UTRACE("Start thread(%s).", get_name().c_str());
        int ret = pthread_create(&_tid, NULL, _run_thread, (void *)this);
        if (0 != ret) {
            UWARNING("[\tlvl=FOLLOW\t] FAIL: pthread_create(name=%s) return %d",
                        get_name().c_str(), ret);
        }
        return ret;
    }

protected:
    /// @brief 退出线程，在run函数中调用，不应该在外部调用。
    /// @param[in] p 退出参数，返回给 join 调用的信息
    void exit(void *p) {
        if (0 != get_tid()) {
            pthread_exit(p);
        }
    }

private:

    /// @brief 线程函数,就是在pthread_create传入的函数
    /// @param[in|out] para : 用于传入给线程处理的数据
    /// @return
    static void* _run_thread(void *para) {
        com_openlog_r();    // 不检查返回值
        Thread *t = reinterpret_cast<Thread*>(para);
        UNOTICE("Thread(name=%s, tid=%d) running.", t->get_name().c_str(),
                t->get_tid());
        int ret = t->run();
        UNOTICE("Thread(name=%s, tid=%d) exit, return %d", t->get_name().c_str(),
                t->get_tid(), ret);
        com_closelog_r();
        return NULL;
    }

private:
    pthread_t   _tid;       ///< 线程ID
    std::string _name;      ///< 线程名
};

}   // namespace unise

#endif

