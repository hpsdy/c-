// Copyright 2017 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#include "retri/branch_iterator.h"
#include <boost/lockfree/detail/branch_hints.hpp>

namespace unise {
using std::vector;
using boost::lockfree::detail::unlikely;

BranchIterator::BranchIterator(const vector<ForwardIterator *> & it_list,
                               const vector<uint32_t> & weight_list) :
        ForwardIterator(),
        _it_list(it_list),
        _weight_list(weight_list) {
    // 初始化SelectedSet，hashset给30000个桶足够了
    _selected_set.create(30000);

    // 初始化优先队列，权重每次自减，轮次每次自增
    for (size_t i = 0; i < _it_list.size(); ++i) {
        if (!_it_list.at(i)->done()) {
            _heap.push(std::make_pair(i, WeightRoundPair(_weight_list.at(i), 0)));
        }
    }
    // 根据当前状态调整迭代器，指向当前可用节点
    get_match();
}

void BranchIterator::get_match() {
    if (unlikely(_heap.empty())) {
        // 如果堆为空，那么将doc_hit复位为ILLEGAL
        _cur_doc_hit.reset();
    } else {
        // 堆顶元素是当前可用节点
        _cur_doc_hit = _it_list.at(_heap.top().first)->get_cur_doc_hit();
    }
}

void BranchIterator::next() {
    // 判断是否已经到底，到底则不能再走了
    if (unlikely(done())) {
        return;
    }

    size_t last_idx = _heap.top().first;
    while (!_heap.empty()) {
        WeightRoundPair wrp = _heap.top().second;
        --wrp.weight;
        // 判断是否需要新增轮数
        if (wrp.weight == 0) {
            ++wrp.round;
            wrp.weight = _weight_list.at(last_idx);
        }
        // 当前的docid被读取过了，进行标记
        DocId cur_docid = _it_list.at(last_idx)->get_cur_doc_hit().docid;
        _selected_set.set(cur_docid);
        UTRACE("docid[%llu] been solved, new weight[%u] round[%u]",
                    cur_docid, wrp.weight, wrp.round);
        // 将当前子树往下迭代一步
        ForwardIterator * fi = _it_list.at(last_idx);
        fi->next();
        // 将当前子树，重新入堆
        _heap.pop();
        if (!fi->done()) {
            _heap.push(std::make_pair(last_idx, wrp));
        }
        // 判断当前堆顶，是否重复，否则继续挑选
        // warning: 上面有过heap操作，所以需要再次判断堆是否为空
        if (!_heap.empty()) {
            last_idx = _heap.top().first;
            DocId new_docid = _it_list.at(last_idx)->get_cur_doc_hit().docid;
            if (_selected_set.get(new_docid) != bsl::HASH_EXIST) {
                UTRACE("docid[%llu] will be the next to be choosen", new_docid);
                break;
            }
        }
    }
    get_match();
}

bool BranchIterator::done() const {
    return _cur_doc_hit.docid == ILLEGAL_DOCID || _heap.empty();
}

void BranchIterator::jump_to(DocId docid, int32_t score) {
    // TODO(wangguangyuan) : 因为整个框架还不支持从固定docid开始检索
    //                       暂时屏蔽该功能，避免误用
    GOOGLE_CHECK(0);
    // 下面是正确的逻辑实现
    if (unlikely(done())) {
        return;
    }
    // 当前没有迭代完的所有的子树都往后jump
    while (!_heap.empty()) {
        size_t last_idx = _heap.top().first;
        ForwardIterator * fi = _it_list.at(last_idx);
        fi->jump_to(docid, score);
        // 出堆
        _heap.pop();
    }

    // jump后没有迭代完毕的子树重新入堆
    for (size_t i = 0; i < _it_list.size(); ++i) {
        ForwardIterator * fi = _it_list.at(i);
        if (!fi->done()) {
            // jump之后，weight和轮数重新计数
            _heap.push(std::make_pair(i, WeightRoundPair(_weight_list.at(i), 0)));
        }
    }
    get_match();
}

const doc_hit_t & BranchIterator::get_cur_doc_hit() const {
    return _cur_doc_hit;
}

bool BranchIterator::post_retrieval_check_internal() {
    // 类似Or迭代器，只要有任何一个孩子同意当前答案，那么
    // 当前branch节点就同意
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        if ((*it)->get_cur_doc_hit() == _cur_doc_hit &&
                (*it)->post_retrieval_check()) {
            return true;
        }
    }
    return false;
}

void BranchIterator::get_hit_list(std::stack<TokenId> * hits) const {
    GOOGLE_DCHECK(hits);
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        if ((*it)->get_cur_doc_hit() == _cur_doc_hit) {
            (*it)->get_hit_list(hits);
        }
    }
}

float BranchIterator::get_progress() const {
    float min_pro = 1.0;
    float cur_pro = 0.0;
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        cur_pro = (*it)->get_progress();
        if (cur_pro < min_pro) {
            min_pro = cur_pro;
        }
    }
    return min_pro;
}

uint64_t BranchIterator::get_estimated_num() const {
    uint64_t est = 0LLU;
    for (vector<ForwardIterator*>::const_iterator it = _it_list.begin();
            it != _it_list.end(); ++it) {
        est += (*it)->get_estimated_num();
    }
    return est;
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
