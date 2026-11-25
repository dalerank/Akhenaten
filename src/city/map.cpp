#include "map.h"
#include "grid/desirability.h"
#include "city/military.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"
#include "grid/vegetation.h"
#include "grid/natives.h"
#include "grid/irrigation_value.h"
#include "grid/trees.h"
#include "game/sim_schedule.h"
#include "city/map_chunks.h"
#include "core/xvalue.h"
#include "io/chunk_serializer.h"
#include "io/gamestate/save_versions.h"

#include "city/city.h"
#include "core/profiler.h"
#include "grid/road_access.h"
#include "grid/grid.h"

city_map_t& city_map() {
    return xvalue<city_map_t>::ref();
}

void city_map_t::reset() {
    *this = city_map_t();
}

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
    void on_reset() override { city_map().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= save_version_city_sections) {
            g_chunk_io.push_chunk<city_map_chunk>(city_map_chunk::size, false);
        }
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_tree_growth, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 2) {
                              return;
                          }
                          map_tree_growth_update();
                      }});
        schedule.add({sim_step_irrigation_value, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 5) {
                              return;
                          }
                          g_irrigation_value.update();
                      }});
        schedule.add({sim_step_natives_land, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 6) {
                              return;
                          }
                          city_military().decrease_native_attack_duration();
                          if (map_natives_check_land()) {
                              city_military().start_native_attack();
                          }
                      }});
        schedule.add({sim_step_road_network, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 7) {
                              return;
                          }
                          city_map().update_road_network();
                      }});
        schedule.add({sim_step_desirability, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 10) {
                              return;
                          }
                          g_desirability.update();
                      }});
        schedule.add({sim_step_vegetation_growth, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 18) {
                              return;
                          }
                          map_vegetation_growth_update();
                      }});
        schedule.add({sim_step_roads_images, SIM_PHASE_MONTH, [](int) { map_tiles_update_all_roads(); }});
        schedule.add({sim_step_land_citizen_routing, SIM_PHASE_MONTH, [](int) { map_routing_update_land_citizen(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_map_system) {
    static map_system system;
    g_simulation.register_system(&system);
}
