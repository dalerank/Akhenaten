#include "building_dike.h"

#include "construction/routed.h"
#include "game/game_config.h"
#include "game/undo.h"
#include "graphics/image.h"
#include "grid/building.h"
#include "grid/image.h"
#include "grid/image_context.h"
#include "grid/property.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "js/js_game.h"

#include "grid/basin.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_dike);

bool building_dike::can_place_on_tile(tile2i tile) {
    if (!tile.valid()) {
        return false;
    }

    const int terrain = map_terrain_get(tile);
    if (terrain & (TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_DEEPWATER | TERRAIN_BUILDING
                   | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ELEVATION | TERRAIN_RUBBLE | TERRAIN_CANAL
                   | TERRAIN_ACCESS_RAMP | TERRAIN_WALL | TERRAIN_GATEHOUSE | TERRAIN_ORE | TERRAIN_DUNE)) {
        return false;
    }

    // Allow existing dike (replace) and road|dike sluice.
    if (terrain & TERRAIN_DIKE) {
        return true;
    }

    // No new dike on submerged road alone (flood season mid-state without crest).
    if (terrain & TERRAIN_SUBMERGED_ROAD) {
        return false;
    }

    if (terrain & TERRAIN_FLOODPLAIN) {
        return true;
    }

    // Clear / meadow land only on the floodplain edge.
    if (map_terrain_count_directly_adjacent_with_type(tile, TERRAIN_FLOODPLAIN) > 0
        || map_terrain_count_diagonally_adjacent_with_type(tile, TERRAIN_FLOODPLAIN) > 0) {
        return true;
    }

    return false;
}

bool building_dike::set_dike(tile2i tile) {
    if (!can_place_on_tile(tile)) {
        return false;
    }

    const int grid_offset = tile.grid_offset();
    bool tile_set = !map_terrain_is(grid_offset, TERRAIN_DIKE);

    map_terrain_add(grid_offset, TERRAIN_DIKE);
    map_property_clear_constructing(grid_offset);

    map_tiles_foreach_region_tile_ex(tile.shifted(-1, -1), tile.shifted(1, 1), [](tile2i t) {
        set_image(t);
    });

    return tile_set;
}

terrain_image building_dike::get_terrain_image(tile2i tile) {
    std::array<int, MAP_IMAGE_MAX_TILES> tiles;
    map_image_context_fill_matches(tile, TERRAIN_DIKE, {0, 1}, tiles);
    return map_image_context_get_terrain_image(CONTEXT_WALL, tiles);
}

void building_dike::set_image(tile2i tile) {
    if (!map_terrain_is(tile, TERRAIN_DIKE)) {
        return;
    }

    // Dry sluice keeps the road graphic; dike bit still seals the basin.
    // During inundation ROAD→SUBMERGED and road::set_image no longer applies —
    // draw the crest so the embankment stays visible.
    if (map_terrain_is(tile, TERRAIN_ROAD)) {
        return;
    }

    terrain_image img = get_terrain_image(tile);
    if (!img.is_valid) {
        return;
    }

    const int id = building_static_params::get(BUILDING_DIKE).base_img();
    map_image_set(tile, id + img.group_offset + img.item_offset);
    map_property_set_multi_tile_size(tile.grid_offset(), 1);
    map_property_mark_draw_tile(tile);
}

void building_dike::update_area_dikes(tile2i tile, int size) {
    tile2i start = tile.shifted(-1, -1);
    tile2i end = tile.shifted(size, size);
    map_tiles_foreach_region_tile_ex(start, end, [](tile2i t) { set_image(t); });
}

int building_dike::place_dike(bool measure_only, tile2i start, tile2i end) {
    if (!game_features::gameplay_enhanced_flood_basins.to_bool()) {
        return 0;
    }

    game_undo_restore_map(0);

    if (!can_place_on_tile(start) || !can_place_on_tile(end)) {
        return 0;
    }

    if (!map_routing_calculate_distances_for_building(ROUTED_BUILDING_DIKE, start)) {
        return 0;
    }

    auto result = place_routed_building(start, end, ROUTED_BUILDING_DIKE);
    if (result.ok && !measure_only) {
        map_routing_update_land();
        map_basin_mark_dirty();
        map_basin_rebuild_dirty();
    }

    return result.ok ? result.items : 0;
}

int building_dike::preview::construction_update(build_planner &p, tile2i start, tile2i end) const {
    return place_dike(true, start, end);
}

int building_dike::preview::construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    return place_dike(false, start, end);
}

bool building_dike::preview::can_construction_start(build_planner &p, tile2i start) const {
    if (!game_features::gameplay_enhanced_flood_basins.to_bool()) {
        return false;
    }
    if (!can_place_on_tile(start)) {
        return false;
    }
    return map_routing_calculate_distances_for_building(ROUTED_BUILDING_DIKE, start);
}
