#include "map.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"
#include "grid/vegetation.h"
#include "grid/natives.h"
#include "grid/irrigation_value.h"
#include "grid/trees.h"
#include "game/sim_schedule.h"

#include "city/city.h"
#include "core/profiler.h"
#include "grid/road_access.h"
#include "grid/grid.h"

tile2i city_map_t::set_entry_flag(tile2i tile) {
    entry_flag = tile;
    return entry_flag;
}

tile2i city_map_t::set_exit_flag(tile2i tile) {
    exit_flag = tile;
    return exit_flag;
}

int city_map_t::road_network_index(int network_id) {
    for (int n = 0; n < 10; n++) {
        if (largest_road_networks[n].id == network_id)
            return n;
    }
    return 11;
} 

void city_map_t::clear_largest_road_networks() {
    for (int i = 0; i < 10; i++) {
        largest_road_networks[i].id = 0;
        largest_road_networks[i].size = 0;
    }
}

void city_map_t::add_to_largest_road_networks(int network_id, int size) {
    for (int n = 0; n < 10; n++) {
        if (size > largest_road_networks[n].size) {
            // move everyone down
            for (int m = 9; m > n; m--) {
                largest_road_networks[m].id = largest_road_networks[m - 1].id;
                largest_road_networks[m].size = largest_road_networks[m - 1].size;
            }
            largest_road_networks[n].id = network_id;
            largest_road_networks[n].size = size;
            break;
        }
    }
}

tile2i city_map_t::closest_exit_tile_within_radius(int size, int radius) {
    OZZY_PROFILER_FUNCTION();
    return map_closest_road_within_radius(exit_point, size, radius, true);
}

ANK_SIM_STEP(tree_growth, SIM_PHASE_TICK_SLOT, 2, 30, SIM_AREA_MAP) {
    map_tree_growth_update();
}

ANK_SIM_STEP(irrigation_value, SIM_PHASE_TICK_SLOT, 5, 50, SIM_AREA_MAP) {
    g_irrigation_value.update();
}

ANK_SIM_STEP(natives_land, SIM_PHASE_TICK_SLOT, 6, 70, SIM_AREA_MAP) {
    map_natives_check_land();
}

ANK_SIM_STEP(road_network, SIM_PHASE_TICK_SLOT, 7, 80, SIM_AREA_MAP) {
    g_city.map.update_road_network();
}

ANK_SIM_STEP(desirability, SIM_PHASE_TICK_SLOT, 10, 110, SIM_AREA_MAP) {
    g_desirability.update();
}

ANK_SIM_STEP(vegetation_growth, SIM_PHASE_TICK_SLOT, 18, 160, SIM_AREA_MAP) {
    map_vegetation_growth_update();
}

ANK_SIM_STEP(roads_images, SIM_PHASE_MONTH, -1, 110, SIM_AREA_MAP) {
    map_tiles_update_all_roads();
}

ANK_SIM_STEP(land_citizen_routing, SIM_PHASE_MONTH, -1, 120, SIM_AREA_MAP) {
    map_routing_update_land_citizen();
}
