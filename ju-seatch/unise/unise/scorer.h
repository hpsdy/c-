// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_SCORER_H_
#define  UNISE_SCORER_H_

#include <string>
#include <vector>
#include "unise/factory.h"
#include "unise/unise_plugin.h"

namespace unise
{
class MatchedDoc;
class GeneralSearchRequest;
class SearchContext;

/**
 * @brief 相关性打分插件，针对query，为每个doc打分
 *
 * @note 1) 继承自UnisePlugin，可以访问UnisePlugin提供的基本函数
 *       2) 每个检索线程有一个Scorer对象，检索线程启动时，初始化scorer对象 
 *       3) 参见EngineUnit的Scorers配置项，多个scorer使用逗号分隔
 *       4）如果配置多个scorers，那么，最终doc的分数求和，按照配置顺序调用
 */
class Scorer : public UnisePlugin
{
public:
    Scorer() {}
    virtual ~Scorer() {}

    /**
     * @breaf 检索初始化，每一个检索，如果交给当前scorer所在的线程来执行
     *        检索逻辑，那么会调用当前scorer的InitForSearch方法
     *
     * @param [in] : none
     * @param [out] : none
     * @return  none
     * @retval none
     * @see
     * @note 注意，这里不判断返回值，每次都会调用
    **/
    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context) = 0;

    /**
     * @breaf 打分函数
     *
     * @param [in] : doc,命中的MatchedDoc
     * @param [out] : score,分数，为该指针所指64位整数赋值，注意不要溢出
     * @return  bool
     * @retval 目前框架未判断返回值
     * @see
     * @note TODO(wangguangyuan) : 后期考虑加入对MatchedDoc获取命中信息
     *       是否启用的开关，来提高检索速度。部分检索逻辑，可能不需要
     *       获取正排的命中信息
    **/
    virtual bool score(MatchedDoc * doc, dynamic_score_t * score) = 0;
};

REGISTER_FACTORY(Scorer);
#define REGISTER_SCORER(name) REGISTER_CLASS(Scorer, name)

}

#endif  // UNISE_SCORER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
