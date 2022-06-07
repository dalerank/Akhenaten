#ifndef GRAPHICS_BOILERPLATE_H
#define GRAPHICS_BOILERPLATE_H

#include "image.h"
#include "graphics/color.h"
#include "graphics/font.h"
#include "image_groups.h"

void graphics_set_to_dialog(void);
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

namespace ImageDraw {
    void img_generic(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 1.0f);
    void img_sprite(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 1.0f);
    void img_ornament(int image_id, int base_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 1.0f);
    void img_from_below(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 1.0f);
    void img_enemy(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 1.0f);
    void img_blended(int image_id, int x, int y, color_t color_mask, float scale = 1.0f);
    void img_alpha_blended(int image_id, int x, int y, color_t color_mask, float scale = 1.0f);
    void img_letter(font_t font, int letter_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 1.0f);
    void img_background(int image_id, float scale = 1.0f);
    void isometric(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 1.0f);
    void isometric_from_drawtile(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE);
}

#endif // GRAPHICS_BOILERPLATE_H
