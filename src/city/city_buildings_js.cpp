#include "js/js_game.h"

#include "city/city.h"
#include "building/building_house.h"

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