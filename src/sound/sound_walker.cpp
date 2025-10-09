#include "sound_walker.h"

#include "js/js_game.h"

figure_sounds_map ANK_VARIABLE(walker_sounds)

xstring snd::get_walker_reaction(xstring reaction) {
    auto it = walker_sounds.find(reaction);
    return (it == walker_sounds.end()) ? xstring() : it->second.sound;
}
