#ifndef UTIL_MASF_MEMPOOL_H_
#define UTIL_MASF_MEMPOOL_H_

#include <vector>
#include "unise/base.h"

namespace unise
{

const size_t kDftItemPerBlock = 64U;
const float kDftBalanceFactor = 0.5;
const int kDftBalancePeriod = 100;

class SolidMempool
{
public:
    SolidMempool(size_t item_size,
            size_t item_per_block = kDftItemPerBlock,
            float balance_factor = kDftBalanceFactor,
            int balance_period = kDftBalancePeriod);
    virtual ~SolidMempool();

    void Destroy();
    void *Malloc();
    virtual void Recycle();

    // for unittest
    size_t GetTotalSize() {
        return blocks_.size() * item_per_block_ * item_size_;
    }
    size_t GetUsedSize() {
        size_t block_size = item_per_block_ * item_size_;
        return block_idx_ * block_size + item_idx_ * item_size_;
    }

protected:
    void AllocNewBlock();
    void BalancePool();

    std::vector<char *> blocks_;
    // param
    size_t item_size_;
    size_t item_per_block_;
    float inv_balance_factor_;
    int balance_period_;

    // runtime variables
    size_t item_idx_;
    size_t block_idx_;
    // for recycle
    uint32_t next_balance_time_;
    uint64_t max_used_per_period_;
};

template <class Type>
class MasfObjPool : public SolidMempool
{
public:
    MasfObjPool(
            size_t item_per_block = kDftItemPerBlock,
            float balance_factor = kDftBalanceFactor,
            int balance_period = kDftBalancePeriod)
        : SolidMempool(sizeof(Type),
                item_per_block,
                balance_factor,
                balance_period) {
        debug_mem_count_ = 0;
    }
    virtual ~MasfObjPool() {}

    virtual void Recycle() {
        GOOGLE_DCHECK_EQ(debug_mem_count_, 0);
        SolidMempool::Recycle();
    }

    Type *New() {
        ++debug_mem_count_;
        void *buf = Malloc();
        return new(buf) Type();
    }

    template <class Arg1>
    Type *New(Arg1 arg1) {
        ++debug_mem_count_;
        void *buf = Malloc();
        return new(buf) Type(arg1);
    }

    template <class Arg1, class Arg2>
    Type *New(Arg1 arg1, Arg2 arg2) {
        ++debug_mem_count_;
        void *buf = Malloc();
        return new(buf) Type(arg1, arg2);
    }

    template <class Arg1, class Arg2, class Arg3>
    Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3) {
        ++debug_mem_count_;
        void *buf = Malloc();
        return new(buf) Type(arg1, arg2, arg3);
    }

    template <class Arg1, class Arg2, class Arg3, class Arg4>
    Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) {
        ++debug_mem_count_;
        void *buf = Malloc();
        return new(buf) Type(arg1, arg2, arg3, arg4);
    }

    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
    Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) {
        ++debug_mem_count_;
        void *buf = Malloc();
        return new(buf) Type(arg1, arg2, arg3, arg4, arg5);
    }

    void Delete(Type *obj) {
        --debug_mem_count_;
        obj->~Type();
    }
private:
    int debug_mem_count_;
};

}

#endif  // UTIL_MASF_MEMPOOL_H_
