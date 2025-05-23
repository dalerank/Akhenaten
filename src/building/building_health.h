#pragma once

#include "building/building.h"

class building_apothecary : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_APOTHECARY, building_apothecary, building_impl)
    virtual building_apothecary *dcast_apothecary() override { return this; }

    struct static_params : public building_model {
        int max_serve_clients;
        virtual void archive_load(archive arch) override;
    } BUILDING_STATIC_DATA(static_params);

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_APOTHECARY; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_APOTHECARY; }
    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_graphic() override;
};

class building_mortuary : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_MORTUARY, building_mortuary, building_impl)

    struct static_params : public building_model {
        uint16_t max_serve_clients;
        virtual void archive_load(archive arch) override;
    } BUILDING_STATIC_DATA(static_params);

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_MORTUARY; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_MORTUARY; }
    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_graphic() override;
    virtual void update_count() const override;
};