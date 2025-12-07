#pragma once

#include "building/building_mine.h"
#include <algorithm>

class building_mine_gems : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_GEMSTONE_MINE, building_mine_gems, building_mine)

    struct static_params : public building_static_params {
        uint16_t production_divider;
    } BUILDING_STATIC_DATA_T;

    virtual int produce_uptick_per_day() const override;
    virtual void update_production() override;
    virtual void on_before_collapse() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int stored_amount(e_resource r) const override;
};
ANK_CONFIG_STRUCT(building_mine_gems::static_params, production_divider)

