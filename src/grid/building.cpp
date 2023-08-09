#include "building.h"
#include "io/io_buffer.h"

#include "building/building.h"
#include "grid/grid.h"
#include "io/config/config.h"

static grid_xx buildings_grid = {0, {FS_UINT16, FS_UINT16}};
static grid_xx damage_grid = {0, {FS_UINT8, FS_UINT16}};
static grid_xx rubble_type_grid = {0, {FS_UINT8, FS_UINT8}};
static grid_xx highlight_grid = {0, {FS_UINT8, FS_UINT8}};

int map_building_at(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) ? map_grid_get(&buildings_grid, grid_offset) : 0;
}
void map_building_set(int grid_offset, int building_id) {
    map_grid_set(&buildings_grid, grid_offset, building_id);
}
void map_building_damage_clear(int grid_offset) {
    map_grid_set(&damage_grid, grid_offset, 0);
}
void map_highlight_set(int grid_offset) {
    map_grid_set(&highlight_grid, grid_offset, 1);
}
void map_highlight_clear(int grid_offset) {
    map_grid_set(&highlight_grid, grid_offset, 0);
}
int map_is_highlighted(int grid_offset) {
    if (config_get(CONFIG_UI_WALKER_WAYPOINTS))
        return map_grid_get(&highlight_grid, grid_offset);

    else {
        return 0;
    }
}
int map_building_damage_increase(int grid_offset) {
    int d = map_grid_get(&damage_grid, grid_offset) + 1;
    map_grid_set(&damage_grid, grid_offset, d);
    return d;
}
int map_rubble_building_type(int grid_offset) {
    return map_grid_get(&rubble_type_grid, grid_offset);
}
void map_set_rubble_building_type(int grid_offset, int type) {
    map_grid_set(&rubble_type_grid, grid_offset, type);
}
void map_building_clear(void) {
    map_grid_clear(&buildings_grid);
    map_grid_clear(&damage_grid);
    map_grid_clear(&rubble_type_grid);
}
void map_clear_highlights(void) {
    map_grid_clear(&highlight_grid);
}

io_buffer* iob_building_grid
  = new io_buffer([](io_buffer* iob, size_t version) { iob->bind(BIND_SIGNATURE_GRID, &buildings_grid); });

io_buffer* iob_damage_grid
  = new io_buffer([](io_buffer* iob, size_t version) { iob->bind(BIND_SIGNATURE_GRID, &damage_grid); });

int map_building_is_reservoir(int x, int y) {
    if (!map_grid_is_inside(x, y, 3))
        return 0;

    int grid_offset = MAP_OFFSET(x, y);
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
