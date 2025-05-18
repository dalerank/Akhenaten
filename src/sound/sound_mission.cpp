#include "sound_mission.h"

#include <map>

#include "js/js_game.h"

std::map<int, snd::mission_config> g_mission_configs;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_mission_sounds) {
    g_config_arch.r_array("mission_sounds", [] (archive arch) {
        const int mission = arch.r_int("mission");
        const char *inter = arch.r_string("briefing");
        const char *won = arch.r_string("victory");
        g_mission_configs[mission] = {inter, won};
    });
}

snd::mission_config snd::get_mission_config(int mission) {
    auto it = g_mission_configs.find(mission);

    return (it == g_mission_configs.end()) ? mission_config() : it->second;
}