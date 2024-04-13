#pragma once

#include "building/building.h"

class building_brewery : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_BREWERY_WORKSHOP, building_brewery)

    building_brewery(building &b) : building_impl(b) {}
    virtual building_brewery *dcast_brewery() override { return this; }

    virtual void on_create(int orientation) override;
    virtual bool is_workshop() const override { return true; }
    virtual e_overlay get_overlay() const override { return OVERLAY_BREWERY; }
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int ready_production() const override { return 10; }

    virtual resources_vec required_resource() const override { return {RESOURCE_BARLEY}; }
};