#pragma once

#include "graphics/color.h"
#include "game/resource.h"
#include "building/building.h"

void building_luxury_workshop_draw_info(object_info& c);
void building_workshop_draw_background(object_info &c, int help_id, pcstr type, int group_id, e_resource resource, e_resource input_resource);
void building_workshop_draw_background(object_info &c, int help_id, pcstr type, int group_id, e_resource resource, e_resource input_resource_a, e_resource input_resource_b);
void building_workshop_draw_foreground(object_info &c);
void building_workshop_draw_raw_material_storage(painter &ctx, const building *b, vec2i pos, color color_mask);