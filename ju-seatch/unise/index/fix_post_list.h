// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_FIX_POST_LIST_H
#define  INDEX_FIX_POST_LIST_H

#include <vector>
#include <string>
#include "index/doc_hit_list.h"

namespace unise {

// 每个ITEM由一个doc_hit和删除位
struct post_item_t {
    doc_hit_t doc_hit;
    uint8_t is_delete:1;  ///< 是否删除
    uint8_t reserved:7;   ///< 预留字段
    bool operator<(const post_item_t & b) const {
        return (doc_hit.score > b.doc_hit.score ||
                doc_hit.score == b.doc_hit.score && doc_hit.docid < b.doc_hit.docid);
    }
    bool operator==(const post_item_t & b) const {
        return (doc_hit.score == b.doc_hit.score && doc_hit.docid == b.doc_hit.docid);
    }
};

class PostBlockCmp {
public:
    bool operator() (const post_item_t * a, const post_item_t * b) {
        return (a[0].doc_hit.score > b[0].doc_hit.score ||
                a[0].doc_hit.score == b[0].doc_hit.score &&
                a[0].doc_hit.docid < b[0].doc_hit.docid);
    }
};

/**
 * @breaf 历史倒排链实现，包含多个大小固定的PostBlock，之间用skiplist来连接
 *        以提高内存利用率
**/
class FixPostList : public DocHitList {
public:
    friend class FixPostListIterator;

    explicit FixPostList(TokenId token_id);

    FixPostList(TokenId token_id, std::vector<doc_hit_t> * array);

    // SkipList会主动析构内部的节点，但是需要节点具备析构函数
    virtual ~FixPostList();

    // 一定是按照顺序增加的，先加最好的
    virtual bool add(const doc_hit_t & doc_hit);

    virtual void remove(const doc_hit_t & doc_hit);

    /**
     * @brief 这个size是精确的
     */
    virtual size_t size() const;

    // must call this method to reserve enough space
    virtual void reserve(size_t s);

    virtual std::string get_name() const {
        return "FixPostList";
    }

    virtual TokenId get_token_id() const {
        return _token_id;
    }

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FixPostList);

private:
    std::vector<post_item_t *> _block_list;
    TokenId _token_id;
    // 最后一个的post item 数组
    post_item_t * _last_block;
    // 最后一个空块的free item个数
    size_t _last_block_free_cnt;
    size_t _size;
};

class FixPostListIterator : public DocHitListIterator {
public:
    explicit FixPostListIterator(const DocHitList & list);
    virtual ~FixPostListIterator() {}
    virtual bool done() const;
    virtual void next();
    virtual const doc_hit_t & get_current_value() const;
    virtual void jump_to(const doc_hit_t & doc_hit);
    virtual float get_progress() const;

private:
    void get_match();

private:
    doc_hit_t _illegal_doc_hit;
    const std::vector<post_item_t *> & _block_list;
    size_t _last_block_size;
    size_t _cur_block_idx;
    size_t _cur_block_size;
    size_t _cur_item_idx;
    size_t _size;
};
}

#endif  // INDEX_FIX_POST_LIST_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
