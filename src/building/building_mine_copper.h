#pragma once

#include "building/building_mine.h"

class building_mine_copper : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_COPPER_MINE, building_mine_copper, building_mine)

    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
    virtual void update_production() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void spawn_figure() override;
    virtual void production_finished() override;
};

