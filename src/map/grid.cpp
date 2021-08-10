#include "grid.h"

#include "map/data.h"

#include <string.h>

struct map_data_t map_data;

static const int DIRECTION_DELTA_C3[] = {-OFFSET_C3(0, 1), OFFSET_C3(1, -1), 1, OFFSET_C3(1, 1), OFFSET_C3(0, 1),
                                         OFFSET_C3(-1, 1), -1, -OFFSET_C3(1, 1)};
static const int DIRECTION_DELTA_PH[] = {-OFFSET_PH(0, 1), OFFSET_PH(1, -1), 1, OFFSET_PH(1, 1), OFFSET_PH(0, 1),
                                         OFFSET_PH(-1, 1), -1, -OFFSET_PH(1, 1)};

#include <stdlib.h>
#include "core/game_environment.h"
#include <cassert>

void map_grid_init(grid_xx *grid) {
    grid->size_field = gr_sizes[grid->datatype[GAME_ENV]];
    grid->size_total = grid->size_field * grid_total_size[GAME_ENV];
    grid->items_xx = malloc(grid->size_total);
    grid->initialized = 1;
}
int64_t map_grid_get(grid_xx *grid, uint32_t at) {
    if (!grid->initialized)
        map_grid_init(grid);

    if (at >= grid_total_size[GAME_ENV])
        return 0;

//    assert(at < grid_total_size[GAME_ENV]);
    int64_t res = 0;
    switch (grid->datatype[GAME_ENV]) {
        case FS_UINT8:
            res = ((uint8_t *) grid->items_xx)[at];
            break;
        case FS_INT8:
            res = ((int8_t *) grid->items_xx)[at];
            break;
        case FS_UINT16:
            res = ((uint16_t *) grid->items_xx)[at];
            break;
        case FS_INT16:
            res = ((int16_t *) grid->items_xx)[at];
            break;
        case FS_UINT32:
            res = ((uint32_t *) grid->items_xx)[at];
            break;
        case FS_INT32:
            res = ((int32_t *) grid->items_xx)[at];
            break;
    }
    return res;
}
void map_grid_set(grid_xx *grid, uint32_t at, int64_t value) {
    if (!grid->initialized)
        map_grid_init(grid);
    if (at >= grid_total_size[GAME_ENV])
        return;
//    assert(at < grid_total_size[GAME_ENV]);
    switch (grid->datatype[GAME_ENV]) {
        case FS_UINT8:
            ((uint8_t *) grid->items_xx)[at] = (uint8_t) value;
            break;
        case FS_INT8:
            ((int8_t *) grid->items_xx)[at] = (int8_t) value;
            break;
        case FS_UINT16:
            ((uint16_t *) grid->items_xx)[at] = (uint16_t) value;
            break;
        case FS_INT16:
            ((int16_t *) grid->items_xx)[at] = (int16_t) value;
            break;
        case FS_UINT32:
            ((uint32_t *) grid->items_xx)[at] = (uint32_t) value;
            break;
        case FS_INT32:
            ((int32_t *) grid->items_xx)[at] = (int32_t) value;
            break;
    }
}
void map_grid_fill(grid_xx *grid, int64_t value) {
    if (!grid->initialized)
        map_grid_init(grid);
    switch (grid->datatype[GAME_ENV]) {
        case FS_UINT8:
            memset(grid->items_xx, (uint8_t) value, grid->size_total);
            break;
        case FS_INT8:
            memset(grid->items_xx, (int8_t) value, grid->size_total);
            break;
        case FS_UINT16:
            memset(grid->items_xx, (uint16_t) value, grid->size_total);
            break;
        case FS_INT16:
            memset(grid->items_xx, (int16_t) value, grid->size_total);
            break;
        case FS_UINT32:
            memset(grid->items_xx, (uint32_t) value, grid->size_total);
            break;
        case FS_INT32:
            memset(grid->items_xx, (int32_t) value, grid->size_total);
            break;
    }
}
void map_grid_clear(grid_xx *grid) {
    if (!grid->initialized)
        map_grid_init(grid);
    memset(grid->items_xx, 0, grid->size_total);
}
void map_grid_copy(grid_xx *src, grid_xx *dst) {
    if (!src->initialized)
        map_grid_init(src);
    if (!dst->initialized)
        map_grid_init(dst);

    assert(src->datatype[GAME_ENV] == dst->datatype[GAME_ENV]);
    assert(src->size_total == dst->size_total);

    memcpy(dst->items_xx, src->items_xx, src->size_total);
}

