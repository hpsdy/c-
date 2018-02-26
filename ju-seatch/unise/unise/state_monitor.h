// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_STATE_MONITOR_H_
#define  UNISE_STATE_MONITOR_H_

#include <bsl/containers/hash/bsl_phashmap.h>
#include <boost/lockfree/queue.hpp>
#include <boost/scoped_ptr.hpp>
#include <map>
#include <list>
#include <algorithm>
#include "unise/boost_wrap.h"
#include "unise/util.h"
#include "unise/thread.h"

namespace unise {
class DequeQueue;

/**
 * @brief 状态描述信息
 * @note if type == 0
 *           那么作为一个key-text_value类型的监控项
 *           只做value值替换
 *       if type == 1
 *           那么作为一个key-number_value类型的监控项
 *           统计min,max,mid,avg,count
 */
struct state_message_t {
    int32_t timestamp;        ///< 具体时间戳
    char key[50];          ///< 状态类型
    int8_t type;              ///< 类型，0：number； 1：text; -1: illegal
    uint64_t number_value;    ///< 需要统计的数字
    char text_value[50];   ///< 字符串状态描述
    
    state_message_t() :
        timestamp(get_timestamp()),
        type(-1),
        number_value(0LLU) {
        key[0] = 0;
        text_value[0] = 0;
    }
    /**
     * @brief key-text_value类型监控项的构造函数
     */
    state_message_t(int32_t ts, const std::string& k, const std::string& t_v) :
        timestamp(ts),
        type(1),
        number_value(0LLU) {
        set_key(k);
        set_text(t_v);
    }
    state_message_t(int32_t ts, const std::string& k, uint64_t n) :
        timestamp(ts),
        type(0),
        number_value(n) {
        set_key(k);
        set_text("");
    }

    // boost新版本要求提供一个copy构造函数
    state_message_t(const state_message_t & from) : 
        timestamp(from.timestamp),
        type(from.type),
        number_value(from.number_value) {
        set_key(from.key);
        set_text(from.text_value);
    }

    void set_key(const std::string& key_str) {
        int len = key_str.length();
        if (len >= 50) {
            len = 49;
        }
        memcpy(key, key_str.c_str(), len);
        key[len] = 0;
    }

    void set_text(const std::string& text_str) {
        int len = text_str.length();
        if (len >= 50) {
            len = 49;
        }
        memcpy(text_value, text_str.c_str(), len);
        text_value[len] = 0;
    }

    bool operator< (const state_message_t& smt) const {
        int ret = strcmp(key, smt.key);
        if (ret == 0) {
            return timestamp < smt.timestamp;
        } else if (ret < 0) {
            return true;
        } else {
            return false;
        }
    }
};

/**
 * @brief 10s内的统计数据
 *        针对number类型的状态统计
 */
struct tens_record_t {
    int32_t timestamp;      ///< 往小端打平，如19s，记录为10s
    uint64_t min;           ///< 10s内的最小值
    uint64_t max;           ///< 10s内的最大值
    double   avg;           ///< 10s内的平均值
    uint32_t count;         ///< 10s内的总数
};

/**
 * @brief 状态监控工具类
 *        使用方法：
 *        1. 设置number类型的统计，会以10分钟为粒度汇总，参与画图
 *        Singleton<StateMonitor>::get()->add_number_state_message(...)
 *        2. 设置text类型的统计，key-value类型
 *        Singleton<StateMonitor>::get()->add_text_state_message(...)
 */
class StateMonitor : public Thread {
public:
    StateMonitor();
    virtual ~StateMonitor();

    /**
     * @brief 新增数字类消息，多线程安全
     *        会进行10s内的min,max,mid,avg,count统计
     * @note 使用当前调用时刻的系统时间
     */
    inline void add_number_state_message(
                const std::string& key,
                uint64_t number) {
        state_message_t stm(get_timestamp(), key, number);
        add_state_message(stm);
    }

    /**
     * @brief 新增数字类消息，多线程安全
     *        会进行10s内的min,max,mid,avg,count统计
     * @note 尽量避免使用默认参数重载
     */
    inline void add_number_state_message(
                int32_t timestamp,
                const std::string& key,
                uint64_t number) {
        state_message_t stm(timestamp, key, number);
        add_state_message(stm);
    }

    /**
     * @brief 新增文本key-value类消息，多线程安全
     *        只更新全局kv信息
     */
    inline void add_text_state_message(
                const std::string& key,
                const std::string& text) {
        state_message_t stm(get_timestamp(), key, text);
        add_state_message(stm);
    }

    /**
     * @brief 获取key-value类型的数据
     */
    std::string get_text_state_message(const std::string& key);

    /**
     * @brief 获取number-value类型的统计数据
     */
    size_t get_number_state_message(
                const std::string& key,
                size_t num,
                std::vector<tens_record_t> *out);

    /**
     * @brief 停止监控线程
     * @note  请用户不要调用
     */
    void stop() { _stop = true; }

private:
    virtual int run();
    void process_text_message(const state_message_t& smt);
    void process_number_message(const state_message_t& smt);
    void add_state_message(const state_message_t& smt);

private:
    typedef boost::lockfree::queue<state_message_t> state_message_queue;
    typedef bsl::phashmap<std::string, std::string> key_value_map;
    typedef bsl::phashmap<std::string, DequeQueue* > record_queue_map;

    // 状态消息队列，用来传递实时消息，生产者消费者模式
    boost::scoped_ptr<state_message_queue> _state_message_queue;

    // key-text_value map，用来存储全局key-value监控信息
    boost::scoped_ptr<key_value_map> _ktv_map;

    // key-number类型的统计信息，按照key放到对应的queue中
    boost::scoped_ptr<record_queue_map> _record_queue_map;
    // 用来消化10s内的数据，避免频繁查找phash与list
    boost::scoped_ptr<std::vector<state_message_t> > _stomach;

    bool _stop;
};

}
#endif  // UNISE_STATE_MONITOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
