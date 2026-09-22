#pragma once

#include "building/building.h"
#include "js/js_struct.h"

class building_palace : public building_impl {
public:
    using inherited = building_impl;

    building_palace(building &b) : building_impl(b) {}
    virtual building_palace *dcast_palace() override { return this; }

    virtual void update_count() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void spawn_figure() override;
    virtual bool add_resource(e_resource resource, int amount, figure_id fid = 0) override;
};

class building_village_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_VILLAGE_PALACE, building_village_palace, building_palace)
};

class building_town_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_TOWN_PALACE, building_town_palace, building_palace)
};

class building_city_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_CITY_PALACE, building_city_palace, building_palace)
};
