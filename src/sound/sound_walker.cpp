#include "sound_walker.h"

#include <map>
#include <string>

std::map<std::string, bstring64> g_walker_reaction;

void snd::set_walker_reaction(pcstr reaction, pcstr sound) {
    g_walker_reaction[reaction] = sound;
}

bstring64 snd::get_walker_reaction(pcstr reaction) {
    auto it = g_walker_reaction.find(reaction);

    return (it == g_walker_reaction.end()) ? bstring64() : it->second;
}