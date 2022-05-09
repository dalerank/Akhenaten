#ifndef OZYMANDIAS_DEBUG_H
#define OZYMANDIAS_DEBUG_H

#include <input/hotkey.h>
#include <graphics/color.h>
#include <city/view/view.h>

extern int debug_range_1;
extern int debug_range_2;
extern int debug_range_3;
extern int debug_range_4;

void handle_debug_hotkeys(const hotkeys *h);

void draw_debug_line(uint8_t* str, int x, int y, int indent, const char *text, int value, color_t color = COLOR_WHITE);
void draw_debug_line_double_left(uint8_t* str, int x, int y, int indent, int indent2, const char *text, int value1, int value2, color_t color = COLOR_WHITE);

void draw_debug_tile(pixel_coordinate pixel, map_point point);
void draw_debug_figures(pixel_coordinate pixel, map_point point);

void draw_debug_ui(int x, int y);

#endif //OZYMANDIAS_DEBUG_H
