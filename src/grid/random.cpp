#include "random.h"
#include "io/io_buffer.h"

#include "core/game_environment.h"
#include "core/random.h"
#include "grid/grid.h"

static grid_xx random_xx = {0, FS_UINT8};

void map_random_clear(void) {
    map_grid_clear(&random_xx);
}
void map_random_init(void) {
    int grid_offset = 0;
    for (int y = 0; y < GRID_LENGTH; y++) {
        for (int x = 0; x < GRID_LENGTH; x++, grid_offset++) {
            random_generate_next();
            map_grid_set(&random_xx, grid_offset, (uint8_t)random_short());
        }
    }
}
int map_random_get(int grid_offset) {
    return map_grid_get(&random_xx, grid_offset);
}

io_buffer* iob_random_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &random_xx);
});