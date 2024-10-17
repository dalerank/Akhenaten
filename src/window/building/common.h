#pragma once

#include "building/building.h"
#include "city/object_info.h"
#include "graphics/elements/ui.h"

static const int MIN_Y_POSITION = 32;
static const int MARGIN_POSITION = 16;

textid get_employment_info_text_id(object_info *c, building *b, int consider_house_covering);
void draw_employment_details(object_info *c, building *b, int y_offset, int text_id);
void draw_employment_details_ui(ui::widget &ui, object_info &c, building *b, int text_id);
vec2i window_building_set_possible_position(vec2i offset, vec2i blocks);
int window_building_get_vertical_offset(object_info* c, int new_window_height);

void window_building_draw_employment(object_info* c, int y_offset);
void window_building_draw_employment_without_house_cover(object_info* c, int y_offset);

void window_building_draw_description(object_info* c, int text_group, int text_id);
void window_building_draw_description_at(object_info* c, int y_offset, int text_group, int text_id);

inline void window_building_draw_description(object_info &c, int text_group, int text_id) { window_building_draw_description(&c, text_group, text_id); }
inline void window_building_draw_description_at(object_info &c, int y_offset, int text_group, int text_id) { window_building_draw_description_at(&c, y_offset, text_group, text_id); }

void window_building_play_sound(object_info* c, const char* sound_file);