#include "window_terrain_info.h"

#include "city/object_info.h"
#include "grid/bridge.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/wall_material.h"
#include "sound/sound.h"
#include "window/building/common.h"
#include "window/message_dialog.h"
#include "city/city.h"

void terrain_info_window::window_info_background(object_info &c) {
    update_buttons(c);

    ui_scope_property holder;
    ui.format_all(&holder);
}

void terrain_info_window::update(object_info &c) {
}

void terrain_info_window::init(object_info &c) {
    common_info_window::init(c);

    xstring terrain_config = terrain_info_type_tokens.name(c.terrain_type);
    ui.load(terrain_config.c_str());

    if (c.can_play_sound && !open_sounds.empty()) {
        c.can_play_sound = 0;
        const xstring &wav = open_sounds[rand() % open_sounds.size()];
        window_building_play_sound(&c, wav.c_str());
    }

    auto type_str = terrain_info_type_tokens.name(c.terrain_type);
    bstring64 init_event_name(type_str, "_init");
    ui.begin_widget(pos);
    ui.event(xstring(init_event_name), {
        { "pos", pos },
        { "terrain_type", c.terrain_type },
        { "grid_offset", c.grid_offset }
    });
    ui.end_widget();

    textid reason;
    textid describe;
    svector<xstring, 16> sounds;

    switch (c.terrain_type) {
    default:
        sounds.push_back("Wavs/empty_land.wav");
        reason = { 70, 20 };
        describe = { 70, 42 };

        ui["title"] = ui::str(reason);
        ui["describe"] = ui::str(describe);
        break;

    case terrain_info_road:
    case terrain_info_wall:
    case terrain_info_mud_wall:
    case terrain_info_brick_wall:
    case terrain_info_dike:
    case terrain_info_plaza:
    case terrain_info_ore_rock:
    case terrain_info_rock:
    case terrain_info_floodplain:
    case terrain_info_floodplain_submerged:
    case terrain_info_garden:
    case terrain_info_water:
    case terrain_info_rubble:
    case terrain_info_bridge:
    case terrain_info_canal:
    case terrain_info_tree:
        break;
    }

    if (c.can_play_sound) {
        c.can_play_sound = 0;
        if (sounds.size() > 0) {
            xstring sound = sounds[rand() % sounds.size()];
            g_sound.speech_play_file(sound, 255);
        }
    }

    xstring help = io.r_string("help_id");
    if (!help.empty()) {
        c.help_link = help;
        c.help_id = 0;
    } else {
        c.help_link = {};
        c.help_id = 0;
        help = "message_dialog_help";
    }
    window_message_setup_help_id(help);
}

bool terrain_info_window::check(object_info &c) {
    tile2i tile(c.grid_offset);
    if (!c.bid && map_is_bridge(c.grid_offset)) {
        c.terrain_type = terrain_info_bridge;
        return true;
    } else if (map_property_is_plaza_or_earthquake(tile)) {
        if (map_terrain_is(c.grid_offset, TERRAIN_ROAD)) {
            c.terrain_type = terrain_info_plaza;
        }

        if (map_terrain_is(c.grid_offset, TERRAIN_ROCK)) {
            c.terrain_type = terrain_info_earthquake;
        }

    } else if (map_terrain_is(c.grid_offset, TERRAIN_TREE)) {
        c.terrain_type = terrain_info_tree;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_DIKE)) {
        // Before FLOODPLAIN/ROAD: bare crest and sluice both identify as dike.
        c.terrain_type = terrain_info_dike;

    } else if (!c.bid && map_terrain_is(c.grid_offset, TERRAIN_FLOODPLAIN)) {
        if (map_terrain_is(c.grid_offset, TERRAIN_WATER)) {
            c.terrain_type = terrain_info_floodplain_submerged;
        } else if (map_terrain_is(c.grid_offset, TERRAIN_ROAD)) {
            c.terrain_type = terrain_info_road;
        } else {
            c.terrain_type = terrain_info_floodplain;
        }

    } else if (map_terrain_is(c.grid_offset, TERRAIN_MARSHLAND)) {
        c.terrain_type = terrain_info_marshland;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_DUNE)) {
        c.terrain_type = terrain_info_dunes;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_ROCK)) {
        if (c.grid_offset == g_city.map.entry_flag.grid_offset()) {
            c.terrain_type = terrain_info_entry_flag;
        } else if (c.grid_offset == g_city.map.exit_flag.grid_offset()) {
            c.terrain_type = terrain_info_exit_flag;
        } else {
            if (map_terrain_is(c.grid_offset, TERRAIN_ORE)) {
                c.terrain_type = terrain_info_ore_rock;
            } else {
                c.terrain_type = terrain_info_rock;
            }
        }
    } else if ((map_terrain_get(c.grid_offset) & (TERRAIN_WATER | TERRAIN_BUILDING)) == TERRAIN_WATER) {
        c.terrain_type = terrain_info_water;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_SHRUB)) {
        c.terrain_type = terrain_info_shrub;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_GARDEN)) {
        c.terrain_type = terrain_info_garden;

    } else if ((map_terrain_get(c.grid_offset) & (TERRAIN_ROAD | TERRAIN_BUILDING)) == TERRAIN_ROAD) {
        c.terrain_type = terrain_info_road;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_CANAL)) {
        c.terrain_type = terrain_info_canal;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_WALL)) {
        const e_wall_material material = map_wall_material_at(c.grid_offset);
        c.terrain_type = (material == WALL_MATERIAL_BRICK) ? terrain_info_brick_wall : terrain_info_mud_wall;

    } else if (!c.bid && map_terrain_is(c.grid_offset, TERRAIN_RUBBLE)) {
        c.terrain_type = terrain_info_rubble;
    }

    return (c.terrain_type != terrain_info_none);
}
