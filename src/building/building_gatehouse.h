#pragma once

#include "building/building.h"

class building_gatehouse : public building_impl {
public:
    building_gatehouse(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
};

class building_brick_gatehouse : public building_gatehouse {
public:
    BUILDING_METAINFO(BUILDING_BRICK_GATEHOUSE, building_brick_gatehouse, building_gatehouse)
};

class building_mud_gatehouse : public building_gatehouse {
public:
    BUILDING_METAINFO(BUILDING_MUD_GATEHOUSE, building_mud_gatehouse, building_gatehouse)

    virtual void window_info_background(object_info &c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_map_orientation(int orientation) override;
};