#pragma once

#include "building/building_industry.h"

class building_bricks_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_BRICKS_WORKSHOP, building_bricks_workshop)

    building_bricks_workshop(building &b) : building_industry(b) {}

    using static_params = static_params_t<building_bricks_workshop>;
    static const static_params& current_params() { return (const static_params&)params(TYPE); }

    virtual bool can_play_animation() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};