#pragma once

#include "building/building.h"
#include "window/window_building_info.h"

class building_garden : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_GARDENS, building_garden)

    building_garden(building &b) : building_impl(b) {}
    virtual building_garden *dcast_garden() override { return this; }

    struct static_params : public buildings::model_t<building_garden> {
        int place_impl(tile2i start, tile2i end) const;
        virtual int planer_construction_update(build_planner &planer, tile2i start, tile2i end) const override;
        virtual int planer_construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const override;
    };

    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_GARDEN; }

    static void set_image(int grid_offset);
    static void determine_tile(int grid_offset);
};

struct info_window_garden : public common_info_window {
    info_window_garden() {
        window_building_register_handler(this);
    }
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override;
};