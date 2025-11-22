#include "city_overlay_desirability.h"

#include "game/state.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/desirability.h"
#include "grid/random.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "game/game_config.h"
#include "graphics/elements/ui.h"
#include "city/city_buildings.h"

static int terrain_on_desirability_overlay(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ROAD
        | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE;
}

static int has_deleted_building(int grid_offset) {
    if (!game_features::gameui_visual_feedback_on_delete)
        return 0;

    building* b = building_at(grid_offset);
    b = b->main();
    return b->id && (b->is_deleted || map_property_is_deleted(b->tile));
}

static int get_desirability_image_offset(int desirability) {
    if (desirability < -10)
        return 0;
    else if (desirability < -5)
        return 1;
    else if (desirability < 0)
        return 2;
    else if (desirability == 1)
        return 3;
    else if (desirability < 5)
        return 4;
    else if (desirability < 10)
        return 5;
    else if (desirability < 15)
        return 6;
    else if (desirability < 20)
        return 7;
    else if (desirability < 25)
        return 8;
    else
        return 9;
}

// static void draw_top_desirability(pixel_coordinate pixel, map_point point) {
//     int grid_offset = point.grid_offset();
//     int x = pixel.x;
//     int y = pixel.y;
//     color color_mask = map_property_is_deleted(grid_offset) ? COLOR_MASK_RED : 0;
//     if (map_terrain_is(grid_offset, terrain_on_desirability_overlay()) &&
//         !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
//         // display normal tile
//         if (map_property_is_draw_tile(grid_offset))
//             ImageDraw::isometric_top_from_drawtile(map_image_at(grid_offset), x, y, color_mask,
//             city_view_get_scale_float());
//
//     } else if (map_terrain_is(grid_offset, TERRAIN_AQUEDUCT | TERRAIN_WALL)) {
//         // groundwater, no top needed
//     } else if (map_terrain_is(grid_offset, TERRAIN_BUILDING) || map_desirability_get(grid_offset)) {
//         if (has_deleted_building(grid_offset))
//             color_mask = COLOR_MASK_RED;
//
//         int offset = get_desirability_image_offset(map_desirability_get(grid_offset));
//         ImageDraw::isometric_top_from_drawtile(image_id_from_group(GROUP_TERRAIN_DESIRABILITY) + offset, x, y,
//                                                color_mask, city_view_get_scale_float());
//     } else
//         ImageDraw::isometric_top_from_drawtile(map_image_at(grid_offset), x, y, color_mask,
//         city_view_get_scale_float());
// }

city_overlay_desirability g_city_overlay_desirability;

bool city_overlay_desirability::show_figure(const figure *f) const {
    return false;
}

int city_overlay_desirability::get_column_height(const building *b) const {
    return COLUMN_TYPE_NONE;
}

void city_overlay_desirability::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    ; // nothing
}

xstring city_overlay_desirability::get_tooltip_for_building(tooltip_context *c, const building *b) {
    return {};
}

xstring city_overlay_desirability::get_tooltip(tooltip_context *c, tile2i tile) const {
    int desirability = g_desirability.get(tile);
    if (desirability < 0) {
        return ui::str(66, 91);
    } else if (desirability == 0) {
        return ui::str(66, 92);
    } else {
        return ui::str(66, 93);
    }
}

bool city_overlay_desirability::draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const {
    int grid_offset = point.grid_offset();

    color color_mask = map_property_is_deleted(grid_offset) ? COLOR_MASK_RED : 0;
    if (map_terrain_is(grid_offset, terrain_on_desirability_overlay()) && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        // display normal tile
        if (map_property_is_draw_tile(grid_offset)) {
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = map_image_at(grid_offset);
            command.pixel = pixel;
            command.mask = color_mask;
        }

    } else if (map_terrain_is(grid_offset, TERRAIN_CANAL | TERRAIN_WALL)) {
        // display empty land/groundwater

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7);
        command.pixel = pixel;
        command.mask = color_mask;

    } else if (map_terrain_is(grid_offset, TERRAIN_BUILDING) || g_desirability.get(grid_offset)) {
        if (has_deleted_building(grid_offset)) {
            color_mask = COLOR_MASK_RED;
        }

        int offset = get_desirability_image_offset(g_desirability.get(grid_offset));
        int img_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY);

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_full);
        command.image_id = img_id + offset;
        command.pixel = pixel;
        command.mask = color_mask;
    } else {
        int img_id = map_image_at(grid_offset);

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile_full);
        command.image_id = img_id;
        command.pixel = pixel;
        command.mask = color_mask;

    }

    return true;
}

bool city_overlay_desirability::show_building(const building *b) const {
    return false;
}
