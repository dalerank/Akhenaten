#pragma once

#include "building/building.h"

class building_garden : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_GARDENS, building_garden)

    building_garden(building &b) : building_impl(b) {}
    virtual building_garden *dcast_garden() override { return this; }

    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_GARDEN; }

    static int place(tile2i start, tile2i end);
    static void set_image(int grid_offset);
    static void determine_tile(int grid_offset);
};