#include "sound_building.h"

#include "building/building_static_params.h"

xstring snd::get_building_info_sound(e_building_type type) {
    return building_static_params::get(type).info_sound;
}
