#pragma once

#include "building/building_industry.h"

class building_fishing_wharf : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_FISHING_WHARF, building_fishing_wharf)

    building_fishing_wharf(building &b) : building_industry(b) {}
    virtual building_fishing_wharf *dcast_fishing_wharf() override { return this; }

    struct static_params : public buildings::model_t<building_fishing_wharf> {
        virtual void load(archive arch) override;
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_count() const override;
    virtual void update_day() override;
    virtual void update_graphic() override;
    virtual void on_tick(bool refresh_only) override;
    virtual void spawn_figure() override;
    virtual void on_place_checks() override;
    virtual void on_undo() override;
    virtual void update_map_orientation(int orientation) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_WHARF; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void highlight_waypoints() override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};