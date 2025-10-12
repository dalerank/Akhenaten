#pragma once

#include "building/building.h"

class building_irrigation_ditch : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_IRRIGATION_DITCH, building_irrigation_ditch, building_impl)

    struct preview : building_planer_renderer {
        virtual bool can_construction_start(build_planner &p, tile2i start) const override;
    };

    struct static_params : public building_model {
        virtual int planer_construction_update(build_planner &p, tile2i start, tile2i end) const override;
        virtual int planer_construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const override;
        virtual void planer_ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;

        bool map_is_straight_road_for_canal(tile2i tile) const;
        bool is_road_tile_for_canal(tile2i tile, int gate_orientation) const;
    } BUILDING_STATIC_DATA_T;

    virtual void on_place_checks() override;
};