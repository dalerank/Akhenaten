#pragma once

#include "building/building.h"

enum e_permission {
    epermission_none = 0,
    epermission_maintenance = 1,
    epermission_priest = 2,
    epermission_market = 3,
    epermission_entertainer = 4,
    epermission_education = 5,
    epermission_medicine = 6,
    epermission_tax_collector = 7
};

class building_roadblock : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_ROADBLOCK, building_roadblock)
    building_roadblock(building &b) : building_impl(b) {}

    virtual building_roadblock *dcast_roadblock() override { return this; }

    virtual void on_place_checks() override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;

    void set_permission(e_permission p);
    int get_permission(e_permission p);

};