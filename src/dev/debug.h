#ifndef OZYMANDIAS_DEBUG_H
#define OZYMANDIAS_DEBUG_H

#include "graphics/color.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "input/hotkey.h"

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

    e_debug_opt_size,
};

extern bool g_debug_show_opts[e_debug_opt_size];

void handle_debug_hotkeys(const hotkeys* h);

void debug_font_test();

void debug_text(uint8_t* str, int x, int y, int indent, const char* text, int value, color color = COLOR_WHITE);
void debug_text_a(uint8_t* str, int x, int y, int indent, const char* text, color color = COLOR_WHITE);
void debug_text_float(uint8_t* str,
                      int x,
                      int y,
                      int indent,
                      const char* text,
                      double value,
                      color color = COLOR_WHITE);
void debug_text_dual_left(uint8_t* str,
                          int x,
                          int y,
                          int indent,
                          int indent2,
                          const char* text,
                          int value1,
                          int value2,
                          color color = COLOR_WHITE);

void debug_draw_line_with_contour(int x_start, int x_end, int y_start, int y_end, color col);
void debug_draw_rect_with_contour(int x, int y, int w, int h, color col);

void debug_draw_crosshair(int x, int y);
void debug_draw_sprite_box(int x, int y, const image_t* img, float scale, color color_mask);
void debug_draw_tile_box(int x, int y, color rect, color bb, int tile_size_x = 1, int tile_size_y = 1);
void debug_draw_tile_top_bb(int x, int y, int height, color color, int size = 1);

void draw_debug_tile(vec2i pixel, map_point point);
void draw_debug_figures(vec2i pixel, map_point point);

void draw_debug_ui(int x, int y);

#endif // OZYMANDIAS_DEBUG_H
