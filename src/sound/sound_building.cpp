#include "sound_building.h"

#include <map>
#include <string>

std::map<std::string, vfs::path> g_building_sounds;

void snd::set_building_info_sound(pcstr type, pcstr sound) {
    g_building_sounds[type] = sound;
}

vfs::path snd::get_building_info_sound(pcstr type) {
    auto it = g_building_sounds.find(type);

    return (it == g_building_sounds.end()) ? vfs::path() : it->second;
}