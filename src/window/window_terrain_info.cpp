#include "window_terrain_info.h"

#include "city/object_info.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/property.h"
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
    window_building_draw_description_at(c, 16 * c->bgsize.y - 144, 141, c->aqueduct_has_water ? 1 : 2);
}

void window_building_draw_rubble(object_info* c) {
    c->help_id = 0;
    window_building_play_sound(c, "Wavs/ruin.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(140, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw(41, c->rubble_building_type, c->offset.x + 32, c->offset.y + 16 * c->bgsize.y - 173, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_multiline(140, 1, c->offset + vec2i{32, 16 * c->bgsize.y - 143}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}

void window_building_draw_wall(object_info& c) {
    window_building_play_sound(&c, "Wavs/wall.wav");

    auto& ui = *c.ui;

    ui["title"] = ui::str(139, 0);
    ui["describe"] = ui::str(139, 1);
}

void terrain_info_window::window_info_background(object_info &c) {
}

void terrain_info_window::init(object_info &c) {
    common_info_window::init(c);

    textid reason;
    textid describe;
    svector<pcstr, 16> sounds;

    switch (c.terrain_type) {
    case TERRAIN_INFO_ROAD:
        c.help_id = 57;
        reason = { 28, 5 };
        describe = { 70, 42 };
        break;

    case TERRAIN_INFO_AQUEDUCT:
        c.help_id = 60;
        window_building_draw_aqueduct(&c);
        break;

    case TERRAIN_INFO_WALL:
        c.help_id = 85;
        window_building_draw_wall(c);
        break;

    case TERRAIN_INFO_BRIDGE:
        c.help_id = 58;
        break;

    case TERRAIN_INFO_RUBBLE:
        window_building_draw_rubble(&c);
        break;

    case TERRAIN_INFO_PLAZA:
        building_plaza::draw_info(c);
        break;

    case TERRAIN_INFO_ORE_ROCK:
        sounds = { "wavs/rock1.wav", "wavs/rock2.wav", "wavs/rock3.wav", "wavs/rock4.wav", "wavs/rock5.wav" };
        reason = { 70, 26 };
        describe = { 70, 38};
        c.help_id = 191;

    case TERRAIN_INFO_ROCK:
        sounds = { "wavs/rock1.wav", "wavs/rock2.wav", "wavs/rock3.wav", "wavs/rock4.wav", "wavs/rock5.wav" };
        reason = { 70, 12 };
        describe = { 70, 38 };
        c.help_id = 191;
        break;

    case TERRAIN_INFO_FLOODPLAIN:
        reason = { 70, 29 };
        describe = { 70, 55 };
        c.help_id = 45;
        break;

    default:
        sounds.push_back("Wavs/empty_land.wav");
        reason = { 70, 20 };
        describe = { 70, 42 };
        break;
    }

    if (c.can_play_sound) {
        c.can_play_sound = 0;
        pcstr sound = sounds[rand() % sounds.size()];
        g_sound.speech_play_file(sound, 255);
    }

    ui["title"] = ui::str(reason);
    ui["describe"] = ui::str(describe);
}

int terrain_info_window::get_height_id(object_info &c) {
    switch (c.terrain_type) {
    case TERRAIN_INFO_AQUEDUCT:
        return 4;
    case TERRAIN_INFO_RUBBLE:
    case TERRAIN_INFO_WALL:
    case TERRAIN_INFO_GARDEN:
        return 1;
    default:
        return 5;
    }
}

bool terrain_info_window::check(object_info &c) {
    if (!c.building_id && map_sprite_animation_at(c.grid_offset) > 0) {
        if (map_terrain_is(c.grid_offset, TERRAIN_WATER)) {
            c.terrain_type = TERRAIN_INFO_BRIDGE;
        } else {
            c.terrain_type = TERRAIN_INFO_EMPTY;
        }
        return true;
    } else if (map_property_is_plaza_or_earthquake(c.grid_offset)) {
        if (map_terrain_is(c.grid_offset, TERRAIN_ROAD)) {
            c.terrain_type = TERRAIN_INFO_PLAZA;
        }

        if (map_terrain_is(c.grid_offset, TERRAIN_ROCK)) {
            c.terrain_type = TERRAIN_INFO_EARTHQUAKE;
        }

    } else if (map_terrain_is(c.grid_offset, TERRAIN_TREE)) {
        c.terrain_type = TERRAIN_INFO_TREE;

    } else if (!c.building_id && map_terrain_is(c.grid_offset, TERRAIN_FLOODPLAIN)) {
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
        c.terrain_type = TERRAIN_INFO_AQUEDUCT;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_RUBBLE)) {
        c.terrain_type = TERRAIN_INFO_RUBBLE;

    } else if (map_terrain_is(c.grid_offset, TERRAIN_WALL)) {
        c.terrain_type = TERRAIN_INFO_WALL;
    }

    return (c.terrain_type != TERRAIN_INFO_NONE);
}
