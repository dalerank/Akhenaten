#pragma once

#include "building/building_industry.h"

class building_brewery : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_BREWERY_WORKSHOP, building_brewery, building_industry)
    virtual building_brewery *dcast_brewery() override { return this; }

    struct static_params : public building_static_params {
        uint8_t water_amount_for_production;
        uint8_t max_water_storage;
    } BUILDING_STATIC_DATA_T;

    virtual bool is_workshop() const override { return true; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_BREWERY_WORKSHOP; }
    virtual bool can_play_animation() const override;
    virtual void update_preproduction() override;
    virtual void update_production() override;
    virtual void start_production() override;
    virtual void production_started() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void on_create(int orientation) override;
    
    void update_water_supply();
    bool has_water_access() const;
    int water_stored() const { return runtime_data().unk_b[0]; }
    void set_water_stored(uint8_t value) { runtime_data().unk_b[0] = value; }
};
ANK_CONFIG_STRUCT(building_brewery::static_params, water_amount_for_production, max_water_storage)