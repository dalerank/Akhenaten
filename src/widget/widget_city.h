#pragma once

#include "input/hotkey.h"
#include "input/mouse.h"
#include "grid/point.h"
#include "graphics/color.h"

#include "city/tile_draw.h"

struct tooltip_context;
struct painter;

struct screen_city_t {
    tile2i current_tile;
    tile2i selected_tile;
    color force_mask;
    int new_start_grid_offset;
    bool capture_input;

    local_render_context_t render_ctx;

    int selected_figure_id;
    int highlighted_formation;

    void handle_touch_scroll(const touch_t *t, bool force_capture_input);
    void update_clouds(painter &ctx);
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
    int input_coords_in_city(int x, int y);

    void draw(painter &ctx);
    void draw_with_overlay(painter &ctx);
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
    void draw_isometric_mark_sound(int building_id, int grid_offset, color &color_mask, int direction);
    void draw_tooltip(tooltip_context* c);
    void debug_draw_figures();
    bool allow_building_info(tile2i tile);
};

extern screen_city_t g_screen_city;

void set_city_clip_rectangle(painter &ctx);
