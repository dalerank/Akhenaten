#pragma once

#include "building/building_industry.h"

class building_hunting_lodge : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_HUNTING_LODGE, building_hunting_lodge, building_industry)

    struct static_params : public building_static_params {
        uint8_t spawn_delay_100_percent; 
        uint8_t spawn_delay_75_percent;
        uint8_t spawn_delay_50_percent;   
        uint8_t spawn_delay_25_percent;
        uint8_t spawn_delay_default;       // default delay for 1-24% workers
    } BUILDING_STATIC_DATA_T;

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
ANK_CONFIG_STRUCT(building_hunting_lodge::static_params, 
    spawn_delay_100_percent, spawn_delay_75_percent, spawn_delay_50_percent, 
    spawn_delay_25_percent, spawn_delay_default)