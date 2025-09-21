#include "sound_walker.h"

#include <unordered_set>
#include <string>

#include "js/js_game.h"

std::unordered_set<figure_sound_t> g_walker_reaction;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_walker_sounds) {
    g_walker_reaction.clear();
    g_config_arch.r("walker_sounds", g_walker_reaction);
}

xstring snd::get_walker_reaction(xstring reaction) {
    auto it = std::find_if(g_walker_reaction.begin(), g_walker_reaction.end(), [reaction] (auto &it) {
        return it.key == reaction;
    });

    return (it == g_walker_reaction.end()) ? xstring() : it->sound;
}

void figure_sounds_t::load(archive arch, pcstr section) {
    sounds.clear();
    arch.r(section, sounds);
}
