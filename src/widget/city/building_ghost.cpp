#include <cmath>
#include "building_ghost.h"

#include "building/Construction/planner.h"
#include "building/count.h"
#include "building/industry.h"
#include "building/properties.h"
#include "building/rotation.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/view.h"
#include "core/config.h"
#include "core/game_environment.h"
#include "figure/formation.h"
#include "graphics/image.h"
#include "input/scroll.h"
#include "map/bridge.h"
#include "map/building.h"
#include "map/building_tiles.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/image_context.h"
#include "map/orientation.h"
#include "map/property.h"
#include "map/road_aqueduct.h"
#include "map/terrain.h"
#include "map/tiles.h"
#include "map/water.h"
#include "scenario/property.h"
#include "widget/city/bridges.h"
#include "tile_draw.h"
#include "ornaments.h"
#include "building/monuments.h"

#define MAX_TILES 25

static const int X_VIEW_OFFSETS[MAX_TILES] = {
        0,
        -30, 30, 0,
        -60, 60, -30, 30, 0,
        -90, 90, -60, 60, -30, 30, 0,
        -120, 120, -90, 90, -60, 60, -30, 30, 0
};

static const int Y_VIEW_OFFSETS[MAX_TILES] = {
        0,
        15, 15, 30,
        30, 30, 45, 45, 60,
        45, 45, 60, 60, 75, 75, 90,
        60, 60, 75, 75, 90, 90, 105, 105, 120
};

//#define OFFSET(x,y) (x + grid_size[GAME_ENV] * y)

static
const int TILE_GRID_OFFSETS_C3[4][MAX_TILES] = {
    {
        OFFSET_C3(0, 0),
        OFFSET_C3(0, 1),
        OFFSET_C3(1, 0),
        OFFSET_C3(1, 1),
        OFFSET_C3(0, 2),
        OFFSET_C3(2, 0),
        OFFSET_C3(1, 2),
        OFFSET_C3(2, 1),
        OFFSET_C3(2, 2),
        OFFSET_C3(0, 3),
        OFFSET_C3(3, 0),
        OFFSET_C3(1, 3),
        OFFSET_C3(3, 1),
        OFFSET_C3(2, 3),
        OFFSET_C3(3, 2),
        OFFSET_C3(3, 3),
        OFFSET_C3(0, 4),
        OFFSET_C3(4, 0),
        OFFSET_C3(1, 4),
        OFFSET_C3(4, 1),
        OFFSET_C3(2, 4),
        OFFSET_C3(4, 2),
        OFFSET_C3(3, 4),
        OFFSET_C3(4, 3),
        OFFSET_C3(4, 4)
    },
    {
        OFFSET_C3(0, 0),
        OFFSET_C3(-1, 0),
        OFFSET_C3(0, 1),
        OFFSET_C3(-1, 1),
        OFFSET_C3(-2, 0),
        OFFSET_C3(0, 2),
        OFFSET_C3(-2, 1),
        OFFSET_C3(-1, 2),
        OFFSET_C3(-2, 2),
        OFFSET_C3(-3, 0),
        OFFSET_C3(0, 3),
        OFFSET_C3(-3, 1),
        OFFSET_C3(-1, 3),
        OFFSET_C3(-3, 2),
        OFFSET_C3(-2, 3),
        OFFSET_C3(-3, 3),
        OFFSET_C3(-4, 0),
        OFFSET_C3(0, 4),
        OFFSET_C3(-4, 1),
        OFFSET_C3(-1, 4),
        OFFSET_C3(-4, 2),
        OFFSET_C3(-2, 4),
        OFFSET_C3(-4, 3),
        OFFSET_C3(-3, 4),
        OFFSET_C3(-4, 4)
    },
    {
        OFFSET_C3(0, 0),
        OFFSET_C3(0, -1),
        OFFSET_C3(-1, 0),
        OFFSET_C3(-1, -1),
        OFFSET_C3(0, -2),
        OFFSET_C3(-2, 0),
        OFFSET_C3(-1, -2),
        OFFSET_C3(-2, -1),
        OFFSET_C3(-2, -2),
        OFFSET_C3(0, -3),
        OFFSET_C3(-3, 0),
        OFFSET_C3(-1, -3),
        OFFSET_C3(-3, -1),
        OFFSET_C3(-2, -3),
        OFFSET_C3(-3, -2),
        OFFSET_C3(-3, -3),
        OFFSET_C3(0, -4),
        OFFSET_C3(-4, 0),
        OFFSET_C3(-1, -4),
        OFFSET_C3(-4, -1),
        OFFSET_C3(-2, -4),
        OFFSET_C3(-4, -2),
        OFFSET_C3(-3, -4),
        OFFSET_C3(-4, -3),
        OFFSET_C3(-4, -4)
    },
    {
        OFFSET_C3(0, 0),
        OFFSET_C3(1, 0),
        OFFSET_C3(0, -1),
        OFFSET_C3(1, -1),
        OFFSET_C3(2, 0),
        OFFSET_C3(0, -2),
        OFFSET_C3(2, -1),
        OFFSET_C3(1, -2),
        OFFSET_C3(2, -2),
        OFFSET_C3(3, 0),
        OFFSET_C3(0, -3),
        OFFSET_C3(3, -1),
        OFFSET_C3(1, -3),
        OFFSET_C3(3, -2),
        OFFSET_C3(2, -3),
        OFFSET_C3(3, -3),
        OFFSET_C3(4, 0),
        OFFSET_C3(0, -4),
        OFFSET_C3(4, -1),
        OFFSET_C3(1, -4),
        OFFSET_C3(4, -2),
        OFFSET_C3(2, -4),
        OFFSET_C3(4, -3),
        OFFSET_C3(3, -4),
        OFFSET_C3(4, -4)
    },
};
static
const int TILE_GRID_OFFSETS_PH[4][MAX_TILES] = {
    {
        OFFSET_PH(0, 0),
        OFFSET_PH(0, 1),
        OFFSET_PH(1, 0),
        OFFSET_PH(1, 1),
        OFFSET_PH(0, 2),
        OFFSET_PH(2, 0),
        OFFSET_PH(1, 2),
        OFFSET_PH(2, 1),
        OFFSET_PH(2, 2),
        OFFSET_PH(0, 3),
        OFFSET_PH(3, 0),
        OFFSET_PH(1, 3),
        OFFSET_PH(3, 1),
        OFFSET_PH(2, 3),
        OFFSET_PH(3, 2),
        OFFSET_PH(3, 3),
        OFFSET_PH(0, 4),
        OFFSET_PH(4, 0),
        OFFSET_PH(1, 4),
        OFFSET_PH(4, 1),
        OFFSET_PH(2, 4),
        OFFSET_PH(4, 2),
        OFFSET_PH(3, 4),
        OFFSET_PH(4, 3),
        OFFSET_PH(4, 4)
    },
    {
        OFFSET_PH(0, 0),
        OFFSET_PH(-1, 0),
        OFFSET_PH(0, 1),
        OFFSET_PH(-1, 1),
        OFFSET_PH(-2, 0),
        OFFSET_PH(0, 2),
        OFFSET_PH(-2, 1),
        OFFSET_PH(-1, 2),
        OFFSET_PH(-2, 2),
        OFFSET_PH(-3, 0),
        OFFSET_PH(0, 3),
        OFFSET_PH(-3, 1),
        OFFSET_PH(-1, 3),
        OFFSET_PH(-3, 2),
        OFFSET_PH(-2, 3),
        OFFSET_PH(-3, 3),
        OFFSET_PH(-4, 0),
        OFFSET_PH(0, 4),
        OFFSET_PH(-4, 1),
        OFFSET_PH(-1, 4),
        OFFSET_PH(-4, 2),
        OFFSET_PH(-2, 4),
        OFFSET_PH(-4, 3),
        OFFSET_PH(-3, 4),
        OFFSET_PH(-4, 4)
    },
    {
        OFFSET_PH(0, 0),
        OFFSET_PH(0, -1),
        OFFSET_PH(-1, 0),
        OFFSET_PH(-1, -1),
        OFFSET_PH(0, -2),
        OFFSET_PH(-2, 0),
        OFFSET_PH(-1, -2),
        OFFSET_PH(-2, -1),
        OFFSET_PH(-2, -2),
        OFFSET_PH(0, -3),
        OFFSET_PH(-3, 0),
        OFFSET_PH(-1, -3),
        OFFSET_PH(-3, -1),
        OFFSET_PH(-2, -3),
        OFFSET_PH(-3, -2),
        OFFSET_PH(-3, -3),
        OFFSET_PH(0, -4),
        OFFSET_PH(-4, 0),
        OFFSET_PH(-1, -4),
        OFFSET_PH(-4, -1),
        OFFSET_PH(-2, -4),
        OFFSET_PH(-4, -2),
        OFFSET_PH(-3, -4),
        OFFSET_PH(-4, -3),
        OFFSET_PH(-4, -4)
    },
    {
        OFFSET_PH(0, 0),
        OFFSET_PH(1, 0),
        OFFSET_PH(0, -1),
        OFFSET_PH(1, -1),
        OFFSET_PH(2, 0),
        OFFSET_PH(0, -2),
        OFFSET_PH(2, -1),
        OFFSET_PH(1, -2),
        OFFSET_PH(2, -2),
        OFFSET_PH(3, 0),
        OFFSET_PH(0, -3),
        OFFSET_PH(3, -1),
        OFFSET_PH(1, -3),
        OFFSET_PH(3, -2),
        OFFSET_PH(2, -3),
        OFFSET_PH(3, -3),
        OFFSET_PH(4, 0),
        OFFSET_PH(0, -4),
        OFFSET_PH(4, -1),
        OFFSET_PH(1, -4),
        OFFSET_PH(4, -2),
        OFFSET_PH(2, -4),
        OFFSET_PH(4, -3),
        OFFSET_PH(3, -4),
        OFFSET_PH(4, -4)
    },
};

