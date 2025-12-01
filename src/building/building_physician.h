#pragma once

#include "building/building.h"

class building_physician : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_PHYSICIAN, building_physician, building_impl)

    struct static_params : public building_static_params {
        int max_serve_clients;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t : public no_copy_assignment {
        int residents_served_this_month;
    } BUILDING_RUNTIME_DATA_T;

    virtual building_physician *dcast_physician() override { return this; }

    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual void update_month() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_PHYSICIAN; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};
ANK_CONFIG_STRUCT(building_physician::static_params, max_serve_clients)