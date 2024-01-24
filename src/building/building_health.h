#pragma once

#include "building/building.h"

class building_apothecary : public building_impl {
public:
    building_apothecary(building &b) : building_impl(b) {}
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
};

void building_dentist_draw_info(object_info& c);
void building_mortuary_draw_info(object_info& c);
void building_physician_draw_info(object_info& c);