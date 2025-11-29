#include "map.h"

#include "core/calc.h"
#include "grid/grid.h"
#include "scenario/scenario.h"

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

void scenario_map_foreach_herd_point(std::function<void(tile2i)> callback) {
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) {
        tile2i tile = g_scenario.herd_points_animals[i];
        if (tile.valid()) {
            callback(g_scenario.herd_points_animals[i]);
        }
    }
}

void scenario_map_foreach_fishing_point(void (*callback)(tile2i)) {
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        tile2i fish_tile = g_scenario.fishing_points[i];
        if (fish_tile.valid()) {
            callback(g_scenario.fishing_points[i]);
        }
    }
}

bool scenario_map_has_flotsam() {
    return g_scenario.env.flotsam_enabled;
}

bool scenario_map_has_animals() {
    return g_scenario.env.has_animals;
}
