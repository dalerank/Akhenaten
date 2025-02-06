#include "sprite.h"
#include "io/io_buffer.h"

#include "grid/grid.h"

grid_xx g_sprite_grid = {0, FS_UINT8};
grid_xx g_sprite_grid_backup = {0, FS_UINT8};

int map_sprite_animation_at(int grid_offset) {
    return map_grid_get(g_sprite_grid, grid_offset);
}
void map_sprite_animation_set(int grid_offset, int value) {
    map_grid_set(g_sprite_grid, grid_offset, value);
}

void map_sprite_clear_tile(int grid_offset) {
    map_grid_set(g_sprite_grid, grid_offset, 0);
}
void map_sprite_clear(void) {
    map_grid_clear(g_sprite_grid);
}

void map_sprite_backup(void) {
    map_grid_copy(g_sprite_grid, g_sprite_grid_backup);
}
void map_sprite_restore(void) {
    map_grid_copy(g_sprite_grid_backup, g_sprite_grid);
}

io_buffer* iob_sprite_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_sprite_grid);
});

io_buffer* iob_sprite_backup_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_sprite_grid_backup);
});