static const int FORT_GROUND_GRID_OFFSETS_C3[4][4] = {
        {OFFSET_C3(3, -1),  OFFSET_C3(4, -1), OFFSET_C3(4, 0),  OFFSET_C3(3, 0)},
        {OFFSET_C3(-1, -4), OFFSET_C3(0, -4), OFFSET_C3(0, -3), OFFSET_C3(-1, -3)},
        {OFFSET_C3(-4, 0),  OFFSET_C3(-3, 0), OFFSET_C3(-3, 1), OFFSET_C3(-4, 1)},
        {OFFSET_C3(0, 3),   OFFSET_C3(1, 3),  OFFSET_C3(1, 4),  OFFSET_C3(0, 4)}
};
static const int FORT_GROUND_GRID_OFFSETS_PH[4][4] = {
        {OFFSET_PH(3, -1),  OFFSET_PH(4, -1), OFFSET_PH(4, 0),  OFFSET_PH(3, 0)},
        {OFFSET_PH(-1, -4), OFFSET_PH(0, -4), OFFSET_PH(0, -3), OFFSET_PH(-1, -3)},
        {OFFSET_PH(-4, 0),  OFFSET_PH(-3, 0), OFFSET_PH(-3, 1), OFFSET_PH(-4, 1)},
        {OFFSET_PH(0, 3),   OFFSET_PH(1, 3),  OFFSET_PH(1, 4),  OFFSET_PH(0, 4)}
};
static const int FORT_GROUND_X_VIEW_OFFSETS[4] = {120, 90, -120, -90};
static const int FORT_GROUND_Y_VIEW_OFFSETS[4] = {30, -75, -60, 45};

static const int RESERVOIR_GRID_OFFSETS_C3[4] = {OFFSET_C3(-1, -1), OFFSET_C3(1, -1), OFFSET_C3(1, 1),
                                                 OFFSET_C3(-1, 1)};
static const int RESERVOIR_GRID_OFFSETS_PH[4] = {OFFSET_PH(-1, -1), OFFSET_PH(1, -1), OFFSET_PH(1, 1),
                                                 OFFSET_PH(-1, 1)};

