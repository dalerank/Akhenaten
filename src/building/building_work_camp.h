#pragma once

#include "building/building.h"
#include "city/object_info.h"

void building_work_camp_draw_info(object_info &c);

class building_work_camp : public building_impl {
public:
    building_work_camp(building &b) : building_impl(b) {}
    virtual void spawn_figure() override;
    virtual void update_day() override;
};