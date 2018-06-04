// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  RETRI_SCORER_HANDLER_H_
#define  RETRI_SCORER_HANDLER_H_

#include <vector>
#include <map>

namespace comcfg {
class ConfigUnit;
}

namespace unise {
class GeneralSearchRequest;
class GeneralSearchResponse;
class MatchedDoc;
class Scorer;
class RepositoryManager;
class SearchContext;

class ScorerHandler {
public:
    explicit ScorerHandler(const RepositoryManager & pm);
    virtual ~ScorerHandler();

    // conf is EngineUnit conf
    bool init(const comcfg::ConfigUnit& conf);
    void init_for_search(const GeneralSearchRequest* request, SearchContext * context);
    void score(MatchedDoc * doc);
    void end_for_search(GeneralSearchResponse * response);

private:
    typedef std::map<uint64_t, std::vector<Scorer*> > UniseScorersMap;
    UniseScorersMap _scorers_map;
    std::vector<Scorer*> * _cur_scorers;
    const RepositoryManager & _repository_manager;
};
}

#endif  // RETRI_SCORER_HANDLER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
