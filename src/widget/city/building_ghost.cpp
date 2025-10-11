#include "building_ghost.h"

#include "grid/routing/routing.h"
#include "building/construction/build_planner.h"
#include "building/building_farm.h"
#include "building/building_fishing_wharf.h"
#include "building/building_road.h"
#include "building/monument_mastaba.h"
#include "building/rotation.h"
#include "building/building_fort.h"
#include "building/building.h"
#include "city/buildings.h"
#include "city/city_finance.h"
#include "grid/bridge.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/figure.h"
#include "grid/image_context.h"
#include "grid/orientation.h"
#include "grid/property.h"
#include "grid/road_canal.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "game/game_config.h"
#include "ornaments.h"
#include "game/game.h"
#include "graphics/image.h"
#include "graphics/view/lookup.h"

#include <cmath>

static const int RESERVOIR_GRID_OFFSETS_PH[4] = {GRID_OFFSET(-1, -1), GRID_OFFSET(1, -1), GRID_OFFSET(1, 1), GRID_OFFSET(-1, 1)};

static const int HIPPODROME_X_VIEW_OFFSETS[4] = {150, 150, -150, -150};
static const int HIPPODROME_Y_VIEW_OFFSETS[4] = {75, -75, -75, 75};

#define RESERVOIR_RANGE_MAX_TILES 520

struct reservoir_range_data_t {
    int total;
    int save_offsets;
    int offsets[RESERVOIR_RANGE_MAX_TILES];
    int last_grid_offset;
};

reservoir_range_data_t reservoir_range_data;

static int get_building_image_id(int map_x, int map_y, int type) {
    const auto &props = building_static_params::get((e_building_type)type);
    int image_id = props.base_img();
    if (type == BUILDING_MUD_GATEHOUSE) {
        int orientation = map_orientation_for_gatehouse(map_x, map_y);
        int image_offset;
        if (orientation == 2)
            image_offset = 1;
        else if (orientation == 1)
            image_offset = 0;
        else {
            image_offset = building_rotation_get_road_orientation() == 2 ? 1 : 0;
        }
        int map_orientation = city_view_orientation();
        if (map_orientation == DIR_6_TOP_LEFT || map_orientation == DIR_2_BOTTOM_RIGHT)
            image_offset = 1 - image_offset;

        image_id += image_offset;
    } else if (type == BUILDING_RESERVED_TRIUMPHAL_ARCH_56) {
        int orientation = map_orientation_for_triumphal_arch(map_x, map_y);
        int image_offset;
        if (orientation == 2)
            image_offset = 2;
        else if (orientation == 1)
            image_offset = 0;
        else {
            image_offset = building_rotation_get_road_orientation() == 2 ? 2 : 0;
        }
        int map_orientation = city_view_orientation();
        if (map_orientation == DIR_6_TOP_LEFT || map_orientation == DIR_2_BOTTOM_RIGHT)
            image_offset = 2 - image_offset;

        image_id += image_offset;
    }
    return image_id;
}

static void get_building_base_xy(int map_x, int map_y, int building_size, int* x, int* y) {
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        *x = map_x;
        *y = map_y;
        break;
    case DIR_2_BOTTOM_RIGHT:
        *x = map_x - building_size + 1;
        *y = map_y;
        break;
    case DIR_4_BOTTOM_LEFT:
        *x = map_x - building_size + 1;
        *y = map_y - building_size + 1;
        break;
    case DIR_6_TOP_LEFT:
        *x = map_x;
        *y = map_y - building_size + 1;
        break;
    default:
        *x = *y = 0;
    }
}