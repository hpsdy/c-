#ifndef  INDEX_COMPACT_FORWARD_INDEX_H_
#define  INDEX_COMPACT_FORWARD_INDEX_H_

#include "forward_index.h"
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <boost/shared_array.hpp>
#include <boost/lockfree/detail/branch_hints.hpp>
#include <stdint.h>
#include <map>

using namespace google::protobuf;
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

namespace unise
{
#pragma pack(push, 1)
struct head_item_t {
    TokenId token_id;           // 8 bytes
    uint32_t offset;            // 4 bytes
    uint32_t num;               // 4 bytes TODO : 删除这一项，改接口

    bool operator < (const head_item_t & b) const {
        return token_id < b.token_id;
    }
    bool operator == (const head_item_t & b) const {
        return token_id == b.token_id;
    }
};

class CompactForwardIndex : public ForwardIndex
{
public:
    CompactForwardIndex() :
      _head(NULL), _end(NULL) {}

    virtual ~CompactForwardIndex()
    {
        if (_head) {
            delete []_head;
        }
    }

    virtual bool build(const std::vector<TokenHit> &token_hits);

    /**
     * @brief 获取Token的个数
     *
     * @return  size_t token个数
     * @retval
     * @see
     * @note
    **/
    virtual size_t get_token_num() const
    {
        if (unlikely(_head == NULL)) {
            return 0U;
        }
        size_t first_item_offset = (reinterpret_cast<head_item_t*>(_head))->offset;
        // 根据第一个token的hit在body中的存储位置
        // 推算token num个数，注意head_item_t的pack信息
        return first_item_offset / sizeof (head_item_t);
    }

    /**
     * @brief 获取TokenId列表
     *
     * @param [out] token_id_list   : TokenId列表
     * @return  bool true 成功；false 失败
     * @retval
     * @see
     * @note
    **/
    virtual bool get_token_id_list(std::vector<TokenId> *token_id_list) const;

    /**
     * @brief 获取TokenId的hits信息的个数
     *
     * @param [in] token_id   : tokenid
     * @return  size_t TokenId的hits信息的个数
     * @retval
     * @see
     * @note
    **/
    virtual size_t get_doc_token_hit_list_size(TokenId token_id) const;

    /**
     * @brief 获取TokenId的hits信息列表
     *
     * @param [in] token_id   : tokenid
     * @param [out] doc_token_hit_list   : TokenId的hits信息列表
     * @return  bool
     * @retval
     * @see
     * @note
    **/
    virtual bool get_doc_token_hit_list(TokenId token_id,
            const std::vector<doc_token_hit_t*> &doc_token_hit_list) const;

    virtual int get_dump_data(uint8_t * buffer, size_t length) const
    {
        GOOGLE_DCHECK(buffer);
        size_t ret = _end - _head;
        if (length < ret) {
            return -1;
        }
        memcpy(buffer, _head, ret);
        return static_cast<int>(ret);
    }

    virtual bool load_dump_data(uint8_t * buffer, size_t length)
    {
        _head = buffer;
        _end = buffer + length;
        return true;
    }

private:
    /**
     * @brief 二分查找token id对应的head_item_t，没有找到则返回NULL
     * @note 内部函数，调用方需要确保_head不为NULL
     */
    const head_item_t * find(TokenId token_id) const
    {
        GOOGLE_DCHECK(_head);
        head_item_t * head = reinterpret_cast<head_item_t*>(_head);
        size_t token_num = get_token_num();
        head_item_t item = {token_id, 0, 0};
        head_item_t * ret = std::find(head, head + token_num, item);
        return (ret == head + token_num) ? NULL : ret;
    }

private:
    /**
     *  head: <tokenid,offset><tokenid,offset><tokenid,offset>
     *  body: <secid,annoid,pos><secid,annoid,pos>
     *  head 中的tokenid从小到大，升序排列
     *
     *  压缩方法：secid与annoid都是1字节，不压缩；pos只做变长压缩，因为
     *            结构化数据，token重复出现的概率很低
     *            如果差分，还需要做标记位，得不偿失
     */
    uint8_t * _head;  ///< 记录内存起始地址
    uint8_t * _end;   ///< 记录内存终止地址，所指地址不被包含在本正排中
};
#pragma pack(pop)
}

#endif  //INDEX_COMPACT_FORWARD_INDEX_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
