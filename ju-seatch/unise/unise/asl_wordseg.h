#ifndef UNISE_ASL_WORDSEG_H
#define UNISE_ASL_WORDSEG_H

#include <map>
#include <pthread.h>
#include <bsl/containers/hash/bsl_phashmap.h>
#include "isegment.h"
#include "scwdef.h"
#include "ucode.h"
#include "unise/base.h"

namespace unise {

/// @brief 安全分配线程切词句柄的封装类，应为单例。它避免了：
/// 1. 在高度抽象的线程框架中，线程自己维护切词线程句柄带来的复杂度；
/// 2. 线程句柄从上层往下层传导的复杂度；
/// 3. 同时承载了unise需要的全局资源的初始化工作
class AslWordseg {
public:
    /// @brief 构造函数
    AslWordseg(): _seg_dict(NULL), _ucode_init_succ(false) {
        pthread_mutex_init(&_lock, NULL);
        _handle_map.create(64); 
    }
    /// @brief 析构函数
    ~AslWordseg() {
        bsl::phashmap<pthread_t, scw_out_t*>::iterator it = _handle_map.begin();
        for (; it != _handle_map.end(); ++it) {
            if (NULL != it->second) {
                scw_destroy_out(it->second);
                it->second = NULL;
            }
        }
        if (NULL != _seg_dict) {
            scw_destroy_worddict(_seg_dict);
            _seg_dict = NULL;
        }
        // 注意pgconf是切词lib的全局成员
        if (NULL != pgconf) {
            scw_destroy_conf(pgconf);
            pgconf = NULL;
        }
        // 释放ucode对词表的加载
        if (_ucode_init_succ) {
          uln_utf8_clear();
        }
        pthread_mutex_destroy(&_lock);
    }

    /// @brief 初始化
    bool init();

    /// @brief 获取切词句柄
    scw_worddict_t * get_dict() {
        return _seg_dict;
    }

    /// @brief 得到线程对应的切词output
    /// @return 0 : 获取切词句柄失败；非 0 : 得到线程对应的切词句柄
    /// @note 因为句柄是分配给每个线程的，而且线程 id 也不是主动传入，所以一旦调用者
    /// 拿到句柄，只存在作用域和生命期问题，不存在分配、释放、同步问题。
    /// @warning 注意句柄的flags，使用的时候，只能使用被包含的切词粒度
    scw_out_t * get_handle(unsigned int tsize = 1024, int type = SCW_OUT_ALL|SCW_OUT_PROP) {
        scw_out_t * ret = NULL;
        if (_seg_dict == NULL) {
            return ret;
        }
        pthread_t tid = pthread_self();
        if (_handle_map.get(tid, &ret) == bsl::HASH_EXIST) {
            return ret;
        } else {
            ret = scw_create_out(tsize, type);
            
            if (NULL != ret) {
                _handle_map.set(tid, ret, 1);
            } else {
                UWARNING("[\tlvl=MONITOR\t_seg_dict=%ld\t_seg_buf_size=%u\t] "
                            "Call seg_open failed.", _seg_dict, tsize);
            }
        }
        return ret;
    }

private:
    pthread_mutex_t                 _lock;
    scw_worddict_t                * _seg_dict;        ///< 打开后的词典指针
    bsl::phashmap<pthread_t, scw_out_t*> _handle_map;
    bool                         _ucode_init_succ;    ///< ucode加载词典成功
};

};

#endif
