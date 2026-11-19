#include "app/app.h"
#include "dev/debug.h"

#include "grid/desirability.h"
#include "grid/gardens.h"

static void draw_desirability_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = g_desirability.get(point.grid_offset());
    if (d == 0)
        return;

    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_LIGHT_RED);
}

static void draw_gardens_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    if (!map_garden_at(grid_offset))
        return;

    char str[64];
    const int x0 = pixel.x + 8;
    const int y = pixel.y;
    debug_text(ctx, str, x0, y + 5, 0, "", map_tiles_garden_get(point, false), COLOR_GREEN);
    debug_text(ctx, str, x0, y + 15, 0, "", map_tiles_garden_decay_get(point), COLOR_LIGHT_RED);
}

void ANK_REGISTER_APPLICATION_MODULE(register_desirability_debug) {
    g_debug.add_tile_render_handler("desirability", draw_desirability_tile);
    g_debug.add_tile_render_handler("gardens", draw_gardens_tile);
}
