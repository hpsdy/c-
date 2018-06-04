#include "unise/search_context.h"
#include "unise/general_servlet.pb.h"
#include "unise/base.h"
#include "unise/util.h"

#include "unise/general_servlet.pb.h"
#include "unise/topfeed.pb.h"

#include "article_search_context.h"

namespace unise {

void ArticleSearchContext::init_for_search_internal(const GeneralSearchRequest *request)
{
    uint64_t sample_id = SearchContext::get_sample_id();

    if (sample_id == 1L) {
        // topfeed
        std::string log_id;
        std::string cuid;
        int64_t uid = 0;

        _topfeedCityId = 0L;

        if (request->has_topfeed()) {
            const TopfeedRequest &topfeed = request->topfeed();

            if (topfeed.has_log_id()) {
                log_id = topfeed.log_id();
            }
            if (topfeed.has_cuid()) {
                cuid = topfeed.cuid();
            }
            if (topfeed.has_passport_uid()) {
                uid = topfeed.passport_uid();
            }

            if (topfeed.has_city_id()) {
                _topfeedCityId = topfeed.city_id();
            }
            if (topfeed.read_docs_size() > 0) {
                TopfeedReadType tmpRead;
                for (int i = 0; i < topfeed.read_docs_size(); ++i) {
                    tmpRead.insert(topfeed.read_docs(i));
                }
                std::swap(_topfeedRead, tmpRead);
            } else {
                _topfeedRead.clear();
            }
            if (topfeed.usercf_docs_size() > 0) {
                TopfeedUsercfType tmpUsercf;
                for (int i = 0; i < topfeed.usercf_docs_size(); ++i) {
                    tmpUsercf.insert(
                        std::pair<uint64_t, double>(
                            topfeed.usercf_docs(i).doc_id(),
                            topfeed.usercf_docs(i).weight()
                        )
                    );
                }
                std::swap(_topfeedUsercf, tmpUsercf);
            } else {
                _topfeedUsercf.clear();
            }
            if (topfeed.favor_cates_size() > 0) {
                TopfeedFavcateType tmpFavcate;
                for (int i = 0; i < topfeed.favor_cates_size(); ++i) {
                    tmpFavcate.insert(
                        std::pair<int32_t, double>(
                            topfeed.favor_cates(i).cate_id(),
                            topfeed.favor_cates(i).weight()
                        )
                    );
                }
                std::swap(_topfeedFavcate, tmpFavcate);
            } else {
                _topfeedFavcate.clear();
            }
        }
        char logStr[300];
        int logseize = sprintf(logStr,
            "RInitSeCtxS1: [logid:%s] [cuid:%s] [uid:%ld] [CityId:%ld] [Read:%ld] [Usercf:%ld] [Favcate:%ld]",
            log_id.c_str(),
            cuid.c_str(),
            uid,
            _topfeedCityId,
            _topfeedRead.size(),
            _topfeedUsercf.size(),
            _topfeedFavcate.size()
        );
        _logStr = logStr;
    }
}

class ArticleSearchContextFactory : public SearchContextFactory
{
public:
    ArticleSearchContextFactory() {}
    ~ArticleSearchContextFactory() {}

    virtual bool init(const comcfg::ConfigUnit &)
    {
        return true;
    }

    virtual SearchContext * produce()
    {
        return new ArticleSearchContext();
    }

    virtual void destroy(SearchContext *c)
    {
        delete c;
    }

    virtual std::string get_name()
    {
        return "ArticleSearchContextFactory";
    }
};

REGISTER_SEARCH_CONTEXT_FACTORY(ArticleSearchContextFactory);

} // namespace unise
