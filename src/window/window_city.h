#pragma once

struct hotkeys;
struct tooltip_context;

void window_city_draw_all();
void window_city_draw_panels();
void window_city_draw();
void window_city_draw_background(int);

void window_city_show();
void window_city_handle_hotkeys(const hotkeys *h);
void window_city_draw_paused_and_time_left();

extern bool city_has_loaded;