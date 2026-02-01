#include "building_granary.h"
#include "city/city_buildings.h"
#include "js/js_game.h"

int __granary_get_amount(int bid, int resource_type) {
    building_granary *granary = building_get(bid)->dcast_granary();
    return granary ? granary->amount((e_resource)resource_type) : 0;
}
ANK_FUNCTION_2(__granary_get_amount)

int __granary_get_total_stored(int bid) {
    building_granary *granary = building_get(bid)->dcast_granary();
    return granary ? granary->total_stored() : 0;
}
ANK_FUNCTION_1(__granary_get_total_stored)

