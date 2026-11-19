#include "app/app.h"
#include "dev/debug.h"

#include "building/building.h"
#include "building/monuments.h"
#include "grid/building.h"

static void draw_monuments_tile(vec2i pixel, tile2i point, painter &ctx) {
    building *b = building_get(map_building_at(point.grid_offset()));
    auto monument = b ? b->dcast_monument() : nullptr;
    if (!monument)
        return;

    const int d = map_monuments_get_progress(point);
    char str[64];
    b->is_valid()
        ? snprintf(str, 30, "%d[%d]", monument->runtime_data().phase, d)
        : snprintf(str, 30, "%d", d);
    debug_text_a(ctx, str, pixel.x + 15, pixel.y + 10, 0, str, COLOR_RED, FONT_SMALL_PLAIN);
}

void ANK_REGISTER_APPLICATION_MODULE(register_monuments_debug) {
    g_debug.add_tile_render_handler("monuments", draw_monuments_tile);
}
