#pragma once

#include "building/building_wharf.h"

class building_warship_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_WARSHIP_WHARF, building_warship_wharf, building_wharf)

    virtual building_warship_wharf *dcast_warship_wharf() override { return this; }

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual int construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    };

    virtual void spawn_figure() override;
    virtual bool ship_moored() const override;
    virtual void update_month() override;
};