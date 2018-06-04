// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_RESULT_FILLER_H_
#define  UNISE_RESULT_FILLER_H_

#include "unise/factory.h"
#include "unise/matched_doc.h"
#include "unise/unise_plugin.h"

namespace unise {
class GeneralSearchRequest;
class SearchResult;
class MatchedDoc;
class SearchContext;

/**
 * @brief 摘要填充插件，只能有一个
 *
 * @note 1) 继承自UnisePlugin，可以访问UnisePlugin提供的基本函数
 *       2) 每个检索线程有一个filler对象，检索线程启动时，初始化filler对象 
 *       3) 参见EngineUnit的ResultFiller配置项
 */
class ResultFiller : public UnisePlugin {
public:
    ResultFiller() {}
    virtual ~ResultFiller() {}

    /**
     * @brief 每一个检索请求处理前，会调用该方法
     * @param [in] : none
     * @param [out] : none
     * @return  none
     * @retval none
     * @see
     * @note 注意，这里不判断返回值，每次都会调用;
    **/
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) = 0;

    /**
     * @brief 当每一个检索结果MatchedDoc在最终返回时，会被调用
     *        此时，所有的结果已经检索完毕，retrieve过程已经结束
     *        
     * @param [in] : result
     * @param [out] : search_result
     * @return  none
     * @retval none
     * @see
     * @note 注意，这里不判断返回值，每次都会调用;
     */
    virtual void fill_search_result(MatchedDoc * result,
                                    SearchResult* search_result) const = 0;
};

REGISTER_FACTORY(ResultFiller);
#define REGISTER_RESULT_FILLER(name) REGISTER_CLASS(ResultFiller, name)

}

#endif  // UNISE_RESULT_FILLER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
