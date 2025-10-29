#pragma once

#include "core/vec2i.h"
#include "graphics/color.h"
#include "graphics/font.h"
#include "graphics/animkeys.h"

struct painter;
struct image_t;
struct image_desc;

void graphics_clear_screen();

void graphics_set_to_dialog();
void graphics_in_dialog_with_size(int width, int height);
void graphics_reset_dialog();

void graphics_set_clip_rectangle(vec2i pos, vec2i size);
bool graphics_inside_clip_rectangle(vec2i pos);
rect graphics_clip_rectangle();
void graphics_reset_clip_rectangle();

void graphics_draw_line(vec2i start, vec2i end, color color);
void graphics_draw_vertical_line(vec2i start, int ny, color color);
void graphics_draw_horizontal_line(vec2i start, int nx, color color);
void graphics_draw_pixel(vec2i pixel, color color);
void graphics_draw_rect(vec2i start, vec2i size, color color);
void graphics_draw_inset_rect(vec2i start, vec2i size);

void graphics_shade_rect(vec2i start, vec2i size, int darkness);

int graphics_save_to_texture(int image_id, vec2i pos, vec2i size);
void graphics_clear_saved_texture(int image_id, color clr);
void graphics_delete_saved_texture(int image_id);
void graphics_draw_from_texture(int image_id, vec2i pos, vec2i size);

enum ImgFlag_ {
    ImgFlag_None = 0,
    ImgFlag_Alpha = (1 << 1),
    ImgFlag_Grayscale = (1 << 2),
    ImgFlag_Mirrored = (1 << 3),
    ImgFlag_InternalOffset = (1 << 4),
};

using ImgFlags = uint32_t;

struct render_command_t {
    enum e_render_type
    {
        ert_none = 0,
        ert_drawtile = 1,
        ert_drawtile_top = 2,
        ert_drawtile_full = 3,
        ert_generic = 4,
        ert_sprite = 5,
        ert_ornament = 6,
        ert_from_below = 7,
    };
    e_render_type rtype = ert_none;
    int32_t image_id = 0;
    int32_t base_id = 0;
    vec2i pixel = {};
    uint32_t mask = COLOR_MASK_NONE;
    float scale = 1.f;
    uint32_t flags = 0;
    uint32_t id = 0;
    uint32_t tag = 0;
    std::vector<render_command_t> commands;
};

namespace ImageDraw {
const image_t* img_generic(painter &ctx, int image_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
const image_t* img_generic(painter &ctx, int pak, int image_id, vec2i p, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
const image_t* img_generic(painter &ctx, const image_desc &img, vec2i p, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
const image_t* img_generic(painter &ctx, int image_id, vec2i p, color color_mask = COLOR_MASK_NONE, float scale = 1.0f, ImgFlags flags = ImgFlag_None);
const image_t* img_generic(painter &ctx, const image_t *img, vec2i p, color color_mask = COLOR_MASK_NONE, float scale = 1.0f, ImgFlags flags = ImgFlag_None);
const image_t* img_isometric(painter& ctx, int image_id, vec2i p, color color_mask = COLOR_MASK_NONE, float scale = 1.0f, ImgFlags flags = ImgFlag_None);
const image_t* img_sprite(painter &ctx, int image_id, vec2i p, color color_mask = COLOR_MASK_NONE, float scale = 1.0f, ImgFlags flags = ImgFlag_None);

void fill_rect(vec2i p, vec2i size, color color);
void img_ornament(painter &ctx, int image_id, int base_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
void img_from_below(painter &ctx, int image_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
void img_letter(painter &ctx, const image_t *img, e_font font, int letter_id, int x, int y, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);
void img_background(painter &ctx, int image_id, float scale = 1.0f, vec2i offset = {0, 0});
void isometric(painter &ctx, int image_id, vec2i pos, color color_mask = COLOR_MASK_NONE, float scale = 1.0f);

void apply_render_commands(painter& ctx);
void execute_render_command(painter& ctx, const render_command_t& command);
void clear_render_commands();
render_command_t& create_command(render_command_t::e_render_type rt);
render_command_t& active_command();
render_command_t& create_subcommand(render_command_t::e_render_type rt);

} // namespace ImageDraw