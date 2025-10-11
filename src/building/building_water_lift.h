#pragma once

#include "building/building.h"

class building_water_lift : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WATER_LIFT, building_water_lift, building_impl)

    struct static_params : public building_model {
        virtual void planer_setup_preview_graphics(build_planner &planer) const override;
        virtual int planer_construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        int input_tiles[2];
        int output_tiles[2];
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void update_day() override;
    virtual int animation_speed(int speed) const override;
    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_POLICE; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_map_orientation(int orientation) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void update_graphic() override;
    virtual void highlight_waypoints() override;

    void update_inout_tiles();
};