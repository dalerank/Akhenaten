#include "graphics/image.h"

#include "graphics/animation.h"
#include "io/io_buffer.h"
#include "grid/grid.h"
#include "image.h"

grid_xx g_images_grid = {0, FS_UINT32};
grid_xx g_images_grid_backup = {0, FS_UINT32};

grid_xx g_images_alt_grid = {0, FS_UINT32};

int map_image_at(int grid_offset) {
    return (int)map_grid_get(g_images_grid, grid_offset);
}

bool map_image_all_ids_in_area_are(tile2i tile, int size, int image_id) {
    if (!map_grid_is_inside(tile, size))
        return false;

    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = tile.shifted(dx, dy).grid_offset();
            if (map_image_at(grid_offset) != image_id)
                return false;
        }
    }
    return true;
}

int map_image_alt_at(int grid_offset) {
    return (int)map_grid_get(g_images_alt_grid, grid_offset);
}

void map_image_set(int grid_offset, int image_id) {
    map_grid_set(g_images_grid, grid_offset, image_id);
}

void map_image_set(tile2i tile, const animation_t &anim) {
    const int image_id = anim.first_img();
    map_grid_set(g_images_grid, tile.grid_offset(), image_id);
}

void map_image_alt_set(int grid_offset, int image_id, int alpha) {
    if (alpha == -1) {
        int current = map_image_alt_at(grid_offset);
        alpha = (current >> 24) & 0xff;
    }
    if (image_id < 0) {
        image_id = map_image_alt_at(grid_offset);
    }
    uint32_t value = (image_id & 0x00ffffff) | (((uint32_t)alpha) << 24);
    map_grid_set(g_images_alt_grid, grid_offset, value);
}

void map_image_backup() {
    map_grid_copy(g_images_grid, g_images_grid_backup);
}
void map_image_restore() {
    map_grid_copy(g_images_grid_backup, g_images_grid);
}
void map_image_restore_at(int grid_offset) {
    map_grid_set(g_images_grid, grid_offset, map_grid_get(g_images_grid_backup, grid_offset));
}

void map_image_fix_icorrect_tiles() {
    io_image_grid::instance().fix_incorrect_tiles_img();
}

void map_image_clear(void) {
    map_grid_clear(g_images_grid);
    map_grid_clear(g_images_alt_grid);
}

void map_image_init_edges() {
    int width = scenario_map_data()->width;
    int height = scenario_map_data()->height;
    //    map_grid_size(&width, &height);
    for (int x = 1; x < width; x++) {
        map_grid_set(g_images_grid, MAP_OFFSET(x, height), 1);
    }
    for (int y = 1; y < height; y++) {
        map_grid_set(g_images_grid, MAP_OFFSET(width, y), 2);
    }
    map_grid_set(g_images_grid, MAP_OFFSET(0, height), 3);
    map_grid_set(g_images_grid, MAP_OFFSET(width, 0), 4);
    map_grid_set(g_images_grid, MAP_OFFSET(width, height), 5);
}

static int image_shift = 0;
void set_image_grid_correction_shift(int shift) {
    image_shift = shift;
}

uint32_t io_image_grid::fix_img_index(int grid_offset, uint32_t index) const {
    if (index >= 15600 && index <= 15616) {
        if (index == 15600 || index == 15601) {
            return 15063;
        }
        return 15063 + index - 15602;
    }

    return index;
}

void io_image_grid::fix_incorrect_tiles_img() {
    for (int grid_offset = 0; grid_offset < GRID_SIZE_TOTAL; grid_offset++) {
        int64_t nv = map_grid_get(g_images_grid, grid_offset) - image_shift;
        nv = fix_img_index(grid_offset, nv);
        map_grid_set(g_images_grid, grid_offset, nv);
    }
}

void io_image_grid::bind_data(size_t version) {
    bind(BIND_SIGNATURE_GRID, &g_images_grid);
}

io_image_grid& io_image_grid::instance() {
    static io_image_grid inst;
    return inst;
}