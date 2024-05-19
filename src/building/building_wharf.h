#pragma once

#include "building/building.h"

class building_wharf : public building_impl {
public:
    building_wharf(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
};

class building_transport_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_TRANSPORT_WHARF, building_transport_wharf)
    building_transport_wharf(building &b) : building_wharf(b) {}
};

class building_warship_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_WARSHIP_WHARF, building_warship_wharf)
    building_warship_wharf(building &b) : building_wharf(b) {}
};

