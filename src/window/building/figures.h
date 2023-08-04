#pragma once

struct building_info_context;
struct mouse;

void window_building_prepare_figure_list(building_info_context* c);

void window_building_draw_figure_list(building_info_context* c);

int window_building_handle_mouse_figure_list(const mouse* m, building_info_context* c);

void window_building_play_figure_phrase(building_info_context* c);
