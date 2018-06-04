#ifndef  _TOPFEED_SCORER_H_
#define  _TOPFEED_SCORER_H_

#include "unise/scorer.h"
#include "Configure.h"

#include "ju-search/article_search_context.h"
#include "time.h"

namespace unise {

class MatchedDoc;
class GeneralSearchRequest;
class SearchContext;
class PluginResponse;

class TopfeedScorer : public Scorer
{
public:
    TopfeedScorer() {}
    virtual ~TopfeedScorer() {}

    virtual bool init(const comcfg::ConfigUnit &conf)
    {
        (void)(conf);
        return true;
    }

    virtual void init_for_search(const GeneralSearchRequest *request, SearchContext *context);
    virtual bool score(MatchedDoc *doc, dynamic_score_t *score);

    virtual std::string get_name() const
    {
        return "TopfeedScorer";
    }

private:
    ArticleSearchContext *_context;
    double caculate_time_score(int publish_time);

    int64_t _usercfFactor;
    int64_t _favcateFactor;
    int64_t _cityhotFactor;
    int64_t _pubtimeFactor;

};

} // namespace unise

#endif  // _TOPFEED_SCORER_H_
