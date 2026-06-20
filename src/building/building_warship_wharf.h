#pragma once

#include "building/building_wharf.h"

class building_warship_wharf : public building_wharf {
public:
    BUILDING_METAINFO(BUILDING_WARSHIP_WHARF, building_warship_wharf, building_wharf)

    virtual building_warship_wharf *dcast_warship_wharf() override { return this; }

    virtual void spawn_figure() override;
    virtual void update_month() override;
};