static const int HIPPODROME_X_VIEW_OFFSETS[4] = {150, 150, -150, -150};
static const int HIPPODROME_Y_VIEW_OFFSETS[4] = {75, -75, -75, 75};

#define RESERVOIR_RANGE_MAX_TILES 520

static struct {
    int total;
    int save_offsets;
    int offsets[RESERVOIR_RANGE_MAX_TILES];
    int last_grid_offset;
} reservoir_range_data;

static int get_building_image_id(int map_x, int map_y, int type, const building_properties *props) {
    int image_id = image_id_from_group(props->image_collection, props->image_group) + props->image_offset;
    if (type == BUILDING_GATEHOUSE) {
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
    } else if (type == BUILDING_TRIUMPHAL_ARCH) {
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
static void get_building_base_xy(int map_x, int map_y, int building_size, int *x, int *y) {
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
static int is_blocked_for_building(int grid_offset, int num_tiles, int *blocked_tiles) {
    int orientation_index = city_view_orientation() / 2;
    int blocked = 0;
    for (int i = 0; i < num_tiles; i++) {
        int tile_offset = grid_offset;// + TILE_GRID_OFFSETS[orientation_index][i];
        switch (GAME_ENV) {
            case ENGINE_ENV_C3:
                tile_offset += TILE_GRID_OFFSETS_C3[orientation_index][i];
                break;
            case ENGINE_ENV_PHARAOH:
                tile_offset += TILE_GRID_OFFSETS_PH[orientation_index][i];
                break;
        }
        int tile_blocked = 0;
        if (map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR))
            tile_blocked = 1;
        if (map_terrain_count_directly_adjacent_with_type(grid_offset, TERRAIN_FLOODPLAIN) > 0
            || map_terrain_count_diagonally_adjacent_with_type(grid_offset, TERRAIN_FLOODPLAIN) > 0)
            tile_blocked = 1;

        if (map_has_figure_at(tile_offset))
            tile_blocked = 1;

        blocked_tiles[i] = tile_blocked;
        blocked += tile_blocked;
    }
    return blocked;
}

static void draw_flat_tile(int x, int y, color_t color_mask) {
    ImageDraw::img_blended(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, color_mask);
}
static void draw_partially_blocked(int x, int y, int fully_blocked, int num_tiles, int *blocked_tiles) {
    for (int i = 0; i < num_tiles; i++) {
        int x_offset = x + X_VIEW_OFFSETS[i];
        int y_offset = y + Y_VIEW_OFFSETS[i];
        if (fully_blocked || blocked_tiles[i])
            draw_flat_tile(x_offset, y_offset, COLOR_MASK_RED);
        else
            draw_flat_tile(x_offset, y_offset, COLOR_MASK_GREEN);
    }
}
void draw_building(int image_id, int x, int y, color_t color_mask) {
    ImageDraw::isometric_footprint(image_id, x, y, color_mask);
    ImageDraw::isometric_top(image_id, x, y, color_mask);
}
static void draw_fountain_range(int x, int y, int grid_offset) {
    ImageDraw::img_alpha_blended(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, COLOR_MASK_BLUE);
}
static void draw_warehouse(int image_id, int x, int y) {
    int image_id_space = image_id_from_group(GROUP_BUILDING_WAREHOUSE_STORAGE_EMPTY);
    int corner = building_rotation_get_corner(building_rotation_get_building_orientation(building_rotation_get_rotation()));
    for (int i = 0; i < 9; i++) {
        if (i == corner) {
            draw_building(image_id, x + X_VIEW_OFFSETS[i], y + Y_VIEW_OFFSETS[i]);
            ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_WAREHOUSE) + 17, x + X_VIEW_OFFSETS[i] - 4,
                                   y + Y_VIEW_OFFSETS[i] - 42, COLOR_MASK_GREEN);
        } else
            draw_building(image_id_space, x + X_VIEW_OFFSETS[i], y + Y_VIEW_OFFSETS[i]);
    }
}

static void draw_regular_building(int type, int image_id, int x, int y, int grid_offset) {
    if (building_is_farm(type)) {
        image_id = get_farm_image(grid_offset);
        draw_building(image_id, x, y);
        // fields
        if (GAME_ENV == ENGINE_ENV_C3) {
            for (int i = 4; i < 9; i++)
                ImageDraw::isometric_footprint(image_id + 1, x + X_VIEW_OFFSETS[i], y + Y_VIEW_OFFSETS[i],
                                               COLOR_MASK_GREEN);
        } else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            draw_ph_crops(type, 0, grid_offset, x - 60, y + 30, COLOR_MASK_GREEN);
    } else if (type == BUILDING_WAREHOUSE)
        draw_warehouse(image_id, x, y);
    else if (type == BUILDING_GRANARY) {
        if (GAME_ENV == ENGINE_ENV_C3) {
            ImageDraw::isometric_footprint(image_id, x, y, COLOR_MASK_GREEN);
            const image *img = image_get(image_id + 1);
            ImageDraw::img_generic(image_id + 1, x + img->sprite_offset_x - 32, y + img->sprite_offset_y - 64,
                                   COLOR_MASK_GREEN);
        } else
            draw_building(image_id, x, y);
    } else if (type == BUILDING_HOUSE_VACANT_LOT)
        draw_building(image_id_from_group(GROUP_BUILDING_HOUSE_VACANT_LOT), x, y);
    else if (type == BUILDING_TRIUMPHAL_ARCH) {
        draw_building(image_id, x, y);
        const image *img = image_get(image_id + 1);
        if (image_id == image_id_from_group(GROUP_BUILDING_TRIUMPHAL_ARCH))
            ImageDraw::img_generic(image_id + 1, x + img->sprite_offset_x + 4, y + img->sprite_offset_y - 51,
                                   COLOR_MASK_GREEN);
        else
            ImageDraw::img_generic(image_id + 1, x + img->sprite_offset_x - 33, y + img->sprite_offset_y - 56,
                                   COLOR_MASK_GREEN);
    } else if (building_is_statue(type)) {
        image_id = get_statue_image(type, building_rotation_get_rotation() + 1, building_rotation_get_building_variant());
        draw_building(image_id, x, y);
    } else if (type == BUILDING_WELL) {
        if (config_get(CONFIG_UI_SHOW_WATER_STRUCTURE_RANGE))
            city_view_foreach_tile_in_range(grid_offset, 1, 2, draw_fountain_range);
        draw_building(image_id, x, y);
    } else if (type != BUILDING_CLEAR_LAND)
        draw_building(image_id, x, y);
}

