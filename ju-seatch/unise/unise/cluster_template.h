// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_CLUSTER_TEMPLATE_H_
#define  UNISE_CLUSTER_TEMPLATE_H_

#include <ext/hash_map>
#include <algorithm>
#include <vector>
#include "unise/result_cluster.h"
#include "unise/comparator.h"
#include "unise/base.h"

namespace unise
{

/**
 * @brief ClusterTemplate是为了方便实现ResultCluster插件而开发的一个模板类
 *        用户在自己的ResultCluster实现中，使用该模板作为成员属性，利用其
 *        方法完成基本聚合
 * Key: 聚合的key的类型
 * Data：聚合的value的类型
 * Capacity，聚合时最多保留key相同的数据
 */
template<typename Key, typename Data, size_t Capacity>
class ClusterTemplate
{
public:
    class ClusterDataSet
    {
    public:
        explicit ClusterDataSet(const Data& first_data, size_t MaxNumPerKey)
            : num_data_(1U),
              max_num_per_key_(MaxNumPerKey) {
            GOOGLE_DCHECK_LE(max_num_per_key_, Capacity);
            data_[0] = first_data;
        }

        cluster_status_t find(const Key& key,
                const Data& input_data,
                Data* replaced_data,
                const Comparator* comparator) {
            (void)(key);
            if (num_data_ < max_num_per_key_) {
                return CLUSTER_ADD;
            } else {
                size_t idx = find_worst_data_index(comparator);
                *replaced_data = data_[idx];
                if ((*comparator)(input_data, data_[idx])) {
                    return CLUSTER_REPLACE;
                } else {
                    return CLUSTER_SKIP;
                }
            }
        }

        cluster_status_t push(const Key& key,
                const Data& input_data,
                const Comparator* comparator) {
            (void)(key);
            if (num_data_ < max_num_per_key_) {
                data_[num_data_++] = input_data;
                return CLUSTER_ADD;
            } else {
                size_t idx = find_worst_data_index(comparator);
                if ((*comparator)(input_data, data_[idx])) {
                    data_[idx] = input_data;
                    return CLUSTER_REPLACE;
                } else {
                    return CLUSTER_SKIP;
                }
            }
        }

        bool remove(const Data& input_data) {
            static const size_t MAX_IDX = 0x7fffffff;
            size_t remove_idx = MAX_IDX;
            for (size_t i = 0; i < num_data_ && i < Capacity; ++i) {
                if (remove_idx == MAX_IDX && data_[i] == input_data) {
                    remove_idx = i;
                }
                if (remove_idx != MAX_IDX) {
                    if (remove_idx < i) {
                        data_[i - 1] = data_[i];
                    }
                }
            }
            if (remove_idx != MAX_IDX) {
                num_data_--;
                return true;
            } else {
                return false;
            }
        }

        size_t get_num_data() { return num_data_; }

    private:
        // TODO(wangguangyuan) : try better algorithm
        size_t find_worst_data_index(const Comparator * comparator) {
            size_t idx = 0;
            for (size_t i = 0; i < num_data_ && i < Capacity; ++i) {
                if ((*comparator)(data_[idx], data_[i])) {
                    idx = i;
                }
            }
            return idx;
        }

        Data data_[Capacity];
        size_t num_data_;
        size_t max_num_per_key_;
    };

    virtual void reset() { hash_cluster_.clear(); }
    explicit ClusterTemplate(Comparator* comparator)
        : comp_(comparator) {}

    explicit ClusterTemplate()
        : comp_(NULL) {}

    void set_comparator(const Comparator* comparator) { comp_ = comparator; }

    virtual ~ClusterTemplate() {}

    /**
     * @breaf 对一个Key为key，value为input_data的元素执行去重聚合操作
     *        根据返回值，框架会执行Add或Remove操作
     *
     * @param [in] : key, 元素的key
     * @param [in] : input_data, 元素的value
     * @param [out] : replaced_data,如果返回值为CLUSTER_REPLACE,该指针指向
     *                被input_data干掉的元素的地址
     * @return cluster_status_t
     * @retval CLUSTER_ADD,结果被采纳
     *         CLUSTER_REPLACE，干掉了别的结果
     *         CLUSTER_SKIP，被别的结果干掉了
     * @see 参见Comparator的实现
     * @note 
    **/
    virtual cluster_status_t cluster_result(const Key& key,
            const Data& input_data,
            Data* replaced_data) {
        GOOGLE_DCHECK(replaced_data);
        GOOGLE_DCHECK(comp_) << "Miss comparator.";
        *replaced_data = NULL;
        typename __gnu_cxx::hash_map<Key, ClusterDataSet>::iterator it =
            hash_cluster_.find(key);
        if (it == hash_cluster_.end()) {
            return CLUSTER_ADD;
        } else {
            return it->second.find(key, input_data, replaced_data, comp_);
        }
    }

    /**
     * @breaf 将一个Key为key，value为input_data的元素插入到去重结果集中
     *
     * @param [in] : key, 元素的key
     * @param [in] : input_data, 元素的value
     * @param [in] : max_num_per_key,当前key保留多少个最好的元素
     * @param [out] : none
     * @return cluster_status_t
     * @retval CLUSTER_ADD,结果被成功插入
     *         CLUSTER_REPLACE，替换了别的结果
     *         CLUSTER_SKIP，被别的结果干掉了,插入失败
     * @see
     * @note 该方法调用前，可以使用ClusterResult函数判断是否当前结果干掉
     *       了别的结果
     *       本函数中，在发生CLUSTER_REPLACE的情况下，是拿不到被干掉的结果的
    **/
    virtual cluster_status_t add(const Key& key,
        const Data& input_data,
        size_t max_num_per_key) {
        typename __gnu_cxx::hash_map<Key, ClusterDataSet>::iterator it =
            hash_cluster_.find(key);
        if (it == hash_cluster_.end()) {
            hash_cluster_.insert(std::make_pair(key, ClusterDataSet(input_data, max_num_per_key)));
            return CLUSTER_ADD;
        } else {
            return it->second.push(key, input_data, comp_);
        }
    }

    /**
     * @breaf 将一个Key为key，value为input_data的元素从去重结果集中
     *        删除
     *
     * @param [in] : key, 元素的key
     * @param [in] : input_data, 元素的value
     * @param [out] : none
     * @return bool
     * @retval true,删除成功
     *         false,删除失败
     * @see
     * @note 
    **/
    virtual bool remove(const Key& key, const Data& input_data) {
        typename __gnu_cxx::hash_map<Key, ClusterDataSet>::iterator it =
            hash_cluster_.find(key);
        if (it != hash_cluster_.end()) {
            bool retv = it->second.remove(input_data);
            if (it->second.get_num_data() == 0) {
                hash_cluster_.erase(it);
            }
            return retv;
        } else {
            return false;
        }
    }

protected:
    const Comparator* comp_;
    __gnu_cxx::hash_map<Key, ClusterDataSet> hash_cluster_;
};

}

#endif  // UNISE_CLUSTER_TEMPLATE_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
