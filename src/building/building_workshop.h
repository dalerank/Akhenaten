#pragma once

#include "graphics/color.h"
#include "game/resource.h"

struct object_info;
struct painter;

void building_brewery_draw_info(object_info& c);
void building_flax_workshop_draw_info(object_info& c);
void building_weapons_workshop_draw_info(object_info& c);
void building_luxury_workshop_draw_info(object_info& c);
void building_brick_maker_workshop_draw_info(object_info& c);
void building_papyrus_workshop_draw_info(object_info &c);
void building_cattle_ranch_draw_info(object_info &c);
void building_workshop_draw_info(object_info &c, int help_id, pcstr type, int group_id, e_resource resource, e_resource input_resource);
void building_workshop_draw_raw_material_storage(painter &ctx, const building *b, vec2i pos, color color_mask);