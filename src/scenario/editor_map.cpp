#include "editor_map.h"

#include "grid/routing/routing_terrain.h"
#include "scenario/scenario.h"

// TODO !!!!!!

void scenario_editor_set_entry_point(int x, int y) {
    //    g_scenario.entry_point.x() = x;
    //    g_scenario.entry_point.y() = y;
    g_scenario.is_saved = 0;
}

void scenario_editor_set_exit_point(int x, int y) {
    //    g_scenario.exit_point.x() = x;
    //    g_scenario.exit_point.y() = y;
    g_scenario.is_saved = 0;
}

static void update_river() {
    map_routing_update_water();
}

void scenario_editor_set_river_entry_point(int x, int y) {
    //    g_scenario.river_entry_point.x() = x;
    //    g_scenario.river_entry_point.y() = y;
    g_scenario.is_saved = 0;
    update_river();
}

void scenario_editor_set_river_exit_point(int x, int y) {
    g_scenario.river_exit_point = tile2i{ x, y };
    g_scenario.is_saved = 0;
    update_river();
}

void scenario_editor_clear_predator_herd_points(void) {
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) {
        g_scenario.herd_points_animals[i] = tile2i::invalid;
    }
    g_scenario.is_saved = 0;
}

tile2i scenario_editor_predator_herd_point(int id) {
    return g_scenario.herd_points_animals[id];
}

void scenario_editor_set_predator_herd_point(int id, int x, int y) {
    g_scenario.herd_points_animals[id] = tile2i::invalid;
    g_scenario.is_saved = 0;
}

void scenario_editor_clear_fishing_points(void) {
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        g_scenario.fishing_points[i] = tile2i::invalid;
    }
    g_scenario.is_saved = 0;
}

tile2i scenario_editor_fishing_point(int id) {
    return g_scenario.fishing_points[id];
}

void scenario_editor_set_fishing_point(int id, int x, int y) {
    g_scenario.fishing_points[id] = tile2i{ x, y };
    g_scenario.is_saved = 0;
}

int scenario_editor_count_invasion_points(void) {
    int points = 0;
    //    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++) {
    //        if (g_scenario.invasion_points_land[i].x != -1)
    //            points++;
    //    }
    //    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++) {
    //        if (g_scenario.invasion_points_sea[i].x != -1)
    //            points++;
    //    }
    return points;
}

void scenario_editor_clear_invasion_points(void) {
    //    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++) {
    //        g_scenario.invasion_points_land[i].x = -1;
    //        g_scenario.invasion_points_land[i].y = -1;
    //    }
    //    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++) {
    //        g_scenario.invasion_points_sea[i].x = -1;
    //        g_scenario.invasion_points_sea[i].y = -1;
    //    }
    g_scenario.is_saved = 0;
}

tile2i scenario_editor_land_invasion_point(int id) {
    return g_scenario.invasion_points_land[id];
}

void scenario_editor_set_land_invasion_point(int id, int x, int y) {
    //    g_scenario.invasion_points_land[id].x = x;
    //    g_scenario.invasion_points_land[id].y = y;
    g_scenario.is_saved = 0;
}

tile2i scenario_editor_earthquake_point(void) {
    return g_scenario.earthquake_point;
}

void scenario_editor_set_earthquake_point(int x, int y) {
    //    g_scenario.earthquake_point.x = x;
    //    g_scenario.earthquake_point.y = y;
    g_scenario.is_saved = 0;
}

void scenario_editor_updated_terrain(void) {
    g_scenario.is_saved = 0;
}
