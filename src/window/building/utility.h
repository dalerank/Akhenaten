#pragma once

#include "input/mouse.h"

struct object_info;

void window_building_draw_roadblock(object_info* c);
void window_building_draw_roadblock_orders(object_info* c);
void window_building_draw_roadblock_orders_foreground(object_info* c);
void window_building_draw_roadblock_foreground(object_info* c);
int window_building_handle_mouse_roadblock(const mouse* m, object_info* c);
int window_building_handle_mouse_roadblock_orders(const mouse* m, object_info* c);

void window_building_draw_burning_ruin(object_info* c);
void window_building_draw_rubble(object_info* c);

void window_building_draw_water_lift(object_info* c);
void window_building_draw_aqueduct(object_info* c);
void window_building_draw_fountain(object_info* c);

void window_building_draw_mission_post(object_info* c);
void window_building_draw_native_hut(object_info* c);
void window_building_draw_native_meeting(object_info* c);
void window_building_draw_native_crops(object_info* c);