static void draw_single_reservoir(int x, int y, int has_water) {
    int image_id = image_id_from_group(GROUP_BUILDING_RESERVOIR);
    draw_building(image_id, x, y);
    if (has_water) {
        const image *img = image_get(image_id);
        int x_water = x - 58 + img->sprite_offset_x - 2;
        int y_water = y + img->sprite_offset_y - (img->height - 90);
        ImageDraw::img_generic(image_id + 1, x_water, y_water, COLOR_MASK_GREEN);
    }
}
static void draw_first_reservoir_range(int x, int y, int grid_offset) {
    if (reservoir_range_data.save_offsets) {
        reservoir_range_data.offsets[reservoir_range_data.total] = grid_offset;
        reservoir_range_data.total++;
    }
    ImageDraw::img_alpha_blended(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, COLOR_MASK_BLUE);
}
static void draw_second_reservoir_range(int x, int y, int grid_offset) {
    for (int i = 0; i < reservoir_range_data.total; ++i) {
        if (reservoir_range_data.offsets[i] == grid_offset)
            return;
    }
    ImageDraw::img_alpha_blended(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, COLOR_MASK_BLUE);
}
static void draw_aqueduct(const map_tile *tile, int x, int y) {
    int grid_offset = tile->grid_offset;
    bool  blocked = false;
    if (Planner.in_progress) { // already dragging aqueduct
        if (!Planner.cost) // ???
            blocked = true;
    } else {
        if (map_terrain_is(grid_offset, TERRAIN_ROAD)) { // starting new aqueduct line
            blocked = !map_is_straight_road_for_aqueduct(grid_offset); // can't start over a road curve!
            if (map_property_is_plaza_or_earthquake(grid_offset)) // todo: plaza not allowing aqueducts? maybe?
                blocked = true;
        } else if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR) && !map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) // terrain is not clear!
            blocked = true;
    }
    if (city_finance_out_of_money()) // check sufficient funds to continue
        blocked = true;
    if (blocked) // cannot draw!
        draw_flat_tile(x, y, COLOR_MASK_RED);
    else {
        const terrain_image *img = map_image_context_get_aqueduct(grid_offset, 1); // get starting tile
        draw_building(get_aqueduct_image(grid_offset, map_terrain_is(grid_offset, TERRAIN_ROAD), 0, img), x, y);
    }
}
static void draw_bridge(const map_tile *tile, int x, int y, int type) {
    int length, direction;
    int end_grid_offset = map_bridge_calculate_length_direction(tile->x, tile->y, &length, &direction);

    int dir = direction - city_view_orientation();
    if (dir < 0)
        dir += 8;

    int blocked = 0;
    if (type == BUILDING_SHIP_BRIDGE && length < 5)
        blocked = 1;
    else if (!end_grid_offset)
        blocked = 1;

    if (city_finance_out_of_money())
        blocked = 1;

    int x_delta, y_delta;
    switch (dir) {
        case DIR_0_TOP_RIGHT:
            x_delta = 29;
            y_delta = -15;
            break;
        case DIR_2_BOTTOM_RIGHT:
            x_delta = 29;
            y_delta = 15;
            break;
        case DIR_4_BOTTOM_LEFT:
            x_delta = -29;
            y_delta = 15;
            break;
        case DIR_6_TOP_LEFT:
            x_delta = -29;
            y_delta = -15;
            break;
        default:
            return;
    }
    if (blocked) {
        draw_flat_tile(x, y, length > 0 ? COLOR_MASK_GREEN : COLOR_MASK_RED);
        if (length > 1)
            draw_flat_tile(x + x_delta * (length - 1), y + y_delta * (length - 1), COLOR_MASK_RED);

    } else {
        if (dir == DIR_0_TOP_RIGHT || dir == DIR_6_TOP_LEFT) {
            for (int i = length - 1; i >= 0; i--) {
                int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_SHIP_BRIDGE);
                city_draw_bridge_tile(x + x_delta * i, y + y_delta * i, sprite_id, COLOR_MASK_GREEN);
            }
        } else {
            for (int i = 0; i < length; i++) {
                int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_SHIP_BRIDGE);
                city_draw_bridge_tile(x + x_delta * i, y + y_delta * i, sprite_id, COLOR_MASK_GREEN);
            }
        }
    }
}
static void draw_fort(const map_tile *tile, int x, int y) {
    int fully_blocked = 0;
    int blocked = 0;
    if (formation_get_num_legions_cached() >= formation_get_max_legions() || city_finance_out_of_money()) {
        fully_blocked = 1;
        blocked = 1;
    }

    int num_tiles_fort = building_properties_for_type(BUILDING_MENU_FORTS)->size;
    num_tiles_fort *= num_tiles_fort;
    int num_tiles_ground = building_properties_for_type(BUILDING_FORT_GROUND)->size;
    num_tiles_ground *= num_tiles_ground;

    int grid_offset_fort = tile->grid_offset;
    int grid_offset_ground = grid_offset_fort;// + FORT_GROUND_GRID_OFFSETS[building_rotation_get_rotation()][city_view_orientation()/2];
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            grid_offset_ground += FORT_GROUND_GRID_OFFSETS_C3[building_rotation_get_rotation()][
                    city_view_orientation() / 2];
            break;
        case ENGINE_ENV_PHARAOH:
            grid_offset_ground += FORT_GROUND_GRID_OFFSETS_PH[building_rotation_get_rotation()][
                    city_view_orientation() / 2];
            break;
    }
    int blocked_tiles_fort[MAX_TILES];
    int blocked_tiles_ground[MAX_TILES];

    blocked += is_blocked_for_building(grid_offset_fort, num_tiles_fort, blocked_tiles_fort);
    blocked += is_blocked_for_building(grid_offset_ground, num_tiles_ground, blocked_tiles_ground);

    int orientation_index = building_rotation_get_building_orientation(building_rotation_get_rotation()) / 2;
    int x_ground = x + FORT_GROUND_X_VIEW_OFFSETS[orientation_index];
    int y_ground = y + FORT_GROUND_Y_VIEW_OFFSETS[orientation_index];

    if (blocked) {
        draw_partially_blocked(x, y, fully_blocked, num_tiles_fort, blocked_tiles_fort);
        draw_partially_blocked(x_ground, y_ground, fully_blocked, num_tiles_ground, blocked_tiles_ground);
    } else {
        int image_id = image_id_from_group(GROUP_BUILDING_FORT);
        if (orientation_index == 0 || orientation_index == 3) {
            // draw fort first, then ground
            draw_building(image_id, x, y);
            draw_building(image_id + 1, x_ground, y_ground);
        } else {
            // draw ground first, then fort
            draw_building(image_id + 1, x_ground, y_ground);
            draw_building(image_id, x, y);
        }
    }
}