void map_grid_and(grid_xx *grid, uint32_t at, int mask) {
    if (!grid->initialized)
        map_grid_init(grid);
    int v = map_grid_get(grid, at);
    v &= mask;
    map_grid_set(grid, at, v);
}
void map_grid_or(grid_xx *grid, uint32_t at, int mask) {
    if (!grid->initialized)
        map_grid_init(grid);
    int v = map_grid_get(grid, at);
    v |= mask;
    map_grid_set(grid, at, v);
}
void map_grid_and_all(grid_xx *grid, int mask) {
    if (!grid->initialized)
        map_grid_init(grid);
    for (int i = 0; i < grid_total_size[GAME_ENV]; i++) {
        switch (grid->datatype[GAME_ENV]) {
            case FS_UINT8:
                ((uint8_t *) grid->items_xx)[i] &= (uint8_t) mask;
                break;
            case FS_INT8:
                ((int8_t *) grid->items_xx)[i] &= (int8_t) mask;
                break;
            case FS_UINT16:
                ((uint16_t *) grid->items_xx)[i] &= (uint16_t) mask;
                break;
            case FS_INT16:
                ((int16_t *) grid->items_xx)[i] &= (int16_t) mask;
                break;
            case FS_UINT32:
                ((uint32_t *) grid->items_xx)[i] &= (uint32_t) mask;
                break;
            case FS_INT32:
                ((int32_t *) grid->items_xx)[i] &= (int32_t) mask;
                break;
        }
    }
}

void map_grid_save_buffer(grid_xx *grid, buffer *buf) {
    if (!grid->initialized)
        map_grid_init(grid);
    switch (grid->datatype[GAME_ENV]) {
        case FS_UINT8:
            buf->write_raw(grid->items_xx, grid_total_size[GAME_ENV]);
            break;
        case FS_INT8:
            buf->write_raw(grid->items_xx, grid_total_size[GAME_ENV]);
            break;
        case FS_UINT16:
            for (int i = 0; i < grid_total_size[GAME_ENV]; i++)
                buf->write_u16(((uint16_t *) grid->items_xx)[i]);
            break;
        case FS_INT16:
            for (int i = 0; i < grid_total_size[GAME_ENV]; i++)
                buf->write_i16(((int16_t *) grid->items_xx)[i]);
            break;
        case FS_UINT32:
            for (int i = 0; i < grid_total_size[GAME_ENV]; i++)
                buf->write_u32(((uint32_t *) grid->items_xx)[i]);
            break;
        case FS_INT32:
            for (int i = 0; i < grid_total_size[GAME_ENV]; i++)
                buf->write_i32(((int32_t *) grid->items_xx)[i]);
            break;
    }
}
void map_grid_load_buffer(grid_xx *grid, buffer *buf) {
    if (!grid->initialized)
        map_grid_init(grid);
    switch (grid->datatype[GAME_ENV]) {
        case FS_UINT8:
            buf->read_raw(grid->items_xx, grid_total_size[GAME_ENV]);
            break;
        case FS_INT8:
            buf->read_raw(grid->items_xx, grid_total_size[GAME_ENV]);
            break;
        case FS_UINT16: {
            uint16_t *dr_data = (uint16_t *) grid->items_xx;
            for (int i = 0; i < grid_total_size[GAME_ENV]; i++)
                dr_data[i] = buf->read_u16();
            break;
        }
        case FS_INT16: {
            int16_t *dr_data = (int16_t *) grid->items_xx;
            for (int i = 0; i < grid_total_size[GAME_ENV]; i++)
                dr_data[i] = buf->read_i16();
            break;
        }
        case FS_UINT32: {
            uint32_t *dr_data = (uint32_t *) grid->items_xx;
            for (int i = 0; i < grid_total_size[GAME_ENV]; i++)
                dr_data[i] = buf->read_u32();
            break;
        }
        case FS_INT32: {
            int32_t *dr_data = (int32_t *) grid->items_xx;
            for (int i = 0; i < grid_total_size[GAME_ENV]; i++)
                dr_data[i] = buf->read_i32();
            break;
        }
    }
    return;
}

void map_grid_data_init(int width, int height, int start_offset, int border_size) {
    if (0) {
        map_data.width = grid_size[GAME_ENV];
        map_data.height = grid_size[GAME_ENV];
        map_data.start_offset = 0;
        map_data.border_size = 0;
    } else {
        map_data.width = width;
        map_data.height = height;
        map_data.start_offset = start_offset;
        map_data.border_size = border_size;
    }
}

int map_grid_is_valid_offset(int grid_offset) {
    return true; // temp
    return grid_offset >= 0 && grid_offset < grid_total_size[GAME_ENV];
}
int map_grid_offset(int x, int y) {
//    return x + y * grid_size[GAME_ENV];
    return map_data.start_offset + x + y * grid_size[GAME_ENV];
}
int map_grid_offset_to_x(int grid_offset) {
    return (grid_offset - map_data.start_offset) % grid_size[GAME_ENV];
}
int map_grid_offset_to_y(int grid_offset) {
    return (grid_offset - map_data.start_offset) / grid_size[GAME_ENV];
}

