#include "rotation.h"

#include "building/construction/build_planner.h"
#include "building/building_statue.h"
#include "core/direction.h"
#include "graphics/view/view.h"
#include "grid/grid.h"
#include "game/game_config.h"

static time_millis road_last_update = 0;

static void building_rotation_rotate() {
    g_city_planner.global_rotation++;
    if (g_city_planner.global_rotation > 3) {
        g_city_planner.global_rotation = 0;
    }
}

int building_rotation_global_rotation() {
    return g_city_planner.global_rotation;
}

void building_rotation_set_global_rotation(int rotation) {
    if (rotation < 0) {
        rotation = 0;
    } else if (rotation > 3) {
        rotation = 0;
    }
    g_city_planner.global_rotation = rotation;
}

int building_rotation_get_road_orientation() {
    return g_city_planner.road_orientation;
}

void building_rotation_set_road_orientation(int orientation) {
    g_city_planner.road_orientation = (orientation == 2) ? 2 : 1;
}

void building_rotation_reset_rotation() {
    g_city_planner.global_rotation = 0;
}

void building_rotation_force_two_orientations() { // for composite buildings like hippodrome
    if (g_city_planner.global_rotation == 1 || g_city_planner.global_rotation == 2) {
        g_city_planner.global_rotation = 3;
    }
}

void building_rotation_update_road_orientation() {
    if (!game_features::gameui_rotate_manually) {
        if (time_get_millis() - road_last_update > 1500) {
            road_last_update = time_get_millis();
            g_city_planner.road_orientation = g_city_planner.road_orientation == 1 ? 2 : 1;
            building_rotation_rotate();
            g_city_planner.update_orientations();
        }
    }
}

int building_rotation_get_storage_fort_orientation(int building_rotation) {
    return (2 * building_rotation + g_camera.orientation) % 8;
}

int building_rotation_get_storage_gatehouse_orientation(int building_rotation) {
    return (2 * building_rotation + g_camera.orientation) % 8;
}

int building_rotation_get_delta_with_rotation(int default_delta) {
    const int global_rotation = g_city_planner.global_rotation;
    if (global_rotation == 0) {
        return GRID_OFFSET(default_delta, 0);
    } else if (global_rotation == 1) {
        return GRID_OFFSET(0, -default_delta);
    } else if (global_rotation == 2) {
        return GRID_OFFSET(-default_delta, 0);
    } else {
        return GRID_OFFSET(0, default_delta);
    }
}

void building_rotation_get_offset_with_rotation(int offset, int rot, int* x, int* y) {
    if (rot == 0) {
        *x = offset;
        *y = 0;
    } else if (rot == 1) {
        *x = 0;
        *y = -offset;
    } else if (rot == 2) {
        *x = -offset;
        *y = 0;
    } else {
        *x = 0;
        *y = offset;
    }
}

int building_rotation_get_corner(int rot) {
    switch (rot) {
    case DIR_2_BOTTOM_RIGHT:
        return 4; // left corner
    case DIR_4_BOTTOM_LEFT:
        return 8; // bottom corner
    case DIR_6_TOP_LEFT:
        return 5; // right corner
    default:
        return 0; // top corner
    }
}