void BuildPlanner::load_build_graphics() {
    const building_properties *props = building_properties_for_type(building_type);
    switch (building_type) {
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_RA:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
        case BUILDING_TEMPLE_COMPLEX_BAST: {
            // size of every big item 3x3, in general 7x13
            // 25 max tiles at the moment to check blocked tiles
            int main_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_MAIN, building_type);
            int oracle_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_ORACLE, building_type);
            int altar_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_ALTAR, building_type);
            int flooring_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_FLOORING, building_type);
            int statue1_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_STATUE_1, building_type);
            int statue2_image_id = image_id_from_group(GROUP_BUILDING_TEMPLE_COMPLEX_STATUE_2, building_type);

            int EMPTY = 0;
            int mn_1A = main_image_id;
            int mn_1B = main_image_id + 3;
            int mn_2A = oracle_image_id;
            int mn_2B = oracle_image_id + 3;
            int mn_3A = altar_image_id;
            int mn_3B = altar_image_id + 3;

            int til_0 = flooring_image_id + 0;
            int til_1 = flooring_image_id + 1;
            int til_2 = flooring_image_id + 2;
            int til_3 = flooring_image_id + 3;

            int smst0 = statue1_image_id + 0; // north
            int smst1 = statue1_image_id + 1; // east
            int smst2 = statue1_image_id + 2; // south
            int smst3 = statue1_image_id + 3; // west

            int lst0A = statue2_image_id + 0; // north
            int lst0B = statue2_image_id + 1;
            int lst1A = statue2_image_id + 2; // east
            int lst1B = statue2_image_id + 3;
            int lst2A = statue2_image_id + 4; // south
            int lst2B = statue2_image_id + 5;
            int lst3A = statue2_image_id + 6; // west
            int lst3B = statue2_image_id + 7;

