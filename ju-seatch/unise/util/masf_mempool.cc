#include "util/masf_mempool.h"

#include <stdlib.h>
#include <algorithm>
#include "unise/base.h"

namespace unise
{

SolidMempool::SolidMempool(
        size_t item_size,
        size_t item_per_block,
        float balance_factor,
        int  balance_period)
    : item_size_(item_size),
      item_per_block_(item_per_block),
      balance_period_(balance_period),
      next_balance_time_(balance_period),
      max_used_per_period_(0)
{
    GOOGLE_DCHECK(balance_factor > 0.0f && balance_factor <= 1.0f);
    inv_balance_factor_ = 1.0f / balance_factor;
    GOOGLE_DCHECK_GT(balance_period_, 0);
    AllocNewBlock();
}

SolidMempool::~SolidMempool()
{
    Destroy();
}

void SolidMempool::Destroy()
{
    for (size_t i = 0; i < blocks_.size(); ++i) {
        free(blocks_[i]);
    }
    blocks_.clear();
}

void *SolidMempool::Malloc()
{
    if (item_idx_ < item_per_block_) {
        return blocks_[block_idx_] + item_size_ * item_idx_++;
    }
    if (blocks_.size() - 1 == block_idx_) {
        AllocNewBlock();
    } else {
        block_idx_++;
        item_idx_ = 0;
    }
    return blocks_[block_idx_] + item_size_ * item_idx_++;
}

void SolidMempool::AllocNewBlock()
{
    char *block =
        reinterpret_cast<char*>(malloc(item_size_ * item_per_block_));
    GOOGLE_CHECK(block);
    blocks_.push_back(block);
    block_idx_ = blocks_.size() - 1;
    item_idx_ = 0;
}

void SolidMempool::Recycle()
{
    BalancePool();
    item_idx_ = 0;
    block_idx_ = 0;
}

void SolidMempool::BalancePool()
{
    int64_t block_size = item_per_block_ * item_size_;
    uint64_t used_size = block_idx_ * block_size + item_idx_ * item_size_;
    max_used_per_period_ = std::max(max_used_per_period_, used_size);
    if (--next_balance_time_ > 0) {
        return;
    }
    // balance time
    int64_t total_size = blocks_.size() * block_size;
    int64_t threshold = static_cast<int64_t>(inv_balance_factor_ * static_cast<float>(max_used_per_period_));
    while (blocks_.size() > 1 && (total_size - block_size) >= threshold) {
        free(blocks_.back());
        blocks_.pop_back();
        total_size -= block_size;
    }
    // reset variables
    max_used_per_period_ = 0;
    next_balance_time_ = balance_period_;
}

}
