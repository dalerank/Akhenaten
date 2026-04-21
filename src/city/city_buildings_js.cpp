#include "js/js_game.h"

#include "city/city.h"
#include "city/city_warnings.h"
#include "city/constants.h"
#include "empire/empire.h"
#include "building/building_house.h"
#include "grid/grid.h"
#include "core/log.h"
#include "game/game_events.h"
#include "city/object_info.h"
#include "window/window_info.h"
#include "building/building.h"
#include "building/monuments.h"
#include "window/building/distribution.h"
#include "city_buildings.h"
#include "game/resource.h"
#include "core/profiler.h"
#include "core/svector.h"

#include <algorithm>
#include <optional>

static svector<building_id, 512> g_city_monuments_advisor_cache;

static void city_monuments_advisor_cache_fill() {
    g_city_monuments_advisor_cache.clear();
    for (auto &b : city_buildings()) {
        if (!b.is_valid() || !b.is_monument()) {
            continue;
        }
        if (&b != b.main()) {
            continue;
        }
        g_city_monuments_advisor_cache.push_back(b.id);
    }
}

int __city_monuments_list_refresh() {
    city_monuments_advisor_cache_fill();
    return (int)g_city_monuments_advisor_cache.size();
}
ANK_FUNCTION(__city_monuments_list_refresh)

int __city_monuments_list_count() {
    return (int)g_city_monuments_advisor_cache.size();
}
ANK_FUNCTION(__city_monuments_list_count)

int __city_monuments_list_id_at(int index) {
    if (index < 0 || index >= (int)g_city_monuments_advisor_cache.size()) {
        return 0;
    }
    return g_city_monuments_advisor_cache[index];
}
ANK_FUNCTION_1(__city_monuments_list_id_at)

int __building_monument_phase_code(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || !b->is_monument()) {
        return -99;
    }
    building_monument *m = b->main()->dcast_monument();
    if (!m) {
        return -99;
    }
    return m->runtime_data().phase;
}
ANK_FUNCTION_1(__building_monument_phase_code)

int __building_monument_phases_total(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || !b->is_monument()) {
        return 0;
    }
    building_monument *m = b->main()->dcast_monument();
    return m ? m->phases() : 0;
}
ANK_FUNCTION_1(__building_monument_phases_total)

int __building_monument_material_pct_min(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || !b->is_monument()) {
        return 0;
    }
    building_monument *m = b->main()->dcast_monument();
    if (!m || m->runtime_data().phase == MONUMENT_FINISHED) {
        return 100;
    }
    auto &d = m->runtime_data();
    int min_pct = 100;
    bool any = false;
    for (int ri = (int)RESOURCES_MIN; ri <= (int)RESOURCES_MAX; ++ri) {
        const auto r = (e_resource)ri;
        if (m->needs_resource(r) <= 0) {
            continue;
        }
        any = true;
        min_pct = std::min(min_pct, (int)d.resources_pct[r]);
    }
    return any ? min_pct : 100;
}
ANK_FUNCTION_1(__building_monument_material_pct_min)

int __city_count_industry_active(int resource) {
    return g_city.buildings.count_industry_active((e_resource)resource);
}
ANK_FUNCTION_1(__city_count_industry_active)

int __city_count_industry_total(int resource) {
    return g_city.buildings.count_industry_total((e_resource)resource);
}
ANK_FUNCTION_1(__city_count_industry_total)

void __city_show_warning(pcstr id) {
    events::emit(event_construction_warning{ id });
}
ANK_FUNCTION_1(__city_show_warning)

int __map_rubble_building_type_at_grid(int grid_offset) {
    return map_rubble_building_type(grid_offset);
}
ANK_FUNCTION_1(__map_rubble_building_type_at_grid)

int __map_rubble_building_type(int bid) {
    building *b = building_get(bid);
    return b ? map_rubble_building_type(b->tile.grid_offset()) : 0;
}
ANK_FUNCTION_1(__map_rubble_building_type)

bool __city_resource_can_produce(int resource) {
    return g_city.can_produce_resource((e_resource)resource);
}
ANK_FUNCTION_1(__city_resource_can_produce)

bool __city_resource_can_import(int resource, bool check_if_import) {
    return g_empire.can_import_resource((e_resource)resource, check_if_import);
}
ANK_FUNCTION_2(__city_resource_can_import)

int __city_resource_trade_status(int resource) {
    return (int)g_city.resource.trade_status[(e_resource)resource];
}
ANK_FUNCTION_1(__city_resource_trade_status)

int __city_count_active_buildings(int btype) {
    return g_city.buildings.count_active((e_building_type)btype);
}
ANK_FUNCTION_1(__city_count_active_buildings);

int __city_count_total_buildings(int btype) {
    return g_city.buildings.count_total((e_building_type)btype);
}
ANK_FUNCTION_1(__city_count_total_buildings);

bool __city_building_is_temple(int bid) {
    building *b = building_get(bid);
    return !!b->dcast_temple();
}
ANK_FUNCTION_1(__city_building_is_temple);

void __city_set_advisor_available(int advisor, int available) {
    g_city.set_advisor_available((e_advisor)advisor, (e_availability)available);
}
ANK_FUNCTION_2(__city_set_advisor_available)

int __city_is_advisor_available(int advisor) {
    return (int)g_city.is_advisor_available((e_advisor)advisor);
}
ANK_FUNCTION_1(__city_is_advisor_available)

bool __city_building_is_tax_collector(int bid) {
    building *b = building_get(bid);
    return !!b->dcast_tax_collector();
}
ANK_FUNCTION_1(__city_building_is_tax_collector)

int __city_get_random_building_id() {
    hvector<building_id, 128> buildings;
    buildings_valid_do([&] (building &b) {
        if (b.is_valid()) {
            buildings.push_back(b.id);
        }
    });

    if (buildings.empty()) {
        return 0;
    }

    return buildings[rand() % buildings.size()];
}
ANK_FUNCTION(__city_get_random_building_id)

int __city_get_random_house_id() {
    hvector<building_id, 128> houses;
    buildings_valid_do([&] (building &b) {
        auto house = b.dcast_house();
        if (house && house->house_population() > 0) {
            houses.push_back(b.id);
        }
    });

    if (houses.empty()) {
        return 0;
    }

    return houses[rand() % houses.size()];
}
ANK_FUNCTION(__city_get_random_house_id)

int __building_at(int x, int y) {
    return map_building_at(tile2i(x, y));
}
ANK_FUNCTION_2(__building_at)

bvariant __map_grid_get_area(tile2i tile, int size, int radius) {
    return bvariant(map_grid_get_area(tile2i(tile), size, radius));
}
ANK_FUNCTION_3(__map_grid_get_area)

std::optional<bvariant> __city_get_object_info_property(pcstr property) {
    const object_info& o = common_info_window::get_object_info();
    return archive_helper::get(o, property, true);
}
ANK_FUNCTION_1(__city_get_object_info_property)

int __city_get_random_building_id_by_type(int type) { return building_id_random((e_building_type)type); }
ANK_FUNCTION_1(__city_get_random_building_id_by_type)

bool __city_resource_is_mothballed(int resource) {
    return g_city.resource.is_mothballed((e_resource)resource);
}
ANK_FUNCTION_1(__city_resource_is_mothballed)

void window_building_distribution_set_bid(int bid) {
    g_window_building_distribution.bid = bid;
}
ANK_FUNCTION_1(window_building_distribution_set_bid)