//            building_rotation_force_two_orientations();
//            orientation = building_rotation_get_building_orientation(building_rotation_get_rotation()) / 2;
            switch (orientation) { // it goes counterclockwise.
                case 0: { // SE
                    int TEMPLE_COMPLEX_SCHEME[7][13] = {
                            {smst0, smst0, til_1, smst0, smst0, til_1, smst0, smst0, til_0, til_2, til_3, til_2, til_3},
                            {til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0, til_0, til_0, lst2B, lst2B, lst2B},
                            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, til_0, lst2A, lst2A, lst2A},
                            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, til_1, til_1, til_1, til_1},
                            {mn_1A, EMPTY, EMPTY, mn_2A, EMPTY, EMPTY, mn_3A, EMPTY, EMPTY, til_0, lst0B, lst0B, lst0B},
                            {til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0, til_0, til_0, lst0A, lst0A, lst0A},
                            {smst2, smst2, til_1, smst2, smst2, til_1, smst2, smst2, til_0, til_2, til_3, til_2, til_3},
                    };
                    init_tiles(13, 7);
                    set_graphics_array((int *)TEMPLE_COMPLEX_SCHEME, 13, 7);
                    set_pivot(0, 2);
                    break;
                }
                case 1: { // NE
                    int TEMPLE_COMPLEX_SCHEME[13][7] = {
                            {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
                            {til_2, lst1A, lst1B, til_1, lst3A, lst3B, til_2},
                            {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
                            {til_2, til_0, til_0, til_1, til_0, til_0, til_2},
                            {til_0, til_0, EMPTY, EMPTY, EMPTY, til_0, til_0},
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {smst3, til_0, mn_1B, EMPTY, EMPTY, til_0, smst1},
                            {til_1, til_1, EMPTY, EMPTY, EMPTY, til_1, til_1},
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {smst3, til_0, mn_2B, EMPTY, EMPTY, til_0, smst1},
                            {til_1, til_1, EMPTY, EMPTY, EMPTY, til_1, til_1},
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {smst3, til_0, mn_3B, EMPTY, EMPTY, til_0, smst1},
                    };
                    init_tiles(7, 13);
                    set_graphics_array((int *)TEMPLE_COMPLEX_SCHEME, 7, 13);
                    set_pivot(2, 12);
                    break;
                }
                case 2: { // NW
                    int TEMPLE_COMPLEX_SCHEME[7][13] = {

                            {til_3, til_2, til_3, til_2, til_0, smst0, smst0, til_1, smst0, smst0, til_1, smst0, smst0},
                            {lst2B, lst2B, lst2B, til_0, til_0, til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0},
                            {lst2A, lst2A, lst2A, til_0, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                            {til_1, til_1, til_1, til_1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                            {lst0B, lst0B, lst0B, til_0, mn_1A, EMPTY, EMPTY, mn_2A, EMPTY, EMPTY, mn_3A, EMPTY, EMPTY},
                            {lst0A, lst0A, lst0A, til_0, til_0, til_0, til_0, til_1, til_0, til_0, til_1, til_0, til_0},
                            {til_3, til_2, til_3, til_2, til_0, smst2, smst2, til_1, smst2, smst2, til_1, smst2, smst2},
                    };
                    init_tiles(13, 7);
                    set_graphics_array((int *)TEMPLE_COMPLEX_SCHEME, 13, 7);
                    set_pivot(12, 2);
                    break;
                }
                case 3: { // SW
                    int TEMPLE_COMPLEX_SCHEME[13][7] = {
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {til_1, til_1, mn_1B, EMPTY, EMPTY, til_1, til_1},
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {til_1, til_1, mn_2B, EMPTY, EMPTY, til_1, til_1},
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {smst3, til_0, EMPTY, EMPTY, EMPTY, til_0, smst1},
                            {til_0, til_0, mn_3B, EMPTY, EMPTY, til_0, til_0},
                            {til_2, til_0, til_0, til_1, til_0, til_0, til_2},
                            {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
                            {til_2, lst1A, lst1B, til_1, lst3A, lst3B, til_2},
                            {til_3, lst1A, lst1B, til_1, lst3A, lst3B, til_3},
                    };
                    init_tiles(7, 13);
                    set_graphics_array((int *)TEMPLE_COMPLEX_SCHEME, 7, 13);
                    set_pivot(2, 0);
                    break;
                }
            }
            break;
        }
        default: // regular buildings
            init_tiles(props->size, props->size);
            int empty_row[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int draw_row[] = {image_id_from_group(props->image_collection, props->image_group), 0, 0, 0, 0, 0, 0, 0, 0, 0};
            for (int row = 0; row < size.y; ++row) {
                if (row == size.y - 1)
                    set_graphics_row(row, draw_row, size.x);
                else
                    set_graphics_row(row, empty_row, size.x);
            }
            break;
    }
}

static void draw_monument_blueprint(const map_tile *tile, int x, int y, int type) {
    // TODO: implement monuments
}
static void draw_shipyard_wharf(const map_tile *tile, int x, int y, int type) {
    int dir_absolute, dir_relative; // todo: water lift
    int blocked = map_water_determine_orientation_size2(tile->x, tile->y, 1, &dir_absolute);
    if (city_finance_out_of_money())
        blocked = 999; // ????

    if (blocked) {
        for (int i = 0; i < 4; i++)
            draw_flat_tile(x + X_VIEW_OFFSETS[i], y + Y_VIEW_OFFSETS[i], COLOR_MASK_RED);
    } else {
        const building_properties *props = building_properties_for_type(type);
        int image_id = image_id_from_group(props->image_collection, props->image_group) + props->image_offset + dir_relative;
        draw_building(image_id, x, y);
    }
}
static void draw_dock(const map_tile *tile, int x, int y) {
    int dir_absolute, dir_relative;
    int blocked = map_water_determine_orientation_size3(tile->x, tile->y, 1, &dir_absolute);
    if (city_finance_out_of_money())
        blocked = 1;
    if (blocked) {
        for (int i = 0; i < 9; i++)
            draw_flat_tile(x + X_VIEW_OFFSETS[i], y + Y_VIEW_OFFSETS[i], COLOR_MASK_RED);
    } else {
        int image_id;
        if (GAME_ENV == ENGINE_ENV_C3)
            switch (dir_relative) {
                case 0:
                    image_id = image_id_from_group(GROUP_BUILDING_DOCK_1);
                    break;
                case 1:
                    image_id = image_id_from_group(GROUP_BUILDING_DOCK_2);
                    break;
                case 2:
                    image_id = image_id_from_group(GROUP_BUILDING_DOCK_3);
                    break;
                default:
                    image_id = image_id_from_group(GROUP_BUILDING_DOCK_4);
                    break;
            }
        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            image_id = image_id_from_group(GROUP_BUILDING_DOCK_1) + dir_relative;
        draw_building(image_id, x, y);
    }
}
static void draw_road(const map_tile *tile, int x, int y) {
    int grid_offset = tile->grid_offset;
    int blocked = 0;
    int image_id = 0;
    if (map_terrain_is(grid_offset, TERRAIN_AQUEDUCT)) {
        image_id = image_id_from_group(GROUP_BUILDING_AQUEDUCT);
        if (map_can_place_road_under_aqueduct(grid_offset))
            image_id += map_get_aqueduct_with_road_image(grid_offset);
        else
            blocked = 1;
    } else if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR - TERRAIN_FLOODPLAIN))
        blocked = 1;
    else {
        if (GAME_ENV == ENGINE_ENV_C3)
            image_id = image_id_from_group(GROUP_TERRAIN_ROAD);
        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            image_id = image_id_from_group(GROUP_TERRAIN_DIRT_ROAD);
        if (!map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_ROAD) &&
            map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_ROAD))
            image_id++;
        if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) // inundated floodplains
                blocked = 1;
        }
        else if (map_terrain_has_adjecent_with_type(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_count_directly_adjacent_with_type(grid_offset, TERRAIN_FLOODPLAIN) != 1)
                blocked = 1;
            else {
                if (map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_FLOODPLAIN)) {
                    if (map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_ROAD))
                        blocked = 1;
                    else
                        image_id++;
                }
                if (map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_FLOODPLAIN) &&
                    map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_ROAD))
                    blocked = 1;
            }
        }
    }
    if (city_finance_out_of_money())
        blocked = 1;
    if (blocked)
        draw_flat_tile(x, y, COLOR_MASK_RED);
    else
        draw_building(image_id, x, y);
}

