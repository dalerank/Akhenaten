#pragma once

#include "building/building_industry.h"

class building_pottery : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_POTTERY_WORKSHOP, building_pottery)

    building_pottery(building &b) : building_industry(b) {}
    virtual building_pottery *dcast_pottery() override { return this; }

    virtual bool can_play_animation() const override;
    virtual bool is_workshop() const override { return true; }
    virtual void on_place_checks() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_POTTERY_WORKSHOP; }
    virtual void update_graphic() override;
    virtual void update_count() const override;
};