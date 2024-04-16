#pragma once

#include "graphics/color.h"
#include "core/vec2i.h"
#include "core/string.h"

class building;
struct object_info;
struct painter;

void building_entertainment_school_draw_info(object_info &c, pcstr type, int group_id);

void building_dancer_school_draw_info(object_info& c);
void building_bullfight_school_draw_info(object_info& c);
