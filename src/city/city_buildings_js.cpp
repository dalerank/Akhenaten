#include "js/js_game.h"

#include "city/city.h"
#include "building/building_house.h"
#include "building/building_bazaar.h"
#include "city/object_info.h"

extern object_info def_object_info;

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

void __building_add_fire_damage(int bid, int damage) {
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_fire, damage);
    }
}
ANK_FUNCTION_2(__building_add_fire_damage)

void __building_add_collapse_damage(int bid, int damage) {
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_collapse, damage);
    }
}
ANK_FUNCTION_2(__building_add_collapse_damage)

bool __building_has_road_access(int bid) { return building_get(bid)->has_road_access; }
ANK_FUNCTION_1(__building_has_road_access)

int __city_get_object_info_building_id() { return def_object_info.bid;}
ANK_FUNCTION(__city_get_object_info_building_id)

int __city_get_object_info_group() { return def_object_info.group_id; }
ANK_FUNCTION(__city_get_object_info_group)

int __building_get_worker_percentage(int bid) { return building_get(bid)->worker_percentage();}
ANK_FUNCTION_1(__building_get_worker_percentage)

int __building_get_num_workers(int bid) { return building_get(bid)->num_workers;}
ANK_FUNCTION_1(__building_get_num_workers)

bool __building_has_figure(int bid, int index) { return building_get(bid)->has_figure(index); }
ANK_FUNCTION_2(__building_has_figure)

int __building_get_figure_id(int bid, int index) { return building_get(bid)->get_figure(index)->id; }
ANK_FUNCTION_2(__building_get_figure_id)

int __bazaar_get_amount(int bid, int index) { auto b = building_get(bid)->dcast_bazaar(); return b ? b->get_food_amount(index) : 0; }
ANK_FUNCTION_2(__bazaar_get_amount)

bool __bazaar_idx_accepted(int bid, int index) { auto b = building_get(bid)->dcast_bazaar(); return b ? b->idx_accepted(index) : false; }
ANK_FUNCTION_2(__bazaar_idx_accepted)

bool __bazaar_res_accepted(int bid, e_resource res) { auto b = building_get(bid)->dcast_bazaar(); return b ? b->res_accepted(res) : false; }
ANK_FUNCTION_2(__bazaar_res_accepted)

int __bazaar_resource_amount(int bid, e_resource resource) { auto b = building_get(bid)->dcast_bazaar(); return b ? b->get_resource_amount(resource) : 0; }
ANK_FUNCTION_2(__bazaar_resource_amount)