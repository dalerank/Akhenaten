#include "window_ruin_info.h"

#include "sound/sound.h"
#include "city/object_info.h"
#include "grid/building.h"
#include "window/building/common.h"

info_window_burning_ruin burning_ruin_infow;

void ruin_info_window::init(object_info &c) {
    if (!open_sounds.empty()) {
        const xstring &wav = open_sounds[rand() % open_sounds.size()];
        window_building_play_sound(&c, wav.c_str());
    }

    int rubble_building_type = map_rubble_building_type(c.grid_offset);
    ui["warning_text"] = textid{ 41, (uint8_t)rubble_building_type };

    ui.format_all(&g_city);
}

void info_window_burning_ruin::init(object_info &c) {
    if (!open_sounds.empty()) {
        const xstring &wav = open_sounds[rand() % open_sounds.size()];
        window_building_play_sound(&c, wav.c_str());
    }

    int rubble_building_type = map_rubble_building_type(c.grid_offset);
    ui["warning_text"] = textid{ 41, (uint8_t)rubble_building_type };
}

bool info_window_burning_ruin::check(object_info &c) {
    return c.building_get()->dcast_burning_ruin();
}