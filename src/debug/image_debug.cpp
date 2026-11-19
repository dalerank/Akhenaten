#include "app/app.h"
#include "dev/debug.h"

#include "grid/image.h"

static void draw_image_tile(vec2i pixel, tile2i point, painter &ctx) {
    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", map_image_at(point.grid_offset()), COLOR_LIGHT_RED);
}

static void draw_image_alt_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int image_alt_value = map_image_alt_at(point.grid_offset());
    const int image_alt_id = (image_alt_value & 0x00ffffff);
    const uint8_t image_alt_alpha = (image_alt_value & 0xff000000) >> 24;
    if (image_alt_id <= 0 || image_alt_alpha == 0)
        return;

    char str[64];
    snprintf(str, 30, "%d(%d)", image_alt_id, image_alt_alpha);
    debug_text_a(ctx, str, pixel.x + 15, pixel.y + 10, 0, str, COLOR_LIGHT_RED);
}

void ANK_REGISTER_APPLICATION_MODULE(register_image_debug) {
    g_debug.add_tile_render_handler("image", draw_image_tile);
    g_debug.add_tile_render_handler("image_alt", draw_image_alt_tile);
}
