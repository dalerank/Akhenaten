#pragma once

#include "graphics/elements/tooltip.h"
#include "graphics/view/view.h"
#include "input/hotkey.h"
#include "input/mouse.h"

void set_city_clip_rectangle();

void widget_city_draw(view_context &ctx);
void widget_city_draw_for_figure(int figure_id, vec2i* coord, view_context &ctx);
void widget_city_draw_without_overlay(int selected_figure_id, vec2i *figure_coord, tile2i tile, view_context &ctx);

bool widget_city_draw_construction_cost_and_size(void);

int widget_city_has_input(void);
void widget_city_handle_input(const mouse* m, const hotkeys* h);
void widget_city_handle_input_military(const mouse* m, const hotkeys* h, int legion_formation_id);

void widget_city_get_tooltip(tooltip_context* c);

void widget_city_clear_current_tile(void);
