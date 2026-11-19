#include "app/app.h"
#include "dev/debug.h"
#include "graphics/text.h"
#include "grid/building.h"
#include "grid/malaria_risk.h"
#include "building/building.h"

static void draw_malaria_risk_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    const int x = pixel.x + 15;
    const int y = pixel.y;
    char str[64];

    const int risk = g_malaria_risk.get(grid_offset);
    if (risk > 0) {
        const color risk_color = (risk < 30) ? COLOR_LIGHT_GREEN : (risk < 60) ? COLOR_YELLOW : COLOR_LIGHT_RED;
        debug_text(ctx, str, x, y + 10, 0, "", risk, risk_color);
    }

    const int b_id = map_building_at(grid_offset);
    building *b = building_get(b_id);
    if (b_id && b && b->malaria_risk > 0) {
        snprintf(str, sizeof(str), "b:%d", b->malaria_risk);
        text_draw(ctx, (uint8_t *)str, x, y + 20, FONT_SMALL_PLAIN, COLOR_LIGHT_BLUE, 0.5f);
    }
}

void ANK_REGISTER_APPLICATION_MODULE(register_malaria_risk_debug) {
    g_debug.add_tile_render_handler("malaria_risk", draw_malaria_risk_tile);
}
