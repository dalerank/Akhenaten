#pragma once

#include "core/buffer.h"
#include "core/game_environment.h"
#include "core/vec2i.h"
#include "core/svector.h"
#include "point.h"
#include "scenario/map.h"

#include <stdint.h>

class building;

constexpr int GRID_LENGTH = 228;
constexpr int GRID_SIZE_TOTAL = GRID_LENGTH * GRID_LENGTH;
#define GRID_OFFSET(abs_x, abs_y) ((abs_x) + GRID_LENGTH * (abs_y))
#define GRID_X(offset) ((offset) % GRID_LENGTH)
#define GRID_Y(offset) ((offset) / GRID_LENGTH)
#define MAP_X(offset) (GRID_X(offset - scenario_map_data()->start_offset))
#define MAP_Y(offset) (GRID_Y(offset - scenario_map_data()->start_offset))

inline uint32_t MAP_OFFSET(uint32_t map_x, uint32_t map_y) {
    return scenario_map_data()->start_offset + GRID_OFFSET(map_x, map_y);
}

inline uint32_t MAP_OFFSET(tile2i point) {
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

struct grid_area {
    tile2i tmin;
    tile2i tmax;

    template<typename T>
    void for_each(T f) {
        for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
            for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
                tile2i tt(xx, yy);
                f(tt);
            }
        }
    }

    template<typename T>
    tile2i find_if(T f) {
        for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
            for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
                tile2i tt(xx, yy);
                if (f(tt)) {
                    return tt;
                }
            }
        }

        return tile2i::invalid;
    }
};

using grid_tiles = std::vector<tile2i>;

void map_grid_init(grid_xx* grid);
int32_t map_grid_get(grid_xx* grid, uint32_t at);
inline int32_t map_grid_get(grid_xx *grid, tile2i at) { return map_grid_get(grid, at.grid_offset()); }
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
inline bool map_grid_is_valid_offset(tile2i tile) { return map_grid_is_valid_offset(tile.grid_offset()); }
int map_grid_direction_delta(int direction);
// void map_grid_size(int *width, int *height);
int map_grid_width();
int map_grid_height();
void map_grid_bound(int* x, int* y);
void map_grid_bound_area(tile2i &tmin, tile2i &tmax);
grid_area map_grid_get_area(tile2i tile, int size, int radius);
grid_tiles map_grid_get_tiles(building *b, int radius);
grid_area map_grid_get_area(tile2i start, tile2i end);
grid_tiles map_grid_get_tiles(tile2i start, tile2i end);
bool map_tile_is_inside_area(tile2i tile, tile2i start, tile2i end, vec2i size = vec2i{0, 0});
bool map_grid_is_inside(tile2i tile, vec2i size);
inline int map_grid_is_inside(tile2i tile, int size) { return map_grid_is_inside(tile, vec2i{size, size}); }
bool map_grid_inside_map_area(int grid_offset, int edge_size = 0);
// bool map_grid_inside_map_area(int x, int y, int edge_size = 0);
using offsets_array = svector<int, 150>;
void map_grid_adjacent_offsets_xy(int sizex, int sizey, offsets_array &arr);
void map_grid_adjacent_offsets(int size, offsets_array &arr);

template<typename T>
inline void map_grid_area_foreach(tile2i tmin, tile2i tmax, T func) {
    for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
        for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
            func(tile2i(xx, yy));
        }
    }
}

template<typename T>
inline void map_grid_area_foreach(tile2i center, int size, T func) {
    map_grid_area_foreach(center.shifted(-size, -size), center.shifted(size, size), func);
}

template<typename T>
inline void map_grid_area_foreach(grid_area area, T func) {
    for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
        for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
            func(tile2i(xx, yy));
        }
    }
}

template<typename T>
inline void map_grid_area_foreach(grid_tiles &tiles, T func) {
    for (auto &tile: tiles) {
        func(tile);
    }
}

template<typename T>
inline tile2i map_grid_area_first(tile2i tmin, tile2i tmax, T func) {
    for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
        for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
            if (func(tile2i(xx, yy))) {
                return tile2i(xx, yy);
            }
        }
    }

    return tile2i(-1, -1);
}

template<typename T>
inline tile2i map_grid_area_first(grid_area area, T func) {
    return map_grid_area_first(area.tmin, area.tmax, func);
}

template<typename T>
inline tile2i map_grid_area_first(grid_tiles &tiles, T func) {
    for (auto &tile: tiles) {
        if (func(tile)) {
           return tile;
        }
    }

    return tile2i(-1, -1);
}