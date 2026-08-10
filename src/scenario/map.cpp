#include "map.h"

#include "core/calc.h"
#include "grid/grid.h"
#include "scenario/scenario.h"
#include "js/js_game.h"

const map_data_t* scenario_map_data() {
    return &g_scenario.map;
}

int scenario_map_size(void) {
    return g_scenario.map.width;
}

void scenario_map_init_entry_exit(void) {
    if (g_scenario.entry_point.x() == -1 || g_scenario.entry_point.y() == -1) {
        g_scenario.entry_point.x(g_scenario.map.width - 1);
        g_scenario.entry_point.y(g_scenario.map.height / 2);
    }

    if (g_scenario.exit_point.x() == -1 || g_scenario.exit_point.y() == -1) {
        g_scenario.exit_point = g_scenario.entry_point;
    }
}

tile2i scenario_map_entry(void) {
    return g_scenario.entry_point;
}

tile2i scenario_map_exit(void) {
    return g_scenario.exit_point;
}

bool scenario_map_has_river_entry() {
    return g_scenario.river_entry_point.valid();
}

tile2i scenario_map_river_entry() {
    return g_scenario.river_entry_point;
}

bool scenario_map_has_river_exit() {
    return g_scenario.river_exit_point.valid();
}

tile2i scenario_map_river_exit() {
    return g_scenario.river_exit_point;
}

void scenario_map_foreach_prey_point(std::function<void(tile2i)> callback) {
    for (const herd_point_t &hp : g_scenario.herd_points_prey) {
        if (hp.valid()) {
            callback(hp.tile);
        }
    }
}

void scenario_map_foreach_fishing_point(void (*callback)(tile2i)) {
    for (const tile2i &fish_tile : g_scenario.fishing_points) {
        if (fish_tile.valid()) {
            callback(fish_tile);
        }
    }
}

ANK_BOUND_BOOL(__scenario_flotsam_enabled, g_scenario.env.flotsam_enabled)
ANK_BOUND_BOOL(__scenario_has_animals, g_scenario.env.has_animals)
ANK_BOUND_BOOL(__scenario_hide_nilometer, g_scenario.env.hide_nilometer)
ANK_BOUND_BOOL(__scenario_alt_predator_type, g_scenario.alt_predator_type)
