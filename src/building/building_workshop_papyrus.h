#pragma once

#include "building/building_industry.h"

class building_papyrus_maker : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_PAPYRUS_WORKSHOP, building_papyrus_maker, building_industry)
    virtual building_papyrus_maker *dcast_papyrus_maker() override { return this; }

    virtual bool can_play_animation() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void on_place_checks() override;
};
