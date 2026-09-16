#pragma once

#include "building/building.h"

class building_road : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_ROAD, building_road, building_impl)

    static void set_image(tile2i tile);
    static bool set_road(tile2i tile);
    static bool is_paved(tile2i tile);
};