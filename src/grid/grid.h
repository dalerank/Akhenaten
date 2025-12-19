#pragma once

#include "core/buffer.h"
#include "core/vec2i.h"
#include "core/svector.h"
#include "core/hvector.h"
#include "point.h"
#include "scenario/map.h"
#include "core/core_utility.h"

#include <utility>
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
    e_grid_data_type datatype;
    size_t size_field;
    uint32_t size_total;

    void* items_xx;

    inline int32_t get(uint32_t grid_offset);
};

struct grid_area {
    tile2i tmin;
    tile2i tmax;

    template<typename T>
    void for_each_bound(T f) {
        for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++)   { f(tile2i(xx, tmin.y())); }
        for (int yy = tmin.y()+1, endy = tmax.y(); yy <= endy; yy++) { f(tile2i(tmax.x(), yy)); }
        for (int xx = tmax.x()-1, endx = tmin.x(); xx >= endx; xx--) { f(tile2i(xx, tmax.y())); }
        for (int yy = tmax.y()-1, endy = tmin.y(); yy >= endy; yy--) { f(tile2i(tmin.x(), yy)); }
    }

    template<typename T>
    void for_each(T f) {
        for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
            for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
                tile2i tt(xx, yy);
                f(tt);
            }
        }
    }

    bool contains(tile2i t) {
        for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
            for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
                tile2i tt(xx, yy);
                if (tt == t) {
                    return true;
                }
            }
        }

        return false;
    }

    template<typename T>
    void find_all(T& out, std::function<bool(tile2i)> f) {
        for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
            for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
                tile2i tt(xx, yy);
                if (f(tt)) {
                    out.push_back(tt);
                }
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
using grid_tiles_sm = hvector<tile2i, 64>;

void map_grid_init(grid_xx& grid);
int32_t map_grid_get(grid_xx& grid, uint32_t at);
inline int32_t map_grid_get(grid_xx &grid, tile2i at) { return map_grid_get(grid, at.grid_offset()); }
void map_grid_set(grid_xx& grid, uint32_t at, int64_t value);
inline void map_grid_set(grid_xx& grid, tile2i at, int64_t value) { map_grid_set(grid, at.grid_offset(), value); }
void map_grid_fill(grid_xx& grid, int64_t value);
void map_grid_clear(grid_xx& grid);
void map_grid_copy(grid_xx& src, grid_xx& dst);

template<typename T>
tile2i map_random_choose(T &arr, tile2i avoid) {
    if (arr.empty()) {
        return tile2i::invalid;
    }

    auto idx = rand() % arr.size();
    if (arr[idx] != avoid) {
        return arr[idx];
    }

    return arr[0];
}

inline int32_t grid_xx::get(uint32_t grid_offset) { return map_grid_get(*this, grid_offset); }

void map_grid_and(grid_xx& grid, uint32_t at, int mask);
void map_grid_or(grid_xx& grid, uint32_t at, int mask);
void map_grid_and_all(grid_xx& grid, int mask);

void map_grid_save_buffer(grid_xx& grid, buffer* buf);
void map_grid_load_buffer(grid_xx& grid, buffer* buf);

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
grid_tiles_sm map_grid_get_tiles_sm(building *b, int radius);
grid_tiles_sm map_grid_get_adjacent_tiles_sm(building *b, int radius);
grid_tiles_sm map_grid_get_adjacent_tiles_sm(tile2i center, int size);
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

namespace detail {
    template<bool is_tile2i_type, typename Func>
    inline void map_grid_area_foreach(grid_area area, Func func) {
        for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
            for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
                if constexpr (is_tile2i_type) {
                    func(tile2i(xx, yy));
                } else {
                    func(MAP_OFFSET(xx, yy));
                }
            }
        }
    }
}

template<typename Func>
inline void map_grid_area_foreach(grid_area area, Func func) {
    using ArgType = typename type_traits::first_func_argument<decltype(&Func::operator())>::type;
    constexpr bool is_tile2i_type = std::is_same_v<ArgType, tile2i>;
    detail::map_grid_area_foreach<is_tile2i_type>(area, func);
}

template<typename T>
inline void map_grid_area_foreach(grid_area area, void (*callback)(T)) {
    constexpr bool is_tile2i_type = std::is_same_v<T, tile2i>;
    detail::map_grid_area_foreach<is_tile2i_type>(area, callback);
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

    return tile2i::invalid;
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