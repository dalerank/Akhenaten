#pragma once

#include "city/object_info.h"
#include "building/building.h"
#include "window/window_building_info.h"

class building_architect_post : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_ARCHITECT_POST, building_architect_post)

    building_architect_post(building &b) : building_impl(b) {}
    virtual building_architect_post *dcast_architect_post() override { return this; }

    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_DAMAGE; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_ENGINEERS_POST; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

struct info_window_architect_post : public building_info_window_t<info_window_architect_post> {
    virtual void window_info_background(object_info& c) override {
        building_info_window::common_info_background(c);
    }

    virtual bool check(object_info& c) override {
        return c.building_get()->dcast_architect_post();
    }
};