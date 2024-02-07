#pragma once

#include "building/building.h"
#include "city/object_info.h"

class building_work_camp : public building_impl {
public:
    building_work_camp(building &b) : building_impl(b) {}
    virtual void spawn_figure() override;
    virtual void update_day() override;
    virtual void window_info_background(object_info &ctx) override;
};