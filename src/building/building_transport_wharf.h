#pragma once

#include "building/building_wharf.h"

class building_transport_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_TRANSPORT_WHARF, building_transport_wharf, building_wharf)

    virtual building_transport_wharf *dcast_transport_wharf() override { return this; }

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
    };

    struct static_params : public building_model {
        virtual int planer_construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    } BUILDING_STATIC_DATA_T;

    virtual void update_month() override;
    virtual void spawn_figure() override;
};