#pragma once

#include "building/building.h"

class building_tower : public building_impl {
public:
    building_tower(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    virtual void on_place_checks() override;
    //virtual void on_place(int orientation, int variant) override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
};

class building_brick_tower : public building_tower {
public:
    BUILDING_METAINFO(BUILDING_BRICK_TOWER, building_brick_tower)
    building_brick_tower(building &b) : building_tower(b) {}
};

class building_mud_tower : public building_tower {
public:
    BUILDING_METAINFO(BUILDING_MUD_TOWER, building_mud_tower)
    building_mud_tower(building &b) : building_tower(b) {}
};