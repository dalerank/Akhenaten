#include "core/app.h"
#include "dev/debug.h"

#include "city/city_floods.h"
#include "core/string.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "grid/floodplain.h"
#include "grid/terrain.h"

#include <cmath>

static void draw_flood_order_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_get_floodplain_row(point.grid_offset());
    if (d > -1) {
        char str[64];
        debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", d, COLOR_LIGHT_RED);
    }
}

static void draw_flood_order_ui(painter &ctx) {
    const int x = 10;
    int y = 30;
    char str[300];

    float _c_curr = g_floods.current_cycle();
    float _c_start = g_floods.start_cycle();
    float _c_end = g_floods.end_cycle();

    int _c_period_last = g_floods.period_length(false);
    int _c_period_next = g_floods.period_length(true);

    float rc_curr = fmod(_c_curr, CYCLES_IN_A_YEAR);
    float rc_start = fmod(_c_start, CYCLES_IN_A_YEAR);
    float rc_end = fmod(_c_end, CYCLES_IN_A_YEAR);

    auto dot = string_from_ascii(",");
    for (int i = 0; i < 392; ++i) {
        text_draw(dot, x + i - 1, y + 15, FONT_SMALL_PLAIN, 0);
    }

    for (int i = 0; i < 392; ++i) {
        int abs_i = i;
        text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_WHITE);

        if ((i > rc_start - 28 && i < rc_end + 28)
            || (i > rc_start - 28 - CYCLES_IN_A_YEAR && i < rc_end + 28 - CYCLES_IN_A_YEAR)
            || (i > rc_start - 28 + CYCLES_IN_A_YEAR && i < rc_end + 28 + CYCLES_IN_A_YEAR)) {
            text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_FONT_ORANGE_LIGHT);
        }

        if ((i > rc_start && i < rc_end) || (i > rc_start - CYCLES_IN_A_YEAR && i < rc_end - CYCLES_IN_A_YEAR)
            || (i > rc_start + CYCLES_IN_A_YEAR && i < rc_end + CYCLES_IN_A_YEAR))
            text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_RED);

        if (g_floods.debug_period() > 0) {
            if (abs_i > _c_start + _c_period_next && abs_i < _c_end - _c_period_next)
                text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_GREEN);
        } else {
            if (abs_i > _c_start + _c_period_last && abs_i < _c_end - _c_period_last)
                text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_GREEN);
        }
    }

    text_draw(dot, x + rc_curr, y + 15, FONT_SMALL_OUTLINED, COLOR_FONT_YELLOW);
    text_draw(string_from_ascii("\'"), x + rc_curr, y + 25, FONT_SMALL_OUTLINED, COLOR_FONT_YELLOW);
    debug_text_float(x + rc_curr + 5, y + 25, 0, "", _c_curr);
    debug_text(ctx, str, x + rc_curr + 54, y + 25, 5, ":", g_floods.state);

    debug_text(ctx, str, x, y + 35, 60, "debug:", g_floods.debug_period());
    debug_text(ctx, str, x, y + 45, 60, "ftick:", g_floods.fticks);

    y += 50;

    int cl = 60;
    debug_text(ctx, str, x, y + 15, cl + 15, "CURRENT:", _c_curr);
    debug_text(ctx, str, x + 105, y + 15, 10, "/", g_floods.current_subcycle());
    debug_text(ctx, str, x, y + 25, cl, "t-49:", _c_start - 49);
    debug_text(ctx, str, x, y + 35, cl, "t-28:", _c_start - 28);
    debug_text(ctx, str, x, y + 45, cl, "  START", _c_start);

    if (g_floods.debug_period() > 0) {
        debug_text(ctx, str, x, y + 55, cl, "rest:", _c_start + _c_period_next);
        debug_text(ctx, str, x, y + 65, cl, "retract:", _c_end - _c_period_next);
    } else {
        debug_text(ctx, str, x, y + 55, cl, "rest:", _c_start + _c_period_last);
        debug_text(ctx, str, x, y + 65, cl, "retract:", _c_end - _c_period_last);
    }

    debug_text(ctx, str, x, y + 75, cl, "    END", _c_end);
    debug_text(ctx, str, x, y + 85, cl, "t+23:", _c_end + 23);
    debug_text(ctx, str, x, y + 95, cl, "t+28:", _c_end + 28);

    cl = 100;
    y += 10;
    debug_text(ctx, str, x, y + 105, cl, "season_initial:", g_floods.season_initial);
    debug_text(ctx, str, x, y + 115, cl, "duration_initial:", g_floods.duration_initial);
    debug_text(ctx, str, x, y + 125, cl, "quality_initial:", g_floods.quality_initial);
    debug_text(ctx, str, x, y + 135, cl, "season:", g_floods.season);
    debug_text(ctx, str, x, y + 145, cl, "duration:", g_floods.duration);
    debug_text(ctx, str, x, y + 155, cl, "quality:", g_floods.quality_current);
    debug_text(ctx, str, x, y + 165, cl, "(unk00):", g_floods.unk00);
    debug_text(ctx, str, x, y + 175, cl, "quality_next:", g_floods.quality_next);
    debug_text(ctx, str, x, y + 185, cl, "quality_last:", g_floods.quality_last);

    cl = 150;
    debug_text(ctx, str, x, y + 205, cl, "progress:", g_floods.flood_progress);
    debug_text(ctx, str, x, y + 215, cl, "season_month:", g_floods.season_month);
    debug_text(ctx, str, x, y + 225, cl, "state:", g_floods.state);
    debug_text(ctx, str, x, y + 235, cl, "width:", g_floods.floodplain_width);
    debug_text(ctx, str, x, y + 245, cl, "hasplains:", g_floods.has_floodplains);
    debug_text(ctx, str, x, y + 255, cl, "force_inundation:", g_floods.force_inundation);
    debug_text(ctx, str, x, y + 265, cl, "flood_progress_tick:", g_floods.flood_progress_tick);
    debug_text(ctx, str, x, y + 275, cl, "target_progress:", g_floods.flood_progress_target);
}

static void draw_floodplain_shore_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_get_floodplain_edge(point);
    if (!d)
        return;

    text_draw(bstring32(d).c_str(), pixel.x + 15, pixel.y + 15, FONT_SMALL_OUTLINED, COLOR_WHITE);
    ctx.img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, pixel, 0x80000000);
}

static void draw_river_shore_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int d = map_terrain_is(point.grid_offset(), TERRAIN_SHORE);
    if (!d)
        return;

    text_draw(bstring32(d).c_str(), pixel.x + 15, pixel.y + 15, FONT_SMALL_PLAIN, COLOR_WHITE);
    ctx.img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, pixel, 0x80000000);
}

void ANK_REGISTER_APPLICATION_MODULE(register_flood_order_debug) {
    g_debug.add_tile_render_handler("flood_order", draw_flood_order_tile);
    g_debug.add_tile_render_handler("floodplain_shore", draw_floodplain_shore_tile);
    g_debug.add_tile_render_handler("river_shore", draw_river_shore_tile);
    g_debug.add_render_handler("flood_order", draw_flood_order_ui);
}
