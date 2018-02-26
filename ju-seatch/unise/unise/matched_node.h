// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_MATCHED_NODE_H_
#define  UNISE_MATCHED_NODE_H_

#include <vector>
#include "unise/base.h"

namespace unise
{
class DocTokenHit;

/**
 * @brief query node的命中信息封装
 */
class MatchedNode
{
public:
    /**
     * @breaf 构造函数，由框架构造生成对象
     *
     * @param [in] : 当前query node代表的token id
     * @param [in] : 当前query node命中了当前doc的哪些位置
     * @param [out] : none
     * @return none
     * @retval
     * @see
     * @note 
    **/
    MatchedNode(TokenId token_id, std::vector<doc_token_hit_t*>* hits);

    /**
     * @breaf 获取当前query node命中当前doc的信息
     *
     * @param [in] : none
     * @param [out] : none
     * @return const vector<doc_token_hit_t*>&
     * @retval 命中当前doc的多个位置
     * @see
     * @note 注意生存周期，同MatchedDoc的生存周期相同
    **/
    inline const std::vector<doc_token_hit_t*>& get_hits() const {
        return *_hits_per_doc;
    }

    /// @brief TODO 这里的内存管理，还需要仔细考虑一下
    /// @return 
    inline std::vector<doc_token_hit_t*> *get_hits_p() {
        return _hits_per_doc;
    }


    /**
     * @breaf 打印命中情况到字符串中
     *
     * @param [in] : output，输出缓冲区
     * @param [out] : output
     * @return none
     * @retval 
     * @see
     * @note 采用output->append()方式
    **/
    void to_string(std::string* output) const;

    TokenId get_token_id() const
    {
        return _token_id;
    }

private:
    TokenId _token_id;
    std::vector<doc_token_hit_t*> * _hits_per_doc;

    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MatchedNode);
};

}

#endif  // UNISE_MATCHED_NODE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
