#ifndef _TOPFEED_PLUGIN_CITYHOT_H_
#define _TOPFEED_PLUGIN_CITYHOT_H_

#include "unise/base.h"

#include <map>
#include <vector>

namespace unise {

class TopfeedPluginCityhot
{
public:
    typedef std::map<uint64_t, double> FeedWeightMap;
    typedef std::map<int64_t, FeedWeightMap > CityFeedWeightMap;

public:
    TopfeedPluginCityhot() {}
    virtual ~TopfeedPluginCityhot() {}

    void reload();

    const FeedWeightMap &getByCity(int64_t cityid) const
    {
        CityFeedWeightMap::const_iterator iter = _map.find(cityid);
        if (iter != _map.end()) {
            return iter->second;
        }

        return _emptyFeedWeightMap;
    }

private:
    CityFeedWeightMap _map;
    FeedWeightMap _emptyFeedWeightMap;
};

} // namespace unise

#endif // _TOPFEED_PLUGIN_CITYHOT_H_
