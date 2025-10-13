#pragma once

#include "building/building.h"

class building_burning_ruin : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_BURNING_RUIN, building_burning_ruin, building_impl)
    virtual building_burning_ruin *dcast_burning_ruin() override { return this; }

    struct static_params : public building_static_params {
        int fire_animations;
    } BUILDING_STATIC_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_tick(bool refresh_only) override;
    virtual bool can_play_animation() const override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_BURNING_RUIN; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    bool update();

    tile2i can_be_accessed();

    static void update_all_ruins();
    static custom_span<uint16_t> get_all();
    static std::pair<int, tile2i> get_closest_from(tile2i tile);
};
ANK_CONFIG_STRUCT(building_burning_ruin::static_params, fire_animations)