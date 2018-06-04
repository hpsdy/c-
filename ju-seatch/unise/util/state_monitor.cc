// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "util/state_monitor.h"
#include <gflags/gflags.h>

// 定义监控队列的大小，最大保留12个小时的数据
DEFINE_int32(monitor_record_queue_size, 6*60*12, "");

namespace unise {
StateMonitor::StateMonitor() :
        Thread("StateMonitor"),
        _stop(false) {
    // 初始化各种资源
    _state_message_queue.reset(new state_message_queue(1024*1024));
    _ktv_map.reset(new key_value_map(1024));
    _record_queue_map.reset(new record_queue_map(1024));
    _stomach.reset(new std::vector<state_message_t>());
}


StateMonitor::~StateMonitor() {
    // 释放_record_queue_map中的Queue
    for (record_queue_map::iterator it = _record_queue_map->begin();
                it != _record_queue_map->end();
                ++it) {
        delete it->second;
    }
}

std::string StateMonitor::get_text_state_message(const std::string& key) {
    std::string value;
    if (bsl::HASH_EXIST == _ktv_map->get(key, &value)) {
        return value;
    } else {
        return "NULL";
    }
}

size_t StateMonitor::get_number_state_message(
            const std::string& key,
            size_t num,
            std::vector<tens_record_t> *out) {
    DequeQueue * cq = NULL;
    if (bsl::HASH_EXIST == _record_queue_map->get(key, &cq)) {
        return cq->get_latest(num, out);
    } else {
        return 0U;
    }
}

int StateMonitor::run() {
    state_message_t smt;
    while (!_stop) {
        if (!_state_message_queue->pop(smt)) {
            // 没有新的监控信息进来，不需要处理
            // 睡1s，监控没有必要太频繁
            usleep(1000000);
            // 发送一个非法的number_message，促进10s区间内数据
            // 的肠道蠕动
            smt.timestamp = get_timestamp();
            smt.type = -1;
            smt.set_key("stomach");
            smt.set_text("moving");
            process_number_message(smt);
            continue;
        }

        UDEBUG("state_monitor new message timestamp[%d] key[%s] type[%d] text[%s] number[%llu]",
                smt.timestamp,
                smt.key,
                smt.type,
                smt.text_value,
                smt.number_value);

        if (smt.type == 0) {
            process_number_message(smt);
        } else if (smt.type == 1) {
            process_text_message(smt);
        }
    }
    return 0;
}

// note: 数据进来是可能有延迟的
void StateMonitor::process_number_message(const state_message_t& smt) {
    // 胃中积累10 s以上的数据，再处理，避免频繁的做底层phash和list查找
    if (_stomach->size() != 0 &&
        smt.timestamp / 10 != _stomach->at(0).timestamp / 10) {
        // warning: 虽然这里已经有了时间窗判断，但是，这仅仅是一个触发条件
        //          真正的数据，不一定只包含1个窗口的数据
        // 首先按照key，timestamp排序
        sort(_stomach->begin(), _stomach->end());
        
        // 为了处理简单，最后push一个哨兵
        state_message_t guard(smt);
        guard.set_key("_NO_SUCK_KEY_");
        _stomach->push_back(guard);

        uint64_t min = 0xFFFFFFFFFFFFFFFF;
        uint64_t max = 0;
        uint64_t sum = 0;
        uint32_t count = 0;
        for (size_t i = 0; i < _stomach->size(); ++i) {
            // 一组不同的key的序列开始了，把之前的数据全部处理下
            // 如果key不同，那么无论如何，需要处理之前的数据
            // 如果时间戳不在同一个0~9秒的时间窗口，需要处理之前的数据
            if (i != 0 &&
                ((strcmp(_stomach->at(i-1).key, _stomach->at(i).key) != 0) ||
                 _stomach->at(i-1).timestamp / 10 != _stomach->at(i).timestamp / 10)) {
                tens_record_t record;
                record.timestamp = (_stomach->at(i-1).timestamp / 10) * 10;
                record.avg = sum / count;
                record.count = count;
                record.min = min;
                record.max = max;
                min = 0xFFFFFFFFFFFFFFFF;
                max = 0;
                sum = 0LLU;
                count = 0;
                DequeQueue * cq = NULL;
                if (_record_queue_map->get(_stomach->at(i-1).key, &cq) == bsl::HASH_NOEXIST) {
                    // 申请一个新的queue
                    cq = new(std::nothrow) DequeQueue(FLAGS_monitor_record_queue_size);
                    if (cq == NULL) {
                        UWARNING("[\tlvl=SERIOUS\tnew DequeQueue failed\t]");
                        break;
                    }
                    _record_queue_map->set(_stomach->at(i-1).key, cq, 1);
                }
                cq->insert(record);
            }

            sum += _stomach->at(i).number_value;
            min = std::min(min, _stomach->at(i).number_value);
            max = std::max(max, _stomach->at(i).number_value);
            count++;
        }
        // 清空消化完的数据
        _stomach->clear();
    }

    // 如果当前消息是真正的消息，那么就push进去
    if (smt.type != -1) {
        _stomach->push_back(smt);
    }
}

void StateMonitor::process_text_message(const state_message_t& smt) {
    // 如果存在旧值，那么直接替换
    _ktv_map->set(smt.key, smt.text_value, 1);
}

void StateMonitor::add_state_message(const state_message_t& smt) {
    UDEBUG("add_state_message timestamp[%d] key[%s] type[%d] text[%s] number[%llu]",
                smt.timestamp,
                smt.key,
                smt.type,
                smt.text_value,
                smt.number_value);
    if (!_state_message_queue->push(smt)) {
        UNOTICE("state_message_queue is full");
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
