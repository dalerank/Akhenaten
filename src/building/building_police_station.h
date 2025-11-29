#pragma once

#include "building/building.h"
#include "core/vec2i.h"
#include "core/svector.h"

class building_police_station : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_POLICE_STATION, building_police_station, building_impl)

    struct static_params : building_static_params {
        vec2i weapon_spot_pos;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        bool weapon_requested_this_month;
    } BUILDING_RUNTIME_DATA_T;

    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual void update_month() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_POLICE; }
    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool add_resource(e_resource resource, int amount) override;

    bool request_weapons_if_need();
    void draw_weapons(vec2i point, color color_mask, painter &ctx);
};

ANK_CONFIG_STRUCT(building_police_station::static_params, weapon_spot_pos);