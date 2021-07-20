#include "random.h"

#include "core/random.h"
#include "core/game_environment.h"
#include "map/grid.h"

static grid_xx random_xx = {0, {FS_UINT8, FS_UINT8}};

void map_random_clear(void) {
    map_grid_clear(&random_xx);
}
void map_random_init(void) {
    int grid_offset = 0;
    for (int y = 0; y < grid_size[GAME_ENV]; y++) {
        for (int x = 0; x < grid_size[GAME_ENV]; x++, grid_offset++) {
            random_generate_next();
            map_grid_set(&random_xx, grid_offset, (uint8_t) random_short());
        }
    }
}
int map_random_get(int grid_offset) {
    return map_grid_get(&random_xx, grid_offset);
}

void map_random_save_state(buffer *buf) {
    map_grid_save_buffer(&random_xx, buf);
}
void map_random_load_state(buffer *buf) {
    map_grid_load_buffer(&random_xx, buf);
}
