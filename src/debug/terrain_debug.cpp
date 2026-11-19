#include "app/app.h"
#include "dev/debug.h"

#include "core/string.h"
#include "graphics/text.h"
#include "grid/building.h"
#include "grid/floodplain.h"
#include "grid/terrain.h"

static void draw_terrain_bits_tile(vec2i pixel, tile2i point, painter &ctx) {
    text_draw(ctx, bstring32().printf("%x", map_terrain_get(point.grid_offset())), pixel.x + 15, pixel.y + 10, FONT_SMALL_PLAIN, COLOR_LIGHT_BLUE, 0.5f);
}

static void draw_terrain_type_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_terrain_get(point.grid_offset());
    text_draw(ctx, bstring32().printf("%x", d), pixel.x + 15, pixel.y + 10, FONT_SMALL_PLAIN, COLOR_LIGHT_BLUE, 0.5f);
}

static void draw_height_tile(vec2i pixel, tile2i point, painter &ctx) {
    char str[64];
    snprintf(str, 30, "%d", map_building_height_at(point.grid_offset()));
    debug_text_a(ctx, str, pixel.x + 15, pixel.y + 10, 0, str, COLOR_RED, FONT_SMALL_PLAIN);
}

static void draw_soil_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_get_UNK04(point.grid_offset());
    if (d == 0)
        return;

    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_LIGHT_RED);
}

static void draw_unk_19_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_get_UNK03(point.grid_offset());
    if (d == 0)
        return;

    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_LIGHT_RED);
}

void ANK_REGISTER_APPLICATION_MODULE(register_terrain_debug) {
    g_debug.add_tile_render_handler("terrain_bits", draw_terrain_bits_tile);
    g_debug.add_tile_render_handler("terrain_type", draw_terrain_type_tile);
    g_debug.add_tile_render_handler("height", draw_height_tile);
    g_debug.add_tile_render_handler("soil", draw_soil_tile);
    g_debug.add_tile_render_handler("unk_19", draw_unk_19_tile);
}
