#include "sound_mission.h"

#include <unordered_set>

#include "js/js_game.h"

std::unordered_set<snd::mission_config> g_mission_configs;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_mission_sounds) {
    g_config_arch.r("mission_sounds", g_mission_configs);
}

snd::mission_config snd::get_mission_config(int mission) {
    auto it = g_mission_configs.find({ mission });

    return (it == g_mission_configs.end()) ? mission_config() : *it;
}