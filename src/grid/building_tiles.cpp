#include "building_tiles.h"

#include "building/monuments.h"
#include "widget/city/ornaments.h"
#include "widget/city/tile_draw.h"
#include "graphics/image.h"

#include "building/building_farm.h"
#include "building/building_entertainment.h"
#include "building/building_temple_complex.h"
#include "grid/canals.h"
#include "grid/bridge.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "game/game.h"
#include "city/city_buildings.h"

static int north_tile_grid_offset(tile2i tile, int* size) {
    int grid_offset = tile.grid_offset();
    *size = map_property_multi_tile_size(grid_offset);
    
    for (int i = 0; i < *size && map_property_multi_tile_x(grid_offset); i++)
        grid_offset += GRID_OFFSET(-1, 0);

    for (int i = 0; i < *size && map_property_multi_tile_y(grid_offset); i++)
        grid_offset += GRID_OFFSET(0, -1);

    return grid_offset;
}
static void adjust_to_absolute_xy(tile2i tile, int size) {
    switch (city_view_orientation()) {
    case DIR_2_BOTTOM_RIGHT:
        tile.set_x(tile.x() - size + 1);
        break;
    case DIR_4_BOTTOM_LEFT:
        tile.set(tile.x() - size + 1);
        // fall-through
    case DIR_6_TOP_LEFT:
        tile.set_y(tile.y() - size + 1);
        break;
    }
}
static void set_crop_tile(painter &ctx, int building_id, int x, int y, int dx, int dy, int crop_image_id, int growth) {
    int grid_offset = MAP_OFFSET(x + dx, y + dy);
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
    //    map_terrain_add(grid_offset, TERRAIN_BUILDING);
    //    map_building_set(grid_offset, building_id);
    //    map_property_clear_constructing(grid_offset);
    //    map_property_set_multi_tile_xy(grid_offset, dx, dy, 1);
    //    map_image_set(grid_offset, crop_image_id + (growth < 4 ? growth : 4));
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH)
    ctx.img_isometric(crop_image_id + (growth < 4 ? growth : 4), vec2i{MAP_X(grid_offset), MAP_Y(grid_offset)});
}

void map_building_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain) {
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

    if (!map_grid_is_inside(tile, size)) {
        return;
    }

    int x_proper = x_leftmost * (size - 1);
    int y_proper = y_leftmost * (size - 1);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = tile.shifted(dx, dy).grid_offset();
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
            map_terrain_add(grid_offset, terrain);
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, size);
            map_image_set(grid_offset, image_id);
            map_property_set_multi_tile_xy(grid_offset, dx, dy, false);
        }
    }
    tile2i draw_tile = tile.shifted(x_proper, y_proper);
    map_property_mark_draw_tile(draw_tile.grid_offset());
}

static void set_underlying_venue_plaza_tile(int grid_offset, int building_id, int image_id, bool update_only) {
    if (!update_only) {
        map_image_set(grid_offset, image_id);
        map_terrain_add(grid_offset, TERRAIN_BUILDING);
        map_building_set(grid_offset, building_id);
        map_property_clear_constructing(grid_offset);
    } else {
        if (building_get(building_id)->type == BUILDING_FESTIVAL_SQUARE || map_terrain_is(grid_offset, TERRAIN_ROAD)) {
            map_image_set(grid_offset, image_id);
        }
    }
}

