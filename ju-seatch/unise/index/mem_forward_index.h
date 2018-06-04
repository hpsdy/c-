/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file mem_forward_index.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/05 16:49:19
 * @version $Revision$
 * @brief 内存FactDoc正排信息
 *
 **/


#ifndef  __MEM_FORWARD_INDEX_H_
#define  __MEM_FORWARD_INDEX_H_

#include "forward_index.h"
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <boost/shared_array.hpp>
#include <stdint.h>
#include <map>

using namespace google::protobuf;

namespace unise
{

/**
* @brief 存储Token的信息
*/
struct TokenInfo {
    uint32_t hit_list_size;
    uint32_t data_len;
    boost::shared_array<uint8> data;

    TokenInfo() : hit_list_size(0), data_len(0) {}
};

/**
* @brief 存储每个(section, annotation)的信息，
* 用于存储中间结果
*/
struct SecAnnoInfo {
    SectionId section_id;        /**< section id       */
    AnnotationId annotation_id;       /**< annotation id       */
    std::vector<int32_t> pos;         /**< pos数组       */
};

class MemForwardIndex : public ForwardIndex
{
public:
    MemForwardIndex() {}

    virtual ~MemForwardIndex() {}

    /**
     * @brief 构建一个doc的正排信息
     *
     * @param [in] token_hits   : tokenid的hits信息
     * @return  bool true 成功；false 失败
     * @retval
     * @see
     * @note
    **/
    virtual bool build(const std::vector<TokenHit> &token_hits);

    /**
     * @brief 获取Token的个数
     *
     * @return  size_t token个数
     * @retval
     * @see
     * @note
    **/
    virtual size_t get_token_num() const;

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
private:
    std::map<TokenId, TokenInfo> _token_map;          /**< 存储token数据的map       */

    /**
     * @brief 添加一个Token的Data到map中
     *
     * @param [in] token_hit_info   :
     * @return
     * @retval
     * @see
     * @note
    **/
    void add_one_token_to_map(TokenId token_id, const std::vector<SecAnnoInfo> &token_hit_info);
};

}

#endif  //__MEM_FORWARD_INDEX_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
