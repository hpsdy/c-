#include "topfeed_filler.h"
#include "unise/factory.h"

namespace unise {

void TopfeedFiller::fill_search_result(MatchedDoc *result, SearchResult *search_result) const
{
    const ArticleDoc *doc = dynamic_cast<const ArticleDoc *>(
        get_dimension_doc(
            "ArticleDoc",
            result->get_doc_id()
        )
    );

    if (doc == NULL) {
        return;
    }

    Snippet *snippet;

    snippet = search_result->add_snippets();
    snippet->set_key("id");
    snippet->set_value(Int64ToString(doc->_column_id));

    snippet = search_result->add_snippets();
    snippet->set_key("resource_id");
    snippet->set_value(Uint64ToString(doc->_resource_id));

    snippet = search_result->add_snippets();
    snippet->set_key("title");
    snippet->set_value(doc->_title);

    snippet = search_result->add_snippets();
    snippet->set_key("image_url");
    snippet->set_value(doc->_image_url);

    snippet = search_result->add_snippets();
    snippet->set_key("source");
    snippet->set_value(doc->_source);
}

void TopfeedFiller::end_for_search(PluginResponse *plugin_response)
{
    ArticleSearchContext *_articleContext = dynamic_cast<ArticleSearchContext *>(_context);
    ArticleSearchContext::TopfeedTriggerType  _topfeedTrigger = _articleContext->_topfeedTrigger;
    Experiment *exper;
    if(!_topfeedTrigger.empty())
    {
        for(ArticleSearchContext::TopfeedTriggerType::iterator p = _topfeedTrigger.begin(); p != _topfeedTrigger.end(); ++p)
        {
            exper = plugin_response->add_trigger_type();
            uint64_t docid = p->first;
            std::stringstream tmpss;
            std::string docStrid;
            tmpss << docid;
            docStrid = tmpss.str();
            std::string desc = p->second;
            exper->set_key(docStrid)
            exper->set_value(desc);
        }
    }
    std::string logStr = _articleContext->_logStr;
    plugin_response->set_context_log(logStr);

    plugin_response->set_name(get_name());
    plugin_response->set_enable(true);
    plugin_response->set_information("plugin time " + get_date(get_timestamp()));
}

REGISTER_RESULT_FILLER(TopfeedFiller);

}
