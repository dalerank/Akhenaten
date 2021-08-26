#include <map/building_tiles.h>
#include <cmath>
#include <map/grid.h>
#include <city/warning.h>
#include "construction_planner.h"
#include "map/terrain.h"
#include "city/view.h"
#include "graphics/image.h"
#include "rotation.h"

BuildPlanner Planner;

static map_point tile_coord_cache[30][30];
static pixel_coordinate pixel_coords_cache[30][30];

void BuildPlanner::reset() {
    // set boundary size and reset pivot
    size.x = 0;
    size.y = 0;
    pivot.x = 0;
    pivot.y = 0;
    tiles_blocked_total = 0;

    // reset special requirements flags/params
    requirement_flags = 0;
    additional_req_param = 0;
    meets_special_requirements = false;
    immediate_warning_id = -1;
}
void BuildPlanner::init_tiles(int size_x, int size_y) {
    size.x = size_x;
    size.y = size_y;
    for (int row = 0; row < size.y; ++row) {
        for (int column = 0; column < size.x; ++column) {
            if (column > 29 || row > 29)
                return;
            tile_graphics_array[row][column] = 0;
            tile_sizes_array[row][column] = 1; // reset tile size to 1 by default
            tile_restricted_terrains[row][column] = TERRAIN_ALL;
            tile_blocked_array[row][column] = false;

            // reset caches
            tile_coord_cache[row][column] = {0, 0};
            pixel_coords_cache[row][column] = {0, 0};
        }
    }
}
void BuildPlanner::set_pivot(int x, int y) {
    pivot.x = x;
    pivot.y = y;
}
void BuildPlanner::update_coord_caches(const map_tile *cursor_tile, int x, int y) {
    end = *cursor_tile;
    int orientation = city_view_orientation() / 2;
    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {

            // get tile offset
            int x_offset = (column - pivot.x);
            int y_offset = (row - pivot.y);

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
                case 3:
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

void BuildPlanner::set_graphics_row(int row, int *image_ids, int total) {
    for (int i = 0; i < total; ++i) {
        if (row > 29 || i > 29)
            return;
        tile_graphics_array[row][i] = image_ids[i];
    }
}
void BuildPlanner::set_graphics_array(int *image_set, int size_x, int size_y) {
    int (*image_array)[size_y][size_x] = (int(*)[size_y][size_x])image_set;

    // do it row by row...
    for (int row = 0; row < size_y; ++row)
        set_graphics_row(row, (*image_array)[row], size_x);
}

void BuildPlanner::set_tile_size(int row, int column, int size) {
    if (row > 29 || column > 29)
        return;
    tile_sizes_array[row][column] = size;
}
void BuildPlanner::set_allowed_terrain(int row, int column, int terrain) {
    if (row > 29 || column > 29)
        return;
    tile_restricted_terrains[row][column] = terrain;
}

void BuildPlanner::set_requirements(long long flags, int extra_param) {
    requirement_flags |= flags;
    additional_req_param = extra_param;
}
void BuildPlanner::update_requirements_check() {
    immediate_warning_id = -1;
    meets_special_requirements = true;

    if (requirement_flags & PlannerReqs::Groundwater) {
        if (!map_terrain_exists_tile_in_radius_with_type(end.x, end.y, size.x, 0, TERRAIN_GROUNDWATER)) {
            immediate_warning_id = WARNING_GROUNDWATER_NEEDED;
            meets_special_requirements = false;
        }
    }
    if (requirement_flags & PlannerReqs::NearbyWater) {
        if (!map_terrain_exists_tile_in_radius_with_type(end.x, end.y, size.x, 3, TERRAIN_WATER)
            && !map_terrain_exists_tile_in_radius_with_type(end.x, end.y, size.x, 3, TERRAIN_FLOODPLAIN)) {
            immediate_warning_id = WARNING_WATER_NEEDED;
            meets_special_requirements = false;
        }
    }
    if (requirement_flags & PlannerReqs::Meadow) {
        int can_place = false;
        if (map_terrain_exists_tile_in_radius_with_type(end.x, end.y, size.x, 0, TERRAIN_MEADOW)) {
            immediate_warning_id = WARNING_MEADOW_NEEDED;
            can_place = true;
        }
        if (GAME_ENV == ENGINE_ENV_PHARAOH && map_terrain_all_tiles_in_radius_are(end.x, end.y, size.x, 0, TERRAIN_FLOODPLAIN)) {
            immediate_warning_id = WARNING_MEADOW_NEEDED;
            can_place = true;
        }
        if (!can_place)
            meets_special_requirements = false;
    }
    if (requirement_flags & PlannerReqs::Rock) {
        if (!map_terrain_exists_tile_in_radius_with_type(end.x, end.y, size.x, 1, TERRAIN_ROCK)) {
            immediate_warning_id = WARNING_ROCK_NEEDED;
            meets_special_requirements = false;
        }
    }
    if (requirement_flags & PlannerReqs::Ore) {
        if (!map_terrain_exists_tile_in_radius_with_type(end.x, end.y, size.x, 1, TERRAIN_ORE)) {
            immediate_warning_id = WARNING_ROCK_NEEDED;
            meets_special_requirements = false;
        }
    }
    if (requirement_flags & PlannerReqs::Trees) {
        if (!map_terrain_exists_tile_in_radius_with_type(end.x, end.y, size.x, 1, TERRAIN_SHRUB | TERRAIN_TREE)) {
            immediate_warning_id = WARNING_TREE_NEEDED;
            meets_special_requirements = false;
        }
    }
    if (requirement_flags & PlannerReqs::Walls) {
        if (!map_terrain_all_tiles_in_radius_are(end.x, end.y, size.x, 0, TERRAIN_WALL)) {
            immediate_warning_id = WARNING_WALL_NEEDED;
            meets_special_requirements = false;
        }
    }
}
void BuildPlanner::dispatch_warnings() {
    if (immediate_warning_id > -1)
        city_warning_show(immediate_warning_id);
}

void BuildPlanner::update_obstructions_check() {
    tiles_blocked_total = 0;
    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {

            // check terrain at coords
            map_point current_tile = tile_coord_cache[row][column];
            int restricted_terrain = tile_restricted_terrains[row][column];

            tile_blocked_array[row][column] = false;
            int grid_offset = map_grid_offset(current_tile.x, current_tile.y);
            if (!map_grid_is_inside(current_tile.x, current_tile.y, 1) || map_terrain_is(grid_offset, restricted_terrain & TERRAIN_NOT_CLEAR)) {
                tile_blocked_array[row][column] = true;
                tiles_blocked_total++;
            }
        }
    }
}

//////

void BuildPlanner::draw_flat_tile(int x, int y, color_t color_mask) {
    ImageDraw::img_blended(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, color_mask);
}
void BuildPlanner::draw_blueprints(bool fully_blocked) {
    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {

            // draw tile!
            pixel_coordinate current_coord = pixel_coords_cache[row][column];
            if (tile_blocked_array[row][column] || fully_blocked)
                draw_flat_tile(current_coord.x, current_coord.y, COLOR_MASK_RED);
            else
                draw_flat_tile(current_coord.x, current_coord.y, COLOR_MASK_GREEN);
        }
    }
}
void BuildPlanner::draw_graphics() {

    // go through the tiles DIAGONALLY to render footprint and top correctly
    for (int dg_y = 0; dg_y < size.y + size.x - 1; dg_y++) {
        for (int dg_x = fmax(0, dg_y - size.y + 1); dg_x < size.x && dg_x < dg_y + 1; dg_x++) {

            // extract proper row and column index from the mess above
            int row = dg_y - dg_x;
            int column = dg_x;

            int image_id = tile_graphics_array[row][column];
            if (image_id > 0) {
                pixel_coordinate current_coord = pixel_coords_cache[row][column];
                ImageDraw::isometric_footprint_from_drawtile(image_id, current_coord.x, current_coord.y, COLOR_MASK_GREEN);
                ImageDraw::isometric_top_from_drawtile(image_id, current_coord.x, current_coord.y, COLOR_MASK_GREEN);
            }
        }
    }
}

