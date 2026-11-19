#include "app/app.h"
#include "dev/debug.h"

#include "building/building.h"
#include "graphics/text.h"
#include "grid/building.h"

static void draw_damage_tile(vec2i pixel, tile2i point, painter &ctx) {
    building *b = building_get(map_building_at(point.grid_offset()));
    if (!b || !b->id)
        return;

    char str[64];
    snprintf(str, 30, "f:%d/d:%d", b->fire_risk, b->collapse_risk);
    text_draw(ctx, (uint8_t *)str, pixel.x + 15, pixel.y + 10, FONT_SMALL_PLAIN, COLOR_LIGHT_BLUE, 0.5f);
}

static void draw_damage_grid_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_get_building_damage(point.grid_offset());
    if (d <= 0)
        return;

    color damage_color = (d < 5) ? COLOR_LIGHT_GREEN : (d < 10) ? COLOR_YELLOW : COLOR_LIGHT_RED;
    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, damage_color);
}

void ANK_REGISTER_APPLICATION_MODULE(register_damage_debug) {
    g_debug.add_tile_render_handler("damage", draw_damage_tile);
    g_debug.add_tile_render_handler("damage_grid", draw_damage_grid_tile);
}
