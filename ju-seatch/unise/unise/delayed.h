#ifndef UNISE_DELAYED_H
#define UNISE_DELAYED_H


#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/noncopyable.hpp>

#include "unise/callback.h"

namespace unise {

/// @brief 线程安全的延时回调容器。将希望延时的回调句柄添加到容器中，每次调用
/// tick 时，自动地执行上一 tick 之前添加的延时回调句柄。
///
/// @note 我们以 tick 作为计数，tick 的时间粒度由上层控制。假如上层以 100ms 为
/// 间隔调用 tick()，那么回调句柄的执行延时在 100ms~200ms 之间。但如果回调任务
/// 过多，或者回调任务执行时间较长，这个延时可能会增大更多。
/// 无锁特性保证了容器接口的安全性，即可以在并发线程中调用 add(), tick()。但
/// 用户需要自行保证 tick() 调用的时间间隔。
class DelayedJobs : public ::boost::noncopyable {
public:
    /// @brief 构造函数，先 push 进第一个 tick 的标记。
    DelayedJobs(size_t n = 1000);

    virtual ~DelayedJobs();

    size_t tick_all();

    /// @brief 添加一个希望延时调用的回调 Closure
    /// @param[in] closure : Closure 封装的回调句柄
    /// @return 是否成功地将回调句柄添加到队列中
    virtual bool add(Closure * closure);

    /// @brief 执行上一次tick调用之前添加的延时回调，用户需自行保证延时调用的间隔。
    /// @return 执行的延时回调个数
    virtual size_t tick();

protected:
    boost::lockfree::queue<Closure *> _cb_queue;    ///< 回调任务的队列，无锁结构
};

/// @brief 一个基于时间的懒惰延时调用容器，只保证延时调用不会在 tick_in_ms 毫秒内被调用。
/// 可能会在后续的某个时间段内被调用
class LazyTimedJobs : public DelayedJobs {
public:
    /// @brief 构造函数
    /// @param[in] tick_in_ms : 在 tick_in_ms 毫秒内，延时回调句柄不会被调用
    LazyTimedJobs(long tick_in_ms, size_t n);

    /// @brief 如果离上次执行 tick 超过了 tick_in_ms 毫秒，执行上一次tick调用
    /// 之前添加的延时回调
    /// @return 执行的延时回调个数
    virtual size_t tick();

private:
    boost::posix_time::ptime    _last_tick;         ///< 上一次执行 tick 的时间
    long                        _tick_in_ms;        ///< 每次 tick 的时间长度，以ms为单位
};

}

#endif  // UNISE_DELAYED_H
