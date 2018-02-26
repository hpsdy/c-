#include "topfeed_final_filter.h"
#include "article_doc.h"

namespace unise {

result_status_t TopfeedFinalFilter::filter(MatchedDoc *result)
{
    const ArticleDoc &doc = dynamic_cast<const ArticleDoc &>(result->get_fact_doc());

    std::string cate = doc._category_id;

    // 如果品类数量设置，则默认使用特殊品类0
    if (_availableCateCounter.find(cate) == _availableCateCounter.end()) {
        cate = "0";
    }
    //UFATAL("flag: num %d", _availableCateCounter[cate]);

    if (_availableCateCounter[cate] < 1) {
        return RESULT_FILTED_FINAL;
    }

    --_availableCateCounter[cate];
    return RESULT_ACCEPTED;
}

REGISTER_RESULT_FILTER(TopfeedFinalFilter);

} // namespace unise
