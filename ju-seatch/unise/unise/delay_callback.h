// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_DELAY_CALLBACK_H_
#define  UNISE_DELAY_CALLBACK_H_

#include <queue>
#include <map>
#include <boost/shared_ptr.hpp>
#include "unise/delayed.h"
#include "unise/thread.h"
#include "unise/singleton.h"

namespace unise
{

/**
 * @brief 管理常用延时调用的环境
 * @note 使用方需要调用DelayedEnv的执行方法，确保延迟回调得到
 *       执行机会
 */
class DelayedEnv
{
public:
    static const long DELAY_MAX = 3600000;  ///< 最多支持延时多少毫秒
    static const long DELAY_UNIT = 100;      ///< 指数增长的时间单位

    /// @brief 构造函数。_ltcb_vec 和 LazyTimedJobs 的构造析构都不是线程安全，不过我们
    /// 用单例管理这个环境，所以不会有同步问题。add_callback 和 execute_callback 是线程
    /// 安全的。
    DelayedEnv() : _frozen(false) {
        // 以 DELAY_UNIT 为基，2的指数级倍数提供时间粒度的 callback
        for (size_t i = 0; (1 << i) < (DELAY_MAX / DELAY_UNIT); ++i) {
            boost::shared_ptr<LazyTimedJobs> jobs(
                        new LazyTimedJobs(
                            (1 << i)*DELAY_UNIT,
                            1024 * 1024));
            _ltcb_vec.push_back(jobs);
        }
        boost::shared_ptr<LazyTimedJobs> jobs(new LazyTimedJobs(DELAY_MAX, 1024 * 1024));
        _ltcb_vec.push_back(jobs);
    }

    ~DelayedEnv() {
        // 使用者需要在外部主动调用execute_callback_now
        // 否则，可能有的延迟回调并没有机会被执行
    }


    /// @brief 添加要延迟执行的 callback，min_delay_ms 为建议的延迟时间。只要
    /// min_delay_ms 不超过 DELAY_MAX，回调在 min_delay_ms 时间内不会调用，但
    /// 不保证一定在 min_delay_ms 后被及时调用。
    /// @param[in] closure : 要添加的回调指针
    /// @param[in] min_delay_ms : 建议的延迟时间。
    /// @return 是否添加成功
    /// @note 线程安全
    bool add_callback(Closure * closure, long min_delay_ms = 15000) {
        if (_frozen) {
            return false;
        }
        size_t i = 0;
        // min_delay_ms 超过了最大的时间范围，那么直接用最大的
        // 否则选择第一个比 min_delay_ms 大的时间间隔，塞到 map 里
        for (i = 0; (1 << i) < (DELAY_MAX / DELAY_UNIT) && (min_delay_ms > (1 << i)*DELAY_UNIT); ++i) {
        }
        return _ltcb_vec[i]->add(closure);
    }

    /// @brief 执行所有到执行时间的回调
    /// @return 执行回调的个数
    /// @note 线程安全，但最好控制延时和调用频率
    size_t execute_callback() {
        std::vector<boost::shared_ptr<LazyTimedJobs> >::iterator iter;
        size_t cb_count = 0;
        for (iter = _ltcb_vec.begin(); iter != _ltcb_vec.end(); ++iter) {
            cb_count += (*iter)->tick();
        }
        return cb_count;
    }

    /// @brief 立刻执行所有的回调，不判断是否到执行时间
    /// @return 执行的回调的个数
    /// @note 主要用于主程序析构时调用和测试的时候，释放内存使用
    size_t execute_callback_now() {
        // 冻结，禁止新加回调
        _frozen = true;

        std::vector<boost::shared_ptr<LazyTimedJobs> >::iterator iter;
        size_t cb_count = 0;
        for (iter = _ltcb_vec.begin(); iter != _ltcb_vec.end(); ++iter) {
            cb_count += (*iter).get()->tick_all();
        }
        return cb_count;
    }

private:
    // 存储不同时间粒度级别延时回调的向量
    std::vector<boost::shared_ptr<LazyTimedJobs> >     _ltcb_vec;   ///< 延时回调级别向量
    bool _frozen;  ///< 回调队列被冻结，不允许再添加新的回调
};

/**
 * @brief 延时删除线程，负责执行全局单例的DelayedEnv的调用
 * @note 非多线程安全，全局只起一个线程使用
 */
class DelayCallbackThread : public Thread
{
public:
    DelayCallbackThread() :
        Thread("DelayCallbackThread"),
        _delay_env(Singleton<DelayedEnv>::get()),
        _stop(false) {}
    virtual ~DelayCallbackThread() {
        // WARNING: 安全起见，析构的时候，需要主动stop并join
        // 否则，线程可能访问本对象的成员属性
        // 但是当前对象已经被析构了
        stop();
        join();
    }
    void stop() { _stop = true; }
private:
    virtual int run()
    {
        while (!_stop) {
            _delay_env->execute_callback();
            /// 最小单位是DELAY_UNIT毫秒
            usleep(DelayedEnv::DELAY_UNIT * 1000);
        }
        // 立刻执行所有的延迟回调
        // 确保线程结束后，所有的延迟回调都得到执行
        _delay_env->execute_callback_now();
        return 0;
    }

private:
    DelayedEnv * _delay_env;
    bool _stop;
};
}

#endif  // UNISE_DELAY_CALLBACK_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
