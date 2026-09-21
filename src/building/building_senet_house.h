#pragma once

#include "building/building_entertainment.h"

class building_senet_house : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_SENET_HOUSE, building_senet_house, building_entertainment)
    building_senet_house* dcast_senet_house() override { return this; }

    virtual void on_destroy() override;
    virtual void spawn_figure() override;
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};


class building_bullfight_school : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_BULLFIGHT_SCHOOL, building_bullfight_school, building_entertainment)
};