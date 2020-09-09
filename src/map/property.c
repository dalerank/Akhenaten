#include "property.h"

#include "map/grid.h"
#include "map/random.h"

enum {
    BIT_SIZE1 = 0x00,
    BIT_SIZE2 = 0x01,
    BIT_SIZE3 = 0x02,
    BIT_SIZE4 = 0x04,
    BIT_SIZE5 = 0x08,
    BIT_SIZES = 0x0f,
    BIT_NO_SIZES = 0xf0,
    BIT_CONSTRUCTION = 0x10,
    BIT_NO_CONSTRUCTION = 0xef,
    BIT_ALTERNATE_TERRAIN = 0x20,
    BIT_DELETED = 0x40,
    BIT_NO_DELETED = 0xbf,
    BIT_PLAZA_OR_EARTHQUAKE = 0x80,
    BIT_NO_PLAZA = 0x7f,
    BIT_NO_CONSTRUCTION_AND_DELETED = 0xaf,
    EDGE_MASK_X = 0x7,
    EDGE_MASK_Y = 0x38,
    EDGE_MASK_XY = 0x3f,
    EDGE_LEFTMOST_TILE = 0x40,
    EDGE_NO_LEFTMOST_TILE = 0xbf,
    EDGE_NATIVE_LAND = 0x80,
    EDGE_NO_NATIVE_LAND = 0x7f,
};

static grid_xx edge_grid = {0, FS_UINT8};
static grid_xx bitfields_grid = {0, FS_UINT8};

static grid_xx edge_backup = {0, FS_UINT8};
static grid_xx bitfields_backup = {0, FS_UINT8};

static int edge_for(int x, int y)
{
    return 8 * y + x;
}

int map_property_is_draw_tile(int grid_offset)
{
    return map_grid_get(&edge_grid, grid_offset) & EDGE_LEFTMOST_TILE;
}
void map_property_mark_draw_tile(int grid_offset)
{
    map_grid_or(&edge_grid, grid_offset, EDGE_LEFTMOST_TILE);
}
void map_property_clear_draw_tile(int grid_offset)
{
    map_grid_and(&edge_grid, grid_offset, ~EDGE_LEFTMOST_TILE);
}
int map_property_is_native_land(int grid_offset)
{
    return map_grid_get(&edge_grid, grid_offset) & EDGE_NATIVE_LAND;
}

void map_property_mark_native_land(int grid_offset)
{
    map_grid_or(&edge_grid, grid_offset, EDGE_NATIVE_LAND);
}
void map_property_clear_all_native_land(void)
{
    map_grid_and_all(&edge_grid, EDGE_NO_NATIVE_LAND);
}

int map_property_multi_tile_xy(int grid_offset)
{
    return map_grid_get(&edge_grid, grid_offset) & EDGE_MASK_XY;
}
int map_property_multi_tile_x(int grid_offset)
{
    return map_grid_get(&edge_grid, grid_offset) & EDGE_MASK_X;
}
int map_property_multi_tile_y(int grid_offset)
{
    return map_grid_get(&edge_grid, grid_offset) & EDGE_MASK_Y;
}

int map_property_is_multi_tile_xy(int grid_offset, int x, int y)
{
    return (map_grid_get(&edge_grid, grid_offset) & EDGE_MASK_XY) == edge_for(x, y);
}
void map_property_set_multi_tile_xy(int grid_offset, int x, int y, int is_draw_tile)
{
    if (is_draw_tile) {
        map_grid_set(&edge_grid, grid_offset, edge_for(x, y) | EDGE_LEFTMOST_TILE);
    } else {
        map_grid_set(&edge_grid, grid_offset, edge_for(x, y));
    }
}
void map_property_clear_multi_tile_xy(int grid_offset)
{
    // only keep native land marker
    map_grid_and(&edge_grid, grid_offset, EDGE_NATIVE_LAND);
}
int map_property_multi_tile_size(int grid_offset)
{
    switch (map_grid_get(&bitfields_grid, grid_offset) & BIT_SIZES) {
        case BIT_SIZE2: return 2;
        case BIT_SIZE3: return 3;
        case BIT_SIZE4: return 4;
        case BIT_SIZE5: return 5;
        default: return 1;
    }
}
void map_property_set_multi_tile_size(int grid_offset, int size)
{
    map_grid_and(&bitfields_grid, grid_offset, BIT_NO_SIZES);
    switch (size) {
        case 2: map_grid_or(&bitfields_grid, grid_offset, BIT_SIZE2); break;
        case 3: map_grid_or(&bitfields_grid, grid_offset, BIT_SIZE3); break;
        case 4: map_grid_or(&bitfields_grid, grid_offset, BIT_SIZE4); break;
        case 5: map_grid_or(&bitfields_grid, grid_offset, BIT_SIZE5); break;
    }
}

