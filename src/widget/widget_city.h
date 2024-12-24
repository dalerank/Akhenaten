#pragma once

#include "graphics/elements/tooltip.h"
#include "graphics/view/view.h"
#include "input/hotkey.h"
#include "input/mouse.h"
#include "grid/point.h"

void set_city_clip_rectangle(painter &ctx);

void widget_city_draw(painter &ctx);
void widget_city_draw_for_figure(painter &ctx, int figure_id, vec2i* coord);
void widget_city_draw_without_overlay(painter &ctx, int selected_figure_id, vec2i *figure_coord, tile2i tile);

bool widget_city_draw_construction_cost_and_size();

int widget_city_has_input();
void widget_city_handle_input(const mouse* m, const hotkeys* h);
void widget_city_handle_input_military(const mouse* m, const hotkeys* h, int legion_formation_id);

void widget_city_get_tooltip(tooltip_context* c);
void widget_city_handle_touch_scroll(const touch_t *t);
void widget_city_scroll_map(const mouse *m);

void widget_city_clear_current_tile();
void widget_city_set_current_tile(tile2i tile);
tile2i widget_city_get_current_tile();
void widget_city_capture_input(bool v);
tile2i widget_city_update_city_view_coords(vec2i pixel);
