#include "map.h"

#include "core/calc.h"
#include "grid/grid.h"
#include "scenario/scenario.h"

const map_data_t* scenario_map_data() {
    return &g_scenario_data.map;
}

int scenario_map_size(void) {
    return g_scenario_data.map.width;
}

void scenario_map_init_entry_exit(void) {
    if (g_scenario_data.entry_point.x() == -1 || g_scenario_data.entry_point.y() == -1) {
        g_scenario_data.entry_point.x(g_scenario_data.map.width - 1);
        g_scenario_data.entry_point.y(g_scenario_data.map.height / 2);
    }

    if (g_scenario_data.exit_point.x() == -1 || g_scenario_data.exit_point.y() == -1) {
        g_scenario_data.exit_point = g_scenario_data.entry_point;
    }
}

tile2i scenario_map_entry(void) {
    return g_scenario_data.entry_point;
}

tile2i scenario_map_exit(void) {
    return g_scenario_data.exit_point;
}

bool scenario_map_has_river_entry() {
    return g_scenario_data.river_entry_point.valid();
}

tile2i scenario_map_river_entry() {
    return g_scenario_data.river_entry_point;
}

bool scenario_map_has_river_exit() {
    return g_scenario_data.river_exit_point.valid();
}

tile2i scenario_map_river_exit() {
    return g_scenario_data.river_exit_point;
}

void scenario_map_foreach_herd_point(std::function<void(tile2i)> callback) {
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) {
        tile2i tile = g_scenario_data.herd_points_predator[i];
        if (tile.valid()) {
            callback(g_scenario_data.herd_points_predator[i]);
        }
    }
}

void scenario_map_foreach_fishing_point(void (*callback)(tile2i)) {
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        tile2i fish_tile = g_scenario_data.fishing_points[i];
        if (fish_tile.valid()) {
            callback(g_scenario_data.fishing_points[i]);
        }
    }
}

bool scenario_map_has_flotsam() {
    return g_scenario_data.env.flotsam_enabled;
}

bool scenario_map_has_animals() {
    return g_scenario_data.env.has_animals;
}
