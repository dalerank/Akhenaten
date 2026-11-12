#pragma once

#include "building/building_entertainment.h"

class building_zoo : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_ZOO, building_zoo, building_entertainment)

    virtual bool add_resource(e_resource resource, int amount, figure_id fid = 0) override;
    virtual void add_ambient_sound(int direction) const override;
};
