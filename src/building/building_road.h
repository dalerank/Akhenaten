#pragma once

#include "building/building.h"

class building_road : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_ROAD, building_road)
    building_road(building &b);

    struct static_params : public buildings::model_t<building_road> {
        virtual bool planer_can_construction_start(build_planner &p, tile2i start) const override;
        virtual int planer_construction_update(build_planner &p, tile2i start, tile2i end) const override;
        virtual int planer_construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const override;
        virtual void planer_ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    virtual void on_place_checks() override;

    static void set_image(tile2i tile);
};