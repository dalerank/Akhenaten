#include <widget/city/tile_draw.h>
#include <widget/city/ornaments.h>
#include "building_tiles.h"

#include "building/building.h"
#include "building/industry.h"
#include "city/view.h"
#include "core/direction.h"
#include "core/image.h"
#include "map/aqueduct.h"
#include "map/bridge.h"
#include "map/building.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/image.h"
#include "map/property.h"
#include "map/random.h"
#include "map/sprite.h"
#include "map/terrain.h"
#include "map/tiles.h"

#include "graphics/image.h"

void map_set_tile_graphics(tile_graphics_query queries[], int queries_num, int terrain) {
    int x_leftmost, y_leftmost;
    switch (city_view_orientation()) {
        case DIR_0_TOP_RIGHT:
            x_leftmost = 0;
            y_leftmost = 1;
            break;
        case DIR_2_BOTTOM_RIGHT:
            x_leftmost = y_leftmost = 0;
            break;
        case DIR_4_BOTTOM_LEFT:
            x_leftmost = 1;
            y_leftmost = 0;
            break;
        case DIR_6_TOP_LEFT:
            x_leftmost = y_leftmost = 1;
            break;
        default:
            return;
    }
    for (int i = 0; i < queries_num; ++i) {
        tile_graphics_query query = queries[i];
        if (!map_grid_is_inside(query.x, query.y, query.size))
            continue;

        int x_proper = x_leftmost * (query.size - 1);
        int y_proper = y_leftmost * (query.size - 1);
        for (int dy = 0; dy < query.size; dy++) {
            for (int dx = 0; dx < query.size; dx++) {
                int grid_offset = map_grid_offset(query.x + dx, query.y + dy);
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                map_terrain_add(grid_offset, terrain);
                map_building_set(grid_offset, query.building_id);
                map_property_clear_constructing(grid_offset);
                map_property_set_multi_tile_size(grid_offset, query.size);
                map_image_set(grid_offset, query.image_id);
                map_property_set_multi_tile_xy(grid_offset, dx, dy,
                                               dx == x_proper && dy == y_proper);
            }
        }
    }
}

static int north_tile_grid_offset(int x, int y, int *size) {
    int grid_offset = map_grid_offset(x, y);
    *size = map_property_multi_tile_size(grid_offset);
    for (int i = 0; i < *size && map_property_multi_tile_x(grid_offset); i++)
        grid_offset += map_grid_delta(-1, 0);
    for (int i = 0; i < *size && map_property_multi_tile_y(grid_offset); i++)
        grid_offset += map_grid_delta(0, -1);
    return grid_offset;
}
static void adjust_to_absolute_xy(int *x, int *y, int size) {
    switch (city_view_orientation()) {
        case DIR_2_BOTTOM_RIGHT:
            *x = *x - size + 1;
            break;
        case DIR_4_BOTTOM_LEFT:
            *x = *x - size + 1;
            // fall-through
        case DIR_6_TOP_LEFT:
            *y = *y - size + 1;
            break;
    }
}
static void set_crop_tile(int building_id, int x, int y, int dx, int dy, int crop_image_id, int growth) {
    int grid_offset = map_grid_offset(x + dx, y + dy);
    if (GAME_ENV == ENGINE_ENV_C3) {
        map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
        map_terrain_add(grid_offset, TERRAIN_BUILDING);
        map_building_set(grid_offset, building_id);
        map_property_clear_constructing(grid_offset);
        map_property_set_multi_tile_xy(grid_offset, dx, dy, 1);
        map_image_set(grid_offset, crop_image_id + (growth < 4 ? growth : 4));
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        ImageDraw::isometric_footprint(crop_image_id + (growth < 4 ? growth : 4), map_grid_offset_to_x(grid_offset),
                                       map_grid_offset_to_y(grid_offset), 0);
}

void map_building_tiles_add(int building_id, int x, int y, int size, int image_id, int terrain) {
    tile_graphics_query queries[] = {
        {x, y, size, image_id, building_id} // single tile query list
    };
    map_set_tile_graphics(queries, 1, terrain);
}
void map_building_tiles_add_farm(int building_id, int x, int y, int crop_image_offset, int progress) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        crop_image_offset += image_id_from_group(GROUP_BUILDING_FARMLAND);
        if (!map_grid_is_inside(x, y, 3))
            return;
        // farmhouse
        int x_leftmost, y_leftmost;
        switch (city_view_orientation()) {
            case DIR_0_TOP_RIGHT:
                x_leftmost = 0;
                y_leftmost = 1;
                break;
            case DIR_2_BOTTOM_RIGHT:
                x_leftmost = 0;
                y_leftmost = 0;
                break;
            case DIR_4_BOTTOM_LEFT:
                x_leftmost = 1;
                y_leftmost = 0;
                break;
            case DIR_6_TOP_LEFT:
                x_leftmost = 1;
                y_leftmost = 1;
                break;
            default:
                return;
        }
        for (int dy = 0; dy < 2; dy++) {
            for (int dx = 0; dx < 2; dx++) {
                int grid_offset = map_grid_offset(x + dx, y + dy);
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                map_terrain_add(grid_offset, TERRAIN_BUILDING);
                map_building_set(grid_offset, building_id);
                map_property_clear_constructing(grid_offset);
                map_property_set_multi_tile_size(grid_offset, 2);
                map_image_set(grid_offset, image_id_from_group(GROUP_BUILDING_FARM_HOUSE));
                map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == x_leftmost && dy == y_leftmost);
            }
        }
    }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
