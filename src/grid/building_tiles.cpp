#include "building_tiles.h"

#include "building/monuments.h"
#include "widget/city/ornaments.h"
#include "widget/city/tile_draw.h"
#include "graphics/image.h"

#include "building/building_farm.h"
#include "building/building_entertainment.h"
#include "building/building_temple_complex.h"
#include "core/log.h"
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
    ctx.img_isometric(crop_image_id + (growth < 4 ? growth : 4), vec2i{MAP_X(grid_offset), MAP_Y(grid_offset)}, COLOR_MASK_NONE, 1.f, ImgFlag_None);
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

void map_building_tiles_remove(int building_id, tile2i tile) {
    if (!map_grid_is_inside(tile, 1)) {
        return;
    }

    int size; // todo: monuments???
    int base_grid_offset = north_tile_grid_offset(tile, &size);
    if (map_terrain_get(base_grid_offset) == TERRAIN_ROCK)
        return;

    building* b = building_get(building_id);
    if (building_id && b->is_farm()) {
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
            map_building_tile_clear_at(grid_offset, building_id ? b->type : 0);
        }
    }

    // Defensive sweep: walk the area around b->tile (persisted reliably via
    // iob_buildings) and clear any tile that still claims this building_id.
    // The targeted clear above keys off type-specific anchors like the
    // entertainment building's booth_corner_grid_offset — if that field is
    // stale from an older save (we've seen bandstands from previous builds
    // leave their textures + TERRAIN_BUILDING behind on demolition), the
    // anchor points elsewhere and the real footprint is never cleared. Going
    // by the building_grid itself catches that case for any building type.
    if (building_id) {
        int sx = b->tile.x();
        int sy = b->tile.y();
        int span = (size > b->size ? size : b->size) + 2; // +1 either side
        int leaks = 0;
        int leak_min_x = 0, leak_min_y = 0, leak_max_x = 0, leak_max_y = 0;
        for (int dy = -1; dy < span; dy++) {
            for (int dx = -1; dx < span; dx++) {
                tile2i t(sx + dx, sy + dy);
                if (!map_grid_is_inside(t, 1)) {
                    continue;
                }
                int grid_offset = t.grid_offset();
                if (map_building_at(grid_offset) != building_id) {
                    continue;
                }
                if (leaks == 0) {
                    leak_min_x = leak_max_x = t.x();
                    leak_min_y = leak_max_y = t.y();
                } else {
                    if (t.x() < leak_min_x) leak_min_x = t.x();
                    if (t.x() > leak_max_x) leak_max_x = t.x();
                    if (t.y() < leak_min_y) leak_min_y = t.y();
                    if (t.y() > leak_max_y) leak_max_y = t.y();
                }
                leaks++;
                map_building_tile_clear_at(grid_offset, b->type);
            }
        }
        if (leaks) {
            logs::info("map_building_tiles_remove fallback cleared %d tile(s) for "
                       "building id=%d type=%d at b->tile=(%d,%d) anchor=(%d,%d) "
                       "leaks=(%d,%d)..(%d,%d)",
                       leaks, building_id, (int)b->type, sx, sy, x, y,
                       leak_min_x, leak_min_y, leak_max_x, leak_max_y);
            // Make sure the surface-update region covers the fallback tiles.
            if (leak_min_x < x) x = leak_min_x;
            if (leak_min_y < y) y = leak_min_y;
            if (leak_max_x >= x + size) size = leak_max_x - x + 1;
            if (leak_max_y >= y + size) size = leak_max_y - y + 1;
        }
    }

    map_tiles_update_region_empty_land(true, tile2i(x - 2, y - 2), tile2i(x + size + 2, y + size + 2));
    map_tiles_update_region_meadow(x - 2, y - 2, x + size + 2, y + size + 2);
    map_tiles_update_region_rubble(x, y, x + size, y + size);
}

void map_building_tile_clear_at(int grid_offset, int building_type) {
    if (building_type != 0 && building_type != BUILDING_BURNING_RUIN) {
        map_set_rubble_building_type(grid_offset, building_type);
    }

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
        map_tiles_set_water(grid_offset);
    } else {
        map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_UGLY_GRASS) + (map_random_get(grid_offset) & 7));
        map_terrain_remove(grid_offset, TERRAIN_CLEARABLE - TERRAIN_ROAD);
    }
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