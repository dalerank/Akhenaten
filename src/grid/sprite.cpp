#include "sprite.h"
#include "grid/sprite_chunks.h"
#include "io/io_buffer.h"

#include "grid/grid.h"


int map_sprite_animation_at(int grid_offset) {
    return map_grid_get(sprite_grid_chunk::grid, grid_offset);
}
void map_sprite_animation_set(int grid_offset, int value) {
    map_grid_set(sprite_grid_chunk::grid, grid_offset, value);
}

void map_sprite_clear_tile(int grid_offset) {
    map_grid_set(sprite_grid_chunk::grid, grid_offset, 0);
}
void map_sprite_clear(void) {
    map_grid_clear(sprite_grid_chunk::grid);
}

void map_sprite_backup(void) {
    map_grid_copy(sprite_grid_chunk::grid, sprite_backup_grid_chunk::grid);
}
void map_sprite_restore(void) {
    map_grid_copy(sprite_backup_grid_chunk::grid, sprite_grid_chunk::grid);
}
