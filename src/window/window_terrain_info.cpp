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
#include "building/building_plaza.h"
#include "window/building/common.h"
#include "window_figure_info.h"
#include "city/city.h"

void window_building_draw_aqueduct(object_info* c) {
    c->help_id = 60;
    window_building_play_sound(c, "Wavs/aquaduct.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(141, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    bool canal_has_water = !!map_canal_at(c->grid_offset) && ((map_image_at(c->grid_offset) - image_id_from_group(GROUP_BUILDING_CANAL)) < 15);
    window_building_draw_description_at(c, 16 * c->bgsize.y - 144, 141, canal_has_water ? 1 : 2);
}

void terrain_info_window::window_info_background(object_info &c) {
    update_buttons(c);
}

void terrain_info_window::update(object_info &c) {
    xstring terrain_config = "terrain_info_window";

    switch (c.terrain_type) {
    case TERRAIN_INFO_ROAD: terrain_config = "terrain_road_info_window"; break;
    case TERRAIN_INFO_WALL: terrain_config = "terrain_wall_info_window"; break;
    case TERRAIN_INFO_PLAZA: terrain_config = "terrain_plaza_info_window"; break;
    case TERRAIN_INFO_ORE_ROCK: terrain_config = "terrain_orerock_info_window"; break;
    case TERRAIN_INFO_ROCK: terrain_config = "terrain_rock_info_window"; break;
    case TERRAIN_INFO_FLOODPLAIN: terrain_config = "terrain_floodplain_info_window"; break;
    default:
        break;
    }

    ui.load(terrain_config.c_str());
    c.help_id = io.r_int("help_id");
}

void terrain_info_window::init(object_info &c) {
    common_info_window::init(c);

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

    case TERRAIN_INFO_ROAD:
    case TERRAIN_INFO_WALL:
    case TERRAIN_INFO_PLAZA:
    case TERRAIN_INFO_ORE_ROCK:
    case TERRAIN_INFO_ROCK:
    case TERRAIN_INFO_FLOODPLAIN:
        break;

    case TERRAIN_INFO_CANAL:
        c.help_id = 60;
        window_building_draw_aqueduct(&c);
        break;

    case TERRAIN_INFO_BRIDGE:
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
            c.terrain_type = TERRAIN_INFO_BRIDGE;
        } else {
            c.terrain_type = TERRAIN_INFO_EMPTY;
        }
        return true;
    } else if (map_property_is_plaza_or_earthquake(tile)) {
        if (map_terrain_is(c.grid_offset, TERRAIN_ROAD)) {
            c.terrain_type = TERRAIN_INFO_PLAZA;
        }

        if (map_terrain_is(c.grid_offset, TERRAIN_ROCK)) {
            c.terrain_type = TERRAIN_INFO_EARTHQUAKE;
        }

    } else if (map_terrain_is(c.grid_offset, TERRAIN_TREE)) {
        c.terrain_type = TERRAIN_INFO_TREE;

    } else if (!c.bid && map_terrain_is(c.grid_offset, TERRAIN_FLOODPLAIN)) {
        if (map_terrain_is(c.grid_offset, TERRAIN_WATER)) {
            c.terrain_type = TERRAIN_INFO_FLOODPLAIN_SUBMERGED;
        } else if (map_terrain_is(c.grid_offset, TERRAIN_ROAD)) {
            c.terrain_type = TERRAIN_INFO_ROAD;
        } else {
            c.terrain_type = TERRAIN_INFO_FLOODPLAIN;
        }

    } else if (map_terrain_is(c.grid_offset, TERRAIN_MARSHLAND)) {
        c.terrain_type = TERRAIN_INFO_MARSHLAND;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_DUNE)) {
        c.terrain_type = TERRAIN_INFO_DUNES;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_ROCK)) {
        if (c.grid_offset == g_city.map.entry_flag.grid_offset()) {
            c.terrain_type = TERRAIN_INFO_ENTRY_FLAG;
        } else if (c.grid_offset == g_city.map.exit_flag.grid_offset()) {
            c.terrain_type = TERRAIN_INFO_EXIT_FLAG;
        } else {
            if (map_terrain_is(c.grid_offset, TERRAIN_ORE)) {
                c.terrain_type = TERRAIN_INFO_ORE_ROCK;
            } else {
                c.terrain_type = TERRAIN_INFO_ROCK;
            }
        }
    } else if ((map_terrain_get(c.grid_offset) & (TERRAIN_WATER | TERRAIN_BUILDING)) == TERRAIN_WATER) {
        c.terrain_type = TERRAIN_INFO_WATER;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_SHRUB)) {
        c.terrain_type = TERRAIN_INFO_SHRUB;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_GARDEN)) {
        c.terrain_type = TERRAIN_INFO_GARDEN;

    } else if ((map_terrain_get(c.grid_offset) & (TERRAIN_ROAD | TERRAIN_BUILDING)) == TERRAIN_ROAD) {
        c.terrain_type = TERRAIN_INFO_ROAD;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_CANAL)) {
        c.terrain_type = TERRAIN_INFO_CANAL;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_WALL)) {
        c.terrain_type = TERRAIN_INFO_WALL;
    }

    return (c.terrain_type != TERRAIN_INFO_NONE);
}
