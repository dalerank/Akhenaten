#pragma once

#include "building/building.h"

class building_library : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_LIBRARY, building_library, building_impl);

    virtual e_overlay get_overlay() const override { return OVERLAY_LIBRARY; }
};
