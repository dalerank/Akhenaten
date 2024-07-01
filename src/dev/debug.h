#pragma once

#include "graphics/color.h"
#include "core/string.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "graphics/font.h"
#include "input/hotkey.h"

#include <functional>
#include <iosfwd>

extern int debug_range_1;
extern int debug_range_2;
extern int debug_range_3;
extern int debug_range_4;

enum e_debug_show_opt {
    e_debug_show_pages = 0,
    e_debug_show_game_time,
    e_debug_show_build_planner,
    e_debug_show_religion,
    e_debug_show_tutorial,
    e_debug_show_floods,
    e_debug_show_camera,
    e_debug_show_tile_cache,
    e_debug_show_migration,
    e_debug_show_sentiment,
    e_debug_show_sound_channels,
    e_debug_show_console,
    e_debug_show_screenshot,
    e_debug_show_full_screenshot,

    e_debug_opt_size,
};

enum e_debug_render {
    e_debug_render_none = 0,
    e_debug_render_building = 1,
    e_debug_render_tilesize = 2,
    e_debug_render_roads = 3,
    e_debug_render_routing_dist = 4,
    e_debug_render_routing_grid = 5,
    e_debug_render_moisture = 6,
    e_debug_render_grass_level = 7,
    e_debug_render_grass_soil_depletion = 8,
    e_debug_render_grass_flood_order = 9,
    e_debug_render_grass_flood_flags = 10,
    e_debug_render_labor = 11,
    e_debug_render_sprite_frames = 12,
    e_debug_render_terrain_bits = 13,
    e_debug_render_image = 14,
    e_debug_render_image_alt = 15,
    e_debug_render_marshland = 16,
    e_debug_render_terrain_type = 17,
    e_debug_render_soil = 18,
    e_debug_render_unk_19,
    e_debug_render_tile_pos = 20,
    e_debug_render_floodplain_shore = 21,
    e_debug_render_tile_toph = 22,
    e_debug_render_monuments = 23,
    e_debug_render_figures = 24,
    e_debug_render_height = 25,
    e_debug_render_marshland_depl = 26,
    e_debug_render_damage_fire = 27,
    e_debug_render_desirability = 28,

    e_debug_render_size
};

extern bool g_debug_show_opts[e_debug_opt_size];
extern int g_debug_tile;
extern int g_debug_render;

void handle_debug_hotkeys(const hotkeys* h);

void debug_text(painter &ctx, uint8_t* str, int x, int y, int indent, const char* text, int value, color color = COLOR_WHITE, e_font font = FONT_SMALL_OUTLINED);
void debug_text_a(painter &ctx, uint8_t* str, int x, int y, int indent, const char* text, color color = COLOR_WHITE, e_font font = FONT_SMALL_OUTLINED);
void debug_text_float(uint8_t* str, int x, int y, int indent, const char* text, double value, color color = COLOR_WHITE);
void debug_text_dual_left(uint8_t* str, int x, int y, int indent, int indent2, const char* text, int value1, int value2, color color = COLOR_WHITE);

void debug_draw_line_with_contour(int x_start, int x_end, int y_start, int y_end, color col);
void debug_draw_rect_with_contour(int x, int y, int w, int h, color col);

void debug_draw_crosshair(int x, int y);
void debug_draw_sprite_box(int x, int y, const image_t* img, float scale, color color_mask);
void debug_draw_tile_box(int x, int y, color rect, color bb, int tile_size_x = 1, int tile_size_y = 1);
void debug_draw_tile_top_bb(int x, int y, int height, color color, int size = 1);

void draw_debug_tile(vec2i pixel, tile2i point, painter &ctx);
void draw_debug_figures(vec2i pixel, tile2i point, painter &ctx);

void draw_debug_ui(int x, int y);

inline bool draw_debug(e_debug_render opt) {
    return g_debug_show_opts[opt];
}

struct console_command {
    console_command(pcstr name, std::function<void(std::istream &is, std::ostream &os)> f);
};

struct console_var_int {
    int value;
    console_var_int(pcstr name, int init);
    int operator()() const { return value; }
};

struct console_var_bool {
    bool value;
    console_var_bool(pcstr name, bool init);
    bool operator()() const { return value; }
};

#define declare_console_command(a, ...) namespace console { bool cmd_##a; }; console_command a(#a, __VA_ARGS__);
#define declare_console_command_p(a, f) namespace console { bool cmd_##a; }; void f(std::istream &, std::ostream &); console_command a(#a, f);
#define declare_console_var_int(a, v) namespace console { bool var_##a; }; console_var_int a(#a, v);
#define declare_console_var_bool(a, v) namespace console { bool var_##a; }; console_var_bool a(#a, v);

