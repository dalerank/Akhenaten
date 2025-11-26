#pragma once

#include "building/building.h"

class building_mortuary : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_MORTUARY, building_mortuary, building_impl)

    struct static_params : public building_static_params {
        uint16_t max_serve_clients;
    } BUILDING_STATIC_DATA_T;

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_MORTUARY; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_MORTUARY; }
    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_graphic() override;
    virtual void update_count() const override;
};
ANK_CONFIG_STRUCT(building_mortuary::static_params, max_serve_clients)

