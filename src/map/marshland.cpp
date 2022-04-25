#include <game/io/io_buffer.h>
#include "marshland.h"
#include "grid.h"

struct {
    int all_marshland_tiles[GRID_SIZE_PH * GRID_SIZE_PH];
    int all_river_tiles_x[GRID_SIZE_PH * GRID_SIZE_PH];
    int all_river_tiles_y[GRID_SIZE_PH * GRID_SIZE_PH];
    int river_total_tiles = 0;
} tile_cache;

static grid_xx terrain_marshland_depletion = {0, {FS_UINT8, FS_UINT8}};

int map_get_marshland_depletion(int grid_offset) {
    return map_grid_get(&terrain_marshland_depletion, grid_offset);
}

io_buffer *iob_marshland_depletion = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_GRID, &terrain_marshland_depletion);
});