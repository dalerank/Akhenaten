#include "industry.h"

#include "building/building.h"
#include "city/buildings.h"
#include "city/resource.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "grid/floodplain.h"
#include "grid/terrain.h"
#include "io/gamefiles/lang.h"

void window_building_draw_shipyard(object_info* c) {
    c->help_id = 82;
    window_building_play_sound(c, "wavs/shipyard.wav");
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(100, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c->building_id);

    if (!c->has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else {
        int pct_done = calc_percentage(b->data.industry.progress, 160);
        int width = lang_text_draw(100, 2, c->x_offset + 32, c->y_offset + 56, FONT_NORMAL_BLACK_ON_LIGHT);
        width += text_draw_percentage(pct_done, c->x_offset + 32 + width, c->y_offset + 56, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw(100, 3, c->x_offset + 32 + width, c->y_offset + 56, FONT_NORMAL_BLACK_ON_LIGHT);
        if (city_buildings_shipyard_boats_requested())
            lang_text_draw_multiline(
              100, 5, c->x_offset + 32, c->y_offset + 80, 16 * (c->width_blocks - 6), FONT_NORMAL_BLACK_ON_LIGHT);
        else {
            lang_text_draw_multiline(
              100, 4, c->x_offset + 32, c->y_offset + 80, 16 * (c->width_blocks - 6), FONT_NORMAL_BLACK_ON_LIGHT);
        }
    }

    inner_panel_draw(c->x_offset + 16, c->y_offset + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}
void window_building_draw_wharf(object_info* c) {
    c->help_id = 84;
    window_building_play_sound(c, "wavs/wharf.wav");
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(102, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_ICONS) + RESOURCE_FIGS + resource_image_offset(RESOURCE_FIGS, RESOURCE_IMAGE_ICON), c->x_offset + 10, c->y_offset + 10);

    building* b = building_get(c->building_id);

    if (!c->has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (!b->data.industry.fishing_boat_id) {
        window_building_draw_description(c, 102, 2);
    } else {
        int text_id;
        switch (figure_get(b->data.industry.fishing_boat_id)->action_state) {
        case FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH:
            text_id = 3;
            break;
        case FIGURE_ACTION_192_FISHING_BOAT_FISHING:
            text_id = 4;
            break;
        case FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF:
            text_id = 5;
            break;
        case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF:
            text_id = 6;
            break;
        case FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH:
            text_id = 7;
            break;
        default:
            text_id = 8;
            break;
        }
        window_building_draw_description(c, 102, text_id);
    }

    inner_panel_draw(c->x_offset + 16, c->y_offset + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}
