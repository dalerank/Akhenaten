#pragma once

#include "building/building_industry.h"

class building_hunting_lodge : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_HUNTING_LODGE, building_hunting_lodge, building_industry)

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_HUNTER_LOUDGE; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_graphic() override;       
    virtual bool can_play_animation() const override;
    virtual int stored_amount(e_resource r) const override;

    int spawn_timer();
    bool can_spawn_ostrich_hunter();
};