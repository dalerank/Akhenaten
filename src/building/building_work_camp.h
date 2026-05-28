#pragma once

#include "building/building.h"
#include "city/object_info.h"

class building_work_camp : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WORK_CAMP, building_work_camp, building_impl)
    building_work_camp *dcast_work_camp() override { return this; }
};
