// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_FORWARD_INDEX_H
#define  INDEX_FORWARD_INDEX_H

#include <vector>
#include "unise/base.h"
#include "index/token_hit.h"

namespace unise
{
class ForwardIndex
{
public:
    ForwardIndex() {}
    virtual ~ForwardIndex() {}

    // build forward index for one doc's token_hits
    virtual bool build(const std::vector<TokenHit> & token_hits) = 0;

    /**
     * @brief 获取当前doc的正排共有多少种不同的token
     *        token id不同，则token不同
     * @return token种类，可能为0
     * @note token与annotation不等价，一个annotation可能生成多个token
     */
    virtual size_t get_token_num() const = 0;

    /**
     * @brief get the token id of the doc
     *        主要用于删除doc的时候，获取所有的token id，然后删除倒排
     * @return 获取token id列表失败时，返回false
     */
    virtual bool get_token_id_list(std::vector<TokenId> * token_id_list) const = 0;

    /**
     * @brief 获取指定token在当前doc中命中了多少次
     *        包含不同section,annotation组合中的命中情况
     * @return 返回命中次数，可能为0
     */
    virtual size_t get_doc_token_hit_list_size(TokenId token_id) const = 0;

    /**
     * @brief 获取指定token的所有hit信息列表
     * @return false则获取失败
     * @note 调用方需要确保传入的doc_token_hit_list中的所有指针的有效性
     *       doc_token_hit_list的大小，应该同实际hit次数一致
     * @warning 该接口将不再被内部调用，废弃
     */
    virtual bool get_doc_token_hit_list(TokenId token_id,
            const std::vector<doc_token_hit_t*> & doc_token_hit_list) const = 0;


    /**
     * @brief 将正排数据dump出来到buffer中，不能超过length
     * @return 长度超过length或dump失败，返回-1
     *         成功返回真正的长度
     * @note 该接口供基量建索引使用
     */
    virtual int get_dump_data(uint8_t * buffer, size_t length) const { return -1; }

    /**
     * @brief 从dump的数据中load正排数据，长度为length
     * @return load失败，返回false
     * @note 该接口供基量加载使用
     */
    virtual bool load_dump_data(uint8_t * buffer, size_t length) { return false; }
};
}

#endif  // INDEX_FORWARD_INDEX_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
