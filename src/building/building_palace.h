#pragma once

#include "building/building.h"
#include "city/city_finance.h"
#include "core/svector.h"
#include "js/js_struct.h"

class building_palace : public building_impl {
public:
    using inherited = building_impl;

    building_palace(building &b) : building_impl(b) {}
    virtual building_palace *dcast_palace() override { return this; }

    struct add_resource_finance_t {
        e_building_type building = BUILDING_NONE;
        e_finance_request_type request = efinance_request_none;
    };

    struct static_params : public building_static_params {
        svector<add_resource_finance_t, 8> add_resource_finance;
    };

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

ANK_CONFIG_STRUCT(building_palace::add_resource_finance_t, building, request)
ANK_CONFIG_STRUCT(building_palace::static_params, add_resource_finance)
