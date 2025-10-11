#pragma once

#include "building/building_industry.h"

class building_weaponsmith : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_WEAPONSMITH, building_weaponsmith, building_industry)

    virtual void on_place_checks() override;
    virtual bool need_road_access() const override { return true; }
    virtual bool can_play_animation() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};