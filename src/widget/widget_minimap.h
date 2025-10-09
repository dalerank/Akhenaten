#pragma once

#include "core/vec2i.h"
#include "graphics/animation.h"
#include "window/autoconfig_window.h"

struct minimap_window : public autoconfig_window_t<minimap_window> {
    tile2i absolute_tile;
    vec2i draw_size;
    vec2i screen_offset;
    vec2i size;
    int cache_width;
    color enemy_color;
    vec2i rel_mouse;
    vec2i mouse_last_coords;
    int refresh_requested;
    bool draw_force = false;
    int cached_texture = 0;
    animation_t terrain_canal;
    animation_t terrain_water;
    animation_t terrain_shrub;
    animation_t terrain_tree;
    animation_t terrain_rock;
    animation_t terrain_elevation;
    animation_t terrain_road;
    animation_t terrain_wall;
    animation_t terrain_meadow;
    animation_t terrain_flooplain;
    animation_t terrain_marshland;
    animation_t terrain_dune;
    animation_t terrain_teal;
    animation_t terrain_bright_teal;
    animation_t terrain_dark_red;
    animation_t terrain_purple;
    animation_t terrain_lilac;
    animation_t terrain_light_yellow;
    animation_t terrain_bright_blue;
    animation_t terrain_orange;

    virtual int handle_mouse(const mouse *m) override;
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override;
    virtual int draw_background(UiFlags flags) override { return 0; }

    virtual void archive_load(archive arch) override;
    virtual void init() override;
    virtual void on_mission_start() override;
    
    bool is_in_minimap(const mouse *m);
    bool draw_figure(vec2i screen, tile2i point);
    vec2i get_mouse_relative_pos(const mouse *m, float &xx, float &yy);
    void set_bounds(vec2i draw_size);
    void draw_uncached(vec2i offset);
    void draw_minimap_tile(vec2i screen, tile2i point);
    void draw_viewport_rectangle(painter &ctx);
    void clear();
    virtual void draw(UiFlags flags) override;
};

void widget_minimap_init();
void widget_minimap_invalidate();
void widget_minimap_draw(vec2i offset, int force);
bool widget_minimap_handle_mouse(const mouse* m);
