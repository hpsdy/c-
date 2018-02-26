#include "topfeed_early_filter.h"

namespace unise {

result_status_t TopfeedEarlyFilter::filter(MatchedDoc *result)
{
    DocId docid = result->get_doc_id();

    if (_context != NULL && _context->_topfeedRead.find(docid) != _context->_topfeedRead.end()) {
        return RESULT_FILTED_EARLY;
    }

    return RESULT_ACCEPTED;
}

REGISTER_RESULT_FILTER(TopfeedEarlyFilter);

} // namespace unise
