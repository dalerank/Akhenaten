#pragma once

#include "building/building.h"

class building_apothecary : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_APOTHECARY, building_apothecary, building_impl)
    virtual building_apothecary *dcast_apothecary() override { return this; }

    struct static_params : public building_static_params {
        int max_serve_clients;
    } BUILDING_STATIC_DATA_T;

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_APOTHECARY; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_APOTHECARY; }
    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_graphic() override;
};
ANK_CONFIG_STRUCT(building_apothecary::static_params, max_serve_clients)

