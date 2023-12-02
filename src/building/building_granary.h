#pragma once

#include "game/resource.h"
#include "core/vec2i.h"
#include "grid/point.h"
#include "graphics/color.h"

class building;
struct painter;

enum e_granary_task {
    GRANARY_TASK_NONE = -1,
    GRANARY_TASK_GETTING = 0,
};

struct granary_task_status {
    e_granary_task status;
    e_resource resource;
};

int building_granary_get_amount(building* granary, e_resource resource);

int building_granary_add_resource(building* granary, e_resource resource, int is_produced, int amount);

int building_granary_remove_resource(building* granary, e_resource resource, int amount);

int building_granary_remove_for_getting_deliveryman(building* src, building* dst, e_resource& resource);

int building_granary_is_not_accepting(e_resource resource, building* b);

granary_task_status building_granary_determine_worker_task(building* granary);

void building_granaries_calculate_stocks();

int building_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, int force_on_stockpile, int* understaffed, tile2i* dst);

int building_getting_granary_for_storing(tile2i tile, e_resource resource, int distance_from_entry, int road_network_id, tile2i* dst);

int building_granary_for_getting(building* src, tile2i* dst);

void building_granary_bless();
void building_granary_warehouse_curse(int big);

bool building_granary_is_getting(e_resource resource, building* b);
void building_granary_set_res_offset(int i, vec2i v);

void building_granary_draw_anim(building &b, vec2i point, tile2i tile, color mask, painter &ctx);