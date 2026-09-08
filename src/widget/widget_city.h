#pragma once

#include "input/hotkey.h"
#include "input/mouse.h"
#include "grid/point.h"
#include "graphics/color.h"
#include "core/svector.h"

#include "city/tile_draw.h"

struct tooltip_context;
struct painter;

using screen_space_effect_cb = void(painter &ctx);

struct screen_city_t {
    tile2i current_tile;
    tile2i selected_tile;
    color force_mask;
    int new_start_grid_offset;
    bool capture_input;
    bool buildings_flat_view = false;

    local_render_context_t render_ctx;
    svector<screen_space_effect_cb *, 8> screen_space_effects;

    int selected_figure_id;
    int highlighted_formation;

    void handle_touch_scroll(const touch_t *t, bool force_capture_input);
    void clear_current_tile();
    void handle_first_touch(tile2i tile);
    void handle_touch();
    void handle_mouse(const mouse *m);
    void handle_input(const mouse *m, const hotkeys *h);
    void handle_escape(const hotkeys *h);
    xstring get_overlay_tooltip(tooltip_context *c, tile2i tile);
    bool handle_cancel_construction_button(const touch_t *t);
    bool handle_legion_click(tile2i tile);
    void update_zoom_level(painter &ctx);
    void scroll_map(const mouse *m);
    tile2i update_city_view_coords(vec2i pixel);
    void handle_input_military(const mouse *m, const hotkeys *h, int legion_formation_id);
    void military_map_click(int legion_formation_id, tile2i tile);
    bool handle_warship_click(tile2i tile);
    void handle_input_warship(const mouse *m, const hotkeys *h, int warship_figure_id);
    void warship_map_click(int warship_figure_id, tile2i tile);
    bool handle_transport_click(tile2i tile);
    void handle_input_transport(const mouse *m, const hotkeys *h, int transport_figure_id, int pick_mode);
    void transport_map_click(int transport_figure_id, int pick_mode, tile2i tile);
    int input_coords_in_city(int x, int y);

    void draw(painter &ctx);
    void draw_with_overlay(painter &ctx, int selected_figure_id);
    void draw_ornaments_overlay(vec2i pixel, tile2i point, painter &ctx);
    void draw_ornaments_and_animations_height(vec2i point, tile2i tile, painter &ctx);
    void draw_without_overlay(painter &ctx, int selected_figure_id);
    void draw_for_figure(painter &ctx, int figure_id);
    void draw_figures(vec2i pixel, tile2i tile, painter &ctx, bool force);
    void draw_figures_on_flat_tiles(vec2i pixel, tile2i tile, painter &ctx);
    void draw_figures_overlay(vec2i pixel, tile2i tile, painter &ctx);
    void draw_isometric_flat(vec2i pixel, tile2i tile, painter &ctx);
    void draw_isometric_terrain_height(vec2i pixel, tile2i tile, painter &ctx);
    void draw_isometric_nonterrain_height(vec2i pixel, tile2i tile, painter &ctx);
    void draw_isometric_nonterrain_height(vec2i pixel, tile2i tile, color mask, painter &ctx);
    void draw_postrender_building_effects(vec2i pixel, tile2i tile, painter &ctx);
    void draw_building_road_access_marker(painter &ctx);
    void draw_recorded_delivery_paths(painter &ctx);
    void draw_isometric_mark_sound(int building_id, int grid_offset, color &color_mask, int direction);
    void draw_tooltip(tooltip_context* c);
    void debug_draw_figures(painter &ctx);
    void draw_current_select_tile(painter &ctx);
    void add_screen_space_effect(screen_space_effect_cb *effect);
    void draw_screen_space_effects(painter &ctx);
    bool allow_building_info(tile2i tile);
};

extern screen_city_t g_screen_city;

void set_city_clip_rectangle(painter &ctx);
