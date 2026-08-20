#include "empire/empire.h"

#include "empire/empire_city.h"
#include "empire/empire_map.h"
#include "empire/empire_object.h"
#include "empire/empire_traders.h"
#include "city/city.h"
#include "city/city_message.h"
#include "game/resource.h"
#include "scenario/distant_battle.h"
#include "scenario/scenario.h"
#include "scenario/empire.h"
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

/** 1-based selected object pick; 0 if none. */
int __empire_map_selected_object() {
    return g_empire_map.selected_object();
}
ANK_FUNCTION(__empire_map_selected_object)

void __empire_map_select_object(vec2i pos) {
    g_empire_map.select_object(pos);
}
ANK_FUNCTION_1(__empire_map_select_object)

void __empire_map_scroll_map(vec2i delta) {
    g_empire_map.scroll_map(delta);
}
ANK_FUNCTION_1(__empire_map_scroll_map)

void __empire_map_clear_selected_object() {
    g_empire_map.clear_selected_object();
}
ANK_FUNCTION(__empire_map_clear_selected_object)

int __empire_luxury_goods_traded_sum() {
    int sum = 0;
    for (const auto &route : g_empire.get_routes()) {
        sum += route.traded(RESOURCE_LUXURY_GOODS);
    }
    return sum;
}
ANK_FUNCTION(__empire_luxury_goods_traded_sum)

std::optional<bvariant> __empire_trader_get_property(int index, pcstr property) {
    if (index < 0 || index >= g_empire_traders.traders.size()) {
        return {};
    }
    return archive_helper::get(g_empire_traders.traders[index], property, true);
}
ANK_FUNCTION_2(__empire_trader_get_property)

bool __empire_trader_faces_left(int index) {
    if (index < 0 || index >= (int)g_empire_traders.traders.size()) {
        return false;
    }
    return g_empire_traders.traders[index].faces_left();
}
ANK_FUNCTION_1(__empire_trader_faces_left)

vec2i __empire_map_adjust_scroll(vec2i pos) {
    return g_empire_map.adjust_scroll(pos);
}
ANK_FUNCTION_1(__empire_map_adjust_scroll)

vec2i __empire_map_get_scroll() {
    return g_empire_map.get_scroll();
}
ANK_FUNCTION(__empire_map_get_scroll)

void __empire_map_set_viewport(vec2i size) {
    g_empire_map.set_viewport(size);
}
ANK_FUNCTION_1(__empire_map_set_viewport)

static constexpr int EMPIRE_TRADE_ROUTE_COUNT = 50;

int __empire_trade_route_num_points(int route_id) {
    if (route_id < 0 || route_id >= EMPIRE_TRADE_ROUTE_COUNT) {
        return 0;
    }
    const map_route_object& obj = g_empire.get_route_object(route_id);
    if (!obj.in_use) {
        return 0;
    }
    return obj.num_points;
}
ANK_FUNCTION_1(__empire_trade_route_num_points)

vec2i __empire_trade_route_point(int route_id, int index) {
    if (route_id < 0 || route_id >= EMPIRE_TRADE_ROUTE_COUNT) {
        return {0, 0};
    }
    const map_route_object& obj = g_empire.get_route_object(route_id);
    if (!obj.in_use || index < 0 || index >= obj.num_points) {
        return {0, 0};
    }
    return obj.points[index].p;
}
ANK_FUNCTION_2(__empire_trade_route_point)

void __imperial_dispatch_distant_battle() {
    g_formations.dispatch_batalions_to_distant_battle();
}
ANK_FUNCTION(__imperial_dispatch_distant_battle)

int __imperial_distant_battle_city_name_id() {
    if (!g_distant_battle.has_distant_battle()) {
        return 0;
    }
    const empire_city *c = g_empire.city(g_distant_battle.battle.city);
    return c ? c->name_id : 0;
}
ANK_FUNCTION(__imperial_distant_battle_city_name_id)

int __empire_get_id() {
    return g_scenario.empire.id;
}
ANK_FUNCTION(__empire_get_id)

void __empire_set_id(int id) {
    g_scenario.empire.id = id;
}
ANK_FUNCTION_1(__empire_set_id)

bool __empire_is_expanded() {
    return g_scenario.empire.is_expanded != 0;
}
ANK_FUNCTION(__empire_is_expanded)

void __empire_set_expanded(bool expanded) {
    g_scenario.empire.is_expanded = expanded ? 1 : 0;
}
ANK_FUNCTION_1(__empire_set_expanded)

void __empire_expand() {
    if (g_scenario.empire.is_expanded) {
        return;
    }
    g_empire.expand();
    g_scenario.empire.is_expanded = 1;
    messages::popup("message_empire_has_expanded", 0, 0);
}
ANK_FUNCTION(__empire_expand)

int __empire_update_map_animation(int object_index, int image_id) {
    const empire_object* obj = g_empire.get_object(object_index);
    if (!obj || image_id <= 0) {
        return 0;
    }
    return g_empire.update_animation(object_index, *obj, image_id);
}
ANK_FUNCTION_2(__empire_update_map_animation)

int __empire_city_image_id(int city_type) {
    return empire_city_images.image_id((e_empire_city)city_type, scenario_empire_is_expanded());
}
ANK_FUNCTION_1(__empire_city_image_id)

void js_register_empire_objects(js_State *J) {
    js_register_empire_object_proto(J);
    js_register_empire_city_map_proto(J);
    js_register_empire_city_proto(J);
    js_register_empire_trader_proto(J);
    js_register_invasion_warning_proto(J);
}