int map_grid_delta(int x, int y) {
    return y * grid_size[GAME_ENV] + x;
}
int map_grid_add_delta(int grid_offset, int x, int y) {
    int raw_x = grid_offset % grid_size[GAME_ENV];
    int raw_y = grid_offset / grid_size[GAME_ENV];
    if (raw_x + x < 0 || raw_x + x >= grid_size[GAME_ENV] ||
        raw_y + y < 0 || raw_y + y >= grid_size[GAME_ENV]) {
        return -1;
    }
    return grid_offset + map_grid_delta(x, y);
}
int map_grid_direction_delta(int direction) {
    if (direction >= 0 && direction < 8) {
        switch (GAME_ENV) {
            case ENGINE_ENV_C3:
                return DIRECTION_DELTA_C3[direction];
            case ENGINE_ENV_PHARAOH:
                return DIRECTION_DELTA_PH[direction];
        }
    } else {
        return 0;
    }
}
void map_grid_size(int *width, int *height) {
    *width = map_data.width;
    *height = map_data.height;
}
int map_grid_width(void) {
    return map_data.width;
}
int map_grid_height(void) {
    return map_data.height;
}
void map_grid_bound(int *x, int *y) {
    if (*x < 0)
        *x = 0;

    if (*y < 0)
        *y = 0;

    if (*x >= map_data.width)
        *x = map_data.width - 1;

    if (*y >= map_data.height)
        *y = map_data.height - 1;
}
void map_grid_bound_area(int *x_min, int *y_min, int *x_max, int *y_max) {
    if (*x_min < 0)
        *x_min = 0;

    if (*y_min < 0)
        *y_min = 0;

    if (*x_max >= map_data.width)
        *x_max = map_data.width - 1;

    if (*y_max >= map_data.height)
        *y_max = map_data.height - 1;

}
void map_grid_get_area(int x, int y, int size, int radius, int *x_min, int *y_min, int *x_max, int *y_max) {
    *x_min = x - radius;
    *y_min = y - radius;
    *x_max = x + size + radius - 1;
    *y_max = y + size + radius - 1;
    map_grid_bound_area(x_min, y_min, x_max, y_max);
}
void map_grid_start_end_to_area(int x_start, int y_start, int x_end, int y_end, int *x_min, int *y_min, int *x_max, int *y_max) {
    if (x_start < x_end) {
        *x_min = x_start;
        *x_max = x_end;
    } else {
        *x_min = x_end;
        *x_max = x_start;
    }
    if (y_start < y_end) {
        *y_min = y_start;
        *y_max = y_end;
    } else {
        *y_min = y_end;
        *y_max = y_start;
    }
    map_grid_bound_area(x_min, y_min, x_max, y_max);
}
int map_grid_is_inside(int x, int y, int size) {
    if (GAME_ENV == ENGINE_ENV_C3)
        return x >= 0 && x + size <= map_data.width && y >= 0 && y + size <= map_data.height;
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {

        // todo? it's not really making anything go haywire at the moment.

//        int start_x = map_grid_offset_to_x(2 * map_data.start_offset);
//        int start_y = map_grid_offset_to_y(2 * map_data.start_offset);
//
//        x += start_x; // -1
//        y += start_y; // -1
//
//        int dist_horizontal = abs(x - y);
//        int dist_vertical = abs(y - (grid_size[GAME_ENV] - x) + 2);
//
//        if (dist_horizontal < map_data.width * 0.5 && dist_vertical < map_data.height * 0.5) // -2, -2
//            return 1;
//        return 0;

        int min_x = 0;
        int max_x = map_data.width;
        int min_y = 0;
        int max_y = map_data.height;

        return x >= min_x && x + size <= max_x && y >= min_y && y + size <= max_y;
    }
}
int map_view_tile_inside_map_area(int x, int y) {
    int dist_horizontal = abs(x - y);
    int dist_vertical = abs(y - (grid_size[GAME_ENV] - x) + 1);

    if (dist_horizontal < map_data.width / 2 + 1 && dist_vertical < map_data.height / 2 + 1)
        return 1; // inside play space
//    if (dist_horizontal < map_data.width / 2 + 1 && dist_vertical < map_data.height / 2 + 1)
//        return 0; // outside play space, but visible
    return 0; // outside viewable area
}

static int offsets_array[150];
const int *map_grid_adjacent_offsets(int size) {

    int array_size = (size + 1) * 4;

    for (int i = 0; i <= array_size; i++) {

        int x = 0;
        int y = 0;
        if (i < 1 * (size + 1)) {
            x = i;
            y = -1;
        } else if (i < 2 * (size + 1)) {
            x = size + 1;
            y = i % (size + 1);
        } else if (i < 3 * (size + 1)) {
            x = size - (i % (size + 1));
            y = size + 1;
        } else if (i < 2 * (size + 1)) {
            x = -1;
            y = size - (i % (size + 1));
        }

        switch (GAME_ENV) {
            case ENGINE_ENV_C3:
                offsets_array[i] = OFFSET_C3(x, y);
                break;
            case ENGINE_ENV_PHARAOH:
                offsets_array[i] = OFFSET_PH(x, y);
                break;
        }
    }
    return offsets_array;
}

