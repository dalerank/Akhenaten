#pragma once

#include "input/mouse.h"

struct object_info;

void window_building_draw_dock(object_info* c);
void window_building_draw_dock_orders_foreground(object_info* c);
void window_building_draw_dock_orders(object_info* c);
void window_building_draw_dock_foreground(object_info* c);

int window_building_handle_mouse_dock(const mouse* m, object_info* c);
int window_building_handle_mouse_dock_orders(const mouse* m, object_info* c);

void window_building_draw_market(object_info* c);
void window_building_draw_market_foreground(object_info* c);
void window_building_draw_market_orders(object_info* c);
void window_building_draw_market_orders_foreground(object_info* c);

void window_building_handle_mouse_market(const mouse* m, object_info* c);
void window_building_handle_mouse_market_orders(const mouse* m, object_info* c);

void window_building_draw_granary(object_info* c);
void window_building_draw_granary_foreground(object_info* c);
void window_building_draw_granary_orders(object_info* c);
void window_building_draw_granary_orders_foreground(object_info* c);

int window_building_handle_mouse_granary(const mouse* m, object_info* c);
int window_building_handle_mouse_granary_orders(const mouse* m, object_info* c);

void window_building_get_tooltip_granary_orders(int* group_id, int* text_id);

void window_building_draw_warehouse(object_info* c);
void window_building_draw_warehouse_foreground(object_info* c);
void window_building_draw_warehouse_orders(object_info* c);
void window_building_draw_warehouse_orders_foreground(object_info* c);

int window_building_handle_mouse_warehouse(const mouse* m, object_info* c);
int window_building_handle_mouse_warehouse_orders(const mouse* m, object_info* c);

void window_building_get_tooltip_warehouse_orders(int* group_id, int* text_id);
