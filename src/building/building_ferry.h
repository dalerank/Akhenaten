#pragma once

#include "building/building.h"

class building_ferry : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FERRY, building_ferry)

    building_ferry(building &b) : building_impl(b) {}
    virtual building_ferry *dcast_ferry() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void window_info_background(object_info &c) override;
    virtual void update_map_orientation(int orientation) override;
    virtual void highlight_waypoints() override;
};