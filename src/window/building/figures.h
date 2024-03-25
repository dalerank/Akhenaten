#pragma once

#include "building/building.h"

int name_group_id();
int big_people_image(e_figure_type type);
int inventory_to_resource_id(int value);
void window_building_prepare_figure_list(object_info* c);
void window_building_draw_figure_list(object_info* c);
int window_building_handle_mouse_figure_list(const mouse* m, object_info* c);
void window_building_play_figure_phrase(object_info* c);
