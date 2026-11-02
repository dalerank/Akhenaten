#include "building_garden.h"

#include "building/building.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/building_tiles.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_garden);

namespace {
// OG Pharaoh terrain masks (TERRAIN_NOT_EMPTY / TERRAIN_NOT_CLEAR in the original). Wider than our
// TERRAIN_NOT_CLEAR: they also block shore, ferry route and the unknown 0x200000-0x800000 / 0x6000000 bits.
// Bit 0x10000000 is left out in both: here it is TERRAIN_PLANER_FUTURE, set on tiles while dragging.
constexpr uint32_t og_terrain_not_empty = 0xEEFFD77F;
constexpr uint32_t og_terrain_not_clear = 0xEEFED77F;

bool area_is_bare_garden(tile2i tile, int size) {
    if (!map_grid_is_inside(tile, size)) {
        return false;
    }

    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            const int grid_offset = tile.shifted(dx, dy).grid_offset();
            if (((uint32_t)map_terrain_get(grid_offset) & og_terrain_not_clear) != TERRAIN_GARDEN) {
                return false;
            }
            if (map_image_at(grid_offset) != 0) {
                return false;
            }
        }
    }
    return true;
}
} // namespace

bool building_garden::can_place_on_tile(tile2i tile) {
    return ((uint32_t)map_terrain_get(tile) & og_terrain_not_empty) == 0;
}

bool __building_garden_can_place_on_tile(tile2i tile) {
    return building_garden::can_place_on_tile(tile);
}
ANK_FUNCTION_1(__building_garden_can_place_on_tile)

void building_garden::set_image(int grid_offset) {
    if (!map_terrain_is(grid_offset, TERRAIN_GARDEN) || map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        return;
    }

    if (map_image_at(grid_offset)) {
        return;
    }

    tile2i tile(grid_offset);
    const auto &params = current_params();
    if (area_is_bare_garden(tile, 3)) {
        map_building_tiles_add(0, tile, 3, params.variants3.at(grid_offset).first_img(), TERRAIN_GARDEN);
    } else if (area_is_bare_garden(tile, 2)) {
        map_building_tiles_add(0, tile, 2, params.variants2.at(grid_offset).first_img(), TERRAIN_GARDEN);
    } else {
        map_image_set(grid_offset, params.variants1.at(grid_offset).first_img());
    }
}

void building_garden::determine_tile(int grid_offset) {
    const int image_id = map_image_at(grid_offset);
    if (!image_id) {
        return;
    }

    auto is_variant = [image_id] (const animations_t &variants) {
        for (const auto &it : variants.data) {
            if (it.second.first_img() == image_id) {
                return true;
            }
        }
        return false;
    };

    const auto &params = current_params();
    if (is_variant(params.variants1) || is_variant(params.variants2) || is_variant(params.variants3)) {
        map_terrain_add(grid_offset, TERRAIN_GARDEN);
        map_property_clear_constructing(grid_offset);
    }
}
