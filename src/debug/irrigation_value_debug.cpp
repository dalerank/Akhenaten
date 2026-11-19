#include "app/app.h"
#include "dev/debug.h"

#include "grid/canals.h"
#include "grid/irrigation_value.h"

static void draw_canals_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_canal_at(point.grid_offset());
    if (!d)
        return;

    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_GREEN);
}

static void draw_irrigation_value_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int irrigation = g_irrigation_value.get(point.grid_offset());
    if (irrigation == 0)
        return;

    color irrigation_color = (irrigation >= 10) ? COLOR_LIGHT_GREEN : (irrigation >= 5) ? COLOR_YELLOW : COLOR_LIGHT_RED;
    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", irrigation, irrigation_color);
}

void ANK_REGISTER_APPLICATION_MODULE(register_irrigation_value_debug) {
    g_debug.add_tile_render_handler("canals", draw_canals_tile);
    g_debug.add_tile_render_handler("irrigation_value", draw_irrigation_value_tile);
}
