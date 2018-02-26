// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_TOKEN_LIST_H_
#define  INDEX_TOKEN_LIST_H_

#include "index/doc_hit_list.h"
#include "unise/base.h"

namespace unise {
class DocHit;

/**
 * @brief 目前只支持2层链，一个实时链，一个历史链
 *
 */
enum token_list_type_t {
    REAL_TIME_LIST = 0,  ///< 实时链类型
    FIX_TIME_ARRAY = 1,  ///< 历史链类型
};

/**
 * @brief TokenList是建索引时对一个token的倒排的封装，使得上层
 *        不需要关心倒排的具体实现逻辑
 *        支持插入、删除两个基本功能
 */
class TokenList {
public:
    /**
     * @breaf 构造一个空的token的倒排
     *
     * @param [in] : token_id表明是哪个token的倒排
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note
    **/
    explicit TokenList(TokenId token_id);

    /**
     * @breaf 该构造函数需要调用方提供一个FixTimeArray的指针
     *        用于服务启动时，基量索引构建完毕，直接初始化一个
     *        空的实时链和具有数据的历史链
     *
     * @param [in] : token_id表明是哪个token的倒排
     * @param [in] : list是一个FixTimeArray指针
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note list is a FixTimeArray pointer
    **/
    TokenList(TokenId token_id, DocHitList * list);
    ~TokenList();

    /**
     * @breaf 往倒排中插入一个DocHit
     *
     * @param [in] : doc_hit,倒排的一个节点
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note 插入永远发生在实时链上，可能触发merge逻辑
     *       merge阈值见FLAGS_buffer_merge_threshold
    **/
    void insert_doc_hit(const doc_hit_t & doc_hit);

   /**
     * @breaf 触发本倒排链的merge逻辑
     *
     * @param [in] : none
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note 一般不需要外部调用，这里暴露出来，是为了考虑框架后期
     *       采用job的方式管理merge
    **/
    void merge();

    /**
     * @breaf 删除倒排链中的一个dochit
     *
     * @param [in] : 要删除的dochit
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note doc_hit需要具备完整的docid和score信息
     *       如果删除失败，没有任何响应
    **/
    void delete_doc_hit(const doc_hit_t & doc_hit);

    /**
     * @breaf 获取指定类型的底层倒排链
     *
     * @param [in] : type，倒排链类型
     * @param [out] : none
     * @return const DocHitList&
     * @retval 实时链或历史链的常引用
     * @see
     * @note 这个链在若干秒后不能再访问，也许被延迟删除了
    **/
    const DocHitList & get_doc_hit_list(token_list_type_t type) const {
        switch (type) {
        case REAL_TIME_LIST:
            return *_buffer_list;
        case FIX_TIME_ARRAY:
            return *_fix_list;
        default :
            GOOGLE_CHECK(0) << "no such token_list_type_t:" << type;
            // 避免编译错误
            return *(const DocHitList *)NULL;
        }
    }

    size_t get_length() const {
        return _buffer_list->size() + _fix_list->size();
    }

    TokenId get_token_id() const {
        return _token_id;
    }


    void set_filter_flag(const doc_hit_t& doc_hit, bool flag) {
        if (flag) {
            // 需要过滤掉
            _buffer_list->remove(doc_hit);
            _fix_list->remove(doc_hit);
        } else {
            // 不能被过滤掉
            _buffer_list->add(doc_hit);
            _fix_list->remove(doc_hit);
        }
    }

private:
    void push_to_list(const doc_hit_t & doc_hit, DocHitList * list);

private:
    // 当前倒排链是那个token的
    TokenId _token_id;
    // 当前倒排链的实时链
    DocHitList * _buffer_list;
    // 当前倒排链的历史链
    DocHitList * _fix_list;
    // 实时链合并到历史链的阈值
    int32_t _buffer_merge_threshold;

private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TokenList);
};
}

#endif  // INDEX_TOKEN_LIST_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
