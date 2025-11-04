#include "js/js_game.h"
#include "city/city.h"

int __city_count_active_buildings(int btype) {
    return g_city.buildings.count_active((e_building_type)btype);
}
ANK_FUNCTION_1(__city_count_active_buildings);

bool __city_building_is_temple(int bid) {
    building *b = building_get(bid);
    return !!b->dcast_temple();
}
ANK_FUNCTION_1(__city_building_is_temple);

void __city_set_advisor_available(int advisor, int available) {
    g_city.set_advisor_available((e_advisor)advisor, (e_availability)available);
}
ANK_FUNCTION_2(__city_set_advisor_available)