//        int image_id = image_id_from_group(GROUP_BUILDING_FARM_HOUSE);
//        if (map_terrain_is(map_grid_offset(x, y), TERRAIN_FLOODPLAIN))
//            image_id = image_id_from_group(GROUP_BUILDING_FARMLAND);
        map_building_tiles_add(building_id, x, y, 3, get_farm_image(map_grid_offset(x, y)), TERRAIN_BUILDING);
//        crop_image_offset += image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH);
        return;
    }
    // crop tile 1
    int growth = progress / 10;
    set_crop_tile(building_id, x, y, 0, 2, crop_image_offset, growth);

    // crop tile 2
    growth -= 4;
    if (growth < 0)
        growth = 0;
    set_crop_tile(building_id, x, y, 1, 2, crop_image_offset, growth);

    // crop tile 3
    growth -= 4;
    if (growth < 0)
        growth = 0;
    set_crop_tile(building_id, x, y, 2, 2, crop_image_offset, growth);

    // crop tile 4
    growth -= 4;
    if (growth < 0)
        growth = 0;
    set_crop_tile(building_id, x, y, 2, 1, crop_image_offset, growth);

    // crop tile 5
    growth -= 4;
    if (growth < 0)
        growth = 0;
    set_crop_tile(building_id, x, y, 2, 0, crop_image_offset, growth);
}
int map_building_tiles_add_aqueduct(int x, int y) {
    int grid_offset = map_grid_offset(x, y);
    map_terrain_add(grid_offset, TERRAIN_AQUEDUCT);
    map_property_clear_constructing(grid_offset);
    return 1;
}

void map_add_temple_complex_tiles(building *b) {

}

