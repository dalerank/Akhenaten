#include "aqueduct.h"

#include "map/grid.h"

/**
 * The aqueduct grid is used in two ways:
 * 1) to mark water/no water (0/1, see map/water_supply.c)
 * 2) to store image IDs for the aqueduct (0-15)
 * This leads to some strange results
 */
static grid_u8_x aqueduct = {0, 0};
static grid_u8_x aqueduct_backup = {0, 0};

int map_aqueduct_at(int grid_offset)
{
    return safe_u8(&aqueduct)->items[grid_offset];
}
void map_aqueduct_set(int grid_offset, int value)
{
    safe_u8(&aqueduct)->items[grid_offset] = value;
}
void map_aqueduct_remove(int grid_offset)
{
    safe_u8(&aqueduct)->items[grid_offset] = 0;
    if (safe_u8(&aqueduct)->items[grid_offset + map_grid_delta(0, -1)] == 5) {
        safe_u8(&aqueduct)->items[grid_offset + map_grid_delta(0, -1)] = 1;
    }
    if (safe_u8(&aqueduct)->items[grid_offset + map_grid_delta(1, 0)] == 6) {
        safe_u8(&aqueduct)->items[grid_offset + map_grid_delta(1, 0)] = 2;
    }
    if (safe_u8(&aqueduct)->items[grid_offset + map_grid_delta(0, 1)] == 5) {
        safe_u8(&aqueduct)->items[grid_offset + map_grid_delta(0, 1)] = 3;
    }
    if (safe_u8(&aqueduct)->items[grid_offset + map_grid_delta(-1, 0)] == 6) {
        safe_u8(&aqueduct)->items[grid_offset + map_grid_delta(-1, 0)] = 4;
    }
}
void map_aqueduct_clear(void)
{
    map_grid_clear_u8(safe_u8(&aqueduct)->items);
}
void map_aqueduct_backup(void)
{
    map_grid_copy_u8(safe_u8(&aqueduct)->items, safe_u8(&aqueduct_backup)->items);
}
void map_aqueduct_restore(void)
{
    map_grid_copy_u8(safe_u8(&aqueduct_backup)->items, safe_u8(&aqueduct)->items);
}

void map_aqueduct_save_state(buffer *buf, buffer *backup)
{
    map_grid_save_state_u8(safe_u8(&aqueduct)->items, buf);
    map_grid_save_state_u8(safe_u8(&aqueduct_backup)->items, backup);
}
void map_aqueduct_load_state(buffer *buf, buffer *backup)
{
    map_grid_load_state_u8(safe_u8(&aqueduct)->items, buf);
    map_grid_load_state_u8(safe_u8(&aqueduct_backup)->items, backup);
}
