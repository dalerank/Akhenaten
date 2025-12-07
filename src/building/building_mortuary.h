#pragma once

#include "building/building.h"

class building_mortuary : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_MORTUARY, building_mortuary, building_impl)

    struct static_params : public building_static_params {
        uint16_t max_serve_clients;
        uint16_t linen_required_for_spawn;
        uint16_t linen_required_for_animation;
        uint16_t monthly_linen_consumption;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t : public no_copy_assignment {
        int residents_served_this_month;
        int residents_served_this_year;
        int total_residents_served;
        int months_active;
    } BUILDING_RUNTIME_DATA_T;

    virtual building_mortuary *dcast_mortuary() override { return this; }

    virtual void spawn_figure() override;
    virtual void on_place_checks() override;
    virtual void update_month() override;
    virtual void update_year() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_MORTUARY; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_MORTUARY; }
    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool can_play_animation() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_graphic() override;
    virtual void update_count() const override;
};
ANK_CONFIG_STRUCT(building_mortuary::static_params, max_serve_clients, linen_required_for_spawn, linen_required_for_animation, monthly_linen_consumption)

