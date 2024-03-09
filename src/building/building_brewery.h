#pragma once

#include "building/building.h"

class building_brewery : public building_impl {
public:
    building_brewery(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual bool is_workshop() const override { return true; }
    virtual e_overlay get_overlay() const { return OVERLAY_BREWERY; }
    virtual void window_info_background(object_info &c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int ready_production() const { return 10; }
    virtual building_brewery *dcast_brewery() { return this; }

    virtual resources_vec required_resource() const override { return {RESOURCE_BARLEY}; }
};