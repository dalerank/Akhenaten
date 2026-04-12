#include "building_bazaar.h"

#include "city/city_buildings.h"
#include "js/js_game.h"
#include "core/profiler.h"

int __bazaar_idx_amount(int bid, int index) {
    auto b = building_get(bid)->dcast_bazaar();
    return b ? b->get_idx_amount(index) : 0;
}
ANK_FUNCTION_2(__bazaar_idx_amount)

bool __bazaar_idx_accepted(int bid, int index) {
    auto b = building_get(bid)->dcast_bazaar();
    return b ? b->idx_accepted(index) : false;
}
ANK_FUNCTION_2(__bazaar_idx_accepted)

bool __bazaar_res_accepted(int bid, e_resource res) {
    auto b = building_get(bid)->dcast_bazaar();
    return b ? b->res_accepted(res) : false;
}
ANK_FUNCTION_2(__bazaar_res_accepted)

int __bazaar_resource_amount(int bid, e_resource resource) {
    auto b = building_get(bid)->dcast_bazaar();
    return b ? b->get_resource_amount(resource) : 0;
}
ANK_FUNCTION_2(__bazaar_resource_amount)

void __bazaar_unaccept_all_goods(int bid) {
    auto b = building_get(bid)->dcast_bazaar();
    if (b) {
        b->unaccept_all_goods();
    }
}
ANK_FUNCTION_1(__bazaar_unaccept_all_goods)
