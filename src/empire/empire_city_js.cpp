#include "empire/empire.h"
#include "empire/empire_city.h"
#include "empire/empire_object.h"
#include "js/js_game.h"
#include "js/js_mujs_bound_offset.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"
#include "mujs/mujs.h"

#include <cstddef>
#include <cstdio>

int __city_resource_stack_proper_quantity(int resource, int value);

static int empire_city_this_id(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

/** nullptr if id invalid or city not in use */
static empire_city* empire_city_this_active(js_State* J) {
    empire_city* city = g_empire.city(empire_city_this_id(J));
    return (city && city->in_use) ? city : nullptr;
}

static js_Object* g_empire_city_map_proto = nullptr;
static js_Object* g_empire_city_proto = nullptr;

static void empire_city_map_proto___property_getter(js_State* J) {
    const int cid = empire_city_this_id(J);
    pcstr prop = js_strnode_cstr(js_tostring(J, 1));
    const empire_city* city = g_empire.city(cid);
    if (!city) {
        js_helpers::js_push_void(J);
        return;
    }
    const empire_object* empire_obj = city->get_empire_object();
    if (!empire_obj) {
        js_helpers::js_push_void(J);
        return;
    }
    auto opt = archive_helper::get(*empire_obj, prop, true);
    js_helpers::js_push_value<std::optional<bvariant>>(J, opt);
}

static void empire_city_map_proto_toString(js_State* J) {
    const int id = empire_city_this_id(J);
    char buf[64];
    snprintf(buf, sizeof buf, "EmpireCityMap(%d)", id);
    J->pushstring(buf);
}

static void js_push_empire_city_object(js_State* J, int id, js_Object* proto) {
    empire_city* c = g_empire.city(id);
    if (!c || !c->in_use) {
        id = 0;
    }
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
}

static void js_push_empire_city(js_State* J, int id, js_Object* proto) {
    empire_city* c = g_empire.city(id);
    if (!c || !c->in_use) {
        id = 0;
    }
    empire_city* cobj_slot = g_empire.city(id);
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
    js_register_cobj_ptr_property(J, cobj_slot);
}

static void jsB_new_EmpireCityObject(js_State* J) {
    const int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_empire_city_object(J, id, g_empire_city_map_proto);
}

static void empire_city_proto_city_buys_resource(js_State* J) {
    const int res = js_helpers::js_to_value<int>(J, 1);
    const empire_city* city = empire_city_this_active(J);
    js_helpers::js_push_value(J, city ? city->buys_resource[(e_resource)res] : false);
}

static void empire_city_proto_city_sells_resource(js_State* J) {
    const int res = js_helpers::js_to_value<int>(J, 1);
    const empire_city* city = empire_city_this_active(J);
    js_helpers::js_push_value(J, city ? city->sells_resource[(e_resource)res] : false);
}

static void empire_city_proto_trade_route_limit(js_State* J) {
    const int res = js_helpers::js_to_value<int>(J, 1);
    const empire_city* city = empire_city_this_active(J);
    js_helpers::js_push_value(J, city ? city->get_route().limit((e_resource)res) : 0);
}

static void empire_city_proto_trade_route_traded(js_State* J) {
    const int res = js_helpers::js_to_value<int>(J, 1);
    const empire_city* city = empire_city_this_active(J);
    js_helpers::js_push_value(J, city ? city->get_route().traded((e_resource)res) : 0);
}

static void empire_city_proto_stack_proper_quantity(js_State* J) {
    const int res = js_helpers::js_to_value<int>(J, 1);
    const int qty = js_helpers::js_to_value<int>(J, 2);
    js_helpers::js_push_value(J, __city_resource_stack_proper_quantity(res, qty));
}

static void empire_city_proto_toString(js_State* J) {
    char buf[64];
    snprintf(buf, sizeof buf, "EmpireCity(%d)", empire_city_this_id(J));
    J->pushstring(buf);
}

static void jsB_new_EmpireCity(js_State* J) {
    const int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_empire_city(J, id, g_empire_city_proto);
}

void js_register_empire_city_map_proto(js_State* J) {
    g_empire_city_map_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_empire_city_map_proto);
    jsB_propf(J, js_intern("EmpireCityObject.prototype.__property_getter"), empire_city_map_proto___property_getter, 1);
    jsB_propf(J, js_intern("EmpireCityObject.prototype.toString"), empire_city_map_proto_toString, 0);
    js_newcconstructor(J, jsB_new_EmpireCityObject, jsB_new_EmpireCityObject, js_intern("EmpireCityObject"), 1);
    js_defglobal(J, js_intern("EmpireCityObject"), JS_DONTENUM);
}

void js_register_empire_city_proto(js_State* J) {
    g_empire_city_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_empire_city_proto);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, is_open);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, is_sea_trade);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, months_under_siege);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, type);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, cost_to_open);

    jsB_propf(J, js_intern("EmpireCity.prototype.city_buys_resource"), empire_city_proto_city_buys_resource, 1);
    jsB_propf(J, js_intern("EmpireCity.prototype.city_sells_resource"), empire_city_proto_city_sells_resource, 1);
    jsB_propf(J, js_intern("EmpireCity.prototype.trade_route_limit"), empire_city_proto_trade_route_limit, 1);
    jsB_propf(J, js_intern("EmpireCity.prototype.trade_route_traded"), empire_city_proto_trade_route_traded, 1);
    jsB_propf(J, js_intern("EmpireCity.prototype.stack_proper_quantity"), empire_city_proto_stack_proper_quantity, 2);
    jsB_propf(J, js_intern("EmpireCity.prototype.toString"), empire_city_proto_toString, 0);

    js_newcconstructor(J, jsB_new_EmpireCity, jsB_new_EmpireCity, js_intern("EmpireCity"), 1);
    js_defglobal(J, js_intern("EmpireCity"), JS_DONTENUM);
}
