#pragma once

#include "core/vec2i.h"
#include "color.h"

struct figure_draw_cache_data_t;
struct view_data_t;
struct SDL_Renderer;
struct SDL_Texture;
struct image_t;

enum e_resource;

struct sprite {
    const image_t *img = nullptr;
};

struct sprite_resource_icon : public sprite {
    sprite_resource_icon(e_resource res);
};

struct painter {
    figure_draw_cache_data_t *figure_cache;
    view_data_t *view;
    SDL_Renderer *renderer;
    float global_render_scale;

    void draw(SDL_Texture *texture, float x, float y, vec2i offset, vec2i size, color color, float scale, bool mirrored);
    void draw(const sprite &spr, vec2i pos, color color_mask = COLOR_MASK_NONE, float scale = 1.0f, bool mirrored = false);
};

