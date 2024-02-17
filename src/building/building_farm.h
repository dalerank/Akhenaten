#pragma once

#include "building/building.h"

struct object_info;
struct painter;
class building;

enum e_farm_worker_state {
    FARM_WORKER_TILING,
    FARM_WORKER_SEEDING,
    FARM_WORKER_HARVESTING
};

class building_farm : public building_impl {
public:
    building_farm(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &ctx) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};

void building_farm_draw_workers(painter &ctx, building *b, int grid_offset, vec2i pos);
bool building_farm_time_to_deliver(bool floodplains, int resource_id = 0);
