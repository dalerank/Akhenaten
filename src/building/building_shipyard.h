#pragma once

#include "building/building_industry.h"

class building_shipyard : public building_industry {
public:
    BUILDING_METAINFO_RT(BUILDING_SHIPWRIGHT, building_shipyard)

    building_shipyard(building &b) : building_industry(b) {}
    virtual building_shipyard *dcast_shipyard() override { return this; }

    struct static_params : public buildings::model_t<building_shipyard> {
        int warship_progress_cost;
        int transport_progress_cost;
        int fishingboat_progress_cost;
        virtual void load(archive arch) override;
        virtual int planer_construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    };

    struct runtime_data_t {
        int dock_tiles[2];
        e_figure_type process_type;
        bool reparing;
        short progress;
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void update_graphic() override;
    virtual void update_count() const override;
    virtual void spawn_figure() override;
    virtual void update_map_orientation(int orientation);
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STORAGE_YARD; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void highlight_waypoints() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool add_resource(e_resource resource, int amount) override;
    virtual void set_water_access_tiles(const water_access_tiles &tiles) override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};