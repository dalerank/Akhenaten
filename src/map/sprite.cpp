#include <game/gamestate/io_buffer.h>
#include "sprite.h"

#include "map/grid.h"

static grid_xx sprite = {0, {FS_UINT8, FS_UINT8}};
static grid_xx sprite_backup = {0, {FS_UINT8, FS_UINT8}};

int map_sprite_animation_at(int grid_offset) {
    return map_grid_get(&sprite, grid_offset);
}
void map_sprite_animation_set(int grid_offset, int value) {
    map_grid_set(&sprite, grid_offset, value);
}

void map_sprite_clear_tile(int grid_offset) {
    map_grid_set(&sprite, grid_offset, 0);
}
void map_sprite_clear(void) {
    map_grid_clear(&sprite);
}

void map_sprite_backup(void) {
    map_grid_copy(&sprite, &sprite_backup);
}
void map_sprite_restore(void) {
    map_grid_copy(&sprite_backup, &sprite);
}


io_buffer *iob_sprite_grid = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_GRID, &sprite);
});
io_buffer *iob_sprite_backup_grid = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_GRID, &sprite_backup);
});