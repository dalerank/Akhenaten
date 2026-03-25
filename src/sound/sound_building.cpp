#include "sound_building.h"

#include "building/building_static_params.h"

xstring snd::get_building_info_sound(e_building_type type) {
    static xstring empty_sound = "Wavs/empty.wav";
    const xstring &path = building_static_params::get(type).info_sound;
    return path.empty() ? empty_sound : path;
}
