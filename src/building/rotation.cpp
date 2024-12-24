#include "rotation.h"

#include "building/construction/build_planner.h"
#include "building/building_statue.h"
#include "core/direction.h"
#include "graphics/view/view.h"
#include "grid/grid.h"
#include "config/config.h"

int g_global_rotation = 0;
static int road_orientation = 1;
static int variant = 0;
static time_millis road_last_update = 0;

static void rotate(void) {
    g_global_rotation++;
    if (g_global_rotation > 3)
        g_global_rotation = 0;
}

int building_rotation_global_rotation() {
    return g_global_rotation;
}

void building_rotation_rotate_by_hotkey() {
    if (config_get(CONFIG_UI_ROTATE_MANUALLY)) {
        rotate();
        road_orientation = road_orientation == 1 ? 2 : 1;
        Planner.update_orientations();
    }
}

void building_rotation_randomize_variant(tile2i tile, int type) {
    variant = tile.grid_offset();
    switch (type) {
    case BUILDING_SMALL_STATUE:
    case BUILDING_MEDIUM_STATUE:
    case BUILDING_LARGE_STATUE:
        variant = building_statue_random_variant(type, variant);
    break;
    }
}

void building_rotation_variant_by_hotkey() {
    switch (Planner.build_type) {
    case BUILDING_SMALL_STATUE:
    case BUILDING_MEDIUM_STATUE:
    case BUILDING_LARGE_STATUE:
        variant = building_statue_next_variant(Planner.build_type, variant);
        break;

    default:
        variant = (variant + 1) % 4;
    }

    Planner.update_orientations();
}

void building_rotation_reset_rotation() {
    g_global_rotation = 0;
    variant = 0;
    Planner.update_orientations();
}

void building_rotation_force_two_orientations(void) { // for composite buildings like hippodrome
    if (g_global_rotation == 1 || g_global_rotation == 2)
        g_global_rotation = 3;
}

void building_rotation_update_road_orientation(void) {
    if (!config_get(CONFIG_UI_ROTATE_MANUALLY)) {
        if (time_get_millis() - road_last_update > 1500) {
            road_last_update = time_get_millis();
            road_orientation = road_orientation == 1 ? 2 : 1;
            rotate();
            Planner.update_orientations();
        }
    }
}
int building_rotation_get_road_orientation() {
    return road_orientation;
}

int building_rotation_get_building_variant() {
    return variant;
}

int building_rotation_get_storage_fort_orientation(int building_rotation) {
    return (2 * building_rotation + city_view_orientation()) % 8;
}

int building_rotation_get_delta_with_rotation(int default_delta) {
    if (g_global_rotation == 0) {
        return GRID_OFFSET(default_delta, 0);
    } else if (g_global_rotation == 1)
        return GRID_OFFSET(0, -default_delta);
    else if (g_global_rotation == 2)
        return GRID_OFFSET(-default_delta, 0);
    else
        return GRID_OFFSET(0, default_delta);
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
