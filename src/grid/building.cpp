#include "building.h"
#include "io/io_buffer.h"

#include "building/building.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/image.h"
#include "game/game_config.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"

grid_xx g_buildings_grid = {0, FS_UINT16};
grid_xx g_damage_grid = {0, FS_UINT16};
grid_xx g_rubble_type_grid = {0, FS_UINT8};
grid_xx g_highlight_grid = {0, FS_UINT8};
grid_xx g_height_building_grid = {0, FS_UINT8};

int map_building_at(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) ? map_grid_get(g_buildings_grid, grid_offset) : 0;
}
int map_building_at(tile2i tile) {
    return map_grid_is_valid_offset(tile.grid_offset()) ? map_grid_get(g_buildings_grid, tile.grid_offset()) : 0;
}
void map_building_set(int grid_offset, int building_id) {
    map_grid_set(g_buildings_grid, grid_offset, building_id);
}
void map_building_damage_clear(int grid_offset) {
    map_grid_set(g_damage_grid, grid_offset, 0);
}

void map_highlight_set(int grid_offset, e_highligth_mode mode) {
    if (grid_offset < 0) {
        return;
    }

    map_grid_set(g_highlight_grid, grid_offset, mode);
}

e_highligth_mode map_is_highlighted(int grid_offset) {
    if (!!game_features::gameui_walker_waypoints) {
        return (e_highligth_mode)map_grid_get(g_highlight_grid, grid_offset);
    }

    return ehighligth_none;
}

void map_highlight_clear(int grid_offset) {
    map_grid_set(g_highlight_grid, grid_offset, 0);
}

int map_building_height_at(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) ? map_grid_get(g_height_building_grid, grid_offset) : 0;
}

void map_building_height_set(int grid_offset, int8_t height) {
    map_grid_set(g_height_building_grid, grid_offset, height);
}

int map_building_damage_increase(int grid_offset) {
    int d = map_grid_get(g_damage_grid, grid_offset) + 1;
    map_grid_set(g_damage_grid, grid_offset, d);
    return d;
}

int map_rubble_building_type(int grid_offset) {
    return map_grid_get(g_rubble_type_grid, grid_offset);
}

void map_set_rubble_building_type(int grid_offset, int type) {
    map_grid_set(g_rubble_type_grid, grid_offset, type);
}

void map_building_clear() {
    map_grid_clear(g_buildings_grid);
    map_grid_clear(g_damage_grid);
    map_grid_clear(g_rubble_type_grid);
    map_grid_clear(g_height_building_grid);
}
void map_clear_highlights() {
    map_grid_clear(g_highlight_grid);
}

int map_building_is_reservoir(tile2i tile) {
    if (!map_grid_is_inside(tile, 3))
        return 0;

    int grid_offset = tile.grid_offset();
    int building_id = map_building_at(grid_offset);
    if (!building_id || building_get(building_id)->type != BUILDING_WATER_LIFT)
        return 0;

    for (int dy = 0; dy < 3; dy++) {
        for (int dx = 0; dx < 3; dx++) {
            if (building_id != map_building_at(grid_offset + GRID_OFFSET(dx, dy)))
                return 0;
        }
    }
    return 1;
}

void map_building_update_all_tiles() {

}

io_buffer *iob_building_grid = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_buildings_grid);
});

io_buffer *iob_damage_grid = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_damage_grid);
});

io_buffer *iob_rubble_type_grid = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_rubble_type_grid);
});