static void draw_entertainment_venue(const map_tile *tile, int x, int y, int type) {
    int can_build = 0;
//    const building_properties *props = building_properties_for_type(type);
    int size = 0;
    int orientation = 0;
//    map_tile northern_corner = *tile;
    switch (type) {
        case BUILDING_BOOTH:
            size = 2; break;
        case BUILDING_BANDSTAND:
            size = 3; break;
            break;
        case BUILDING_PAVILLION:
            size = 4; break;
            break;
        case BUILDING_FESTIVAL_SQUARE:
            size = 5; break;
            break;
    }
//    int map_orientation = city_view_orientation();
//    switch (map_orientation) {
//        case 2: // east
//            northern_corner.x -= (size - 1);
//            break;
//        case 4: // south
//            northern_corner.x -= (size - 1);
//            northern_corner.y -= (size - 1);
//            break;
//        case 6: // west
//            northern_corner.y -= (size - 1);
//            break;
//    }
    switch (type) {
        case BUILDING_BOOTH:
            can_build = map_orientation_for_venue_with_map_orientation(tile->x, tile->y, 0, &orientation);
            break;
        case BUILDING_BANDSTAND:
            can_build = map_orientation_for_venue_with_map_orientation(tile->x, tile->y, 1, &orientation);
            break;
        case BUILDING_PAVILLION:
            can_build = map_orientation_for_venue_with_map_orientation(tile->x, tile->y, 2, &orientation);
            break;
        case BUILDING_FESTIVAL_SQUARE:
            can_build = map_orientation_for_venue_with_map_orientation(tile->x, tile->y, 3, &orientation);
            break;
    }
    // TODO: proper correct for map orientation (for now, just use a different orientation)
    orientation = abs(orientation + (8 - city_view_orientation())) % 8;

    if (can_build != 1) { // no can place
        for (int i = 0; i < size * size; i++)
            draw_flat_tile(x + X_VIEW_OFFSETS[i], y + Y_VIEW_OFFSETS[i], COLOR_MASK_RED);
    } else { // can place (theoretically)
        if (type == BUILDING_FESTIVAL_SQUARE && city_building_has_festival_square()) {
            for (int i = 0; i < size * size; i++)
                ImageDraw::isometric_footprint(image_id_from_group(GROUP_FESTIVAL_SQUARE) + i,
                                               x + ((i % size) - (i / size)) * 30,
                                               y + ((i % size) + (i / size)) * 15,
                                               COLOR_MASK_RED);
            return;
        }
        switch (type) {
            case BUILDING_BOOTH:
                for (int i = 0; i < size * size; i++)
                    ImageDraw::isometric_footprint(image_id_from_group(GROUP_BOOTH_SQUARE) + i,
                                                   x + ((i % size) - (i / size)) * 30,
                                                   y + ((i % size) + (i / size)) * 15,
                                                   COLOR_MASK_GREEN);
                switch (orientation / 2) {
                    case 0:
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x, y, COLOR_MASK_GREEN);
                        break;
                    case 1:
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x + 30, y + 15, COLOR_MASK_GREEN);
                        break;
                    case 2:
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x, y + 30, COLOR_MASK_GREEN);
                        break;
                    case 3:
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x - 30, y + 15, COLOR_MASK_GREEN);
                        break;
                }
                break;
            case BUILDING_BANDSTAND:
                for (int i = 0; i < size * size; i++)
                    ImageDraw::isometric_footprint(image_id_from_group(GROUP_BANDSTAND_SQUARE) + i,
                                                   x + ((i % size) - (i / size)) * 30,
                                                   y + ((i % size) + (i / size)) * 15,
                                                   COLOR_MASK_GREEN);
                switch (orientation / 2) {
                    case 0:
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x, y, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x - 30, y + 15, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x + 60, y + 30, COLOR_MASK_GREEN);
                        break;
                    case 1:
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 2, x + 30, y + 15, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 3, x + 60, y + 30, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x, y + 60, COLOR_MASK_GREEN);
                        break;
                    case 2:
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x - 30, y + 15, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x - 60, y + 30, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x, y + 60, COLOR_MASK_GREEN);
                        break;
                    case 3:
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 2, x, y, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 3, x + 30, y + 15, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x - 60, y + 30, COLOR_MASK_GREEN);
                        break;
                }
                break;
            case BUILDING_PAVILLION:
                for (int i = 0; i < size * size; i++)
                    ImageDraw::isometric_footprint(image_id_from_group(GROUP_PAVILLION_SQUARE) + i,
                                                   x + ((i % size) - (i / size)) * 30,
                                                   y + ((i % size) + (i / size)) * 15,
                                                   COLOR_MASK_GREEN);
                switch (orientation) {
                    case 0:
                        draw_building(image_id_from_group(GROUP_BUILDING_PAVILLION), x, y, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x + 90, y + 45, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x + 60, y + 60, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x - 60, y + 30, COLOR_MASK_GREEN);
                        break;
                    case 1:
                        draw_building(image_id_from_group(GROUP_BUILDING_PAVILLION), x + 60, y + 30, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x, y, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x - 30, y + 15, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x - 60, y + 30, COLOR_MASK_GREEN);
                        break;
                    case 2:
                        draw_building(image_id_from_group(GROUP_BUILDING_PAVILLION), x + 30, y + 15, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x + 90, y + 45, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x + 60, y + 60, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x, y + 90, COLOR_MASK_GREEN);
                        break;
                    case 3:
                        draw_building(image_id_from_group(GROUP_BUILDING_PAVILLION), x - 30, y + 45, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x + 30, y + 75, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x, y + 90, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x + 90, y + 45, COLOR_MASK_GREEN);
                        break;
                    case 4:
                        draw_building(image_id_from_group(GROUP_BUILDING_PAVILLION), x + 30, y + 45, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x - 30, y + 15, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x - 60, y + 30, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x - 90, y + 45, COLOR_MASK_GREEN);
                        break;
                    case 5:
                        draw_building(image_id_from_group(GROUP_BUILDING_PAVILLION), x - 30, y + 15, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x + 60, y + 60, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x + 30, y + 75, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x - 90, y + 45, COLOR_MASK_GREEN);
                        break;
                    case 6:
                        draw_building(image_id_from_group(GROUP_BUILDING_PAVILLION), x - 60, y + 30, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x, y + 60, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x - 30, y + 75, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x, y, COLOR_MASK_GREEN);
                        break;
                    case 7:
                        draw_building(image_id_from_group(GROUP_BUILDING_PAVILLION), x, y, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, x + 60, y + 30, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BANDSTAND), x + 30, y + 45, COLOR_MASK_GREEN);
                        draw_building(image_id_from_group(GROUP_BUILDING_BOOTH), x - 90, y + 45, COLOR_MASK_GREEN);
                        break;
                }
                break;
            case BUILDING_FESTIVAL_SQUARE:
                for (int i = 0; i < size * size; i++)
                    ImageDraw::isometric_footprint(image_id_from_group(GROUP_FESTIVAL_SQUARE) + i,
                                                   x + ((i % size) - (i / size)) * 30,
                                                   y + ((i % size) + (i / size)) * 15,
                                                   COLOR_MASK_GREEN);
                break;
        }
    }
}

