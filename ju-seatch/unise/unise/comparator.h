// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_COMPARATOR_H_
#define  UNISE_COMPARATOR_H_

#include "Configure.h"
#include "unise/matched_doc.h"
#include "unise/factory.h"
#include "unise/unise_plugin.h"
#include "unise/search_context.h"

namespace unise {
/**
 * @brief 比较器接口
 */
class Comparator : public UnisePlugin {
public:
    Comparator() {}
    virtual ~Comparator() {}

    /**
     * @brief 每一个检索请求处理前，会调用该方法
     * @param [in] : request, 检索请求
     * @param [out] : none
     * @return  none
     * @retval none
     * @see
     * @note 注意，无返回值，无需要可以不实现
     */
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) {
        (void)(request);
        (void)(context);
    }

    /**
     * @brief 比较函数
     * @param [in] : a,b都为MatchedDoc
     * @param [out] : none
     * @return bool
     * @retval true则a比b质量高，应该排在前面
     *
     * @see 
     * @note
     */
    virtual bool operator()(const MatchedDoc* a, const MatchedDoc* b) const = 0;
};
REGISTER_FACTORY(Comparator);
#define REGISTER_COMPARATOR(name) REGISTER_CLASS(Comparator, name)

}

#endif  // UNISE_COMPARATOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
