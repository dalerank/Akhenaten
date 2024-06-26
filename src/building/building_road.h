#pragma once

#include "building/building.h"

class building_road : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_ROAD, building_road)
    building_road(building &b) : building_impl(b) {}

    virtual void on_place_checks() override;

    static int place(bool measure_only, tile2i start, tile2i end);
    static void ghost_preview(tile2i tile, vec2i pixel, painter &ctx);
    static void set_image(tile2i tile);
};