#pragma once

#include "building/building.h"

class building_temple : public building_impl {
public:
    building_temple(building &b) : building_impl(b) {}

    //virtual void on_create() override;
    virtual e_overlay get_overlay() const override;
    virtual e_sound_channel_city sound_channel() const override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual const static_params &params() const override;
    const animation_t &anim(pcstr key) const;
};