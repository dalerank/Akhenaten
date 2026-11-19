#include "app/app.h"
#include "dev/debug.h"

#include "grid/terrain.h"
#include "grid/vegetation.h"

static void draw_vegetation_growth_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    if (!map_terrain_is(grid_offset, TERRAIN_MARSHLAND | TERRAIN_TREE))
        return;

    const int d = map_get_vegetation_growth(grid_offset);
    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, (d < 200) ? COLOR_LIGHT_RED : COLOR_LIGHT_BLUE);
}

static void draw_marshland_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_terrain_is(point.grid_offset(), TERRAIN_MARSHLAND);
    if (d == 0)
        return;

    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_LIGHT_RED);
}

void ANK_REGISTER_APPLICATION_MODULE(register_vegetation_growth_debug) {
    g_debug.add_tile_render_handler("vegetation_growth", draw_vegetation_growth_tile);
    g_debug.add_tile_render_handler("marshland", draw_marshland_tile);
}
