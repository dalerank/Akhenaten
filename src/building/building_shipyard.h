#pragma once

#include "building/building_industry.h"

class building_shipyard : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_SHIPWRIGHT, building_shipyard)

    building_shipyard(building &b) : building_industry(b) {}
    virtual building_shipyard *dcast_shipyard() override { return this; }

    struct static_params : public buildings::model_t<building_shipyard> {
        virtual void load(archive arch) override;
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_count() const override;
    virtual void window_info_background(object_info &ctx) override;
    virtual void spawn_figure() override;
    virtual void update_map_orientation(int orientation);
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STORAGE_YARD; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void highlight_waypoints() override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};