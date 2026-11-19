#include "app/app.h"
#include "dev/debug.h"

#include "building/building.h"
#include "building/building_house.h"
#include "grid/building.h"

static void draw_overall_entertainment_tile(vec2i pixel, tile2i point, painter &ctx) {
    building *b = building_get(map_building_at(point.grid_offset()));
    auto house = b ? b->dcast_house() : nullptr;
    if (!house)
        return;

    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", house->runtime_data().entertainment, COLOR_LIGHT_BLUE);
}

void ANK_REGISTER_APPLICATION_MODULE(register_entertainment_debug) {
    g_debug.add_tile_render_handler("overall_entertainment", draw_overall_entertainment_tile);
}
