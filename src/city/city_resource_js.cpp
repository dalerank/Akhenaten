#include "city/city_resource.h"

#include "city/city_resource_handle.h"
#include "core/profiler.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "js/js_game.h"
#include "city/city.h"

#include <cstdio>

int __city_yards_stored(int resource) {
    return g_city.resource.yards_stored((e_resource)resource);
}
ANK_FUNCTION_1(__city_yards_stored)

void __cheat_add_resource(int resource, int amount) {
    city_resource_add_items((e_resource)resource, amount);
    city_resource_was_added_warning((e_resource)resource);
}
ANK_FUNCTION_2(__cheat_add_resource)

int __city_resources_count() {
    return (int)resource_list::all.size() - 1;
}
ANK_FUNCTION(__city_resources_count)

e_resource __city_resource_at(int index) {
    return resource_list::all.at(index).type;
}
ANK_FUNCTION_1(__city_resource_at)

void __city_resource_set_produce(int resource, bool val) {
    g_city.set_produce_resource((e_resource)resource, val);
    if ((e_resource)resource == RESOURCE_FISH) {
        if (val) {
            g_city.fishing_points.reset();
        } else {
            g_city.fishing_points.clear();
        }
    }
}
ANK_FUNCTION_2(__city_resource_set_produce)

pcstr __city_resource_name(int resource) {
    return resource_name((e_resource)resource);
}
ANK_FUNCTION_1(__city_resource_name)

int __city_resource_id_by_name(pcstr name) {
    if (!name || !*name) {
        return (int)RESOURCE_NONE;
    }
    return (int)resource_type(name);
}
ANK_FUNCTION_1(__city_resource_id_by_name)

bvariant_map __city_resources_available() {
    city_resource_determine_available();
    bvariant_map out;
    const auto &av = g_city.resource.available();
    for (const auto &r : av) {
        out[resource_name(r.type)] = (int32_t)r.type;
    }
    return out;
}
ANK_FUNCTION(__city_resources_available)

bvariant_map __city_resources_available_market_goods() {
    city_resource_determine_available();
    bvariant_map out;
    const auto &av = g_city.resource.available_market_goods();
    for (const auto &r : av) {
        out[resource_name(r.type)] = (int32_t)r.type;
    }
    return out;
}
ANK_FUNCTION(__city_resources_available_market_goods)

bool __city_resource_is_stockpiled(int resource) {
    city_resource_handle h{ (e_resource)resource };
    return h.is_stockpiled();
}
ANK_FUNCTION_1(__city_resource_is_stockpiled)

int __city_resource_stack_proper_quantity(int resource, int value) {
    city_resource_handle h{ (e_resource)resource };
    return h.stack_proper_quantity(value);
}
ANK_FUNCTION_2(__city_resource_stack_proper_quantity)

int __city_resource_trading_amount(int resource) {
    city_resource_handle h{ (e_resource)resource };
    return h.trading_amount();
}
ANK_FUNCTION_1(__city_resource_trading_amount)

bool __city_resource_can_export(int resource, bool check) {
    city_resource_handle h{ (e_resource)resource };
    return h.can_export(check);
}
ANK_FUNCTION_2(__city_resource_can_export)

void __city_resource_cycle_trade_import(int resource) {
    city_resource_handle h{ (e_resource)resource };
    h.cycle_trade_import();
}
ANK_FUNCTION_1(__city_resource_cycle_trade_import)

void __city_resource_cycle_trade_export(int resource) {
    city_resource_handle h{ (e_resource)resource };
    h.cycle_trade_export();
}
ANK_FUNCTION_1(__city_resource_cycle_trade_export)

void __city_resource_change_trading_amount(int resource, int delta) {
    city_resource_handle h{ (e_resource)resource };
    h.change_trading_amount(delta);
}
ANK_FUNCTION_2(__city_resource_change_trading_amount)

void __city_resource_toggle_stockpiled(int resource) {
    city_resource_handle h{ (e_resource)resource };
    h.toggle_stockpiled();
}
ANK_FUNCTION_1(__city_resource_toggle_stockpiled)