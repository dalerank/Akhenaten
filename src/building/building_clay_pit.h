#pragma once

#include "building/building_industry.h"

class building_clay_pit : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_CLAY_PIT, building_clay_pit, building_industry)
    virtual building_clay_pit *dcast_clay_pit() override { return this; }

    virtual int get_fire_risk(int value) const override;
    virtual void on_before_flooded() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void spawn_figure() override;
    virtual void update_production() override;
    virtual bool is_deletable() const override;
};

