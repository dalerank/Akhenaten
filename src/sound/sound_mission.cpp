#include "sound_mission.h"

#include <unordered_set>

#include "js/js_game.h"

std::unordered_set<snd::mission_config> ANK_VARIABLE(mission_sounds);

snd::mission_config snd::get_mission_config(int mission) {
    auto it = mission_sounds.find({ mission });

    return (it == mission_sounds.end()) ? mission_config() : *it;
}