#pragma once

struct object_info;
struct mouse;

void window_building_draw_wall(object_info* c);
void window_building_draw_ferry(object_info* c);
void window_building_draw_gatehouse(object_info* c);
void window_building_draw_tower(object_info* c);
void window_building_draw_barracks(object_info* c);
void window_building_draw_barracks_foreground(object_info* c);
int window_building_handle_mouse_barracks(const mouse* m, object_info* c);
void window_building_draw_military_academy(object_info* c);
void window_building_draw_fort(object_info* c);
void window_building_draw_legion_info(object_info* c);
void window_building_draw_legion_info_foreground(object_info* c);
int window_building_handle_mouse_legion_info(const mouse* m, object_info* c);
int window_building_get_legion_info_tooltip_text(object_info* c);
