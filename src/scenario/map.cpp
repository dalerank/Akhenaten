#include "map.h"

#include "core/calc.h"
#include "grid/grid.h"
#include "scenario/scenario_data.h"

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
        //        g_scenario_data.exit_point.x() = g_scenario_data.entry_point.x();
        //        g_scenario_data.exit_point.y() = g_scenario_data.entry_point.y();
    }
}

tile2i scenario_map_entry(void) {
    tile2i point = {g_scenario_data.entry_point.x(), g_scenario_data.entry_point.y()};
    return point;
}

tile2i scenario_map_exit(void) {
    tile2i point = {g_scenario_data.exit_point.x(), g_scenario_data.exit_point.y()};
    return point;
}

int scenario_map_has_river_entry(void) {
    return g_scenario_data.river_entry_point.x() != -1 && g_scenario_data.river_entry_point.y() != -1;
}

tile2i scenario_map_river_entry(void) {
    tile2i point = {g_scenario_data.river_entry_point.x(), g_scenario_data.river_entry_point.y()};
    return point;
}

int scenario_map_has_river_exit(void) {
    return g_scenario_data.river_exit_point.x() != -1 && g_scenario_data.river_exit_point.y() != -1;
}

tile2i scenario_map_river_exit(void) {
    tile2i point = {g_scenario_data.river_exit_point.x(), g_scenario_data.river_exit_point.y()};
    return point;
}

void scenario_map_foreach_herd_point(void (*callback)(int x, int y)) {
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) {
        if (g_scenario_data.herd_points_predator[i].x() > 0)
            callback(g_scenario_data.herd_points_predator[i].x(), g_scenario_data.herd_points_predator[i].y());
    }
}

void scenario_map_foreach_fishing_point(void (*callback)(int x, int y)) {
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        if (g_scenario_data.fishing_points[i].x() > 0)
            callback(g_scenario_data.fishing_points[i].x(), g_scenario_data.fishing_points[i].y());
    }
}

int scenario_map_closest_fishing_point(tile2i pos, tile2i &fish) {
    int num_fishing_spots = 0;
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        if (g_scenario_data.fishing_points[i].x() > 0)
            num_fishing_spots++;
    }
    if (num_fishing_spots <= 0)
        return 0;

    int min_dist = 10000;
    int min_fish_id = 0;
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        if (g_scenario_data.fishing_points[i].x() > 0) {
            int dist = calc_maximum_distance(pos, g_scenario_data.fishing_points[i]);
            if (dist < min_dist) {
                min_dist = dist;
                min_fish_id = i;
            }
        }
    }
    if (min_dist < 10000) {
        map_point_store_result(g_scenario_data.fishing_points[min_fish_id], fish);
        return 1;
    }
    return 0;
}

int scenario_map_has_flotsam() {
    return g_scenario_data.flotsam_enabled;
}
