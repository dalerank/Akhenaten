#pragma once

#include "building/building_wharf.h"

class building_fishing_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_FISHING_WHARF, building_fishing_wharf)

    building_fishing_wharf(building &b) : building_wharf(b) {}
    virtual building_fishing_wharf *dcast_fishing_wharf() override { return this; }

    struct static_params : public buildings::model_t<building_fishing_wharf> {
        virtual void load(archive arch) override;
        virtual int planer_construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    };

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

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};