//////

void BuildPlanner::update_orientations() {

    switch (building_type) {
        case BUILDING_SMALL_STATUE:
        case BUILDING_MEDIUM_STATUE:
        case BUILDING_LARGE_STATUE:
            orientation = building_rotation_get_rotation() + 1;
            variant = building_rotation_get_building_variant();
            break;
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_RA:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
        case BUILDING_TEMPLE_COMPLEX_BAST:
            building_rotation_force_two_orientations();
            orientation = building_rotation_get_building_orientation(building_rotation_get_rotation()) / 2;
            variant = 0;
            break;
        default:
            orientation = 0;
            variant = 0;
            break;
    }
    load_build_graphics(); // reload graphics, tiles, etc.
}

void BuildPlanner::update(const map_tile *cursor_tile, int x, int y) {
    update_coord_caches(cursor_tile, x, y);
    update_obstructions_check();
    update_requirements_check();
}
void BuildPlanner::draw() {
    // draw!
    if (!meets_special_requirements)
        return draw_blueprints(true);
    else if (tiles_blocked_total > 0)
        draw_blueprints(false);
    else
        draw_graphics();
}
bool BuildPlanner::place_check_attempt() {
    if (tiles_blocked_total > 0 || !meets_special_requirements) {
        dispatch_warnings();
        return false;
    }
    return true;
}