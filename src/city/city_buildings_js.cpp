#include "js/js_game.h"

#include "city/city.h"
#include "city/city_warnings.h"
#include "city/constants.h"
#include "empire/empire.h"
#include "building/building_house.h"
#include "grid/grid.h"
#include "core/core.h"
#include "core/log.h"
#include "game/game_events.h"
#include "city/object_info.h"
#include "window/window_info.h"
#include "building/building.h"
#include "core/profiler.h"

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

int __city_get_object_info_building_id() { return common_info_window::get_object_info().bid;}
ANK_FUNCTION(__city_get_object_info_building_id)

int __city_get_object_info_group() { return common_info_window::get_object_info().group_id; }
ANK_FUNCTION(__city_get_object_info_group)

int __city_get_random_building_id_by_type(int type) { return building_id_random((e_building_type)type); }
ANK_FUNCTION_1(__city_get_random_building_id_by_type)

bool __city_resource_is_mothballed(int resource) {
    return g_city.resource.is_mothballed((e_resource)resource);
}
ANK_FUNCTION_1(__city_resource_is_mothballed)