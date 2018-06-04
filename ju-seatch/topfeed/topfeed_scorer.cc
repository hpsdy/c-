#include "topfeed_scorer.h"

#include <vector>
#include "gflags/gflags.h"
#include "unise/matched_node.h"
#include "unise/matched_doc.h"
#include "unise/fact_doc.h"
#include "unise/general_servlet.pb.h"
#include "unise/base.h"
#include "unise/search_context.h"

#include "ju-search/article_doc.h"
#include "topfeed/topfeed_plugin_cityhot.h"
#include "unise/singleton.h"

#include "ju-search/article_search_context.h"
#include "math.h"
#include <stdlib.h>

namespace unise {

void TopfeedScorer::init_for_search(const GeneralSearchRequest *request, SearchContext *context)
{
    _context = dynamic_cast<ArticleSearchContext *>(context);

    _usercfFactor = 500;
    _favcateFactor = 200;
    _cityhotFactor = 200;
    _pubtimeFactor = 100;

    context->get_experiment_value("usercf_factor", &_usercfFactor);
    context->get_experiment_value("favcate_factor", &_favcateFactor);
    context->get_experiment_value("cityhot_factor", &_cityhotFactor);
    context->get_experiment_value("pubtime_factor", &_pubtimeFactor);
}

bool TopfeedScorer::score(MatchedDoc *doc, dynamic_score_t *score)
{
    UTRACE("get docid[%llu] with score[%f]", doc->get_doc_id(), score);

    // get the static score use docid
    const ArticleDoc &factDoc = dynamic_cast<const ArticleDoc &>(doc->get_fact_doc());

    double usercfWeight = 0.0;
    double favcateWeight = 0.0;
    double cityhotWeight = 0.0;
    std::string triggerTypeStr;

    if (_context != NULL && _context->_topfeedCityId > 0L) {
        const TopfeedPluginCityhot::FeedWeightMap &map = Singleton<TopfeedPluginCityhot>::get()->getByCity(_context->_topfeedCityId);
        TopfeedPluginCityhot::FeedWeightMap::const_iterator iter = map.find(factDoc._resource_id);
        if (iter != map.end()) {
            cityhotWeight = iter->second;
            cityhotWeight = 1 / ( 1 + cityhotWeight);
        }
    }

    int64_t cityId = factDoc._city_id;
    if(cityId)
    {
        const TopfeedPluginCityhot::FeedWeightMap &hitcity = Singleton<TopfeedPluginCityhot>::get()->getByCity(cityId);
        if(!hitcity.empty())
        {
            triggerTypeStr += "1";
        }
    }

    if (_context != NULL && _context->_topfeedUsercf.size() > 0) {
        ArticleSearchContext::TopfeedUsercfType::const_iterator iter = _context->_topfeedUsercf.find(factDoc._resource_id);
        if (iter != _context->_topfeedUsercf.end()) {
            usercfWeight = iter->second;
            usercfWeight = 1 / (1 + usercfWeight);
            triggerTypeStr += "2";
        }
    }

    uint64_t eachDocId = doc->get_doc_id();
    _context->_topfeedTrigger[eachDocId] = triggerTypeStr;
    
    if (_context != NULL && _context->_topfeedFavcate.size() > 0) {
        int32_t category_id = atoi(factDoc._category_id.c_str());
        ArticleSearchContext::TopfeedFavcateType::const_iterator iter = _context->_topfeedFavcate.find(category_id);
        if (iter != _context->_topfeedFavcate.end()) {
            favcateWeight = iter->second;
            favcateWeight = 1 / (1 + favcateWeight);
        }
    }

    // factDoc._category_id
    int publish_time = factDoc._publish_time; 
    double publishWeight = caculate_time_score(publish_time);
    double usercf_score = usercfWeight * _usercfFactor;
    double cityhot_score = _cityhotFactor * cityhotWeight;
    double time_score = publishWeight * _pubtimeFactor;
    double fav_score = favcateWeight * _favcateFactor;

    
    double sum = usercf_score + cityhot_score + time_score + fav_score;
    if (factDoc._category_id == "2180"){
        sum = sum * 0.8;
    }
    
    //UFATAL("resource_id: %d", factDoc._resource_id);
    //UFATAL("user_cf score: %f ; cityhot_score: %f ; time_score: %f ; favorite_score: %f ; sum: %f", 
    //        usercf_score, cityhot_score, time_score, fav_score, sum);
    dynamic_score_t max_score = ~(1LLU << ((sizeof (dynamic_score_t)<<3) - 1));
    if (sum > static_cast<double>(max_score)) {
        *score = max_score;
    } else {
        *score = static_cast<dynamic_score_t>(sum);
    }

    return true;
}

double TopfeedScorer::caculate_time_score(int publish_time) 
{
    time_t now;
    time(&now);
    int current_time = now;
    double time_score = 1.0;
    double alpha = 0.25; //建议文章数量小的时候取得小一点，之后再变大。
    int interval = current_time - publish_time;
    if (interval < 0) {
        return time_score;
    }
    double day_interval = interval/43200.0;
    time_score = 1.0 / (1.0 + alpha * log(day_interval));
    return time_score;

}

REGISTER_SCORER(TopfeedScorer);

} // namespace unise
