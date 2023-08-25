#pragma once

struct building_info_context;
struct mouse;

void window_building_draw_wall(building_info_context* c);
void window_building_draw_ferry(building_info_context* c);
void window_building_draw_gatehouse(building_info_context* c);
void window_building_draw_tower(building_info_context* c);

void window_building_draw_barracks(building_info_context* c);
void window_building_draw_barracks_foreground(building_info_context* c);
int window_building_handle_mouse_barracks(const mouse* m, building_info_context* c);

void window_building_draw_military_academy(building_info_context* c);

void window_building_draw_fort(building_info_context* c);

void window_building_draw_legion_info(building_info_context* c);
void window_building_draw_legion_info_foreground(building_info_context* c);
int window_building_handle_mouse_legion_info(const mouse* m, building_info_context* c);
int window_building_get_legion_info_tooltip_text(building_info_context* c);
