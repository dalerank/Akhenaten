#include "building_irrigation_ditch.h"

#include "grid/routing/routing.h"
#include "building/construction/routed.h"
#include "construction/build_planner.h"
#include "grid/tiles.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/canals.h"
#include "city/city_buildings.h"
#include "city/city.h"
#include "game/undo.h"

building_irrigation_ditch::static_params irrigation_ditch_m;

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
    return map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start);
}

int building_irrigation_ditch::preview::construction_update(build_planner &p, tile2i start, tile2i end) const {
    int items_placed = building_construction_place_canal(/*measure_only*/true, start, end);
    map_canal_update_all_tiles(0);

    return items_placed;
}

int building_irrigation_ditch::preview::construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    int items_placed = building_construction_place_canal(false, start, end);

    map_canal_update_all_tiles(0);
    map_routing_update_land();

    return items_placed;
}

bool building_irrigation_ditch::static_params::is_road_tile_for_canal(tile2i tile, int gate_orientation) const {
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

bool building_irrigation_ditch::static_params::map_is_straight_road_for_canal(tile2i tile) const {
    int road_tiles_x = is_road_tile_for_canal(tile.shifted(1, 0), 2) | is_road_tile_for_canal(tile.shifted(-1, 0), 2);
    int road_tiles_y = is_road_tile_for_canal(tile.shifted(0, -1), 1) | is_road_tile_for_canal(tile.shifted(0, 1), 1);

    if (road_tiles_x == 2 && road_tiles_y == 0) {
        return true;
    }

    if (road_tiles_y == 2 && road_tiles_x == 0) {
        return true;
    }

    return false;
}

void building_irrigation_ditch::static_params::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    bool blocked = false;
    if (!map_can_place_initial_road_or_canal(end.grid_offset(), true)) {
        blocked = true;
    }

    if (planer.in_progress) {   // already dragging aqueduct
        if (!planer.total_cost) // ???
            blocked = true;
    } else {
        if (map_terrain_is(end, TERRAIN_ROAD)) {               // starting new aqueduct line
            blocked = !map_is_straight_road_for_canal(end); // can't start over a road curve!
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

void building_irrigation_ditch::on_place_checks() {
    // nothing
}
