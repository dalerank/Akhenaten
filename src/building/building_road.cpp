#include "building/building_road.h"

#include "city/city.h"
#include "city/city_labor.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/floodplain.h"
#include "grid/image.h"
#include "grid/canals.h"
#include "grid/property.h"
#include "grid/road_canal.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "building/building_static_params.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_road);

bool building_road::set_road(tile2i tile) {
    bool tile_set = false;
    if (!map_terrain_is(tile, TERRAIN_ROAD)) {
        tile_set = true;
    }

    map_terrain_add(tile, TERRAIN_ROAD);
    map_property_clear_constructing(tile);

    map_tiles_foreach_region_tile_ex(tile.shifted(-1, -1), tile.shifted(1, 1), set_image);
    return tile_set;
}

bool building_road::is_paved(tile2i tile) {
    int desirability = g_desirability.get(tile.grid_offset());
    if (desirability > 4) {
        return true;
    }

    if (desirability > 0 && map_terrain_is(tile, TERRAIN_FOUNTAIN_RANGE)) {
        return true;
    }

    return false;
}

void building_road::set_image(tile2i tile) {
    if (!map_terrain_is(tile, TERRAIN_ROAD)
        || map_terrain_is(tile, TERRAIN_WATER)
        || map_terrain_is(tile, TERRAIN_BUILDING)) {
        return;
    }

    if (map_terrain_is(tile, TERRAIN_CANAL)) {
        map_tiles_set_canal_image(tile.grid_offset());
        return;
    }

    if (map_property_is_plaza_or_earthquake(tile)) {
        return;
    }

    const auto &params = building_static_params::get(TYPE);
    int base_img = params.base_img();
    if (is_paved(tile)) {
        const terrain_image img = map_image_context_get_paved_road(tile);
        map_image_set(tile, base_img + img.group_offset + img.item_offset);
    } else {
        if (!map_terrain_is(tile, TERRAIN_FLOODPLAIN)) {
            map_image_set_road_floodplain(tile);
        } else {
            const terrain_image img = map_image_context_get_dirt_road(tile);
            map_image_set(tile, base_img + img.group_offset + img.item_offset + 49 + 344);
        }
    }

    map_property_set_multi_tile_size(tile.grid_offset(), 1);
    map_property_mark_draw_tile(tile.grid_offset());
}
