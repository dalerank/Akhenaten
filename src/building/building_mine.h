#pragma once

#include "building/building_industry.h"

class building_mine : public building_industry {
public:
    building_mine(building &b) : building_industry(b) {}
    virtual building_mine *dcast_mine() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

