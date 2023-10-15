#include "building.h"

#include <map>
#include <string>

std::map<std::string, building::metainfo> g_building_info;

building::metainfo &building::get_info(pcstr type) {
    return g_building_info[type];
}
