#ifndef _ARTICLE_SEARCH_CONTEXT_H_
#define _ARTICLE_SEARCH_CONTEXT_H_

#include <set>
#include <map>
#include <string>
#include <Configure.h>
#include "unise/factory.h"
#include "unise/search_context.h"

namespace unise {

class GeneralSearchRequest;

class ArticleSearchContext : public SearchContext
{
public:
    ArticleSearchContext() {}
    virtual ~ArticleSearchContext() {}

    virtual void init_for_search_internal(const GeneralSearchRequest* request);

    typedef std::set<uint64_t> TopfeedReadType;
    typedef std::map<uint64_t, double> TopfeedUsercfType;
    typedef std::map<int32_t, double> TopfeedFavcateType;
    typedef std::map<uint64_t , std::string> TopfeedTriggerType;

    int64_t _topfeedCityId;
    TopfeedReadType _topfeedRead;
    TopfeedUsercfType _topfeedUsercf;
    TopfeedFavcateType _topfeedFavcate;
    std::string _logStr; 
    TopfeedTriggerType  _topfeedTrigger;
};

} // namespace unise

#endif // _ARTICLE_SEARCH_CONTEXT_H_
