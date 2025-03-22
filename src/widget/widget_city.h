#pragma once

#include "input/hotkey.h"
#include "input/mouse.h"
#include "grid/point.h"

struct tooltip_context;
struct painter;

struct screen_city_t {
    tile2i current_tile;
    tile2i selected_tile;
    int new_start_grid_offset;
    bool capture_input;

    void handle_touch_scroll(const touch_t *t, bool force_capture_input);
    void draw(painter &ctx);
    void draw_with_overlay(painter &ctx);
    void draw_without_overlay(painter &ctx, int selected_figure_id, vec2i *figure_coord);
    void draw_for_figure(painter &ctx, int figure_id, vec2i *coord);
    void update_clouds(painter &ctx);
    void clear_current_tile();
    void handle_first_touch(tile2i tile);
    void handle_touch();
    void handle_mouse(const mouse *m);
    void handle_input(const mouse *m, const hotkeys *h);
    void handle_escape(const hotkeys *h);
    void draw_tooltip(tooltip_context* c);
    xstring get_overlay_tooltip(tooltip_context *c, tile2i tile);
};

extern screen_city_t g_screen_city;

void set_city_clip_rectangle(painter &ctx);

int widget_city_has_input();
void widget_city_handle_input_military(const mouse* m, const hotkeys* h, int legion_formation_id);

void widget_city_scroll_map(const mouse *m);

tile2i widget_city_update_city_view_coords(vec2i pixel);
