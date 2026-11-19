#include "app/app.h"
#include "dev/debug.h"

#include "grid/image.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"

static void draw_tile_pos_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int x = pixel.x + 15;
    const int y = pixel.y;
    char str[64];

    ctx.img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, pixel, 0x80000000);
    if (!(point.x() % 5) && !(point.y() % 5)) {
        snprintf(str, 30, "(%d,%d)", point.x(), point.y());
        debug_text_a(ctx, str, x, y + 10, 0, str, COLOR_WHITE, FONT_SMALL_PLAIN);

        vec2i voff = point.to_view();
        snprintf(str, 48, "(%d,%d) (%d,%d)", pixel.x, pixel.y, voff.x, voff.y);
        debug_text_a(ctx, str, x, y + 20, 0, str, COLOR_BLUE, FONT_SMALL_PLAIN);
    }
}

static void draw_tile_toph_tile(vec2i pixel, tile2i point, painter &ctx) {
    const image_t *img = image_get(map_image_at(point.grid_offset()));
    char str[64];
    snprintf(str, 30, "%d", img->isometric_top_height);
    debug_text_a(ctx, str, pixel.x + 15, pixel.y + 10, 0, str, COLOR_WHITE, FONT_SMALL_PLAIN);
}

void ANK_REGISTER_APPLICATION_MODULE(register_tile_pos_debug) {
    g_debug.add_tile_render_handler("tile_pos", draw_tile_pos_tile);
    g_debug.add_tile_render_handler("tile_toph", draw_tile_toph_tile);
}
