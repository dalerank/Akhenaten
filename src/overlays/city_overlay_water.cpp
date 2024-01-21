#include "city_overlay_water.h"

#include "overlays/city_overlay.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/image.h"
#include "graphics/image.h"
#include "graphics/boilerplate.h"
#include "building/building.h"
#include "widget/city/tile_draw.h"
#include "core/vec2i.h"
#include "figure/figure.h"

static int terrain_on_water_overlay(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ROAD
        | TERRAIN_CANAL | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE | TERRAIN_DUNE
        | TERRAIN_MARSHLAND;
}

static void draw_footprint_water(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();

    // roads, bushes, dunes, etc. are drawn normally
    if (map_terrain_is(grid_offset, terrain_on_water_overlay())) {
        // (except for roadblocks on roads, draw these as flattened tiles)
        if (building_at(grid_offset)->type == BUILDING_ROADBLOCK) {
            city_with_overlay_draw_building_footprint(ctx, pixel.x, pixel.y, grid_offset, 0);
        } else if (map_property_is_draw_tile(grid_offset)) {
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), pixel, 0);
        }
    } else {
        int terrain = map_terrain_get(grid_offset);
        building* b = building_at(grid_offset);
        // draw houses, wells and water supplies either fully or flattened
        if (terrain & TERRAIN_BUILDING && (building_is_house(b->type)) || b->type == BUILDING_WELL || b->type == BUILDING_WATER_SUPPLY) {
            if (map_property_is_draw_tile(grid_offset)) {
                city_with_overlay_draw_building_footprint(ctx, pixel.x, pixel.y, grid_offset, 0);
            }
        } else {
            // draw groundwater levels
            int image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY_WATER);
            switch (map_terrain_get(grid_offset) & (TERRAIN_GROUNDWATER | TERRAIN_FOUNTAIN_RANGE)) {
            case TERRAIN_GROUNDWATER | TERRAIN_FOUNTAIN_RANGE:
            case TERRAIN_FOUNTAIN_RANGE:
                image_id += 2;
                break;

            case TERRAIN_GROUNDWATER:
                image_id += 1;
                break;
            }
            ImageDraw::isometric(ctx, image_id, pixel);
        }
    }
}

static int get_tooltip_water(tooltip_context* c, int grid_offset) {
    int building_id = map_building_at(grid_offset);
    if (building_id && building_is_house(building_get(building_id)->type)) {
        if (map_terrain_is(grid_offset, TERRAIN_FOUNTAIN_RANGE)) {
            return 3;
        } else {
            return 2;
        }
    } else if (map_terrain_is(grid_offset, TERRAIN_GROUNDWATER)) {
        if (map_terrain_is(grid_offset, TERRAIN_FOUNTAIN_RANGE)) {
            return 3;
        } else {
            return 1;
        }
    }
    
    return 0;
}

static int get_column_height_water(const building* b) {
    return b->house_size ? b->data.house.water_supply * 17 / 10 : NO_COLUMN;
}

static void draw_top_water(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }

    if (map_terrain_is(grid_offset, terrain_on_water_overlay())) {
        if (!map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            color color_mask = 0;
            if (map_property_is_deleted(grid_offset) && map_property_multi_tile_size(grid_offset) == 1)
                color_mask = COLOR_MASK_RED;
            //            ImageDraw::isometric_top_from_drawtile(map_image_at(grid_offset), x, y, color_mask,
            //            city_view_get_scale_float());
        }
    } else if (map_building_at(grid_offset)) {
        city_with_overlay_draw_building_top(pixel, point, ctx);
    }
}

struct city_overlay_water : public city_overlay {
    city_overlay_water() {
        type = OVERLAY_WATER;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        draw_custom_footprint = draw_footprint_water;
        draw_custom_top_func = draw_top_water;
        get_column_height = get_column_height_water;
        get_tooltip_for_grid_offset = get_tooltip_water;
    }

    bool show_figure(const figure* f) const override {
        return f->type == FIGURE_WATER_CARRIER;
    }

    void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override {
        int grid_offset = point.grid_offset();
        if (!map_property_is_draw_tile(grid_offset)) {
            return;
        }

        if (map_building_at(grid_offset)) {
            city_with_overlay_draw_building_top(pixel, point, ctx);
        }
    }

    bool show_building(const building *b) const override {
        return building_type_any_of(*(building*)b, BUILDING_WELL, BUILDING_MENU_BEAUTIFICATION, BUILDING_WATER_LIFT, BUILDING_WATER_SUPPLY);
    }
};

city_overlay_water g_city_overlay_water;

city_overlay* city_overlay_for_water() {
    return &g_city_overlay_water;
}
