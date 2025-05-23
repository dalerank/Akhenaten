#pragma once

#include "building/building.h"

class building_plaza : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_PLAZA, building_plaza, building_impl)

    struct static_params : public buildings::model_t<building_plaza> {
        int planer_place(build_planner &planer, tile2i start, tile2i end) const;

        virtual int planer_construction_update(build_planner &p, tile2i start, tile2i end) const override;
        virtual int planer_construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
    };

    virtual building_plaza *dcast_plaza() override { return this; }

    static void draw_info(object_info &c);
    static void set_image(int grid_offset);
};