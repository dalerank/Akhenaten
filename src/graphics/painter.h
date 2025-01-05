#pragma once

#include "core/vec2i.h"
#include "color.h"
#include "game/resource.h"
#include "graphics/image_desc.h"
#include "graphics/graphics.h"

struct view_data_t;
struct SDL_Renderer;
struct SDL_Texture;
struct image_t;

struct sprite {
    const image_t *img = nullptr;
    inline sprite() {}
};

struct sprite_resource_icon : public sprite {
    sprite_resource_icon(e_resource);
};

struct painter {
    view_data_t *view;
    SDL_Renderer *renderer;
    float global_render_scale;

    void draw(SDL_Texture *texture, float x, float y, vec2i offset, vec2i size, color color = COLOR_MASK_NONE, float scale = 1.f, ImgFlags flags = ImgFlag_None);
    void draw_grayscale(SDL_Texture *texture, float x, float y, vec2i offset, vec2i size, float scale = 1.f, ImgFlags flags = ImgFlag_None);
    inline void draw(SDL_Texture *texture, vec2i pos, vec2i offset, vec2i size, color color = COLOR_MASK_NONE, float scale = 1.f, ImgFlags flags = ImgFlag_None) {
        draw(texture, pos.x, pos.y, offset, size, color, scale, flags);
    }
    void draw(const sprite &spr, vec2i pos, color color_mask = COLOR_MASK_NONE, float scale = 1.f, ImgFlags flags = ImgFlag_None);

protected:
    void draw_impl(SDL_Texture *texture, float x, float y, vec2i offset, vec2i size, color color = COLOR_MASK_NONE, float scale = 1.f, ImgFlags flags = ImgFlag_None);
    SDL_Texture *convertToGrayscale(SDL_Texture *tx, vec2i offset, vec2i size);
};

