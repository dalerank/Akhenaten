#pragma once

#include "building/building_entertainment.h"

class building_zoo : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_ZOO, building_zoo, building_entertainment)

    virtual void spawn_figure() override;
    virtual bool add_resource(e_resource resource, int amount, figure_id fid = 0) override;

    static int resource_consume_amount();
};
