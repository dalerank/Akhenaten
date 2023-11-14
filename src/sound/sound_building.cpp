#include "sound_building.h"

#include <map>
#include <string>

#include "js/js_game.h"

std::map<std::string, vfs::path> g_building_sounds;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_sounds);
void config_load_building_sounds(archive arch) {
    arch.load_global_array("building_sounds", [] (archive arch) {
        const char *type = arch.read_string("type");
        const char *path = arch.read_string("sound");
        g_building_sounds[type] = path;
    });
}

vfs::path snd::get_building_info_sound(pcstr type) {
    auto it = g_building_sounds.find(type);

    return (it == g_building_sounds.end()) ? vfs::path() : it->second;
}