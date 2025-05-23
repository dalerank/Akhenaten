#pragma once

#include "building/building.h"

class building_water_supply : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WATER_SUPPLY, building_water_supply, building_impl)

    virtual building_water_supply *dcast_water_supply() override { return this; }

    virtual void on_place_checks() override;
    virtual void spawn_figure() override;
    virtual void update_month() override;
    virtual void update_graphic() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_WATER; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};