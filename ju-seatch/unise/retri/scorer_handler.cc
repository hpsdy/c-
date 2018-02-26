// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include <stdint.h>
#include "retri/scorer_handler.h"
#include <string>
#include "Configure.h"
#include "unise/scorer.h"
#include "unise/general_servlet.pb.h"
#include "unise/matched_doc.h"
#include "unise/search_context.h"
#include "util/util.h"
#include "index/repository_manager.h"
#include "retri/matched_doc_internal.h"

namespace unise {
using std::string;

ScorerHandler::ScorerHandler(const RepositoryManager & pm) : _repository_manager(pm) {}

ScorerHandler::~ScorerHandler() {
    for (UniseScorersMap::iterator it = _scorers_map.begin();
                it != _scorers_map.end(); ++it) {
        std::vector<Scorer*> & scorers = it->second;
        for (size_t i = 0; i < scorers.size(); ++i) {
            delete scorers.at(i);
        }
    }
}

// conf is EngineUnit conf
bool ScorerHandler::init(const comcfg::ConfigUnit& conf) {
    std::vector<std::pair<uint64_t, string> > plugins;
    bool missing_default = true;
    try {
        int num = conf["Scorers"].size();
        for (int i = 0; i < num; ++i) {
            uint64_t sample_id = conf["Scorers"][i]["sample_id"].to_uint64();
            string str(conf["Scorers"][i]["plugin"].to_cstr());
            plugins.push_back(std::make_pair(sample_id, str));
            UNOTICE("sample_id:%llu Scorers:%s", sample_id, str.c_str());
            if (sample_id == DEFAULT_SAMPLE_ID) {
                missing_default = false;
            }
        }
    } catch (comcfg::ConfigException & e) {
        UFATAL("illegal Configure for ScorerHandler:%s", e.what());
        return false;
    }

    if (missing_default) {
        UFATAL("missing sample_id 0 conf for Scorers");
        return false;
    }
    for (size_t idx = 0; idx < plugins.size(); ++idx) {
        vector<string> values;
        uint64_t sample_id = plugins.at(idx).first;
        string & str = plugins.at(idx).second;
        if (_scorers_map.find(sample_id) != _scorers_map.end()) {
            UFATAL("sample id:%ull conflict for Scorers", sample_id);
            return false;
        }
        string_split(str, ",", &values);
        vector<Scorer*> scorers;
        for (size_t i = 0; i < values.size(); ++i) {
            UNOTICE("Init Scorer:%s", values.at(i).c_str());
            Scorer * scorer = ScorerFactory::get_instance(values.at(i));
            if (scorer == NULL) {
                UFATAL("GetInstance failed:%s", values.at(i).c_str());
                return false;
            } else if (scorer->basic_init(&_repository_manager, conf["Scorers"][idx]) == false) {
                UFATAL("init failed:%s", values.at(i).c_str());
                delete scorer;
                return false;
            } else {
                scorers.push_back(scorer);
            }
        }
        _scorers_map.insert(std::make_pair(sample_id, scorers));
    }
    return true;
}

void ScorerHandler::init_for_search(const GeneralSearchRequest* request,
                                    SearchContext * context) {
    UniseScorersMap::iterator it = _scorers_map.find(context->get_sample_id());
    if (it == _scorers_map.end()) {
        it = _scorers_map.find(DEFAULT_SAMPLE_ID);
        GOOGLE_DCHECK(it != _scorers_map.end());
    }

    _cur_scorers = &(it->second);
    for (size_t i = 0; i < _cur_scorers->size(); ++i) {
        Scorer * scorer = _cur_scorers->at(i);
        scorer->init_for_search(request, context);
    }
}

void ScorerHandler::score(MatchedDoc * doc) {
    dynamic_score_t score = 0;
    // use int64_t
    dynamic_score_t sum = 0;
    for (size_t i = 0; i < _cur_scorers->size(); ++i) {
        // reset the score, if the scorer miss to set the score
        score = 0;
        Scorer * scorer = _cur_scorers->at(i);
        if (scorer->score(doc, &score)) {
            sum += score;
        }
    }
    (down_cast<MatchedDocInternal*>(doc))->set_score(sum);
}


void ScorerHandler::end_for_search(GeneralSearchResponse * response) {
    PluginResponse pr;
    for (size_t i = 0; i < _cur_scorers->size(); ++i) {
        Scorer * scorer = _cur_scorers->at(i);
        pr.Clear();
        pr.set_enable(false);
        scorer->end_for_search(&pr);
        if (pr.enable()) {
            response->add_plugin_responses()->CopyFrom(pr);
        }
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=80: */