void map_property_init_alternate_terrain(void)
{
    int map_width, map_height;
    map_grid_size(&map_width, &map_height);
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            int grid_offset = map_grid_offset(x, y);
            if (map_random_get(grid_offset) & 1) {
                map_property_set_alternate_terrain(grid_offset);
            }
        }
    }
}
int map_property_is_alternate_terrain(int grid_offset)
{
    return map_grid_get(&bitfields_grid, grid_offset) & BIT_ALTERNATE_TERRAIN;
}
void map_property_set_alternate_terrain(int grid_offset)
{
    map_grid_or(&bitfields_grid, grid_offset, BIT_ALTERNATE_TERRAIN);
}
int map_property_is_plaza_or_earthquake(int grid_offset)
{
    return map_grid_get(&bitfields_grid, grid_offset) & BIT_PLAZA_OR_EARTHQUAKE;
}

void map_property_mark_plaza_or_earthquake(int grid_offset)
{
    map_grid_or(&bitfields_grid, grid_offset, BIT_PLAZA_OR_EARTHQUAKE);
}
void map_property_clear_plaza_or_earthquake(int grid_offset)
{
    map_grid_and(&bitfields_grid, grid_offset, BIT_NO_PLAZA);
}

int map_property_is_constructing(int grid_offset)
{
    return map_grid_get(&bitfields_grid, grid_offset) & BIT_CONSTRUCTION;
}
void map_property_mark_constructing(int grid_offset)
{
    map_grid_or(&bitfields_grid, grid_offset, BIT_CONSTRUCTION);
}
void map_property_clear_constructing(int grid_offset)
{
    map_grid_and(&bitfields_grid, grid_offset, BIT_NO_CONSTRUCTION);
}
int map_property_is_deleted(int grid_offset)
{
    return map_grid_get(&bitfields_grid, grid_offset) & BIT_DELETED;
}

void map_property_mark_deleted(int grid_offset)
{
    map_grid_or(&bitfields_grid, grid_offset, BIT_DELETED);
}
void map_property_clear_deleted(int grid_offset)
{
    map_grid_and(&bitfields_grid, grid_offset, BIT_NO_DELETED);
}
void map_property_clear_constructing_and_deleted(void)
{
    map_grid_and_all(&bitfields_grid, BIT_NO_CONSTRUCTION_AND_DELETED);
}
void map_property_clear(void)
{
    map_grid_clear(&bitfields_grid);
    map_grid_clear(&edge_grid);
}

void map_property_backup(void)
{
    map_grid_copy(&bitfields_grid, &bitfields_backup);
    map_grid_copy(&edge_grid, &edge_backup);
}
void map_property_restore(void)
{
    map_grid_copy(&bitfields_backup, &bitfields_grid);
    map_grid_copy(&edge_backup, &edge_grid);
}
void map_property_save_state(buffer *bitfields, buffer *edge)
{
    map_grid_save_state(&bitfields_grid, bitfields);
    map_grid_save_state(&edge_grid, edge);
}
void map_property_load_state(buffer *bitfields, buffer *edge)
{
    map_grid_load_state(&bitfields_grid, bitfields);
    map_grid_load_state(&edge_grid, edge);
}
