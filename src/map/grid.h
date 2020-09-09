#ifndef MAP_GRID_H
#define MAP_GRID_H

#include "core/buffer.h"
#include "core/game_environment.h"

#include <stdint.h>

enum {
    GRID_SIZE_C3 = 162,
    GRID_SIZE_PH = 228
};

static int grid_size[] = {
        GRID_SIZE_C3,
        GRID_SIZE_PH
};
static int grid_total_size[] = {
    GRID_SIZE_C3 * GRID_SIZE_C3,
    GRID_SIZE_PH * GRID_SIZE_PH
};

#define OFFSET_C3(x,y) (x + GRID_SIZE_C3 * y)
#define OFFSET_PH(x,y) (x + GRID_SIZE_PH * y)

//typedef struct {
//    uint8_t items[GRID_SIZE_C3 * GRID_SIZE_C3];
//} grid_u8_C3;
//
//typedef struct {
//    int8_t items[GRID_SIZE_C3 * GRID_SIZE_C3];
//} grid_i8_C3;
//
//typedef struct {
//    uint16_t items[GRID_SIZE_C3 * GRID_SIZE_C3];
//} grid_u16_C3;
//
//typedef struct {
//    int16_t items[GRID_SIZE_C3 * GRID_SIZE_C3];
//} grid_i16_C3;

/////

#define MAX_GRID_ITEMS 300 * 300

enum {
    FS_NONE = 0,
    FS_UINT8 = 1,
    FS_INT8 = 2,
    FS_UINT16 = 3,
    FS_INT16 = 4
};

static size_t gr_sizes[] = {
        0,
        sizeof(uint8_t),
        sizeof(int8_t),
        sizeof(uint16_t),
        sizeof(int16_t)
};

typedef struct {
    int initialized;
    char datatype;
    size_t size_field;
    int size_total;

    void *items_xx;
//    uint8_t *items_u8;
//    int8_t *items_i8;
//    uint16_t *items_u16;
//    int16_t *items_i16;
} grid_xx;

//typedef struct {
//    int initialized;
//    uint8_t *items;
//} grid_u8_x;
//
//typedef struct {
//    int initialized;
//    int8_t *items;
//} grid_i8_x;
//
//typedef struct {
//    int initialized;
//    uint16_t *items;
//} grid_u16_x;
//
//typedef struct {
//    int initialized;
//    int16_t *items;
//} grid_i16_x;

void map_grid_init(grid_xx *grid);
int map_grid_get(grid_xx *grid, uint32_t at);
void map_grid_set(grid_xx *grid, uint32_t at, int value);
void map_grid_fill(grid_xx *grid, int value);
void map_grid_clear(grid_xx *grid);
void map_grid_copy(grid_xx *src, grid_xx *dst);

void map_grid_and(grid_xx *grid, int at, int mask);
void map_grid_or(grid_xx *grid, int at, int mask);
void map_grid_and_all(grid_xx *grid, int mask);

void map_grid_save_state(grid_xx *grid, buffer *buf);
void map_grid_load_state(grid_xx *grid, buffer *buf);

//void grid_array_init_u8(grid_u8_x *grid);
//void grid_array_init_i8(grid_i8_x *grid);
//void grid_array_init_u16(grid_u16_x *grid);
//void grid_array_init_i16(grid_i16_x *grid);
//
//grid_u8_x *safe_u8(grid_u8_x *gr);
//grid_i8_x *safe_i8(grid_i8_x *gr);
//grid_u16_x *safe_u16(grid_u16_x *gr);
//grid_i16_x *safe_i16(grid_i16_x *gr);

void map_data_init(int width, int height, int start_offset, int border_size);

int map_grid_is_valid_offset(int grid_offset);
int map_grid_offset(int x, int y);
int map_grid_offset_to_x(int grid_offset);
int map_grid_offset_to_y(int grid_offset);

int map_grid_delta(int x, int y);
/**
 * Adds the specified X and Y to the given offset with error checking
 * @return New grid offset, or -1 if the x/y would wrap around to a different row/column
 */
int map_grid_add_delta(int grid_offset, int x, int y);
int map_grid_direction_delta(int direction);
void map_grid_size(int *width, int *height);
int map_grid_width(void);
int map_grid_height(void);
void map_grid_bound(int *x, int *y);
void map_grid_bound_area(int *x_min, int *y_min, int *x_max, int *y_max);
void map_grid_get_area(int x, int y, int size, int radius, int *x_min, int *y_min, int *x_max, int *y_max);
void map_grid_start_end_to_area(int x_start, int y_start, int x_end, int y_end, int *x_min, int *y_min, int *x_max, int *y_max);
int map_grid_is_inside(int x, int y, int size);
const int *map_grid_adjacent_offsets(int size);

//void map_grid_init_i8(int8_t *grid, int8_t value);
//
//void map_grid_clear_u8(uint8_t *grid);
//void map_grid_clear_i8(int8_t *grid);
//void map_grid_clear_u16(uint16_t *grid);
//void map_grid_clear_i16(int16_t *grid);
//
//void map_grid_and_u8(uint8_t *grid, uint8_t mask);
//void map_grid_and_u16(uint16_t *grid, uint16_t mask);
//
//void map_grid_copy_u8(const uint8_t *src, uint8_t *dst);
//void map_grid_copy_u16(const uint16_t *src, uint16_t *dst);


void map_grid_save_state_u8(const uint8_t *grid, buffer *buf);
void map_grid_save_state_i8(const int8_t *grid, buffer *buf);
void map_grid_save_state_u16(const uint16_t *grid, buffer *buf);

void map_grid_load_state_u8(uint8_t *grid, buffer *buf);
void map_grid_load_state_i8(int8_t *grid, buffer *buf);
void map_grid_load_state_u16(uint16_t *grid, buffer *buf);

#endif // MAP_GRID_H
