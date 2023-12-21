#include "monument_mastaba.h"

#include "graphics/view/view.h"
#include "monuments.h"
#include "core/direction.h"
#include "graphics/image.h"
#include "grid/random.h"
#include "grid/tiles.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/image.h"
#include "graphics/view/lookup.h"
#include "graphics/boilerplate.h"

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain) {
    int x_leftmost, y_leftmost;
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT: x_leftmost = 0; y_leftmost = 1; break;
    case DIR_2_BOTTOM_RIGHT: x_leftmost = y_leftmost = 0; break;
    case DIR_4_BOTTOM_LEFT: x_leftmost = 1; y_leftmost = 0; break;
    case DIR_6_TOP_LEFT: x_leftmost = y_leftmost = 1; break;
    default:
    return;
    }

    if (!map_grid_is_inside(tile, size)) {
        return;
    }

    int x_proper = x_leftmost * (size - 1);
    int y_proper = y_leftmost * (size - 1);
    //int clear_land_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = tile.shifted(dx, dy).grid_offset();
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
            map_terrain_add(grid_offset, terrain);
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, size);
            map_monuments_set_progress(grid_offset, 0);
            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == x_proper && dy == y_proper);
        }
    }
}

void draw_small_mastaba_anim_flat(painter &ctx, int x, int y, building *b, int color_mask) {
    int clear_land_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND);
    //map_image_set(grid_offset, clear_land_id + (map_random_get(grid_offset) & 7));
    int image_grounded = image_group(IMG_SMALL_MASTABA) + 5;
    if (b->data.monuments.phase == 0) {
        for (int dy = 0; dy < 4; dy++) {
            for (int dx = 0; dx < 4; dx++) {
                tile2i ntile = b->tile.shifted(dx, dy);
                vec2i offset = tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile.grid_offset());
                if (progress < 200) {
                    ImageDraw::img_sprite(ctx, clear_land_id + ((dy * 4 + dx) & 7), offset.x, offset.y, color_mask);
                }

                if (progress > 0 && progress <= 200) {
                    int clr = ((0xff * progress / 200) << 24) | 0x00ffffff;
                    ImageDraw::img_sprite(ctx, image_grounded + ((dy * 4 + dx) & 7), offset, clr, 1.f, true);
                }
            }
        }

        int image_stick = image_group(IMG_SMALL_MASTABA) + 5 + 8;
        const image_t *img = image_get(image_stick);
        tile2i left_top = b->tile.shifted(0, 0);
        if (map_monuments_get_progress(left_top.grid_offset()) == 0) {
            vec2i offset = tile_to_pixel(left_top);
            ImageDraw::img_sprite(ctx, image_stick, offset.x + img->animation.sprite_x_offset, offset.y + img->animation.sprite_y_offset - img->height + 30, color_mask);
        }

        tile2i right_top = b->tile.shifted(3, 0);
        if (map_monuments_get_progress(right_top.grid_offset()) == 0) {
            vec2i offset = tile_to_pixel(right_top);
            ImageDraw::img_sprite(ctx, image_stick, offset.x + img->animation.sprite_x_offset, offset.y + img->animation.sprite_y_offset - img->height + 30, color_mask);
        }

        tile2i left_bottom = b->tile.shifted(0, 3);
        if (map_monuments_get_progress(left_bottom.grid_offset()) == 0) {
            vec2i offset = tile_to_pixel(left_bottom);
            ImageDraw::img_sprite(ctx, image_stick, offset.x + img->animation.sprite_x_offset, offset.y + img->animation.sprite_y_offset - img->height + 30, color_mask);
        }

        tile2i right_bottom = b->tile.shifted(3, 3);
        if (map_monuments_get_progress(right_bottom.grid_offset()) == 0) {
            vec2i offset = tile_to_pixel(right_bottom);
            ImageDraw::img_sprite(ctx, image_stick, offset.x + img->animation.sprite_x_offset, offset.y + img->animation.sprite_y_offset - img->height + 30, color_mask);
        }
    }
}