#pragma once

#include "building/building_entertainment.h"

class building_conservatory : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_CONSERVATORY, building_conservatory, building_entertainment)

    virtual building_conservatory *dcast_conservatory() override { return this; }

    struct static_params : public building_static_params {
        uint8_t spawn_interval;
    } BUILDING_STATIC_DATA_T;

    virtual void spawn_figure() override;
    virtual void update_day() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_CONSERVATORY; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};
ANK_CONFIG_STRUCT(building_conservatory::static_params, spawn_interval)