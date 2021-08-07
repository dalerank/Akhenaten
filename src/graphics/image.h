#ifndef GRAPHICS_IMAGE_H
#define GRAPHICS_IMAGE_H

#include "core/image.h"
#include "graphics/color.h"
#include "graphics/font.h"

namespace ImageDraw {
    void img_generic(int image_id, int x, int y, color_t color_mask = 0);
    void img_sprite(int image_id, int x, int y, color_t color_mask);
    void img_from_below(int image_id, int x, int y, color_t color_mask);
    void img_enemy(int image_id, int x, int y);
    void img_blended(int image_id, int x, int y, color_t color);
    void img_alpha_blended(int image_id, int x, int y, color_t color);
    void img_letter(font_t font, int letter_id, int x, int y, color_t color);
    void img_background(int image_id);
    void isometric_footprint(int image_id, int x, int y, color_t color_mask);
    void isometric_footprint_from_drawtile(int image_id, int x, int y, color_t color_mask);
    void isometric_top(int image_id, int x, int y, color_t color_mask);
    void isometric_top_from_drawtile(int image_id, int x, int y, color_t color_mask);
}

#endif // GRAPHICS_IMAGE_H
