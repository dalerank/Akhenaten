#include "image.h"

#include "map/grid.h"

static grid_u16_x images = {0, 0};
static grid_u16_x images_backup = {0, 0};

int map_image_at(int grid_offset)
{
    return safe_u16(&images)->items[grid_offset];
}
void map_image_set(int grid_offset, int image_id)
{
    safe_u16(&images)->items[grid_offset] = image_id;
}

void map_image_backup(void)
{
    map_grid_copy_u16(safe_u16(&images)->items, safe_u16(&images_backup)->items);
}
void map_image_restore(void)
{
    map_grid_copy_u16(safe_u16(&images_backup)->items, safe_u16(&images)->items);
}
void map_image_restore_at(int grid_offset)
{
    safe_u16(&images)->items[grid_offset] = safe_u16(&images_backup)->items[grid_offset];
}

void map_image_clear(void)
{
    map_grid_clear_u16(safe_u16(&images)->items);
}
void map_image_init_edges(void)
{
    int width, height;
    map_grid_size(&width, &height);
    for (int x = 1; x < width; x++) {
        safe_u16(&images)->items[map_grid_offset(x, height)] = 1;
    }
    for (int y = 1; y < height; y++) {
        safe_u16(&images)->items[map_grid_offset(width, y)] = 2;
    }
    safe_u16(&images)->items[map_grid_offset(0, height)] = 3;
    safe_u16(&images)->items[map_grid_offset(width, 0)] = 4;
    safe_u16(&images)->items[map_grid_offset(width, height)] = 5;
}

void map_image_save_state(buffer *buf)
{
    map_grid_save_state_u16(safe_u16(&images)->items, buf);
}
void map_image_load_state(buffer *buf)
{
    map_grid_load_state_u16(safe_u16(&images)->items, buf);
}
