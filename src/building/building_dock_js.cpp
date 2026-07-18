#include "building_dock.h"

#include "city/city_buildings.h"
#include "js/js_game.h"
#include "core/profiler.h"

bool __dock_is_trade_accepted(int bid, int resource) {
    auto b = building_get(bid)->dcast_dock();
    return b ? b->is_trade_accepted((e_resource)resource) : false;
}
ANK_FUNCTION_2(__dock_is_trade_accepted)

void __dock_toggle_good_accepted(int bid, int resource) {
    auto b = building_get(bid)->dcast_dock();
    if (b) {
        b->toggle_good_accepted((e_resource)resource);
    }
}
ANK_FUNCTION_2(__dock_toggle_good_accepted)

void __dock_unaccept_all_goods(int bid) {
    auto b = building_get(bid)->dcast_dock();
    if (b) {
        b->unaccept_all_goods();
    }
}
ANK_FUNCTION_1(__dock_unaccept_all_goods)

bool __dock_has_trade_ship(int bid) {
    auto b = building_get(bid)->dcast_dock();
    return b && b->runtime_data().trade_ship != 0;
}
ANK_FUNCTION_1(__dock_has_trade_ship)

int __dock_count_idle_dockers(int bid) {
    auto b = building_get(bid)->dcast_dock();
    return b ? b->count_idle_dockers() : 0;
}
ANK_FUNCTION_1(__dock_count_idle_dockers)
