#pragma once

#include "core/buffer.h"
#include "core/game_environment.h"
#include "core/vec2i.h"
#include "core/svector.h"
#include "point.h"
#include "scenario/map.h"

#include <stdint.h>

#define GRID_LENGTH 228
#define GRID_SIZE_TOTAL GRID_LENGTH* GRID_LENGTH
#define GRID_OFFSET(abs_x, abs_y) ((abs_x) + GRID_LENGTH * (abs_y))
#define GRID_X(offset) ((offset) % GRID_LENGTH)
#define GRID_Y(offset) ((offset) / GRID_LENGTH)
#define MAP_X(offset) (GRID_X(offset - scenario_map_data()->start_offset))
#define MAP_Y(offset) (GRID_Y(offset - scenario_map_data()->start_offset))

inline uint32_t MAP_OFFSET(uint32_t map_x, uint32_t map_y) {
    return scenario_map_data()->start_offset + GRID_OFFSET(map_x, map_y);
}

inline uint32_t MAP_OFFSET(map_point point) {
    return scenario_map_data()->start_offset + GRID_OFFSET(point.x(), point.y());
}

enum e_grid_data_type {
    FS_NONE = 0,
    FS_UINT8 = 1,
    FS_INT8 = 2,
    FS_UINT16 = 3,
    FS_INT16 = 4,
    FS_UINT32 = 5,
    FS_INT32 = 6
};

static size_t gr_sizes[] = {
    0, sizeof(uint8_t), sizeof(int8_t), sizeof(uint16_t), sizeof(int16_t), sizeof(uint32_t), sizeof(int32_t)
};

struct grid_xx {
    int initialized;
    e_grid_data_type datatype[2];
    size_t size_field;
    int size_total;

    void* items_xx;
};

void map_grid_init(grid_xx* grid);
int32_t map_grid_get(grid_xx* grid, uint32_t at);
void map_grid_set(grid_xx* grid, uint32_t at, int64_t value);
void map_grid_fill(grid_xx* grid, int64_t value);
void map_grid_clear(grid_xx* grid);
void map_grid_copy(grid_xx* src, grid_xx* dst);

void map_grid_and(grid_xx* grid, uint32_t at, int mask);
void map_grid_or(grid_xx* grid, uint32_t at, int mask);
void map_grid_and_all(grid_xx* grid, int mask);

void map_grid_save_buffer(grid_xx* grid, buffer* buf);
void map_grid_load_buffer(grid_xx* grid, buffer* buf);

// void map_grid_data_init(int width, int height, int start_offset, int border_size);

bool map_grid_is_valid_offset(int grid_offset);
// int MAP_OFFSET(int x, int y);
// int MAP_X(int grid_offset);
// int MAP_Y(int grid_offset);

int map_grid_direction_delta(int direction);
// void map_grid_size(int *width, int *height);
int map_grid_width();
int map_grid_height();
void map_grid_bound(int* x, int* y);
void map_grid_bound_area(tile2i &tmin, tile2i &tmax);
void map_grid_get_area(tile2i tile, int size, int radius, tile2i &tmin, tile2i &tmax);
void map_grid_start_end_to_area(tile2i start, tile2i end, tile2i &tmin, tile2i &tmax);
int map_grid_is_inside(tile2i tile, vec2i size);
inline int map_grid_is_inside(tile2i tile, int size) { return map_grid_is_inside(tile, vec2i{size, size}); }
bool map_grid_inside_map_area(int grid_offset, int edge_size = 0);
// bool map_grid_inside_map_area(int x, int y, int edge_size = 0);
using offsets_array = svector<int, 150>;
void map_grid_adjacent_offsets_xy(int sizex, int sizey, offsets_array &arr);
void map_grid_adjacent_offsets(int size, offsets_array &arr);

template<typename T>
void map_grid_area_foreach(tile2i tmin, tile2i tmax, T func) {
    for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
        for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
            func(tile2i(xx, yy));
        }
    }
}