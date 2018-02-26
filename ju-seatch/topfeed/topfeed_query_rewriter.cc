#include "topfeed_query_rewriter.h"

#include "unise/general_servlet.pb.h"
#include "unise/topfeed.pb.h"
#include "unise/base.h"
#include "unise/util.h"
#include "unise/query_rewriter.h"
#include "index/index.h"
#include <sstream>

namespace unise {

void TopfeedQueryRewriter::rewrite_internal(GeneralSearchRequest *req)
{
    std::vector<int64_t> cityVector;
    cityVector.push_back(0L);

    if (req->has_topfeed()) {
        const TopfeedRequest &topfeed = req->topfeed();
        if (topfeed.has_city_id() && topfeed.city_id() > 0L) {
            cityVector.push_back(topfeed.city_id());
        }
    }

    req->clear_query_tree();

    QueryNode *query = req->mutable_query_tree();
    query->set_type(OR);

    for (size_t i = 0; i < cityVector.size(); ++i) {
        QueryNode *subquery = query->add_children();
        subquery->set_type(VALUE);
        QueryNodeValue *subqueryValue = subquery->mutable_value();
        subqueryValue->set_annotation_name("tags");
        subqueryValue->set_text_value("cityid=" + Int64ToString(cityVector[i]));
    }

    // @todo 配置化召回数量 暂时写死1000
    // zehui改为2k
    req->mutable_search_params()->set_recall_docs(2000);

    Experiment *exp = req->mutable_search_params()->add_experiments();
    exp->set_key("topfeed_original_num_results");
    std::stringstream ss;
    ss << req->num_results();
    
    exp->set_value(ss.str());
}

REGISTER_QUERY_REWRITER(TopfeedQueryRewriter);

} // namespace unise
