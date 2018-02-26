#ifndef  _TOPFEED_FILLER_H_
#define  _TOPFEED_FILLER_H_

#include <string>

#include "Configure.h"

#include "unise/matched_doc.h"
#include "unise/util.h"
#include "unise/search_context.h"
#include "unise/result_filler.h"

#include "article_doc.h"

namespace unise {

class TopfeedFiller : public ResultFiller
{
public:
    TopfeedFiller() {}
    virtual ~TopfeedFiller() {}

    virtual bool init(const comcfg::ConfigUnit &conf)
    {
        (void)(conf);
        return true;
    }

    virtual void init_for_search(const GeneralSearchRequest *request, SearchContext *context)
    {
        (void)(request);
        (void)(context);
    }

    virtual void fill_search_result(MatchedDoc *result, SearchResult *search_result) const;

    virtual void end_for_search(PluginResponse *plugin_response);

    virtual std::string get_name() const
    {
        return "TopfeedFiller";
    }
private:
    SearchContext *_context=0;

};

} // namespace unise

#endif  // _TOPFEED_FILLER_H_
