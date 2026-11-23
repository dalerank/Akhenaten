#include "app/app.h"
#include "city/city.h"
#include "dev/debug.h"

#include "city/city_floods.h"
#include "core/string.h"
#include "core/log.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "grid/floodplain.h"
#include "grid/terrain.h"

#include <algorithm>
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

    float _c_curr = floods().current_cycle();
    float _c_start = floods().start_cycle();
    float _c_end = floods().end_cycle();

    int _c_period_last = floods().period_length(false);
    int _c_period_next = floods().period_length(true);

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

        if (floods().debug_period() > 0) {
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
    debug_text(ctx, str, x + rc_curr + 54, y + 25, 5, ":", floods().state);

    debug_text(ctx, str, x, y + 35, 60, "debug:", floods().debug_period());
    debug_text(ctx, str, x, y + 45, 60, "ftick:", floods().fticks);

    y += 50;

    int cl = 60;
    debug_text(ctx, str, x, y + 15, cl + 15, "CURRENT:", _c_curr);
    debug_text(ctx, str, x + 105, y + 15, 10, "/", floods().current_subcycle());
    debug_text(ctx, str, x, y + 25, cl, "t-49:", _c_start - 49);
    debug_text(ctx, str, x, y + 35, cl, "t-28:", _c_start - 28);
    debug_text(ctx, str, x, y + 45, cl, "  START", _c_start);

    if (floods().debug_period() > 0) {
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
    debug_text(ctx, str, x, y + 105, cl, "season_initial:", floods().season_initial);
    debug_text(ctx, str, x, y + 115, cl, "duration_initial:", floods().duration_initial);
    debug_text(ctx, str, x, y + 125, cl, "quality_initial:", floods().quality_initial);
    debug_text(ctx, str, x, y + 135, cl, "season:", floods().season);
    debug_text(ctx, str, x, y + 145, cl, "duration:", floods().duration);
    debug_text(ctx, str, x, y + 155, cl, "quality:", floods().quality_current);
    debug_text(ctx, str, x, y + 165, cl, "(unk00):", floods().unk00);
    debug_text(ctx, str, x, y + 175, cl, "quality_next:", floods().quality_next);
    debug_text(ctx, str, x, y + 185, cl, "quality_last:", floods().quality_last);

    cl = 150;
    debug_text(ctx, str, x, y + 205, cl, "progress:", floods().flood_progress);
    debug_text(ctx, str, x, y + 215, cl, "season_month:", floods().season_month);
    debug_text(ctx, str, x, y + 225, cl, "state:", floods().state);
    debug_text(ctx, str, x, y + 235, cl, "width:", floods().floodplain_width);
    debug_text(ctx, str, x, y + 245, cl, "hasplains:", floods().has_floodplains);
    debug_text(ctx, str, x, y + 255, cl, "force_inundation:", floods().force_inundation);
    debug_text(ctx, str, x, y + 265, cl, "flood_progress_tick:", floods().flood_progress_tick);
    debug_text(ctx, str, x, y + 275, cl, "target_progress:", floods().flood_progress_target);
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

// Returns the cycle index for a calendar token (case-insensitive: JAN..DEC, MID_JAN..MID_DEC).
// Falls back to numeric parsing if the token isn't a name. Returns -1 for empty input.
static int parse_calendar_token(const bstring64& arg) {
    if (arg.empty()) {
        return -1;
    }

    bstring64 up = arg;
    up.toupper();

    static constexpr struct {
        const char* name;
        int cycle;
    } table[] = {
      {"JAN", 0},
      {"MID_JAN", 16},
      {"FEB", 32},
      {"MID_FEB", 48},
      {"MAR", 64},
      {"MID_MAR", 80},
      {"APR", 96},
      {"MID_APR", 112},
      {"MAY", 128},
      {"MID_MAY", 144},
      {"JUN", 160},
      {"MID_JUN", 176},
      {"JUL", 192},
      {"MID_JUL", 208},
      {"AUG", 224},
      {"MID_AUG", 240},
      {"SEP", 256},
      {"MID_SEP", 272},
      {"OCT", 288},
      {"MID_OCT", 304},
      {"NOV", 320},
      {"MID_NOV", 336},
      {"DEC", 352},
      {"MID_DEC", 368},
    };

    for (const auto& entry : table) {
        if (up == entry.name) {
            return entry.cycle;
        }
    }

    return atoi(arg.c_str());
}

declare_console_command_p(startflood) {
    bstring64 arg;
    args.next(arg);

    if (arg == "+") {
        floods().force_inundation++;
    } else if (arg == "-") {
        floods().force_inundation--;
    } else {
        floods().force_inundation = atoi(arg.empty() ? (pcstr) "0" : arg.c_str());
    }
}

declare_console_command_p(set_flood_start) {
    bstring64 arg;
    args.next(arg);
    const int target_cycle = parse_calendar_token(arg);
    if (target_cycle < 0) {
        return;
    }
    // start_cycle = floor(season * 1.05 + 14.5)  =>  season = ceil((target - 14.5) / 1.05)
    const int season = std::clamp((int)std::ceil((target_cycle - 14.5f) / 1.05f), 0, 255);
    floods().season_initial = season;
    floods().season = season;
}

declare_console_command_p(set_flood_end) {
    bstring64 arg;
    args.next(arg);
    const int target_cycle = parse_calendar_token(arg);
    if (target_cycle < 0) {
        return;
    }
    const int duration = std::max(0, target_cycle - floods().start_cycle() - floods().floodplain_width * 2);
    floods().duration_initial = duration;
    floods().duration = duration;
}

declare_console_command_p(set_flood_reset) {
    floods().season_initial = floods().season_default;
    floods().season = floods().season_default;
    floods().duration_initial = floods().duration_default;
    floods().duration = floods().duration_default;
}

declare_console_command_p(flood_dump) {
    const int start = floods().start_cycle();
    const int end = floods().end_cycle();
    const int width = floods().floodplain_width;
    const float period_last = floods().period_length(false);
    logs::info("[flood_dump] season=%d (init=%d default=%d)  duration=%d (init=%d default=%d)", floods().season,
      floods().season_initial, floods().season_default, floods().duration, floods().duration_initial,
      floods().duration_default);
    logs::info("[flood_dump] floodplain_width=%d  start_cycle=%d  end_cycle=%d  total_flood=%d cycles", width, start,
      end, end - start);
    logs::info("[flood_dump] quality_current=%d  quality_last=%d  quality_next=%d  flooding_period=%.1f",
      floods().quality_current, floods().quality_last, floods().quality_next, period_last);
    logs::info("[flood_dump] state=%d  current_cycle=%d  flood_progress=%d/%d", (int)floods().state,
      floods().current_cycle(), floods().flood_progress, floods().flood_progress_target);
}
