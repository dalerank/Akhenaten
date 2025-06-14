#include "sound_building.h"

#include <map>
#include <string>

#include "js/js_game.h"

std::map<e_building_type, xstring> g_building_sounds;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_building_sounds) {
    g_config_arch.r_array("building_sounds", [] (archive arch) {
        e_building_type type = arch.r_type<e_building_type>("type");
        pcstr path = arch.r_string("sound");
        g_building_sounds[type] = path;
    });
}

xstring snd::get_building_info_sound(e_building_type type) {
    auto it = g_building_sounds.find(type);

    static xstring empty_sound = "Wavs/empty.wav";
    return (it == g_building_sounds.end()) ? empty_sound : it->second;
}