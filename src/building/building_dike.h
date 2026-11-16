#pragma once

#include "building/building.h"
#include "grid/image_context.h"

class building_dike : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_DIKE, building_dike, building_impl)

    struct preview : building_planer_renderer {
        virtual bool can_construction_start(build_planner &p, tile2i start) const override;
        virtual int construction_update(build_planner &p, tile2i start, tile2i end) const override;
        virtual int construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const override;
    };


    static int place_dike(bool measure_only, tile2i start, tile2i end);
    static bool set_dike(tile2i tile);
    static bool can_place_on_tile(tile2i tile);
    static void set_image(tile2i tile);
    static void update_area_dikes(tile2i tile, int size);
    static terrain_image get_terrain_image(tile2i tile);
};
