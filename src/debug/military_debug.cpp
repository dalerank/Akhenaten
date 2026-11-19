#include "app/app.h"
#include "dev/debug.h"

#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "grid/enemy_strength.h"
#include "grid/soldier_strength.h"
#include "scenario/scenario_invasion.h"

static void draw_invasion_point_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_invasion_point(point);
    if (!d)
        return;

    ctx.img_generic(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, pixel, 0x80000000);
    text_draw((d == 1) ? "L" : "S", pixel.x + 15, pixel.y + 15, FONT_SMALL_PLAIN, COLOR_RED);
}

static void draw_soldier_strength_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_soldier_strength_get(point.grid_offset());
    if (!d)
        return;

    char str[64];
    ctx.img_generic(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, pixel, 0x80000000);
    snprintf(str, 30, "%d", d);
    text_draw(str, pixel.x + 15, pixel.y + 15, FONT_SMALL_PLAIN, COLOR_RED);
}

static void draw_enemy_strength_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_enemy_strength_get(point.grid_offset());
    if (!d)
        return;

    char str[64];
    ctx.img_generic(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, pixel, 0x80000000);
    snprintf(str, 30, "%d", d);
    text_draw(str, pixel.x + 15, pixel.y + 15, FONT_SMALL_PLAIN, COLOR_LIGHT_RED);
}

void ANK_REGISTER_APPLICATION_MODULE(register_military_debug) {
    g_debug.add_tile_render_handler("invasion_point", draw_invasion_point_tile);
    g_debug.add_tile_render_handler("soldier_strength", draw_soldier_strength_tile);
    g_debug.add_tile_render_handler("enemy_strength", draw_enemy_strength_tile);
}
