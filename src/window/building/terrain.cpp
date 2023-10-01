#include "terrain.h"

#include "government.h"
#include "military.h"
#include "utility.h"

#include "figure/figure.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "sound/speech.h"
#include "window/building/figures.h"
#include "building/building_garden.h"
#include "building/building_plaza.h"

void window_building_draw_no_people(object_info* c) {
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(70, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
}

void window_building_draw_terrain(object_info* c) {
    switch (c->terrain_type) {
    case TERRAIN_INFO_ROAD:
        c->help_id = 57;
        break;

    case TERRAIN_INFO_AQUEDUCT:
        c->help_id = 60;
        break;

    case TERRAIN_INFO_WALL:
        c->help_id = 85;
        break;

    case TERRAIN_INFO_BRIDGE:
        c->help_id = 58;
        break;

    default:
        c->help_id = 0;
        break;
    }

    if (c->terrain_type == TERRAIN_INFO_AQUEDUCT)
        window_building_draw_aqueduct(c);
    else if (c->terrain_type == TERRAIN_INFO_RUBBLE)
        window_building_draw_rubble(c);
    else if (c->terrain_type == TERRAIN_INFO_WALL)
        window_building_draw_wall(c);
    else if (c->terrain_type == TERRAIN_INFO_GARDEN)
        building_garden_draw_info(*c);
    else if (c->terrain_type == TERRAIN_INFO_PLAZA && c->figure.count <= 0)
        building_plaza_draw_info(*c);
    else {
        if (c->can_play_sound) {
            c->can_play_sound = 0;
            if (c->figure.count > 0) {
                window_building_play_figure_phrase(c);
            } else {
                sound_speech_play_file("wavs/empty_land.wav");
            }
        }

        if (c->figure.count > 0 && c->figure.figure_ids[c->figure.selected_index]) {
            figure* f = figure_get(c->figure.figure_ids[c->figure.selected_index]);
            if (f->type < FIGURE_SHIPWRECK)
                c->help_id = 42;
            else
                c->help_id = 330;
        }

        window_building_prepare_figure_list(c);
        outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);

        int text_id_offset = 0;
        text_id_offset = 36;
        c->figure.draw_debug_path = 1;

        if (!c->figure.count) {
            lang_text_draw_centered(70, c->terrain_type + 10, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
        }

        if (c->terrain_type != TERRAIN_INFO_ROAD && c->terrain_type != TERRAIN_INFO_PLAZA) {
            lang_text_draw_multiline(70, c->terrain_type + text_id_offset, c->x_offset + 40, c->y_offset + 16 * c->height_blocks - 113, 16 * (c->width_blocks - 4), FONT_NORMAL_BLACK_ON_LIGHT);
        }
        window_building_draw_figure_list(c);
    }
}
