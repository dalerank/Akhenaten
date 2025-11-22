#pragma once

#include "building/building_industry.h"

class building_chariots_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_CHARIOTS_WORKSHOP, building_chariots_workshop, building_industry)

    //virtual void on_place(int orientation, int variant) override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
    virtual bool can_play_animation() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};
