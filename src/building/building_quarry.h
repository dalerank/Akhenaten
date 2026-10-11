#pragma once

#include "building/building_industry.h"

class building_quarry : public building_industry {
public:
    building_quarry(building &b) : building_industry(b) {}
    virtual building_quarry *dcast_quarry() override { return this; }
};

class building_sandstone_quarry : public building_quarry {
public:
    BUILDING_METAINFO(BUILDING_SANDSTONE_QUARRY, building_sandstone_quarry, building_quarry)
};

class building_stone_quarry : public building_quarry {
public:
    BUILDING_METAINFO(BUILDING_STONE_QUARRY, building_stone_quarry, building_quarry)
};

class building_limestone_quarry : public building_quarry {
public:
    BUILDING_METAINFO(BUILDING_LIMESTONE_QUARRY, building_limestone_quarry, building_quarry)
};

class building_granite_quarry : public building_quarry {
public:
    BUILDING_METAINFO(BUILDING_GRANITE_QUARRY, building_granite_quarry, building_quarry)
};
