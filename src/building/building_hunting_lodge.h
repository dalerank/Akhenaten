#pragma once

#include "building/building.h"

class building_hunting_lodge : public building_impl {
public:
    building_hunting_lodge(building &b) : building_impl(b) {}
    virtual void on_create(int orientation) override;
    virtual void window_info_background(object_info &ctx) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_HUNTER_LOUDGE; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    int spawn_timer();
    bool can_spawn_ostrich_hunter();
};