#pragma once

#include "core/vec2i.h"

struct object_info;
struct painter;
class building;

enum e_farm_worker_state {
    FARM_WORKER_TILING,
    FARM_WORKER_SEEDING,
    FARM_WORKER_HARVESTING
};

void building_farm_draw_info(object_info& c);
void building_farm_draw_workers(painter &ctx, building *b, int grid_offset, vec2i pos);
bool building_farm_time_to_deliver(bool floodplains, int resource_id = 0);
