#ifndef GRAPHICS_GRAPHICS_H
#define GRAPHICS_GRAPHICS_H

#include "graphics/color.h"

#define FOOTPRINT_WIDTH 58
#define FOOTPRINT_HEIGHT 30
#define FOOTPRINT_HALF_HEIGHT 15

void graphics_in_dialog(void);
void graphics_in_dialog_with_size(int width, int height);
void graphics_reset_dialog(void);

void graphics_set_clip_rectangle(int x, int y, int width, int height);
void graphics_reset_clip_rectangle(void);

void graphics_clear_screen(void);

void graphics_draw_line(int x_start, int x_end, int y_start, int y_end, color_t color);
void graphics_draw_vertical_line(int x, int y1, int y2, color_t color);
void graphics_draw_horizontal_line(int x1, int x2, int y, color_t color);
void graphics_draw_rect(int x, int y, int width, int height, color_t color);
void graphics_draw_inset_rect(int x, int y, int width, int height);

void graphics_fill_rect(int x, int y, int width, int height, color_t color);
void graphics_shade_rect(int x, int y, int width, int height, int darkness);

int graphics_save_to_texture(int image_id, int x, int y, int width, int height);
void graphics_draw_from_texture(int image_id, int x, int y, int width, int height);

#endif // GRAPHICS_GRAPHICS_H
