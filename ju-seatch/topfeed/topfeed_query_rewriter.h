#ifndef _TOPFEED_QUERY_REWRITER_H_
#define _TOPFEED_QUERY_REWRITER_H_

#include <string>
#include "util/util.h"
#include "Configure.h"
#include "unise/query_rewriter.h"

namespace unise {

class TopfeedQueryRewriter : public QueryRewriter
{

public:
    TopfeedQueryRewriter() {}
    virtual ~TopfeedQueryRewriter() {}

    virtual bool init(const comcfg::ConfigUnit &)
    {
        return true;
    }

    virtual void rewrite_internal(GeneralSearchRequest *req);

    virtual std::string get_name() const
    {
        return "TopfeedQueryRewriter";
    }
};

} // namespace unise

#endif // _TOPFEED_QUERY_REWRITER_H_
