// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#include "unise/delayed.h"

namespace unise {

DelayedJobs::DelayedJobs(size_t n) : _cb_queue(n) {
    _cb_queue.push(NULL);
}

DelayedJobs::~DelayedJobs() {
    tick_all();
}

size_t DelayedJobs::tick_all() {
    Closure *closure = NULL;
    size_t n = 0;
    while (_cb_queue.pop(closure)) {
        if (closure) {
            closure->Run();
            ++n;
        }
    }
    return n;
}

bool DelayedJobs::add(Closure * closure) {
    if (NULL != closure) {
        return _cb_queue.push(closure);
    }
    return false;
}

size_t DelayedJobs::tick() {
    _cb_queue.push(NULL);
    Closure *closure = NULL;
    size_t cb_count = 0;
    while (_cb_queue.pop(closure) && NULL != closure) {
        closure->Run();
        ++cb_count;
    }
    return cb_count;
}

LazyTimedJobs::LazyTimedJobs(long tick_in_ms, size_t n) :
    DelayedJobs(n),
    _tick_in_ms(tick_in_ms) {
    _last_tick = boost::posix_time::microsec_clock::local_time();
}

size_t LazyTimedJobs::tick() {
    size_t cb_count = 0;
    // 每次 tick 都计算时间简化了调用，略有代价。
    // 若后续需进一步优化，可将时间改为外部传入
    boost::posix_time::ptime this_tick = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration msdiff = this_tick - _last_tick;
    if (msdiff.total_milliseconds() >= _tick_in_ms) {
        cb_count = DelayedJobs::tick();
        _last_tick = this_tick;
    }
    return cb_count;
}

}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
