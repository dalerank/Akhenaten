#include "image.h"

#include "map/grid.h"

static grid_xx images = {0, {FS_UINT16, FS_UINT32}};
static grid_xx images_backup = {0, {FS_UINT16, FS_UINT32}};

int map_image_at(int grid_offset) {
    return map_grid_get(&images, grid_offset);
}
void map_image_set(int grid_offset, int image_id) {
    map_grid_set(&images, grid_offset, image_id);
}

void map_image_backup(void) {
    map_grid_copy(&images, &images_backup);
}
void map_image_restore(void) {
    map_grid_copy(&images_backup, &images);
}
void map_image_restore_at(int grid_offset) {
    map_grid_set(&images, grid_offset, map_grid_get(&images_backup, grid_offset));
}

void map_image_clear(void) {
    map_grid_clear(&images);
}
void map_image_init_edges(void) {
    int width, height;
    map_grid_size(&width, &height);
    for (int x = 1; x < width; x++) {
        map_grid_set(&images, map_grid_offset(x, height), 1);
    }
    for (int y = 1; y < height; y++) {
        map_grid_set(&images, map_grid_offset(width, y), 2);
    }
    map_grid_set(&images, map_grid_offset(0, height), 3);
    map_grid_set(&images, map_grid_offset(width, 0), 4);
    map_grid_set(&images, map_grid_offset(width, height), 5);
}

void map_image_save_state(buffer *buf) {
    map_grid_save_buffer(&images, buf);
}
void map_image_load_state(buffer *buf, int shift) {
    map_grid_load_buffer(&images, buf);
    for (int i = 0; i < grid_total_size[GAME_ENV]; i++) {
        auto nv = map_grid_get(&images, i) - shift;
        map_grid_set(&images, i, nv);
    }
}
