#pragma once

#include "building/building_mine.h"

class building_mine_copper : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_COPPER_MINE, building_mine_copper, building_mine)

    virtual void update_production() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void spawn_figure() override;
    virtual void production_finished() override;
};
