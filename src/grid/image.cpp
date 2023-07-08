#include "io/io_buffer.h"
#include "graphics/image.h"

#include "grid/grid.h"

grid_xx g_images_grid = {0,
                           {
                             FS_UINT16, // c3
                             FS_UINT32  // ph
                            }
                        };
grid_xx g_images_grid_backup = {0,
                                  {
                                    FS_UINT16, // c3
                                    FS_UINT32  // ph
                                  }
                               };

int map_image_at(int grid_offset) {
    return map_grid_get(&g_images_grid, grid_offset);
}
void map_image_set(int grid_offset, int image_id) {
    map_grid_set(&g_images_grid, grid_offset, image_id);
}

void map_image_backup(void) {
    map_grid_copy(&g_images_grid, &g_images_grid_backup);
}
void map_image_restore(void) {
    map_grid_copy(&g_images_grid_backup, &g_images_grid);
}
void map_image_restore_at(int grid_offset) {
    map_grid_set(&g_images_grid, grid_offset, map_grid_get(&g_images_grid_backup, grid_offset));
}

void map_image_clear(void) {
    map_grid_clear(&g_images_grid);
}
void map_image_init_edges(void) {
    int width = scenario_map_data()->width;
    int height = scenario_map_data()->height;
//    map_grid_size(&width, &height);
    for (int x = 1; x < width; x++) {
        map_grid_set(&g_images_grid, MAP_OFFSET(x, height), 1);
    }
    for (int y = 1; y < height; y++) {
        map_grid_set(&g_images_grid, MAP_OFFSET(width, y), 2);
    }
    map_grid_set(&g_images_grid, MAP_OFFSET(0, height), 3);
    map_grid_set(&g_images_grid, MAP_OFFSET(width, 0), 4);
    map_grid_set(&g_images_grid, MAP_OFFSET(width, height), 5);
}

static int image_shift = 0;
void set_image_grid_correction_shift(int shift) {
    image_shift = shift;
}
io_buffer *iob_image_grid = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_GRID, &g_images_grid);
    for (int i = 0; i < GRID_SIZE_TOTAL; i++) {
        auto nv = map_grid_get(&g_images_grid, i) - image_shift;
        map_grid_set(&g_images_grid, i, nv);
    }
});