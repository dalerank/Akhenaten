#pragma once

#include "building/building.h"

class building_gatehouse : public building_impl {
public:
    building_gatehouse(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
};

class building_brick_gatehouse : public building_gatehouse {
public:
    BUILDING_METAINFO(BUILDING_BRICK_GATEHOUSE, building_brick_gatehouse)
    building_brick_gatehouse(building &b) : building_gatehouse(b) {}
};

class building_mud_gatehouse : public building_gatehouse {
public:
    BUILDING_METAINFO(BUILDING_MUD_GATEHOUSE, building_mud_gatehouse)
    building_mud_gatehouse(building &b) : building_gatehouse(b) {}
};