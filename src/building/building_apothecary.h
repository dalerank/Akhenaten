#pragma once

#include "building/building.h"

class building_apothecary : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_APOTHECARY, building_apothecary, building_impl)
    virtual building_apothecary *dcast_apothecary() override { return this; }

    struct static_params : public building_static_params {
        int max_serve_clients;
    } BUILDING_STATIC_DATA_T;

    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};
ANK_CONFIG_STRUCT(building_apothecary::static_params, max_serve_clients)

