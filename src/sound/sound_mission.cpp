#include "sound_mission.h"

#include <map>

std::map<int, snd::mission_config> g_mission_configs;

void snd::set_mission_config(int mission, pcstr inter, pcstr won) {
    g_mission_configs[mission] = {inter, won};
}

snd::mission_config snd::get_mission_config(int mission) {
    auto it = g_mission_configs.find(mission);

    return (it == g_mission_configs.end()) ? mission_config() : it->second;
}