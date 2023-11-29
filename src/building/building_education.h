#pragma once

#include "graphics/color.h"
#include "core/vec2i.h"

struct object_info;
struct painter;
class building;

void building_scribal_school_draw_info(object_info& c);
void building_academy_draw_info(object_info& c);
void building_library_draw_info(object_info& c);
void building_education_draw_raw_material_storage(painter &ctx, const building *b, vec2i pos, color color_mask);