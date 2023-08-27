#include "city_overlay_desirability.h"

#include "city_overlay.h"
#include "game/state.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/desirability.h"
#include "grid/random.h"
#include "graphics/color.h"
#include "graphics/boilerplate.h"
#include "io/config/config.h"

static int terrain_on_desirability_overlay(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ROAD
        | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE;
}

static int has_deleted_building(int grid_offset) {
    if (!config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE))
        return 0;

    building* b = building_at(grid_offset);
    b = b->main();
    return b->id && (b->is_deleted || map_property_is_deleted(b->tile.grid_offset()));
}

static int get_tooltip_desirability(tooltip_context* c, int grid_offset) {
    int desirability = map_desirability_get(grid_offset);
    if (desirability < 0)
        return 91;
    else if (desirability == 0)
        return 92;
    else {
        return 93;
    }
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

static void draw_footprint_desirability(vec2i pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    color color_mask = map_property_is_deleted(grid_offset) ? COLOR_MASK_RED : 0;
    if (map_terrain_is(grid_offset, terrain_on_desirability_overlay())
        && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        // display normal tile
        if (map_property_is_draw_tile(grid_offset))
            ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y, color_mask);

    } else if (map_terrain_is(grid_offset, TERRAIN_AQUEDUCT | TERRAIN_WALL)) {
        // display empty land/groundwater
        int image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7);
        ImageDraw::isometric_from_drawtile(image_id, x, y, color_mask);
    } else if (map_terrain_is(grid_offset, TERRAIN_BUILDING) || map_desirability_get(grid_offset)) {
        if (has_deleted_building(grid_offset))
            color_mask = COLOR_MASK_RED;

        int offset = get_desirability_image_offset(map_desirability_get(grid_offset));
        ImageDraw::isometric_from_drawtile(image_id_from_group(GROUP_TERRAIN_DESIRABILITY) + offset, x, y, color_mask);
    } else
        ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y, color_mask);
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

struct city_overlay_desirability : public city_overlay {
    city_overlay_desirability() {
        type = OVERLAY_DESIRABILITY;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        get_column_height = get_column_height_none;
        get_tooltip_for_grid_offset = get_tooltip_desirability;
        draw_custom_footprint = draw_footprint_desirability;
    }

    bool show_figure(const figure* f) const override {
        return false;
    }

    void draw_custom_top(vec2i pixel, map_point point) const override {
        ; // nothing
    }

    bool show_building(const building* b) const override {
        return false;
    }
};

city_overlay_desirability g_city_overlay_desirability;
const city_overlay* city_overlay_for_desirability() {
    return &g_city_overlay_desirability;
}