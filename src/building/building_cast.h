#pragma once

class building;
class building_impl;

#include "building_fwd.h"
#include "core/smart_cast.h"

GENERATE_SMART_CAST(building_impl)
#define GENERATE_SMART_CAST_BUILDING(type) GENERATE_SMART_CAST_CUSTOM(building_##type, type)

BUILDING_CLASS_LIST(GENERATE_SMART_CAST_BUILDING)

template <typename dest_type, typename r_type = std::add_pointer_t<std::remove_pointer_t<dest_type>>>
inline r_type smart_cast(building *b);
