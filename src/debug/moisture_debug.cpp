#include "app/app.h"
#include "dev/debug.h"

#include "grid/moisture.h"

static void draw_moisture_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_moisture_get(point.grid_offset());
    char str[64];
    if (d & MOISTURE_GRASS)
        debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_WHITE);
    else if (d & MOISTURE_TRANSITION)
        debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_LIGHT_BLUE);
    else if (d & MOISTURE_SHORE_TALLGRASS)
        debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_GREEN);
}

static void draw_grass_level_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_grasslevel_get(point.grid_offset());
    if (!d)
        return;

    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_GREEN);
}

void ANK_REGISTER_APPLICATION_MODULE(register_moisture_debug) {
    g_debug.add_tile_render_handler("moisture", draw_moisture_tile);
    g_debug.add_tile_render_handler("grass_level", draw_grass_level_tile);
}
