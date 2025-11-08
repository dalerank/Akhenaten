#include "building_bridge.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/property.h"
#include "grid/sprite.h"
#include "grid/terrain.h"

void city_draw_bridge(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    if (!map_terrain_is(grid_offset, TERRAIN_WATER)) {
        map_sprite_clear_tile(grid_offset);
        return;
    }
    if (map_terrain_is(grid_offset, TERRAIN_BUILDING))
        return;
    color color_mask = 0;
    if (map_property_is_deleted(grid_offset))
        color_mask = COLOR_MASK_RED;

    city_draw_bridge_tile(ctx, x, y, map_sprite_animation_at(grid_offset) + 1, color_mask);
}

void city_draw_bridge_tile(painter &ctx, int x, int y, int bridge_sprite_id, color color_mask) {
    int image_id = image_id_from_group(GROUP_BUILDING_BRIDGE);
    switch (bridge_sprite_id) {
    case 1:
        ctx.img_generic(image_id + 5, { x, y - 20 }, color_mask);
        break;
    case 2:
        ctx.img_generic(image_id, { x - 1, y - 8 }, color_mask);
        break;
    case 3:
        ctx.img_generic(image_id + 3, { x, y - 8 }, color_mask);
        break;
    case 4:
        ctx.img_generic(image_id + 2, { x + 7, y - 20 }, color_mask);
        break;
    case 5:
        ctx.img_generic(image_id + 4, { x, y - 21 }, color_mask);
        break;
    case 6:
        ctx.img_generic(image_id + 1, { x + 5, y - 21 }, color_mask);
        break;
    case 7:
        ctx.img_generic(image_id + 11, { x - 3, y - 50 }, color_mask);
        break;
    case 8:
        ctx.img_generic(image_id + 6, { x - 1, y - 12 }, color_mask);
        break;
    case 9:
        ctx.img_generic(image_id + 9, { x - 30, y - 12 }, color_mask);
        break;
    case 10:
        ctx.img_generic(image_id + 8, { x - 23, y - 53 }, color_mask);
        break;
    case 11:
        ctx.img_generic(image_id + 10, { x, y - 37 }, color_mask);
        break;
    case 12:
        ctx.img_generic(image_id + 7, { x + 7, y - 38 }, color_mask);
        break;
        // Note: no nr 13
    case 14:
        ctx.img_generic(image_id + 13, { x, y - 38 }, color_mask);
        break;
    case 15:
        ctx.img_generic(image_id + 12, { x + 7, y - 38 }, color_mask);
        break;
    }
}
