#ifndef GRAPHICS_IMAGE_H
#define GRAPHICS_IMAGE_H

#include "core/image.h"
#include "graphics/color.h"
#include "graphics/font.h"
#include "core/image_group.h"

namespace ImageDraw {
    void img_generic(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 1.0f);
    void img_sprite(int image_id, int x, int y, color_t color_mask, float scale = 0);
    void img_ornament(int image_id, int base_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 0);
    void img_from_below(int image_id, int x, int y, color_t color_mask, float scale);
    void img_enemy(int image_id, int x, int y, color_t color_mask, float scale = 0);
    void img_blended(int image_id, int x, int y, color_t color_mask, float scale);
    void img_alpha_blended(int image_id, int x, int y, color_t color_mask, float scale);
    void img_letter(font_t font, int letter_id, int x, int y, color_t color_mask, float scale = 1.0f);
    void img_background(int image_id, float scale = 1.0f);
    void isometric(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE, float scale = 0);
    void isometric_from_drawtile(int image_id, int x, int y, color_t color_mask = COLOR_MASK_NONE);
}

#endif // GRAPHICS_IMAGE_H
