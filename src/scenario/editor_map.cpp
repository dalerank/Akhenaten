#include "editor_map.h"

#include "figuretype/water.h"
#include "map/routing_terrain.h"
#include "scenario/data.h"

void scenario_editor_set_entry_point(int x, int y) {
    scenario_data.entry_point.x = x;
    scenario_data.entry_point.y = y;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_exit_point(int x, int y) {
    scenario_data.exit_point.x = x;
    scenario_data.exit_point.y = y;
    scenario_data.is_saved = 0;
}

static void update_river(void) {
    figure_create_flotsam();
    map_routing_update_water();
}

void scenario_editor_set_river_entry_point(int x, int y) {
    scenario_data.river_entry_point.x = x;
    scenario_data.river_entry_point.y = y;
    scenario_data.is_saved = 0;
    update_river();
}

void scenario_editor_set_river_exit_point(int x, int y) {
    scenario_data.river_exit_point.x = x;
    scenario_data.river_exit_point.y = y;
    scenario_data.is_saved = 0;
    update_river();
}

void scenario_editor_clear_herd_points(void) {
    for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++) {
        scenario_data.herd_points[i].x = -1;
        scenario_data.herd_points[i].y = -1;
    }
    scenario_data.is_saved = 0;
}

map_point scenario_editor_herd_point(int id) {
    return scenario_data.herd_points[id];
}

void scenario_editor_set_herd_point(int id, int x, int y) {
    scenario_data.herd_points[id].x = x;
    scenario_data.herd_points[id].y = y;
    scenario_data.is_saved = 0;
}

void scenario_editor_clear_fishing_points(void) {
    for (int i = 0; i < MAX_FISH_POINTS[GAME_ENV]; i++) {
        scenario_data.fishing_points[i].x = -1;
        scenario_data.fishing_points[i].y = -1;
    }
    scenario_data.is_saved = 0;
}

map_point scenario_editor_fishing_point(int id) {
    return scenario_data.fishing_points[id];
}

void scenario_editor_set_fishing_point(int id, int x, int y) {
    scenario_data.fishing_points[id].x = x;
    scenario_data.fishing_points[id].y = y;
    scenario_data.is_saved = 0;
}

int scenario_editor_count_invasion_points(void) {
    int points = 0;
    for (int i = 0; i < MAX_INVASION_POINTS[GAME_ENV]; i++) {
        if (scenario_data.invasion_points[i].x != -1)
            points++;

    }
    return points;
}

void scenario_editor_clear_invasion_points(void) {
    for (int i = 0; i < MAX_INVASION_POINTS[GAME_ENV]; i++) {
        scenario_data.invasion_points[i].x = -1;
        scenario_data.invasion_points[i].y = -1;
    }
    scenario_data.is_saved = 0;
}

map_point scenario_editor_invasion_point(int id) {
    return scenario_data.invasion_points[id];
}

void scenario_editor_set_invasion_point(int id, int x, int y) {
    scenario_data.invasion_points[id].x = x;
    scenario_data.invasion_points[id].y = y;
    scenario_data.is_saved = 0;
}

map_point scenario_editor_earthquake_point(void) {
    return scenario_data.earthquake_point;
}

void scenario_editor_set_earthquake_point(int x, int y) {
    scenario_data.earthquake_point.x = x;
    scenario_data.earthquake_point.y = y;
    scenario_data.is_saved = 0;
}

void scenario_editor_updated_terrain(void) {
    scenario_data.is_saved = 0;
}
