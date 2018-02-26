// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UTIL_STATE_MONITOR_H
#define  UTIL_STATE_MONITOR_H

#include "unise/state_monitor.h"
namespace unise {
/**
 * @brief 一写多读的循环deque，如果大小超过，那么使用最老的节点
 */
class DequeQueue {
public:
    /**
     * @brief 构造一个可以容纳max_size个元素的DequeQueue
     */
    DequeQueue(size_t max_size) :
        _max_size(max_size) {}

    /**
     * @brief insert一个新的tens_record_t进去
     *        选择合适的位置
     */
    void insert(const tens_record_t& t) {
        // 找到需要插入的位置
        std::list<tens_record_t>::iterator it = _list.begin();
        while (it != _list.end() && it->timestamp > t.timestamp) {
            ++it;
        }

        // 写锁，修改的过程中不允许读
        boost::unique_lock<boost::shared_mutex> lock(_mu);
        if (it == _list.end()){
            if (_list.size() < _max_size) {
                _list.push_back(t);
            }
        } else if (it->timestamp == t.timestamp) {
            // 找到了合适的位置，且已存在节点，可以直接赋值
            it->min = std::min(it->min, t.min);
            it->max = std::max(it->max, t.max);
            it->avg = ((it->avg * it->count) + (t.avg * t.count)) / (it->count + t.count);
            it->count += t.count;
        } else {
            // 找到合适的位置，但是不存在节点，需要插入节点
            _list.insert(it, t);
            // 大小超标，需要扔一个最老的出来
            if (_list.size() > _max_size) {
                _list.pop_back();
            }
        }
    }

    /**
     * @brief 获取最新的num个元素，赋值到out指向的vector中
     * @retval 实际获取到的个数
     */
    size_t get_latest(size_t num, std::vector<tens_record_t>* out) {
        boost::shared_lock<boost::shared_mutex> lock(_mu);
        size_t ret = 0U;
        for (std::list<tens_record_t>::iterator it = _list.begin();
                    it != _list.end() && ret < num;
                    ++it, ++ret) {
            out->push_back(*it);
        }
        return ret;
    }

private:
    mutable boost::shared_mutex _mu;
    std::list<tens_record_t> _list;
    size_t _max_size;
};

}
#endif  // UTIL_STATE_MONITOR_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
