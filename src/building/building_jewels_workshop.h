#pragma once

#include "building/building_industry.h"

class building_jewels_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_JEWELS_WORKSHOP, building_jewels_workshop, building_industry)

    struct static_params : public building_static_params {
        uint8_t material_reduction_per_nearby_workshop;
    } BUILDING_STATIC_DATA_T;

    virtual bool can_play_animation() const override;
    virtual void on_place_checks() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_graphic() override;
    virtual void start_production() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }

private:
    int count_nearby_workshops() const;
};
ANK_CONFIG_STRUCT(building_jewels_workshop::static_params, material_reduction_per_nearby_workshop)