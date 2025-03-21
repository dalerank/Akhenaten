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
};

extern screen_city_t g_screen_city;

void set_city_clip_rectangle(painter &ctx);

void widget_city_draw(painter &ctx);
void widget_city_draw_for_figure(painter &ctx, int figure_id, vec2i* coord);
void widget_city_draw_without_overlay(painter &ctx, int selected_figure_id, vec2i *figure_coord, tile2i tile);

bool widget_city_draw_construction_cost_and_size();

int widget_city_has_input();
void widget_city_handle_input(const mouse* m, const hotkeys* h);
void widget_city_handle_input_military(const mouse* m, const hotkeys* h, int legion_formation_id);

void widget_city_get_tooltip(tooltip_context* c);
void widget_city_scroll_map(const mouse *m);

void widget_city_clear_current_tile();
void widget_city_set_current_tile(tile2i tile);
tile2i widget_city_get_current_tile();
tile2i widget_city_update_city_view_coords(vec2i pixel);
