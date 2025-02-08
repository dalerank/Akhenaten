#pragma once

#include "building/building.h"

class building_temple_complex_altar : public building_impl {
public:
    building_temple_complex_altar(building &b) : building_impl(b) {}
    virtual building_temple_complex_altar *dcast_temple_complex_altar() override { return this; }

    virtual void on_place_checks() override {
        // nothing
    }
};

class building_temple_complex_altar_ra : public building_temple_complex_altar {
public:
    BUILDING_METAINFO(BUILDING_TEMPLE_COMPLEX_ALTAR_AMON, building_temple_complex_altar_ra)
    building_temple_complex_altar_ra(building &b) : building_temple_complex_altar(b) {}
};