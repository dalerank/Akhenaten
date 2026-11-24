#pragma once

#include "building/building_type.h"
#include "core/custom_span.hpp"

enum e_temple_compex_upgrade : uint8_t;
struct city_buildings_t;
struct kingdome_state;

struct temple_complexes_context {
    const city_buildings_t& buildings;
    kingdome_state& kingdome;
};

class temple_complexes_system {
public:
    explicit temple_complexes_system(const temple_complexes_context& ctx) : _ctx(ctx) {}

    static span_const<e_building_type> types();

    building_id id(e_building_type type) const;
    building_id any_id() const;
    bool has_any() const;
    bool has_upgrade(e_building_type type, e_temple_compex_upgrade upgrade) const;
    void ra_yearly_favour();

private:
    temple_complexes_context _ctx;
};

temple_complexes_system city_temple_complexes();