void map_add_venue_plaza_tiles(int building_id, int size, tile2i tile, int image_id, bool update_only) {
    int x = tile.x();
    int y = tile.y();
    switch (city_view_orientation()) {
    case 0: // north
        for (int dy = 0; dy < size; dy++) {
            for (int dx = 0; dx < size; dx++) {
                int grid_offset = MAP_OFFSET(x + dx, y + dy);
                set_underlying_venue_plaza_tile(grid_offset, building_id, image_id + dx + (dy * size), update_only);
            }
        }
        break;
    case 2: // east
        for (int dy = 0; dy < size; dy++) {
            for (int dx = 0; dx < size; dx++) {
                int grid_offset = MAP_OFFSET(x + size - 1 - dy, y + dx);
                set_underlying_venue_plaza_tile(grid_offset, building_id, image_id + dx + (dy * size), update_only);
            }
        }
        break;
    case 4: // south
        for (int dy = 0; dy < size; dy++) {
            for (int dx = 0; dx < size; dx++) {
                int grid_offset = MAP_OFFSET(x + size - 1 - dx, y + size - 1 - dy);
                set_underlying_venue_plaza_tile(grid_offset, building_id, image_id + dx + (dy * size), update_only);
            }
        }
        break;
    case 6: // west
        for (int dy = 0; dy < size; dy++) {
            for (int dx = 0; dx < size; dx++) {
                int grid_offset = MAP_OFFSET(x + dy, y + size - 1 - dx);
                set_underlying_venue_plaza_tile(grid_offset, building_id, image_id + dx + (dy * size), update_only);
            }
        }
        break;
    }
}

void map_building_tiles_add_temple_complex_parts(building* b) {
    auto complex = b->dcast_temple_complex();
    if (!complex) {
        return;
    }

    auto &d = complex->runtime_data();
    int orientation = (5 - (d.variant / 2)) % 4;
    int orientation_rel = city_view_relative_orientation(orientation);
    int orientation_binary = (1 + orientation_rel) % 2;
    int part = 0;                                             // default = main
    if (b->prev_part_building_id && b->next_part_building_id) // the middle part is ALWAYS the altar
        part = 1;
    //else if (b == get_temple_complex_front_facing_part(b)) // front facing part (oracle)
    //    part = 2;

    auto mainc = b->main()->dcast_temple_complex();
    auto &maind = mainc->runtime_data();
    int image_id = get_temple_complex_part_image(b->type, part, orientation_binary, (bool)(maind.temple_complex_upgrades & part));
    map_building_tiles_add(b->id, b->tile, b->size, image_id, TERRAIN_BUILDING);
    if (b->next_part_building_id) {
        map_building_tiles_add_temple_complex_parts(b->next());
    }
}

void map_building_tiles_remove(int building_id, tile2i tile) {
    if (!map_grid_is_inside(tile, 1)) {
        return;
    }

    int size; // todo: monuments???
    int base_grid_offset = north_tile_grid_offset(tile, &size);
    if (map_terrain_get(base_grid_offset) == TERRAIN_ROCK)
        return;

    building* b = building_get(building_id);
    if (building_id && building_is_farm(b->type)) {
        size = 3;
    }

    switch (b->type) {
    case BUILDING_BOOTH:
    case BUILDING_BANDSTAND:
    case BUILDING_PAVILLION:
        {
            auto &ent = b->dcast_entertainment()->runtime_data();
            size = b->size;
            base_grid_offset = ent.booth_corner_grid_offset;
        }
        break;

    case BUILDING_FESTIVAL_SQUARE:
        size = 5;
        break;

    default:
        ; // nothing
    }

    int x = MAP_X(base_grid_offset);
    int y = MAP_Y(base_grid_offset);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = MAP_OFFSET(x + dx, y + dy);
            //            if (building_id && map_building_at(grid_offset) != building_id)
            //                continue;

            if (building_id && b->type != BUILDING_BURNING_RUIN)
                map_set_rubble_building_type(grid_offset, b->type);

            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_property_clear_multi_tile_xy(grid_offset);
            map_property_mark_draw_tile(grid_offset);
            map_canal_set(grid_offset, 0);
            map_building_set(grid_offset, 0);
            map_building_damage_clear(grid_offset);
            map_sprite_clear_tile(grid_offset);
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                map_terrain_set(grid_offset, TERRAIN_WATER); // clear other flags
                map_tiles_set_water(MAP_OFFSET(x + dx, y + dy));
            } else {
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_UGLY_GRASS) + (map_random_get(grid_offset) & 7));
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE - TERRAIN_ROAD);
            }
        }
    }
    map_tiles_update_region_empty_land(true, tile2i(x - 2, y - 2), tile2i(x + size + 2, y + size + 2));
    map_tiles_update_region_meadow(x - 2, y - 2, x + size + 2, y + size + 2);
    map_tiles_update_region_rubble(x, y, x + size, y + size);
}

