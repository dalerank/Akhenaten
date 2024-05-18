#pragma once

#include "building/building.h"

class building_plaza : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_PLAZA, building_plaza)

    building_plaza(building &b) : building_impl(b) {}
    virtual building_plaza *dcast_plaza() override { return this; }

    static int place(tile2i start, tile2i end);
    static void draw_info(object_info &c);
};