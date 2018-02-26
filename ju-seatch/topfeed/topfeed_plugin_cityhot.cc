#include "topfeed_plugin_cityhot.h"

#include <sstream>
#include <fstream>

#include "util/util.h"

DEFINE_string(cityhot_fullpath, "./data/cityhot.dat", "city hot article path");

namespace unise {

void TopfeedPluginCityhot::reload()
{
    std::ifstream ifs(FLAGS_cityhot_fullpath.c_str(), std::ios::in);
    if (!ifs) {
        UWARNING("Cannot open cityhot file %s.", FLAGS_cityhot_fullpath.c_str());
        return;
    }

    char buf[1024];
    buf[1023] = '\0';

    int cnt = 0;
    CityFeedWeightMap tmpMap;

    while (ifs.getline(buf, 1023)) {
        uint64_t source_id = 0;
        int64_t city_id = 0;
        double weight = 0.0;

        std::istringstream(buf) >> source_id >> city_id >> weight;

        if (source_id && city_id && weight) {
            if (tmpMap.find(city_id) == tmpMap.end()) {
                tmpMap.insert(std::pair<int64_t, FeedWeightMap>(city_id, FeedWeightMap()));
            }
            FeedWeightMap &fw = tmpMap[city_id];
            if (fw.find(source_id) == fw.end()) {
                fw.insert(std::pair<uint64_t, double>(source_id, weight));
                ++cnt;
            }
        }
    }

    std::swap(_map, tmpMap);

    UNOTICE("Loaded cityhot items: %d", cnt);
}

} // namespace unise
