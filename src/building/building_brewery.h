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
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_count() const override;
    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }

    virtual resources_vec required_resource() const override { return {RESOURCE_BARLEY}; }
};