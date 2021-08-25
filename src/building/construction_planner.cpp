#include <map/building_tiles.h>
#include "construction_planner.h"

#include "map/terrain.h"
#include "city/view.h"
#include "industry.h"

static int tile_max_x = 0;
static int tile_max_y = 0;
static int tile_pivot_x = 0;
static int tile_pivot_y = 0;
static int tile_graphics_array[30][30] = {};
static int tile_sizes_array[30][30] = {};
static int tile_restricted_terrains[30][30] = {};
static bool tile_blocked_array[30][30] = {};
static int tiles_blocked_total = 0;

static map_point tile_coord_cache[30][30];
static pixel_coordinate pixel_coords_cache[30][30];

void planner_reset_tiles(int size_x, int size_y) {
    tile_max_x = size_x;
    tile_max_y = size_y;
    tile_pivot_x = 0;
    tile_pivot_y = 0;
    for (int row = 0; row < size_y; ++row) {
        for (int column = 0; column < size_x; ++column) {
            if (column > 29 || row > 29)
                return;
            tile_graphics_array[row][column] = 0; // reset tile size to 1 by default
            tile_sizes_array[row][column] = 1; // reset tile size to 1 by default
            tile_restricted_terrains[row][column] = TERRAIN_ALL;
            tile_blocked_array[row][column] = false;
            tiles_blocked_total = 0;

            // reset caches
            tile_coord_cache[row][column] = {0, 0};
            pixel_coords_cache[row][column] = {0, 0};
        }
    }
}
void planner_set_pivot(int x, int y) {
    tile_pivot_x = x;
    tile_pivot_y = y;
}
void planner_update_coord_caches(const map_tile *cursor_tile, int x, int y) {
    int orientation = city_view_orientation() / 2;
    for (int row = 0; row < tile_max_y; row++) {
        for (int column = 0; column < tile_max_x; column++) {

            // get tile offset
            int x_offset = (column - tile_pivot_x);
            int y_offset = (row - tile_pivot_y);

            // get abs. tile
            int tile_x = 0;
            int tile_y = 0;
            switch (orientation) {
                case 0:
                    tile_x = cursor_tile->x + x_offset;
                    tile_y = cursor_tile->y + y_offset;
                    break;
                case 1:
                    tile_x = cursor_tile->x - y_offset;
                    tile_y = cursor_tile->y + x_offset;
                    break;
                case 2:
                    tile_x = cursor_tile->x - x_offset;
                    tile_y = cursor_tile->y - y_offset;
                    break;
                case 31:
                    tile_x = cursor_tile->x + y_offset;
                    tile_y = cursor_tile->y - x_offset;
                    break;
            }

            // get tile pixel coords
            int current_x = x + x_offset * 30 - y_offset * 30;
            int current_y = y + x_offset * 15 + y_offset * 15;

            // save values in cache
            tile_coord_cache[row][column] = {tile_x, tile_y};
            pixel_coords_cache[row][column] = {current_x, current_y};
        }
    }
}

void planner_set_graphics_row(int row, int *image_ids, int total) {
    for (int i = 0; i < total; ++i) {
        if (row > 29 || i > 29)
            return;
        tile_graphics_array[row][i] = image_ids[i];
    }
}
void planner_set_graphics_array(int *image_set, int size_x, int size_y) {
    int (*image_array)[size_y][size_x] = (int(*)[size_y][size_x])image_set;

    for (int row = 0; row < size_y; ++row) {
        planner_set_graphics_row(row, (*image_array)[row], size_x);
//        for (int column = 0; column < size_x; ++column) {
//            if (column > 29 || row > 29)
//                return;
//            int image_id = (*image_array)[row][column];
//        }
    }
}

void planner_set_tile_size(int row, int column, int size) {
    if (row > 29 || column > 29)
        return;
    tile_sizes_array[row][column] = size;
}
void plannet_set_allowed_terrain(int row, int column, int terrain) {
    if (row > 29 || column > 29)
        return;
    tile_restricted_terrains[row][column] = terrain;
}

