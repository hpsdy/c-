// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_DEFAULT_COMPARATOR_H
#define  RETRI_DEFAULT_COMPARATOR_H

#include <boost/lockfree/detail/branch_hints.hpp>
#include "unise/comparator.h"
#include "unise/general_servlet.pb.h"

using boost::lockfree::detail::unlikely;

namespace unise{

class SearchResultComparator
{
public:
    SearchResultComparator() {}
    ~SearchResultComparator() {}

    /**
     * @brief 比较两个SearchResult的大小
     * @note 这里的比较使用的是SearchResult里面的score和docid
     *       理论上，SearchResult的score同MatchedDoc的score是一致的
     * @retval true 则a应该排在b前面
     *         false 则a应该排在b的后面
     */
    bool operator()(const SearchResult* a, const SearchResult* b) const
    {
        int com_size = static_cast<int>(_orders.size());
        GOOGLE_DCHECK_EQ(a->values_size(), b->values_size());
        GOOGLE_DCHECK_EQ(a->values_size(), com_size);
        for (int i = 0; i < com_size; ++i) {
            const Value & a_v = a->values(i);
            const Value & b_v = b->values(i);
            bool asc = _orders[i];
            if (a_v.id() != ILLEGAL_ANNOTATION_ID && b_v.id() != ILLEGAL_ANNOTATION_ID) {
                GOOGLE_DCHECK_EQ(a_v.id(), b_v.id());
                if (a_v.has_number_value()) {
                    GOOGLE_DCHECK(b_v.has_number_value());
                    if (a_v.number_value() == b_v.number_value()) {
                        continue;
                    } else if (a_v.number_value() < b_v.number_value()) {
                        return asc;
                    } else {
                        return !asc;
                    }
                } else {
                    GOOGLE_DCHECK(a_v.has_text_value());
                    GOOGLE_DCHECK(b_v.has_text_value());
                    int ret = strcmp(a_v.text_value().c_str(), b_v.text_value().c_str());
                    if (ret == 0) {
                        continue;
                    } else if (ret < 0) {
                        return asc;
                    } else {
                        return !asc;
                    }
                }
            } else if (a_v.id() != ILLEGAL_ANNOTATION_ID && b_v.id() == ILLEGAL_ANNOTATION_ID) {
                // b没有合法的值，那么b排在最后面;
                return true;
            } else if (a_v.id() == ILLEGAL_ANNOTATION_ID && b_v.id() != ILLEGAL_ANNOTATION_ID) {
                // a没有合法的值，应该a排在最后面
                return false;
            } // else 说明两个doc都没有合适annotation，那么，跳过比较
        }

        // 比较到这里都没有比较出胜负，得分大的排在前面，得分相同则docid小的排在前面
        // 通常，doc的动态得分应该是有区别的，所以使用unlikely
        if (unlikely(a->score() == b->score())) {
            return a->docid() < b->docid();
        } else {
            return a->score() > b->score();
        }
    }
    inline void reset(const GeneralSearchRequest * request)
    {
        _orders.clear();
        if (request->has_search_params()) {
            const SearchParams & sp = request->search_params();
            for (int i = 0; i < sp.sort_params_size(); ++i) {
                bool asc = true;
                if (sp.sort_params(i).has_ascending()) {
                    asc = sp.sort_params(i).ascending();
                }
                _orders.push_back(asc);
            }
        }
    }

    /**
     * @brief 该比较器是否生效,生效，则采用该比较器进行比较
     * @retval true，request有排序参数，需要生效
     *         false, request无排序参数，不能生效
     */
    inline bool enable() const
    {
        return _orders.size() != 0U;
    }
private:
    std::vector<bool> _orders;
};

/**
 * @brief 默认的MatchedDoc比较器
 */
class DefaultComparator : public Comparator
{
public:
    DefaultComparator() {}
    virtual ~DefaultComparator() {}

    virtual void init_for_search(const GeneralSearchRequest* request,
                                 SearchContext * context)
    {
        (void)(context);
        // 注意每次查询，都需要初始化一次comparator
        _comparator.reset(request);
    }

    /**
     * @breaf 比较函数
     *
     * @param [in] : a，待比较的MatchedDoc的指针
     * @param [in] : b，待比较的MatchedDoc的指针
     * @param [out] : none
     * @return bool
     * @retval true, a比b的质量高
     *
     * @see 
     * @note a比b的质量高，在检索逻辑中我们认为质量高的doc应该排在
     *       质量低的doc的前面，去重时，去重质量低的
    **/
    virtual bool operator()(const MatchedDoc* a, const MatchedDoc* b) const;

    virtual std::string get_name() const
    {
        return "DefaultComparator";
    }
private:
    SearchResultComparator _comparator;      ///< 基于排序参数的排序器
};
}

#endif  // RETRI_DEFAULT_COMPARATOR_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
