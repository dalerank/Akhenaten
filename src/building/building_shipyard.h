#pragma once

#include "building/building_industry.h"

class building_shipyard : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_SHIPWRIGHT, building_shipyard, building_industry)

    virtual building_shipyard *dcast_shipyard() override { return this; }

    struct static_params : public building_model {
        int warship_progress_cost;
        int transport_progress_cost;
        int fishingboat_progress_cost;
        virtual int planer_construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        int dock_tiles[2];
        e_figure_type process_type;
        bool reparing;
        short progress;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void update_graphic() override;
    virtual void update_count() const override;
    virtual void spawn_figure() override;
    virtual void update_map_orientation(int orientation) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STORAGE_YARD; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void highlight_waypoints() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool add_resource(e_resource resource, int amount) override;
    virtual void set_water_access_tiles(const water_access_tiles &tiles) override;
};
ANK_CONFIG_STRUCT(building_shipyard::static_params,
    warship_progress_cost, transport_progress_cost, fishingboat_progress_cost)