#include "empire/empire.h"

#include "empire/empire_city.h"
#include "empire/empire_map.h"
#include "empire/empire_object.h"
#include "city/city.h"
#include "scenario/distant_battle.h"
#include "core/profiler.h"
#include "js/js_game.h"

std::optional<bvariant> __empire_get_city_object_property(int cid, pcstr property) {
    const auto *empire_city = g_empire.city(cid);
    if (!empire_city) {
        return {};
    }

    const auto *empire_obj = empire_city->get_empire_object();
    verify_no_crash(empire_obj && "empire_obj should exist");

    return archive_helper::get(*empire_obj, property, true);
}
ANK_FUNCTION_2(__empire_get_city_object_property)

std::optional<bvariant> __empire_get_ourcity_property(pcstr property) {
    const auto *ourcity_obj = g_empire.ourcity_object();
    if (!ourcity_obj) {
        return {};
    }

    verify_no_crash(ourcity_obj && "empire_obj should exist");
    return archive_helper::get(*ourcity_obj, property, true);
}
ANK_FUNCTION_1(__empire_get_ourcity_property)

int __empire_map_selected_empire_object_id() {
    int selected_object = g_empire_map.selected_object();
    if (selected_object <= 0) {
        return 0;
    }
    const empire_object* object = g_empire.get_object(selected_object - 1);
    return object ? object->id : 0;
}
ANK_FUNCTION(__empire_map_selected_empire_object_id)

bool __empire_city_buys_resource(int city_index, int resource) {
    const empire_city* city = g_empire.city(city_index);
    if (!city || !city->in_use) {
        return false;
    }
    return city->buys_resource[(e_resource)resource];
}
ANK_FUNCTION_2(__empire_city_buys_resource)

bool __empire_city_sells_resource(int city_index, int resource) {
    const empire_city* city = g_empire.city(city_index);
    if (!city || !city->in_use) {
        return false;
    }
    return city->sells_resource[(e_resource)resource];
}
ANK_FUNCTION_2(__empire_city_sells_resource)

int __empire_trade_route_limit(int city_id, int resource) {
    const empire_city* city = g_empire.city(city_id);
    if (!city) {
        return 0;
    }
    return city->get_route().limit((e_resource)resource);
}
ANK_FUNCTION_2(__empire_trade_route_limit)

int __empire_trade_route_traded(int city_id, int resource) {
    const empire_city* city = g_empire.city(city_id);
    if (!city) {
        return 0;
    }
    return city->get_route().traded((e_resource)resource);
}
ANK_FUNCTION_2(__empire_trade_route_traded)

int __empire_map_selected_city() {
    return g_empire_map.selected_city;
}
ANK_FUNCTION(__empire_map_selected_city)

int __empire_city_type(int city_index) {
    const empire_city* city = g_empire.city(city_index);
    if (!city || !city->in_use) {
        return -1;
    }
    return (int)city->type;
}
ANK_FUNCTION_1(__empire_city_type)

bool __empire_city_is_open(int city_index) {
    const empire_city* city = g_empire.city(city_index);
    return city && city->in_use && city->is_open;
}
ANK_FUNCTION_1(__empire_city_is_open)

void js_register_empire_objects(js_State *J) {
}