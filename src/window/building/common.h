#pragma once

#include "building/building.h"
#include "city/object_info.h"
#include "graphics/elements/ui.h"

static const int MIN_Y_POSITION = 32;
static const int MARGIN_POSITION = 16;

pcstr get_employment_info_text_key(object_info* c, building* b, int consider_house_covering);
void draw_employment_details_ui(ui::widget &ui, object_info &c, building *b, int text_id);
vec2i window_building_set_possible_position(vec2i offset, vec2i blocks);
int window_building_get_vertical_offset(object_info* c, int new_window_height);

void window_building_play_sound(object_info* c, xstring sound_file);