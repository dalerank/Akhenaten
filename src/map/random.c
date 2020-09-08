#include "random.h"

#include "core/random.h"
#include "core/game_environment.h"
#include "map/grid.h"

static grid_u8_x random = {0, 0};

void map_random_clear(void)
{
    map_grid_clear_u8(safe_u8(&random)->items);
}
void map_random_init(void)
{
    int grid_offset = 0;
    for (int y = 0; y < grid_size[GAME_ENV]; y++) {
        for (int x = 0; x < grid_size[GAME_ENV]; x++, grid_offset++) {
            random_generate_next();
            safe_u8(&random)->items[grid_offset] = (uint8_t) random_short();
        }
    }
}
int map_random_get(int grid_offset)
{
    return safe_u8(&random)->items[grid_offset];
}

void map_random_save_state(buffer *buf)
{
    map_grid_save_state_u8(safe_u8(&random)->items, buf);
}
void map_random_load_state(buffer *buf)
{
    map_grid_load_state_u8(safe_u8(&random)->items, buf);
}
