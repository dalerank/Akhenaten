#pragma once

#include "building/building.h"

class building_irrigation_ditch : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_IRRIGATION_DITCH, building_irrigation_ditch, building_impl)

    struct preview : building_planer_renderer {
        virtual bool can_construction_start(build_planner &p, tile2i start) const override;
        virtual int construction_update(build_planner &p, tile2i start, tile2i end) const override;
        virtual int construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const override;
        virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual bool ghost_allow_tile(build_planner &p, tile2i tile) const;
        bool map_is_straight_road_for_canal(tile2i tile) const;
        bool is_road_tile_for_canal(tile2i tile, int gate_orientation) const;
    };

    virtual void on_place_checks() override;
};