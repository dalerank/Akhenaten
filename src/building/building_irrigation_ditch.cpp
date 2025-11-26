#include "building_irrigation_ditch.h"

#include "grid/routing/routing.h"
#include "building/construction/routed.h"
#include "construction/build_planner.h"
#include "grid/tiles.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "city/city_buildings.h"
#include "city/city.h"
#include "game/undo.h"
#include "js/js_game.h"

#include <array>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_irrigation_ditch);

static bool has_water_source_nearby(tile2i tile) {
    // Check for water (river/lake) directly adjacent
    if (map_terrain_count_directly_adjacent_with_type(tile, TERRAIN_WATER) > 0) {
        return true;
    }

    // Check for water lift building nearby (within 1 tile radius)
    std::array<vec2i, 4> adjacent_offsets = { vec2i(0, 1), vec2i(1, 0), vec2i(0, -1), vec2i(-1, 0) };
    for (const auto &offset : adjacent_offsets) {
        tile2i adjacent_tile = tile.shifted(offset);
        if (map_terrain_is(adjacent_tile, TERRAIN_BUILDING)) {
            building *b = building_at(adjacent_tile);
            if (b && b->type == BUILDING_WATER_LIFT) {
                return true;
            }
        }

        if (map_terrain_is(adjacent_tile, TERRAIN_CANAL)) {
            return true;
        }
    }

    return false;
}

int building_construction_place_canal(bool measure_only, tile2i start, tile2i end) {
    game_undo_restore_map(0);
    if (!map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start)) {
        return 0;
    }

    auto result = place_routed_building(start, end, ROUTED_BUILDING_CANALS);
    if (result.ok && !measure_only) {
        map_canal_update_all_tiles(0);
        map_routing_update_land();
    }

    return result.items;
}

routed_building_result building_construction_place_canal_for_lift(bool measure_only, tile2i start, tile2i end) {
    e_routed_mode type = measure_only ? ROUTED_BUILDING_CANALS_WITHOUT_GRAPHIC : ROUTED_BUILDING_CANALS;
    return place_routed_building(start, end, type);
}


bool building_irrigation_ditch::preview::can_construction_start(build_planner &p, tile2i start) const {
    // First check if routing is possible
    if (!map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start)) {
        return false;
    }

    // Check if starting point is valid (road, canal, floodplain, or clear land)
    bool is_valid_start = map_terrain_is(start, TERRAIN_ROAD) 
                       || map_terrain_is(start, TERRAIN_CANAL)
                       || map_terrain_is(start, TERRAIN_FLOODPLAIN)
                       || (!map_terrain_is(start, TERRAIN_NOT_CLEAR) && !map_terrain_is(start, TERRAIN_WATER));
    
    if (!is_valid_start) {
        return false;
    }

    if (!has_water_source_nearby(start)) {
        return false;
    }

    return true;
}

int building_irrigation_ditch::preview::construction_update(build_planner &p, tile2i start, tile2i end) const {
    int items_placed = building_construction_place_canal(/*measure_only*/true, start, end);
    
    // Update canal images in the region around the path for interactive preview
    // Similar to how place_routed_building updates empty land around each tile
    if (items_placed > 0) {
        grid_area area = map_grid_get_area(start, end);
        // Add padding for neighboring tiles (like routed.cpp does with -4, +4)
        tile2i pmin = area.tmin.shifted(-2, -2);
        tile2i pmax = area.tmax.shifted(2, 2);
        map_tiles_update_region_canals(pmin, pmax);
    }
    
    return items_placed;
}

int building_irrigation_ditch::preview::construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    int items_placed = building_construction_place_canal(false, start, end);

    map_canal_update_all_tiles(0);
    map_routing_update_land();

    return items_placed;
}

bool building_irrigation_ditch::preview::is_road_tile_for_canal(tile2i tile, int gate_orientation) const {
    bool is_road = map_terrain_is(tile, TERRAIN_ROAD);
    if (map_terrain_is(tile, TERRAIN_BUILDING)) {
        building *b = building_at(tile);
        if (b->type == BUILDING_MUD_GATEHOUSE) {
            if (b->orientation == gate_orientation)
                is_road = true;

        } else if (b->type == BUILDING_GRANARY) {
            if (map_routing_citizen_is_road(tile))
                is_road = true;
        }
    }

    return is_road;
}

bool building_irrigation_ditch::preview::map_is_straight_road_for_canal(tile2i tile) const {
    bool road_tiles_x = is_road_tile_for_canal(tile.shifted(1, 0), 2) || is_road_tile_for_canal(tile.shifted(-1, 0), 2);
    bool road_tiles_y = is_road_tile_for_canal(tile.shifted(0, -1), 1) || is_road_tile_for_canal(tile.shifted(0, 1), 1);

    if (road_tiles_x && !road_tiles_y) {
        return true;
    }

    if (road_tiles_y && !road_tiles_x) {
        return true;
    }

    return false;
}

bool building_irrigation_ditch::preview::ghost_allow_tile(build_planner &p, tile2i tile) const {
    if (!p.in_progress) {
        return has_water_source_nearby(tile);
    }

    return building_planer_renderer::ghost_allow_tile(p, tile);
}

void building_irrigation_ditch::preview::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    bool blocked = false;
    if (!map_can_place_initial_road_or_canal(end.grid_offset(), true)) {
        blocked = true;
    }

    if (planer.in_progress) {   // already dragging aqueduct
        if (!planer.total_cost) // ???
            blocked = true;
    } else {
        // Check if starting point has water source nearby
        if (!has_water_source_nearby(start)) {
            blocked = true;
            planer.set_warning("#irrigation_ditch_needs_water_source");
        }
        
        if (map_terrain_is(end, TERRAIN_ROAD)) {               // starting new aqueduct line
            blocked = !map_is_straight_road_for_canal(end) || blocked; // can't start over a road curve!
            if (map_property_is_plaza_or_earthquake(end))      // todo: plaza not allowing aqueducts? maybe?
                blocked = true;
        } else if (map_terrain_is(end, TERRAIN_NOT_CLEAR)
            && !map_terrain_is(end, TERRAIN_FLOODPLAIN)) {// terrain is not clear!
            blocked = true;
        }
    }

    if (g_city.finance.is_out_of_money()) { // check sufficient funds to continue
        blocked = true;
    }

    if (blocked) { // cannot draw!
        planer.draw_flat_tile(ctx, pixel, COLOR_MASK_RED);
    } else {
        const terrain_image img = map_image_context_get_canal(end.grid_offset()); // get starting tile
        const bool is_road = map_terrain_is(end, TERRAIN_ROAD);
        int canal_image = get_canal_image(end.grid_offset(), is_road, 0, img);
        planer.draw_building_ghost(ctx, canal_image, pixel);
    }
}

int building_irrigation_ditch::preview::can_place(build_planner &p, tile2i tile, tile2i end, int state) const {
    // Check if starting point has water source nearby
    if (!has_water_source_nearby(tile)) {
        p.set_warning("#irrigation_ditch_needs_water_source");
        return CAN_NOT_PLACE;
    }
    return state;
}

void building_irrigation_ditch::on_place_checks() {
    // nothing
}
