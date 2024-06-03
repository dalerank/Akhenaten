#pragma once

#include "building/building.h"

class building_burning_ruin : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_BURNING_RUIN, building_burning_ruin)

    building_burning_ruin(building &b) : building_impl(b) {}
    virtual building_burning_ruin *dcast_burning_ruin() override { return this; }
    virtual bool can_play_animation() const override { return true; }
    bool update();

    tile2i can_be_accessed();
};