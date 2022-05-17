#ifndef GRAPHICS_IMAGE_H
#define GRAPHICS_IMAGE_H

#include "core/image.h"
#include "graphics/color.h"
#include "graphics/font.h"

namespace ImageDraw {
    void img_generic(int image_id, int x, int y, color_t color_mask = 0, float scale = 1.0f);
    void img_sprite(int image_id, int x, int y, color_t color_mask, float scale = 1.0f);
    void img_from_below(int image_id, int x, int y, color_t color_mask, float scale = 1.0f);
    void img_enemy(int image_id, int x, int y, float scale = 1.0f);
    void img_blended(int image_id, int x, int y, color_t color, float scale = 1.0f);
    void img_alpha_blended(int image_id, int x, int y, color_t color, float scale = 1.0f);
    void img_letter(font_t font, int letter_id, int x, int y, color_t color, float scale = 1.0f);
    void img_background(int image_id, float scale = 1.0f);
    void isometric_footprint(int image_id, int x, int y, color_t color_mask, float scale = 1.0f);
    void isometric_footprint_from_drawtile(int image_id, int x, int y, color_t color_mask, float scale = 1.0f);
    void isometric_top(int image_id, int x, int y, color_t color_mask, float scale = 1.0f);
    void isometric_top_from_drawtile(int image_id, int x, int y, color_t color_mask, float scale = 1.0f);
}

#endif // GRAPHICS_IMAGE_H