int city_building_ghost_mark_deleting(const map_tile *tile) {
    if (!config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE))
        return 0;

    int construction_type = Planner.building_type;
    if (!tile->grid_offset || Planner.draw_as_constructing ||
        scroll_in_progress() || construction_type != BUILDING_CLEAR_LAND) {
        return (construction_type == BUILDING_CLEAR_LAND);
    }
    if (!Planner.in_progress)
        map_property_clear_constructing_and_deleted();

    map_building_tiles_mark_deleting(tile->grid_offset);
    return 1;
}
void city_building_ghost_draw(const map_tile *tile) {
    if (!tile->grid_offset) // || scroll_in_progress()
        return;
    int type = Planner.building_type;
    if (Planner.draw_as_constructing || type == BUILDING_NONE || type == BUILDING_CLEAR_LAND)
        return;
    int x, y;
    city_view_get_selected_tile_pixels(&x, &y);

    Planner.update(tile, x, y);
    Planner.draw();
    return;

    // update road required based on timer
//    building_rotation_update_road_orientation();
//    switch (type) {
//        case BUILDING_WATER_LIFT:
//            if (GAME_ENV == ENGINE_ENV_PHARAOH)
////                draw_draggable_waterlift(tile, x, y);
//                draw_shipyard_wharf(tile, x, y, BUILDING_WATER_LIFT);
//            else
//                draw_draggable_reservoir(tile, x, y);
//            break;
//        case BUILDING_IRRIGATION_DITCH:
//            draw_aqueduct(tile, x, y);
//            break;
//        case BUILDING_MENU_BEAUTIFICATION:
//            draw_fountain(tile, x, y);
//            break;
//        case BUILDING_MENU_MONUMENTS:
//            draw_bathhouse(tile, x, y);
//            break;
//        case BUILDING_LOW_BRIDGE:
//        case BUILDING_SHIP_BRIDGE:
//            draw_bridge(tile, x, y, type);
//            break;
//        case BUILDING_FORT_CHARIOTEERS:
//        case BUILDING_FORT_ARCHERS:
//        case BUILDING_FORT_INFANTRY:
//            draw_fort(tile, x, y);
//            break;
//        case BUILDING_SENET_HOUSE:
//            if (GAME_ENV == ENGINE_ENV_C3) {
////                draw_hippodrome(tile, x, y);
//            } else if (GAME_ENV == ENGINE_ENV_PHARAOH)
//                draw_default(tile, x, y, type); // Senet house
//            break;
//        case BUILDING_SHIPYARD:
//        case BUILDING_FISHING_WHARF:
//            draw_shipyard_wharf(tile, x, y, type);
//            break;
//        case BUILDING_DOCK:
//            draw_dock(tile, x, y);
//            break;
//        case BUILDING_ROAD:
//            draw_road(tile, x, y);
//            break;
//        case BUILDING_BOOTH:
//        case BUILDING_BANDSTAND:
//        case BUILDING_PAVILLION:
//        case BUILDING_FESTIVAL_SQUARE:
//            draw_entertainment_venue(tile, x, y, type);
//            break;
//        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
//        case BUILDING_TEMPLE_COMPLEX_RA:
//        case BUILDING_TEMPLE_COMPLEX_PTAH:
//        case BUILDING_TEMPLE_COMPLEX_SETH:
//        case BUILDING_TEMPLE_COMPLEX_BAST:
//            draw_temple_complex(tile, x, y, type - BUILDING_TEMPLE_COMPLEX_OSIRIS);
//            break;
//        case BUILDING_PYRAMID:
//        case BUILDING_SPHYNX:
//        case BUILDING_MAUSOLEUM:
//        case BUILDING_ALEXANDRIA_LIBRARY:
//        case BUILDING_CAESAREUM:
//        case BUILDING_PHAROS_LIGHTHOUSE:
//        case BUILDING_SMALL_ROYAL_TOMB:
//        case BUILDING_ABU_SIMBEL:
//        case BUILDING_MEDIUM_ROYAL_TOMB:
//        case BUILDING_LARGE_ROYAL_TOMB:
//        case BUILDING_GRAND_ROYAL_TOMB:
//            draw_monument_blueprint(tile, x, y, type);
//            break;
//        default:
//            draw_default(tile, x, y, type);
//            break;
//    }
}

void BuildPlanner::draw_flat_tile(int x, int y, color_t color_mask) {
    ImageDraw::img_blended(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, color_mask);
}
void BuildPlanner::draw_blueprints(bool fully_blocked) {
    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {

            // draw tile!
            pixel_coordinate current_coord = pixel_coords_cache[row][column];
            if (tile_blocked_array[row][column] || fully_blocked)
                draw_flat_tile(current_coord.x, current_coord.y, COLOR_MASK_RED);
            else
                draw_flat_tile(current_coord.x, current_coord.y, COLOR_MASK_GREEN);
        }
    }
}
void BuildPlanner::draw_graphics() {

    // go through the tiles DIAGONALLY to render footprint and top correctly
    for (int dg_y = 0; dg_y < size.y + size.x - 1; dg_y++) {
        for (int dg_x = fmax(0, dg_y - size.y + 1); dg_x < size.x && dg_x < dg_y + 1; dg_x++) {

            // extract proper row and column index from the mess above
            int row = dg_y - dg_x;
            int column = dg_x;

            int image_id = tile_graphics_array[row][column];
            if (image_id > 0) {
                pixel_coordinate current_coord = pixel_coords_cache[row][column];
                ImageDraw::isometric_footprint_from_drawtile(image_id, current_coord.x, current_coord.y, COLOR_MASK_GREEN);
                ImageDraw::isometric_top_from_drawtile(image_id, current_coord.x, current_coord.y, COLOR_MASK_GREEN);
            }
        }
    }
}