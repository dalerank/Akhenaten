#include "app/app.h"
#include "dev/debug.h"

#include "grid/clay.h"
#include "grid/copper.h"
#include "grid/gems.h"
#include "grid/golden.h"
#include "grid/granite.h"
#include "grid/limestone.h"
#include "grid/sandstone.h"
#include "grid/stone.h"

static color resource_amount_color(int d) {
    if (d > 40000)
        return COLOR_LIGHT_GREEN;
    if (d > 20000)
        return COLOR_YELLOW;
    return COLOR_LIGHT_RED;
}

static void draw_resource_amount_tile(vec2i pixel, tile2i point, painter &ctx, int (*get)(int)) {
    const int d = get(point.grid_offset());
    if (d <= 0)
        return;

    char str[64];
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, resource_amount_color(d));
}

static void draw_sandstone_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_resource_amount_tile(pixel, point, ctx, map_get_sandstone);
}
static void draw_stone_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_resource_amount_tile(pixel, point, ctx, map_get_stone);
}
static void draw_limestone_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_resource_amount_tile(pixel, point, ctx, map_get_limestone);
}
static void draw_granite_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_resource_amount_tile(pixel, point, ctx, map_get_granite);
}
static void draw_golden_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_resource_amount_tile(pixel, point, ctx, map_get_golden);
}
static void draw_clay_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_resource_amount_tile(pixel, point, ctx, map_get_clay);
}
static void draw_copper_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_resource_amount_tile(pixel, point, ctx, map_get_copper);
}
static void draw_gems_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_resource_amount_tile(pixel, point, ctx, map_get_gems);
}

void ANK_REGISTER_APPLICATION_MODULE(register_resources_debug) {
    g_debug.add_tile_render_handler("sandstone", draw_sandstone_tile);
    g_debug.add_tile_render_handler("stone", draw_stone_tile);
    g_debug.add_tile_render_handler("limestone", draw_limestone_tile);
    g_debug.add_tile_render_handler("granite", draw_granite_tile);
    g_debug.add_tile_render_handler("golden", draw_golden_tile);
    g_debug.add_tile_render_handler("clay", draw_clay_tile);
    g_debug.add_tile_render_handler("copper", draw_copper_tile);
    g_debug.add_tile_render_handler("gems", draw_gems_tile);
}
