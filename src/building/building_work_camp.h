#pragma once

#include "building/building.h"
#include "city/object_info.h"

class building_work_camp : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WORK_CAMP, building_work_camp, building_impl)
    building_work_camp *dcast_work_camp() override { return this; }

    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual void update_month() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;

    building *determine_worker_needed();
};