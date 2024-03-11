#pragma once

#include "building/building.h"
#include "city/object_info.h"

class building_work_camp : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WORK_CAMP, building_work_camp)

    building_work_camp(building &b) : building_impl(b) {}
    virtual void spawn_figure() override;
    virtual void update_day() override;
    virtual void window_info_background(object_info &ctx) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};