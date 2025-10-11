#pragma once

#include "building/building_industry.h"

class building_brewery : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_BREWERY_WORKSHOP, building_brewery, building_industry)

    virtual building_brewery *dcast_brewery() override { return this; }

    struct static_params : public building_model {
    } BUILDING_STATIC_DATA_T;

    virtual bool is_workshop() const override { return true; }
    virtual e_overlay get_overlay() const override { return OVERLAY_BREWERY; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }
};
ANK_CONFIG_STRUCT(building_brewery::static_params, meta)