void map_add_bandstand_tiles(building *b) {
    int b_delta_0_m1 = b->grid_offset - map_grid_delta(0, -1);
    int b_delta_0_1 = b->grid_offset - map_grid_delta(0, 1);
    int b_delta_1_0 = b->grid_offset - map_grid_delta(1, 0);
    int b_delta_m1_0 = b->grid_offset - map_grid_delta(-1, 0);

    int offsets_by_orientation[4];
    switch (city_view_orientation()) {
        case 0: // north
            offsets_by_orientation[0] = b_delta_0_m1;
            offsets_by_orientation[1] = b_delta_0_1;
            offsets_by_orientation[2] = b_delta_1_0;
            offsets_by_orientation[3] = b_delta_m1_0;
            break;
        case 2: // east
            offsets_by_orientation[3] = b_delta_0_m1;
            offsets_by_orientation[2] = b_delta_0_1;
            offsets_by_orientation[0] = b_delta_1_0;
            offsets_by_orientation[1] = b_delta_m1_0;
            break;
        case 4: // south
            offsets_by_orientation[1] = b_delta_0_m1;
            offsets_by_orientation[0] = b_delta_0_1;
            offsets_by_orientation[3] = b_delta_1_0;
            offsets_by_orientation[2] = b_delta_m1_0;
            break;
        case 6: // west
            offsets_by_orientation[2] = b_delta_0_m1;
            offsets_by_orientation[3] = b_delta_0_1;
            offsets_by_orientation[1] = b_delta_1_0;
            offsets_by_orientation[0] = b_delta_m1_0;
            break;
    }

    for (int j = 0; j < 4; ++j) {
        auto neighbor = building_at(offsets_by_orientation[j]);
        if (neighbor->type == BUILDING_BANDSTAND
            && neighbor->grid_offset == offsets_by_orientation[j]
            && neighbor->main() == b->main()) {
            map_image_set(neighbor->grid_offset, image_id_from_group(GROUP_BUILDING_BANDSTAND) + j);
            continue;
        }
    }
}
static void set_underlying_venue_plaza_tile(int grid_offset, int building_id, int image_id, bool update_only) {
    if (!update_only) {
        map_image_set(grid_offset, image_id);
        map_terrain_add(grid_offset, TERRAIN_BUILDING);
        map_building_set(grid_offset, building_id);
        map_property_clear_constructing(grid_offset);
    } else {
        if (building_get(building_id)->type == BUILDING_FESTIVAL_SQUARE || map_terrain_is(grid_offset, TERRAIN_ROAD))
            map_image_set(grid_offset, image_id);
    }
}
void map_add_venue_plaza_tiles(int building_id, int size, int x, int y, int image_id, bool update_only) {
    switch (city_view_orientation()) {
        case 0: // north
            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    int grid_offset = map_grid_offset(x + dx, y + dy);
                    set_underlying_venue_plaza_tile(grid_offset, building_id, image_id + dx + (dy * size), update_only);
                }
            }
            break;
        case 2: // east
            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    int grid_offset = map_grid_offset(x + size - 1 - dy, y + dx);
                    set_underlying_venue_plaza_tile(grid_offset, building_id, image_id + dx + (dy * size), update_only);
                }
            }
            break;
        case 4: // south
            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    int grid_offset = map_grid_offset(x + size - 1 - dx, y + size - 1 - dy);
                    set_underlying_venue_plaza_tile(grid_offset, building_id, image_id + dx + (dy * size), update_only);
                }
            }
            break;
        case 6: // west
            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    int grid_offset = map_grid_offset(x + dy, y + size - 1 - dx);
                    set_underlying_venue_plaza_tile(grid_offset, building_id, image_id + dx + (dy * size), update_only);
                }
            }
            break;
    }
}

void map_building_tiles_remove(int building_id, int x, int y) {
    if (!map_grid_is_inside(x, y, 1))
        return;
    int size; // todo: monuments???
    int base_grid_offset = north_tile_grid_offset(x, y, &size);
    if (map_terrain_get(base_grid_offset) == TERRAIN_ROCK)
        return;
    building *b = building_get(building_id);
    if (building_id && building_is_farm(b->type))
        size = 3;
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        switch (b->type) {
            case BUILDING_BOOTH:
                size = 2;
                base_grid_offset = b->data.entertainment.booth_corner_grid_offset;
                break;
            case BUILDING_BANDSTAND:
                size = 3;
                base_grid_offset = b->data.entertainment.booth_corner_grid_offset;
                break;
            case BUILDING_PAVILLION:
                size = 4;
                base_grid_offset = b->data.entertainment.booth_corner_grid_offset;
                break;
            case BUILDING_FESTIVAL_SQUARE:
                size = 5;
                break;
        }
    }
    x = map_grid_offset_to_x(base_grid_offset);
    y = map_grid_offset_to_y(base_grid_offset);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = map_grid_offset(x + dx, y + dy);
