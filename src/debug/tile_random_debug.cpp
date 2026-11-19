#include "app/app.h"
#include "dev/debug.h"

#include "grid/random.h"

static void draw_tile_random_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_random_get(point);
    if (!d)
        return;

    char str[64];
    snprintf(str, 30, "%d", d);
    debug_text_a(ctx, str, pixel.x + 15, pixel.y + 10, 0, str, COLOR_LIGHT_BLUE, FONT_SMALL_PLAIN);
}

void ANK_REGISTER_APPLICATION_MODULE(register_tile_random_debug) {
    g_debug.add_tile_render_handler("tile_random", draw_tile_random_tile);
}
