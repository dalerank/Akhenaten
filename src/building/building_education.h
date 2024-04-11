#pragma once

#include "building/building.h"

void building_academy_draw_info(object_info& c);
void building_library_draw_info(object_info& c);
void building_education_draw_info(object_info &c, const char *type, e_figure_type ftype, e_resource resource, vec2i icon_res, vec2i text_res);