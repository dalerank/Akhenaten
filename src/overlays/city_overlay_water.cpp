#include "city_overlay_water.h"

#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/image.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "building/building.h"
#include "widget/city/tile_draw.h"
#include "city/city_buildings.h"
#include "figure/figure.h"
#include "widget/city/tile_draw.h"
#include "building/building_house.h"

static int terrain_on_water_overlay(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ROAD
        | TERRAIN_CANAL | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE | TERRAIN_DUNE
        | TERRAIN_MARSHLAND;
}

city_overlay_water g_city_overlay_water;

city_overlay* city_overlay_for_water() {
    return &g_city_overlay_water;
}

void city_overlay_water::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    if (!map_property_is_draw_tile(tile)) {
        return;
    }

    if (map_terrain_is(tile, terrain_on_water_overlay())) {
        if (!map_terrain_is(tile, TERRAIN_BUILDING)) {
            color color_mask = 0;
            if (map_property_is_deleted(tile) && map_property_multi_tile_size(tile) == 1)
                color_mask = COLOR_MASK_RED;
            //            ImageDraw::isometric_top_from_drawtile(map_image_at(grid_offset), x, y, color_mask,
            //            city_view_get_scale_float());
        }
    } else if (map_building_at(tile)) {
        city_overlay::draw_building_top(pixel, tile, ctx);
    }
}

bool city_overlay_water::draw_custom_footprint(vec2i pixel, tile2i tile, painter &ctx) const {
    // roads, bushes, dunes, etc. are drawn normally
    if (map_terrain_is(tile, terrain_on_water_overlay())) {
        // (except for roadblocks on roads, draw these as flattened tiles)
        if (building_at(tile)->type == BUILDING_ROADBLOCK) {
            city_overlay::draw_building_footprint(ctx, pixel, tile, 0);
        } else if (map_property_is_draw_tile(tile)) {
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(tile), pixel, 0);
            ImageDraw::isometric_from_drawtile_top(ctx, map_image_at(tile), pixel, 0);
        }
    } else {
        int terrain = map_terrain_get(tile);
        building* b = building_at(tile);
        // draw houses, wells and water supplies either fully or flattened
        if ((terrain & TERRAIN_BUILDING) && (building_is_house(b->type)) || show_building(b)) {
            if (map_property_is_draw_tile(tile)) {
                city_overlay::draw_building_footprint(ctx, pixel, tile, 0);
            }
        } else {
            // draw groundwater levels
            int image_id = image_id_from_group(GROUP_TERRAIN_OVERLAY_WATER);
            switch (map_terrain_get(tile) & (TERRAIN_GROUNDWATER | TERRAIN_FOUNTAIN_RANGE)) {
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

    return true;
}

xstring city_overlay_water::get_tooltip_for_grid_offset(tooltip_context* c, int grid_offset) const {
    int building_id = map_building_at(grid_offset);
    if (building_id && building_is_house(building_get(building_id)->type)) {
        if (map_terrain_is(grid_offset, TERRAIN_FOUNTAIN_RANGE)) {
            return ui::str(66, 3);
        } else {
            return ui::str(66, 2);
        }
    } else if (map_terrain_is(grid_offset, TERRAIN_GROUNDWATER)) {
        if (map_terrain_is(grid_offset, TERRAIN_FOUNTAIN_RANGE)) {
            return ui::str(66, 3);
        } else {
            return ui::str(66, 1);
        }
    }

    return 0;
}

int city_overlay_water::get_column_height(const building *b) const {
    auto house = ((building *)b)->dcast_house();

    if (!house) {
        return COLUMN_TYPE_NONE;
    }

    auto &housed = house->runtime_data();
    return b->house_size ? housed.water_supply * 17 / 10 : COLUMN_TYPE_NONE;
}