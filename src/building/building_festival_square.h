#pragma once

#include "building/building.h"

class building_festival_square : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FESTIVAL_SQUARE, building_festival_square)

    building_festival_square(building &b) : building_impl(b) {}
    virtual building_festival_square *dcast_festival_square() override { return this; }

    struct static_params : public buildings::model_t<building_festival_square> {
        int square;
        virtual void load(archive arch) override;
        virtual void planer_setup_preview_graphics(build_planner &planer) const override;
        virtual void planer_ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void update_day() override;
    virtual void on_undo() override;
    virtual void on_post_load() override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};