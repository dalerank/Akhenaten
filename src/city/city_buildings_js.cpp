#include "js/js_game.h"

#include "city/city.h"
#include "city/city_warnings.h"
#include "city/constants.h"
#include "empire/empire.h"
#include "building/building_house.h"
#include "building/building_bazaar.h"
#include "grid/grid.h"
#include "core/log.h"
#include "city/object_info.h"
#include "window/window_info.h"
#include "building/building.h"
#include "core/profiler.h"
#include "game/game_events.h"

int __city_count_industry_active(int resource) {
    return g_city.buildings.count_industry_active((e_resource)resource);
}
ANK_FUNCTION_1(__city_count_industry_active)

void __city_show_warning(pcstr id) {
    events::emit(event_construction_warning{ id });
}
ANK_FUNCTION_1(__city_show_warning)

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

bool __building_is_valid(int bid) {
    building* b = building_get(bid);
    return b && b->is_valid();
}
ANK_FUNCTION_1(__building_is_valid)

int __building_des_influence_value(int bid) {
    building* b = building_get(bid);
    return b ? (int)b->des_influence.value : 0;
}
ANK_FUNCTION_1(__building_des_influence_value)

int __building_des_influence_step_size(int bid) {
    building* b = building_get(bid);
    return b ? b->des_influence.step_size : 0;
}
ANK_FUNCTION_1(__building_des_influence_step_size)

int __building_des_influence_range(int bid) {
    building* b = building_get(bid);
    return b ? b->des_influence.range : 0;
}
ANK_FUNCTION_1(__building_des_influence_range)

int __building_stored_resource(int bid, int resource) { return building_get(bid)->stored_amount((e_resource)resource); }
ANK_FUNCTION_2(__building_stored_resource)

int __building_get_overlay(int bid) { return building_get(bid)->get_overlay(); }
ANK_FUNCTION_1(__building_get_overlay)

int __city_get_object_info_building_id() { return common_info_window::get_object_info().bid;}
ANK_FUNCTION(__city_get_object_info_building_id)

int __city_get_object_info_group() { return common_info_window::get_object_info().group_id; }
ANK_FUNCTION(__city_get_object_info_group)

int __building_get_worker_percentage(int bid) { return building_get(bid)->worker_percentage();}
ANK_FUNCTION_1(__building_get_worker_percentage)

int __building_get_num_workers(int bid) { return building_get(bid)->num_workers;}
ANK_FUNCTION_1(__building_get_num_workers)

bool __building_has_figure(int bid, int index) { return building_get(bid)->has_figure(index); }
ANK_FUNCTION_2(__building_has_figure)

int __building_get_figure_id(int bid, int index) { return building_get(bid)->get_figure(index)->id; }
ANK_FUNCTION_2(__building_get_figure_id)

int __bazaar_idx_amount(int bid, int index) { auto b = building_get(bid)->dcast_bazaar(); return b ? b->get_idx_amount(index) : 0; }
ANK_FUNCTION_2(__bazaar_idx_amount)

bool __bazaar_idx_accepted(int bid, int index) { auto b = building_get(bid)->dcast_bazaar(); return b ? b->idx_accepted(index) : false; }
ANK_FUNCTION_2(__bazaar_idx_accepted)

bool __bazaar_res_accepted(int bid, e_resource res) { auto b = building_get(bid)->dcast_bazaar(); return b ? b->res_accepted(res) : false; }
ANK_FUNCTION_2(__bazaar_res_accepted)

int __bazaar_resource_amount(int bid, e_resource resource) { auto b = building_get(bid)->dcast_bazaar(); return b ? b->get_resource_amount(resource) : 0; }
ANK_FUNCTION_2(__bazaar_resource_amount)

int __city_get_random_building_id_by_type(int type) { return building_id_random((e_building_type)type); }
ANK_FUNCTION_1(__city_get_random_building_id_by_type)

int __building_get_state(int bid) { return (int)building_get(bid)->state; }
ANK_FUNCTION_1(__building_get_state)

int __building_mothball_toggle(int bid) {
    building* b = building_get(bid);
    return b->max_workers ? b->mothball_toggle() : 0;
}
ANK_FUNCTION_1(__building_mothball_toggle)

bool __building_can_play_animation(int bid) { return building_get(bid)->dcast()->can_play_animation(); }
ANK_FUNCTION_1(__building_can_play_animation)

void __building_set_animation(int bid, pcstr animkey) { building_get(bid)->dcast()->set_animation(animkey); }
ANK_FUNCTION_2(__building_set_animation)

bool __building_common_spawn_roamer(int bid, int figure_type, int min_houses_coverage, int action) {
    return building_get(bid)->dcast()->common_spawn_roamer((e_figure_type)figure_type, min_houses_coverage, (e_figure_action)action);
}
ANK_FUNCTION_4(__building_common_spawn_roamer)

bool __city_resource_is_mothballed(int resource) {
    return g_city.resource.is_mothballed((e_resource)resource);
}
ANK_FUNCTION_1(__city_resource_is_mothballed)