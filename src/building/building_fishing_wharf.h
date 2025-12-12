#pragma once

#include "building/building_wharf.h"

class building_fishing_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_FISHING_WHARF, building_fishing_wharf, building_wharf)

    virtual building_fishing_wharf *dcast_fishing_wharf() override { return this; }

    struct preview : public building_planer_renderer {
        virtual int construction_update(build_planner &planer, tile2i start, tile2i end) const override;
        virtual void setup_preview_graphics(build_planner &planer) const override;
    };

    struct static_params : public building_static_params {
        uint16_t max_storage;
        uint8_t wait_time_multiplier;
        uint8_t wait_time_base;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t : public building_wharf::runtime_data_t {
        uint8_t no_fishing_points_warning_shown;  // Counter to limit warning frequency
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_count() const override;
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void update_graphic() override;
    virtual void spawn_figure() override;
    virtual void on_place_checks() override;
    virtual void on_undo() override;
    virtual void update_map_orientation(int orientation) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_WHARF; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void highlight_waypoints() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
};
ANK_CONFIG_STRUCT(building_fishing_wharf::static_params, max_storage, wait_time_multiplier, wait_time_base)