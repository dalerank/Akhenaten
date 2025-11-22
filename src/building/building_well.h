#pragma once

#include "building/building.h"
#include "window/window_building_info.h"

class building_well : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WELL, building_well, building_impl)

    virtual building_well *dcast_well() override { return this; }

    struct static_params : public building_static_params {
        uint8_t desirability_range_check;
        uint8_t desirability_fancy;
        uint8_t unnecessary_range_check;
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    virtual void update_graphic() override;
    virtual void update_month() override;
    virtual bool need_road_access() const override { return false; }
    virtual void on_place_checks() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_WELL; }
    virtual bool can_play_animation() const override;
};
ANK_CONFIG_STRUCT(building_well::static_params, desirability_range_check, desirability_fancy)

struct well_info_window : public building_info_window_t<well_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override;
};