#include "aqueduct.h"

#include "grid/grid.h"

/**
 * The aqueduct grid is used in two ways:
 * 1) to mark water/no water (0/1, see grid/bathhouse.c)
 * 2) to store image IDs for the aqueduct (0-15)
 * This leads to some strange results
 */
static grid_xx aqueduct = {0, {FS_UINT8, FS_UINT8}};
static grid_xx aqueduct_backup = {0, {FS_UINT8, FS_UINT8}};

int map_aqueduct_at(int grid_offset) {
    return map_grid_get(&aqueduct, grid_offset);
}
void map_aqueduct_set(int grid_offset, int value) {
    map_grid_set(&aqueduct, grid_offset, value);
}
void map_aqueduct_remove(int grid_offset) {
    map_grid_set(&aqueduct, grid_offset, 0);
    if (map_grid_get(&aqueduct, grid_offset + GRID_OFFSET(0, -1)) == 5)
        map_grid_set(&aqueduct, grid_offset + GRID_OFFSET(0, -1), 1);

    if (map_grid_get(&aqueduct, grid_offset + GRID_OFFSET(1, 0)) == 6)
        map_grid_set(&aqueduct, grid_offset + GRID_OFFSET(1, 0), 2);

    if (map_grid_get(&aqueduct, grid_offset + GRID_OFFSET(0, 1)) == 5)
        map_grid_set(&aqueduct, grid_offset + GRID_OFFSET(0, 1), 3);

    if (map_grid_get(&aqueduct, grid_offset + GRID_OFFSET(-1, 0)) == 6)
        map_grid_set(&aqueduct, grid_offset + GRID_OFFSET(-1, 0), 4);
}
void map_aqueduct_clear(void) {
    map_grid_clear(&aqueduct);
}

#include "io/io_buffer.h"
#include <stdlib.h>

void map_aqueduct_backup(void) {
    void* t = malloc(12);
    uint16_t* x = (uint16_t*)t;

    uint16_t g = x[2];
    x[4] = 1;

    map_grid_copy(&aqueduct, &aqueduct_backup);
}
void map_aqueduct_restore(void) {
    map_grid_copy(&aqueduct_backup, &aqueduct);
}

io_buffer* iob_aqueduct_grid = new io_buffer([](io_buffer* iob) { iob->bind(BIND_SIGNATURE_GRID, &aqueduct); });
io_buffer* iob_aqueduct_backup_grid
  = new io_buffer([](io_buffer* iob) { iob->bind(BIND_SIGNATURE_GRID, &aqueduct_backup); });