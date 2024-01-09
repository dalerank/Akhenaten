#pragma once

#include "graphics/color.h"
#include "graphics/font.h"
#include "image.h"
#include "image_groups.h"
#include "core/vec2i.h"

struct painter;

void graphics_set_to_dialog(void);
void graphics_in_dialog_with_size(int width, int height);
void graphics_reset_dialog(void);

void graphics_set_clip_rectangle(int x, int y, int width, int height);
void graphics_reset_clip_rectangle(void);

void graphics_draw_line(int x_start, int x_end, int y_start, int y_end, color color);
void graphics_draw_vertical_line(int x, int y1, int y2, color color);
void graphics_draw_horizontal_line(int x1, int x2, int y, color color);
void graphics_draw_rect(int x, int y, int width, int height, color color);
void graphics_draw_inset_rect(int x, int y, int width, int height);

void graphics_fill_rect(int x, int y, int width, int height, color color);
void graphics_shade_rect(int x, int y, int width, int height, int darkness);

int graphics_save_to_texture(int image_id, int x, int y, int width, int height);
void graphics_draw_from_texture(int image_id, int x, int y, int width, int height);

namespace ImageDraw {
void img_generic(painter &ctx, int image_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
void img_generic(painter &ctx, int image_id, vec2i p, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
void img_sprite(painter &ctx, int image_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f, bool alpha = false);
inline void img_sprite(painter &ctx, int image_id, vec2i p, color color_mask = COLOR_MASK_NONE, float scale = 1.0f, bool alpha = false) { img_sprite(ctx, image_id, p.x, p.y, color_mask, scale, alpha); }

void img_ornament(painter &ctx, int image_id, int base_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
void img_from_below(painter &ctx, int image_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
void img_letter(painter &ctx, font_t font, int letter_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
void img_background(painter &ctx, int image_id, float scale = 1.0f);
void isometric(painter &ctx, int image_id, vec2i pos, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
const image_t* isometric_from_drawtile(painter &ctx, int image_id, vec2i pos, color color_mask = COLOR_MASK_NONE, bool alpha = false);
const image_t* isometric_from_drawtile_part(painter &ctx, int image_id, vec2i pos, int offset, color color_mask = COLOR_MASK_NONE);
} // namespace ImageDraw