void map_building_tiles_set_rubble(int building_id, tile2i tile, int size) {
    if (!map_grid_is_inside(tile, size)) {
        return;
    }
    building* b = building_get(building_id);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            const int grid_offset = tile.shifted(dx, dy).grid_offset();
            if (map_building_at(grid_offset) != building_id)
                continue;

            if (building_id && building_at(grid_offset)->type != BUILDING_BURNING_RUIN) {
                map_set_rubble_building_type(grid_offset, b->type);
            } else if (!building_id && map_terrain_get(grid_offset) & TERRAIN_WALL) {
                map_set_rubble_building_type(grid_offset, BUILDING_MUD_WALL);
            }

            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_canal_set(grid_offset, 0);
            map_building_set(grid_offset, 0);
            map_building_damage_clear(grid_offset);
            map_sprite_clear_tile(grid_offset);
            map_property_set_multi_tile_xy(grid_offset, 0, 0, 1);
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                map_terrain_set(grid_offset, TERRAIN_WATER); // clear other flags
                map_tiles_set_water(grid_offset);
            } else {
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                map_terrain_add(grid_offset, TERRAIN_RUBBLE);
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_RUBBLE) + (map_random_get(grid_offset) & 7));
            }
        }
    }
}

bool map_building_tiles_mark_construction(tile2i tile, int size_x, int size_y, int terrain, bool absolute_xy) {
    if (!absolute_xy) {
        adjust_to_absolute_xy(tile, size_x); // todo??
    }

    if (!map_grid_is_inside(tile, size_x))
        return false;

    if (!map_grid_is_inside(tile, size_y))
        return false;

    for (int dy = 0; dy < size_y; dy++) {
        for (int dx = 0; dx < size_x; dx++) {
            tile2i otile = tile.shifted(dx, dy);
            int grid_offset = otile.grid_offset();
            if (map_terrain_is(grid_offset, terrain & TERRAIN_NOT_CLEAR) || map_has_figure_at(grid_offset)
                || map_terrain_exists_tile_in_radius_with_type(otile, 1, 1, TERRAIN_FLOODPLAIN))
                return false;
        }
    }

    // update empty land
    // todo: maybe...
    // -----> map_property_is_constructing() <------
    //    map_tiles_update_region_empty_land(x - 2, y - 2, x + size + 2, y + size + 2);

    // mark as being constructed
    for (int dy = 0; dy < size_y; dy++) {
        for (int dx = 0; dx < size_x; dx++) {
            int grid_offset = tile.shifted(dx, dy).grid_offset();
            map_property_mark_constructing(grid_offset);
        }
    }
    return true;
}
void map_building_tiles_mark_deleting(int grid_offset) {
    int building_id = map_building_at(grid_offset);
    if (!building_id)
        map_bridge_remove(grid_offset, 1);
    else
        grid_offset = building_get(building_id)->main()->tile.grid_offset();
    map_property_mark_deleted(grid_offset);
}

int map_building_tiles_are_clear(tile2i tile, int size, int terrain) {
    adjust_to_absolute_xy(tile, size);
    if (!map_grid_is_inside(tile, size)) {
        return 0;
    }

    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = tile.shifted(dx, dy).grid_offset();
            if (map_terrain_is(grid_offset, terrain & TERRAIN_NOT_CLEAR))
                return 0;
        }
    }
    return 1;
}