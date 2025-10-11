#pragma once

#include "building/building_industry.h"

class building_bricks_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_BRICKS_WORKSHOP, building_bricks_workshop, building_industry)

    struct static_params : public building_model{
    } BUILDING_STATIC_DATA_T;

    virtual bool can_play_animation() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};
ANK_CONFIG_STRUCT(building_bricks_workshop::static_params, meta)