//            if (building_id && map_building_at(grid_offset) != building_id)
//                continue;

            if (building_id && b->type != BUILDING_BURNING_RUIN)
                map_set_rubble_building_type(grid_offset, b->type);

            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_property_clear_multi_tile_xy(grid_offset);
            map_property_mark_draw_tile(grid_offset);
            map_aqueduct_set(grid_offset, 0);
            map_building_set(grid_offset, 0);
            map_building_damage_clear(grid_offset);
            map_sprite_clear_tile(grid_offset);
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                map_terrain_set(grid_offset, TERRAIN_WATER); // clear other flags
                map_tiles_set_water(x + dx, y + dy);
            } else {
                map_image_set(grid_offset,
                              image_id_from_group(GROUP_TERRAIN_UGLY_GRASS) +
                              (map_random_get(grid_offset) & 7));
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE - TERRAIN_ROAD);
            }
        }
    }
    map_tiles_update_region_empty_land(true, x - 2, y - 2, x + size + 2, y + size + 2);
    map_tiles_update_region_meadow(x, y, x + size, y + size);
    map_tiles_update_region_rubble(x, y, x + size, y + size);
}
void map_building_tiles_set_rubble(int building_id, int x, int y, int size) {
    if (!map_grid_is_inside(x, y, size))
        return;
    building *b = building_get(building_id);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = map_grid_offset(x + dx, y + dy);
            if (map_building_at(grid_offset) != building_id)
                continue;

            if (building_id && building_at(grid_offset)->type != BUILDING_BURNING_RUIN)
                map_set_rubble_building_type(grid_offset, b->type);
            else if (!building_id && map_terrain_get(grid_offset) & TERRAIN_WALL)
                map_set_rubble_building_type(grid_offset, BUILDING_WALL);

            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_aqueduct_set(grid_offset, 0);
            map_building_set(grid_offset, 0);
            map_building_damage_clear(grid_offset);
            map_sprite_clear_tile(grid_offset);
            map_property_set_multi_tile_xy(grid_offset, 0, 0, 1);
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                map_terrain_set(grid_offset, TERRAIN_WATER); // clear other flags
                map_tiles_set_water(x + dx, y + dy);
            } else {
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                map_terrain_add(grid_offset, TERRAIN_RUBBLE);
                map_image_set(grid_offset,
                              image_id_from_group(GROUP_TERRAIN_RUBBLE) + (map_random_get(grid_offset) & 7));
            }
        }
    }
}
int map_building_tiles_mark_construction(int x, int y, int size, int terrain, int absolute_xy) {
    if (!absolute_xy)
        adjust_to_absolute_xy(&x, &y, size);

    if (!map_grid_is_inside(x, y, size))
        return 0;

    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = map_grid_offset(x + dx, y + dy);
            if (map_terrain_is(grid_offset, terrain & TERRAIN_NOT_CLEAR) || map_has_figure_at(grid_offset) || map_terrain_exists_tile_in_radius_with_type(x + dx, y + dy, 1, 1, TERRAIN_FLOODPLAIN))
                return 0;

        }
    }

    // update empty land
    // todo: maybe...
    // -----> map_property_is_constructing() <------
//    map_tiles_update_region_empty_land(x - 2, y - 2, x + size + 2, y + size + 2);

    // mark as being constructed
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = map_grid_offset(x + dx, y + dy);
            map_property_mark_constructing(grid_offset);
        }
    }
    return 1;
}
void map_building_tiles_mark_deleting(int grid_offset) {
    int building_id = map_building_at(grid_offset);
    if (!building_id)
        map_bridge_remove(grid_offset, 1);
    else
        grid_offset = building_get(building_id)->main()->grid_offset;
    map_property_mark_deleted(grid_offset);
}
int map_building_tiles_are_clear(int x, int y, int size, int terrain) {
    adjust_to_absolute_xy(&x, &y, size);
    if (!map_grid_is_inside(x, y, size))
        return 0;

    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = map_grid_offset(x + dx, y + dy);
            if (map_terrain_is(grid_offset, terrain & TERRAIN_NOT_CLEAR))
                return 0;
        }
    }
    return 1;
}