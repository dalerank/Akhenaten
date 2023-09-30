#include "sound_walker.h"

#include <map>
#include <string>

std::map<std::string, vfs::path> g_walker_reaction;

void snd::set_walker_reaction(pcstr reaction, pcstr sound) {
    g_walker_reaction[reaction] = sound;
}

vfs::path snd::get_walker_reaction(pcstr reaction) {
    auto it = g_walker_reaction.find(reaction);

    return (it == g_walker_reaction.end()) ? vfs::path() : it->second;
}