#include "random.h"
#include "grid/random_chunks.h"
#include "io/io_buffer.h"

#include "core/random.h"
#include "grid/grid.h"


void map_random_clear() {
    map_grid_clear(random_grid_chunk::grid);
}

void map_random_init() {
    int grid_offset = 0;
    for (int y = 0; y < GRID_LENGTH; y++) {
        for (int x = 0; x < GRID_LENGTH; x++, grid_offset++) {
            random_generate_next();
            map_grid_set(random_grid_chunk::grid, grid_offset, (uint8_t)random_short());
        }
    }
}

int map_random_get(int grid_offset) {
    return map_grid_get(random_grid_chunk::grid, grid_offset);
}

void map_random_set(int grid_offset, int value) {
    map_grid_set(random_grid_chunk::grid, grid_offset, value);
}
