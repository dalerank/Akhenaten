#pragma once

#include "city/object_info.h"

static const int MIN_Y_POSITION = 32;
static const int MARGIN_POSITION = 16;

void window_building_set_possible_position(int* x_offset, int* y_offset, int width_blocks, int height_blocks);
int window_building_get_vertical_offset(object_info* c, int new_window_height);

void window_building_draw_employment(object_info* c, int y_offset);
void window_building_draw_employment_without_house_cover(object_info* c, int y_offset);
void window_building_draw_employment_flood_farm(object_info* c, int y_offset);

void window_building_draw_description(object_info* c, int text_group, int text_id);
void window_building_draw_description_at(object_info* c, int y_offset, int text_group, int text_id);

void window_building_play_sound(object_info* c, const char* sound_file);