#include "sprite.h"

#include "map/grid.h"

static grid_xx sprite = {0, FS_UINT8};
static grid_xx sprite_backup = {0, FS_UINT8};

int map_sprite_animation_at(int grid_offset)
{
    return map_grid_get(&sprite, grid_offset);
}

void map_sprite_animation_set(int grid_offset, int value)
{
    map_grid_set(&sprite, grid_offset, value);
}

int map_sprite_bridge_at(int grid_offset)
{
    return map_grid_get(&sprite, grid_offset);
}

void map_sprite_bridge_set(int grid_offset, int value)
{
    map_grid_set(&sprite, grid_offset, value);
}

void map_sprite_clear_tile(int grid_offset)
{
    map_grid_set(&sprite, grid_offset, 0);
}

void map_sprite_clear(void)
{
    map_grid_clear(&sprite);
}

void map_sprite_backup(void)
{
    map_grid_copy(&sprite, &sprite_backup);
}

void map_sprite_restore(void)
{
    map_grid_copy(&sprite_backup, &sprite);
}

void map_sprite_save_state(buffer *buf, buffer *backup)
{
    map_grid_save_state(&sprite, buf);
    map_grid_save_state(&sprite_backup, backup);
}

void map_sprite_load_state(buffer *buf, buffer *backup)
{
    map_grid_load_state(&sprite, buf);
    map_grid_load_state(&sprite_backup, backup);
}
