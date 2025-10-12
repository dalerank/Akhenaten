#pragma once

#include "building/building.h"

class building_garden : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_GARDENS, building_garden, building_impl)
    virtual building_garden *dcast_garden() override { return this; }


    struct preview : building_planer_renderer {
        int place_impl(tile2i start, tile2i end, bool place) const;
        virtual int construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const override;
        virtual int construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    };

    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_GARDEN; }

    static void set_image(int grid_offset);
    static void determine_tile(int grid_offset);
};