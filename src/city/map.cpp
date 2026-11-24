#include "map.h"
#include "game/simulation.h"
#include "core/app_module.h"
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

class map_system : public sim_system {
public:
    const char* name() const override { return "map"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_tree_growth, SIM_PHASE_TICK_SLOT, 2, [] { map_tree_growth_update(); }});
        schedule.add({sim_step_irrigation_value, SIM_PHASE_TICK_SLOT, 5, [] { g_irrigation_value.update(); }});
        schedule.add({sim_step_natives_land, SIM_PHASE_TICK_SLOT, 6, [] { map_natives_check_land(); }});
        schedule.add({sim_step_road_network, SIM_PHASE_TICK_SLOT, 7, [] { g_city.map.update_road_network(); }});
        schedule.add({sim_step_desirability, SIM_PHASE_TICK_SLOT, 10, [] { g_desirability.update(); }});
        schedule.add({sim_step_vegetation_growth, SIM_PHASE_TICK_SLOT, 18, [] { map_vegetation_growth_update(); }});
        schedule.add({sim_step_roads_images, SIM_PHASE_MONTH, -1, [] { map_tiles_update_all_roads(); }});
        schedule.add({sim_step_land_citizen_routing, SIM_PHASE_MONTH, -1, [] { map_routing_update_land_citizen(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_map_system) {
    static map_system system;
    g_simulation.register_system(&system);
}
