#include "window_terrain_info.h"

#include "city/object_info.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/canals.h"
#include "grid/image.h"
#include "sound/sound.h"
#include "building/building_garden.h"
#include "building/building_plaza.h"
#include "building/building_irrigation_ditch.h"
#include "window/building/common.h"
#include "window_figure_info.h"
#include "city/city.h"

void window_building_draw_canal(object_info* c) {
    c->help_id = 60;
    window_building_play_sound(c, "Wavs/aquaduct.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(141, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    int water_start_image = building_irrigation_ditch::images().begin;
    bool canal_has_water = !!map_canal_at(c->grid_offset) && ((map_image_at(c->grid_offset) - water_start_image) < 15);
    window_building_draw_description_at(c, 16 * c->bgsize.y - 144, 141, canal_has_water ? 1 : 2);
}

void terrain_info_window::window_info_background(object_info &c) {
    update_buttons(c);
}

void terrain_info_window::update(object_info &c) {
    xstring terrain_config =  terrain_info_type_tokens.name(c.terrain_type);

    ui.load(terrain_config.c_str());
    c.help_id = io.r_int("help_id");
}

void terrain_info_window::init(object_info &c) {
    common_info_window::init(c);

    bvariant_map event_data;
    event_data["pos"] = bvariant(pos);
    event_data["terrain_type"] = bvariant(c.terrain_type);

    auto type_str = terrain_info_type_tokens.name(c.terrain_type);
    bstring64 init_event_name(type_str, "_init");
    ui.event(init_event_name.c_str(), event_data);

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
    case terrain_info_plaza:
    case terrain_info_ore_rock:
    case terrain_info_rock:
    case terrain_info_floodplain:
    case terrain_info_garden:
    case terrain_info_water:
        break;

    case terrain_info_canal:
        c.help_id = 60;
        window_building_draw_canal(&c);
        break;

    case terrain_info_bridge:
        c.help_id = 58;
        break;
    }

    if (c.can_play_sound) {
        c.can_play_sound = 0;
        if (sounds.size() > 0) {
            xstring sound = sounds[rand() % sounds.size()];
            g_sound.speech_play_file(sound, 255);
        }
    }
}

bool terrain_info_window::check(object_info &c) {
    tile2i tile(c.grid_offset);
    if (!c.bid && map_sprite_animation_at(c.grid_offset) > 0) {
        if (map_terrain_is(c.grid_offset, TERRAIN_WATER)) {
            c.terrain_type = terrain_info_bridge;
        } else {
            c.terrain_type = terrain_info_empty;
        }
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
        c.terrain_type = terrain_info_wall;
    }

    return (c.terrain_type != terrain_info_none);
}
