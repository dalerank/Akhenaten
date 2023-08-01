#pragma once

#include "building/type.h"

struct building_properties {
    int size;
    int fire_proof;
    int image_collection;
    int image_group;
    int image_offset;
};

const building_properties* building_properties_for_type(int type);
