#pragma once

#include "building/building_type.h"
#include "core/custom_span.hpp"

enum e_temple_compex_upgrade : uint8_t;

struct city_temple_complexes_t {
    static span_const<e_building_type> types();

    building_id id(e_building_type type) const;
    building_id any_id() const;
    bool has_any() const;
    bool has_upgrade(e_building_type type, e_temple_compex_upgrade upgrade) const;
    void ra_yearly_favour();
};

city_temple_complexes_t& city_temple_complexes();
