#ifndef _TOPFEED_FINAL_FILTER_H_
#define _TOPFEED_FINAL_FILTER_H_

#include "unise/result_filter.h"

#include "unise/factory.h"
#include "unise/matched_doc.h"
#include "unise/base.h"
#include "unise/unise_plugin.h"
#include "unise/search_context.h"
#include "unise/general_servlet.pb.h"
#include "ju-search/article_search_context.h"
#include "unise/util.h"

#include <map>

namespace unise {

class GeneralSearchRequest;
class MatchedDoc;
class SearchContext;

/**
 * @brief 过滤插件，有三类：EarlyResultFilter,LaterResultFilter,FinalResultFilter
 *
 * @note 1) 继承自UnisePlugin，可以访问UnisePlugin提供的基本函数
 *       2) 对象生存空间和作用方式同其他UnisePlugin插件
 *       3) 参见EngineUnit的XXX_ResultFilter配置项，多个filters使用逗号分隔
 *       4）如果配置多个filters，按照配置顺序调用，依次生效
 *       5) unise会维护结果状态
 * @see 设计文档，对三类Filter的定义
 */
class TopfeedFinalFilter : public ResultFilter
{
public:
    TopfeedFinalFilter() {}
    virtual ~TopfeedFinalFilter() {}

    /**
     * @brief 每一个检索请求处理前，会调用该方法
     * @param [in] : request, 检索请求
     * @param [out] : none
     * @return  none
     * @retval none
     * @see
     * @note 注意，无返回值，无需要可以不实现
     */
    virtual void init_for_search(const GeneralSearchRequest *request, SearchContext *context)
    {
        (void)(request);
        (void)(context);

        // 允许返回的品类数量
        std::map<std::string, int32_t> m;

        std::string num_results_str;
        int num_res = 0;
        if (get_string_experiment_value(*request, "topfeed_original_num_results", &num_results_str)) {
            if (!StringToInt(num_results_str, &num_res)) {
                num_res = 0;
            }
        }
        //UFATAL("num res%d", num_res); 
        if (num_res <= 6){

            m["0"]      = 3;    // 未知品类

            m["326"]    = 4;    // 美食
            m["702"]    = 2;    // 亲子
            m["320"]    = 2;    // 休闲娱乐
            m["642"]    = 2;    // 酒店
            m["2182"]   = 2;    // 社区
            m["2180"]   = 2;    // 丽人
            m["2149"]   = 2;    // 结婚
            m["375"]    = 2;    // 教育
            m["706"]    = 2;    // 汽车
            m["2179"]   = 2;    // 家装
            m["960"]    = 2;    // 音乐娱乐
            m["345"]    = 2;    // 电影
            m["875"]    = 2;    // 购物
            m["708"]    = 2;    // 旅游
        }else{
            m["0"]      = 5;    // 未知品类

            m["326"]    = 20;    // 美食
            m["702"]    = 7;    // 亲子
            m["320"]    = 7;    // 休闲娱乐
            m["642"]    = 8;    // 酒店
            m["2182"]   = 8;    // 社区
            m["2180"]   = 5;    // 丽人
            m["2149"]   = 3;    // 结婚
            m["375"]    = 3;    // 教育
            m["706"]    = 3;    // 汽车
            m["2179"]   = 4;    // 家装
            m["960"]    = 8;    // 音乐娱乐
            m["345"]    = 8;    // 电影
            m["875"]    = 8;    // 购物
            m["708"]    = 8;    // 旅游

        }
        m.swap(_availableCateCounter);
    }

    /**
     * @breaf 每retrieve到一个MatchedDoc，都会调用filter函数
     *
     * @param [in] : doc,命中的MatchedDoc
     * @param [out] : none
     * @return  result_status_t
     * @retval 只有返回RESULT_ACCEPTED的结果被留下
     * @see base.h
     * @note FinalFilter，不会改变检索过程中其他插件(cluster)的状态了
     *       LaterFilter,如果过滤掉了一个doc，那么，cluster是会调用remove
     *       方面的方法，从sign结合中除去它
    **/
    virtual result_status_t filter(MatchedDoc *result);

    virtual std::string get_name() const
    {
        return "TopfeedFinalFilter";
    }

private:
    std::map<std::string, int32_t> _availableCateCounter;
};

} // namespace unise

#endif // _TOPFEED_FINAL_FILTER_H_