void planner_check_obstructions() {
//    int orientation = city_view_orientation() / 2;
    for (int row = 0; row < tile_max_y; row++) {
        for (int column = 0; column < tile_max_x; column++) {

//            int tile_x = 0;
//            int tile_y = 0;
//
//            // adjust checking tile coords depending on orientation
//            int x_offset = (row - tile_pivot_x);
//            int y_offset = (column - tile_pivot_y);
//            switch (orientation) {
//                case 0:
//                    tile_x = cursor_tile->x + x_offset;
//                    tile_y = cursor_tile->y + y_offset;
//                    break;
//                case 1:
//                    tile_x = cursor_tile->x - y_offset;
//                    tile_y = cursor_tile->y + x_offset;
//                    break;
//                case 2:
//                    tile_x = cursor_tile->x - x_offset;
//                    tile_y = cursor_tile->y - y_offset;
//                    break;
//                case 31:
//                    tile_x = cursor_tile->x + y_offset;
//                    tile_y = cursor_tile->y - x_offset;
//                    break;
//            }

            // check terrain at coords
            map_point current_tile = tile_coord_cache[row][column];
            int restricted_terrain = tile_restricted_terrains[row][column];
            if (!map_building_tiles_are_clear(current_tile.x, current_tile.y, 1, restricted_terrain)) {
                tile_blocked_array[row][column] = true;
                tiles_blocked_total++;
            }
        }
    }
}
int planner_get_blocked_count() {
    return tiles_blocked_total;
}
bool planner_is_obstructed() {
    return tiles_blocked_total > 0;
}

static void draw_flat_tile(int x, int y, color_t color_mask) {
    ImageDraw::img_blended(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, color_mask);
}
void planner_draw_blueprints(int x, int y, bool fully_blocked) {
    for (int row = 0; row < tile_max_y; row++) {
        for (int column = 0; column < tile_max_x; column++) {

//            int x_offset = (row - tile_pivot_x);
//            int y_offset = (column - tile_pivot_y);
//
//            // get tile pixel coords
//            int current_x = x + x_offset * 30 - y_offset * 30;
//            int current_y = y + x_offset * 15 + y_offset * 15;

            // draw tile!
            pixel_coordinate current_coord = pixel_coords_cache[row][column];
            if (tile_blocked_array[row][column])
                draw_flat_tile(current_coord.x, current_coord.y, COLOR_MASK_RED);
            else
                draw_flat_tile(current_coord.x, current_coord.y, COLOR_MASK_GREEN);
        }
    }
}
void planner_draw_graphics(int x, int y) {

    // draw footprints first
    for (int row = 0; row < tile_max_y; row++) {
        for (int column = 0; column < tile_max_x; column++) {

            int image_id = tile_graphics_array[row][column];
            if (image_id > 0) {
                pixel_coordinate current_coord = pixel_coords_cache[row][column];
                ImageDraw::isometric_footprint_from_drawtile(image_id, current_coord.x, current_coord.y, COLOR_MASK_GREEN);
            }
        }
    }

    // finally, draw tile top's
    for (int row = 0; row < tile_max_y; row++) {
        for (int column = 0; column < tile_max_x; column++) {

            int image_id = tile_graphics_array[row][column];
            if (image_id > 0) {
                pixel_coordinate current_coord = pixel_coords_cache[row][column];
                ImageDraw::isometric_top_from_drawtile(image_id, current_coord.x, current_coord.y, COLOR_MASK_GREEN);
            }
        }
    }
}

void planner_draw_all(const map_tile *cursor_tile, int x, int y) {
    planner_update_coord_caches(cursor_tile, x, y);
    planner_check_obstructions();
    if (planner_is_obstructed())
        planner_draw_blueprints(x, y);
    else
        planner_draw_graphics(x, y);
}