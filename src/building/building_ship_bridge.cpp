#include "building_ship_bridge.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "js/js_register.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_ship_bridge);

static void enqueue_ship_bridge_image(painter &ctx, int image_id, vec2i pixel, color color_mask) {
    auto &command = ImageDraw::create_command(ctx, render_command_t::ert_generic);
    command.image_id = image_id;
    command.pixel = pixel;
    command.mask = color_mask;
    command.scale = 1.f;
}

void city_draw_ship_bridge_tile(painter &ctx, int x, int y, int bridge_sprite_id, color color_mask) {
    int image_id = image_id_from_group(GROUP_BUILDING_BRIDGE);
    switch (bridge_sprite_id) {
    case 7:
        enqueue_ship_bridge_image(ctx, image_id + 11, {x - 3, y - 50}, color_mask);
        break;
    case 8:
        enqueue_ship_bridge_image(ctx, image_id + 6, {x - 1, y - 12}, color_mask);
        break;
    case 9:
        enqueue_ship_bridge_image(ctx, image_id + 9, {x - 30, y - 12}, color_mask);
        break;
    case 10:
        enqueue_ship_bridge_image(ctx, image_id + 8, {x - 23, y - 53}, color_mask);
        break;
    case 11:
        enqueue_ship_bridge_image(ctx, image_id + 10, {x, y - 37}, color_mask);
        break;
    case 12:
        enqueue_ship_bridge_image(ctx, image_id + 7, {x + 7, y - 38}, color_mask);
        break;
    case 14:
        enqueue_ship_bridge_image(ctx, image_id + 13, {x, y - 38}, color_mask);
        break;
    case 15:
        enqueue_ship_bridge_image(ctx, image_id + 12, {x + 7, y - 38}, color_mask);
        break;
    default:
        break;
    }
}
