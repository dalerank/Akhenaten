#pragma once

struct figure_draw_cache_data_t;
struct view_data_t;
struct SDL_Renderer;

struct painter {
    figure_draw_cache_data_t *figure_cache;
    view_data_t *view;
    SDL_Renderer *renderer;
    float global_render_scale;
};