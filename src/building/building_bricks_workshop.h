#pragma once

#include "building/building_industry.h"

class building_bricks_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_BRICKS_WORKSHOP, building_ferry)

    building_bricks_workshop(building &b) : building_industry(b) {}

    virtual void on_create(int orientation) override;
    virtual void window_info_background(object_info &c) override;
    virtual void update_count() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};