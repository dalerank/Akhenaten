#include "empire/empire.h"
#include "empire/empire_city.h"
#include "empire/empire_object.h"
#include "empire/empire_traders.h"
#include "js/js_game.h"
#include "js/js.h"
#include "js/js_mujs_bound_offset.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"
#include "mujs/mujs.h"
#include "scenario/scenario.h"
#include "scenario/scenario_invasion.h"

#include <cstdio>

static js_Object* g_empire_city_map_proto = nullptr;
static js_Object* g_empire_city_proto = nullptr;
static js_Object* g_empire_object_proto = nullptr;

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

static int empire_object_this_slot(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static empire_object* empire_object_this_ptr(js_State* J) {
    full_empire_object* full = g_empire.ref_full_object(empire_object_this_slot(J));
    return full ? &full->obj : nullptr;
}

static void empire_object_proto___property_getter(js_State* J) {
    xstring prop = js_toxstring(J, 1);
    const int slot = empire_object_this_slot(J);
    const empire_object* obj = empire_object_this_ptr(J);
    if (!obj) {
        js_helpers::js_push_void(J);
        return;
    }

    if (prop == "city_id") {
        js_helpers::js_push_value(J, g_empire.get_city_for_object(slot));
        return;
    }

    auto opt = archive_helper::get(*obj, prop, true);
    js_helpers::js_push_value<std::optional<bvariant>>(J, opt);
}

static void empire_object_proto_toString(js_State* J) {
    char buf[64];
    snprintf(buf, sizeof buf, "EmpireObject(%d)", empire_object_this_slot(J));
    J->pushstring(buf);
}

static void js_push_empire_object(js_State* J, int slot) {
    full_empire_object* full = g_empire.ref_full_object(slot);
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_empire_object_proto));
    js_pushnumber(J, (double)slot);
    js_setproperty(J, -2, js_intern("id"));
    js_register_cobj_ptr_property(J, full);
}

static void jsB_new_EmpireObject(js_State* J) {
    const int slot = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_empire_object(J, slot);
}

static void empire_city_map_proto___property_getter(js_State* J) {
    const int cid = empire_city_this_id(J);
    xstring prop = js_toxstring(J, 1);
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
        c = g_empire.city(id);
    }
    full_empire_object* full = (c && c->in_use) ? g_empire.ref_full_object(c->empire_object_id) : nullptr;
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
    js_register_cobj_ptr_property(J, full);
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

static void empire_city_proto_toString(js_State* J) {
    char buf[64];
    snprintf(buf, sizeof buf, "EmpireCity(%d)", empire_city_this_id(J));
    J->pushstring(buf);
}

static void jsB_new_EmpireCity(js_State* J) {
    const int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_empire_city(J, id, g_empire_city_proto);
}

void js_register_empire_object_proto(js_State* J) {
    g_empire_object_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_empire_object_proto);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, full_empire_object, in_use);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, full_empire_object, city_name_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, full_empire_object, text_key);
    JS_REGISTER_BOUND_OFFSET_MEMBER(J, full_empire_object, obj.type, js_intern("type"));
    JS_REGISTER_BOUND_OFFSET_MEMBER(J, full_empire_object, obj.image_id, js_intern("image_id"));
    JS_REGISTER_BOUND_OFFSET_MEMBER(J, full_empire_object, obj.distant_battle_travel_months, js_intern("distant_battle_travel_months"));
    jsB_propf(J, js_intern("EmpireObject.prototype.__property_getter"), empire_object_proto___property_getter, 1);
    jsB_propf(J, js_intern("EmpireObject.prototype.toString"), empire_object_proto_toString, 0);
    js_newcconstructor(J, jsB_new_EmpireObject, jsB_new_EmpireObject, js_intern("EmpireObject"), 1);
    js_defglobal(J, js_intern("EmpireObject"), JS_DONTENUM);
}

void js_register_empire_city_map_proto(js_State* J) {
    g_empire_city_map_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_empire_city_map_proto);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, full_empire_object, trade_route_open);
    jsB_propf(J, js_intern("EmpireCityObject.prototype.__property_getter"), empire_city_map_proto___property_getter, 1);
    jsB_propf(J, js_intern("EmpireCityObject.prototype.toString"), empire_city_map_proto_toString, 0);
    js_newcconstructor(J, jsB_new_EmpireCityObject, jsB_new_EmpireCityObject, js_intern("EmpireCityObject"), 1);
    js_defglobal(J, js_intern("EmpireCityObject"), JS_DONTENUM);
}

void js_register_empire_city_proto(js_State* J) {
    g_empire_city_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_empire_city_proto);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, in_use);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, is_open);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, is_sea_trade);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, months_under_siege);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, type);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, cost_to_open);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, name_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_city, route_id);

    jsB_propf(J, js_intern("EmpireCity.prototype.city_buys_resource"), empire_city_proto_city_buys_resource, 1);
    jsB_propf(J, js_intern("EmpireCity.prototype.city_sells_resource"), empire_city_proto_city_sells_resource, 1);
    jsB_propf(J, js_intern("EmpireCity.prototype.trade_route_limit"), empire_city_proto_trade_route_limit, 1);
    jsB_propf(J, js_intern("EmpireCity.prototype.trade_route_traded"), empire_city_proto_trade_route_traded, 1);
    jsB_propf(J, js_intern("EmpireCity.prototype.toString"), empire_city_proto_toString, 0);

    js_newcconstructor(J, jsB_new_EmpireCity, jsB_new_EmpireCity, js_intern("EmpireCity"), 1);
    js_defglobal(J, js_intern("EmpireCity"), JS_DONTENUM);
}

static js_Object* g_empire_trader_proto = nullptr;
static js_Object* g_invasion_warning_proto = nullptr;

static void proto_set_readonly(js_State* J) {
    (void)J;
}

static void proto_def_readonly(js_State* J, js_CFunction get, const char* name) {
    js_newcfunction(J, get, js_intern(""), 0);
    js_newcfunction(J, proto_set_readonly, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

static int empire_trader_this_index(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static empire_trader* empire_trader_this_ptr(js_State* J) {
    const int index = empire_trader_this_index(J);
    if (index < 0 || index >= (int)g_empire_traders.traders.size()) {
        return nullptr;
    }
    return &g_empire_traders.traders[index];
}

static void empire_trader_proto_current_position(js_State* J) {
    empire_trader* t = empire_trader_this_ptr(J);
    js_helpers::js_push_value<vec2i>(J, t ? t->current_position : vec2i{});
}

static void empire_trader_proto_faces_left(js_State* J) {
    empire_trader* t = empire_trader_this_ptr(J);
    js_helpers::js_push_value(J, t ? t->faces_left() : false);
}

static void empire_trader_proto_toString(js_State* J) {
    char buf[64];
    snprintf(buf, sizeof buf, "EmpireTrader(%d)", empire_trader_this_index(J));
    J->pushstring(buf);
}

static void js_push_empire_trader(js_State* J, int index) {
    empire_trader* t = nullptr;
    if (index >= 0 && index < (int)g_empire_traders.traders.size()) {
        t = &g_empire_traders.traders[index];
    }
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_empire_trader_proto));
    js_pushnumber(J, (double)index);
    js_setproperty(J, -2, js_intern("id"));
    js_register_cobj_ptr_property(J, t);
}

static void jsB_new_EmpireTrader(js_State* J) {
    const int index = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_empire_trader(J, index);
}

void js_register_empire_trader_proto(js_State* J) {
    g_empire_trader_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_empire_trader_proto);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_trader, is_ship);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_trader, is_active);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_trader, trade_route_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, empire_trader, destination_city_id);
    proto_def_readonly(J, empire_trader_proto_current_position, "current_position");
    proto_def_readonly(J, empire_trader_proto_faces_left, "faces_left");
    jsB_propf(J, js_intern("EmpireTrader.prototype.toString"), empire_trader_proto_toString, 0);
    js_newcconstructor(J, jsB_new_EmpireTrader, jsB_new_EmpireTrader, js_intern("EmpireTrader"), 1);
    js_defglobal(J, js_intern("EmpireTrader"), JS_DONTENUM);
}

static int invasion_warning_this_index(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static invasion_warning_t* invasion_warning_this_ptr(js_State* J) {
    const int index = invasion_warning_this_index(J);
    if (index < 0 || index >= (int)g_invasions.warnings.size()) {
        return nullptr;
    }
    return &g_invasions.warnings[index];
}

static void invasion_warning_proto_pos(js_State* J) {
    invasion_warning_t* w = invasion_warning_this_ptr(J);
    js_helpers::js_push_value<vec2i>(J, w ? w->pos : vec2i{});
}

static void invasion_warning_proto_toString(js_State* J) {
    char buf[64];
    snprintf(buf, sizeof buf, "InvasionWarning(%d)", invasion_warning_this_index(J));
    J->pushstring(buf);
}

static void js_push_invasion_warning(js_State* J, int index) {
    invasion_warning_t* w = nullptr;
    if (index >= 0 && index < (int)g_invasions.warnings.size()) {
        w = &g_invasions.warnings[index];
    }
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_invasion_warning_proto));
    js_pushnumber(J, (double)index);
    js_setproperty(J, -2, js_intern("id"));
    js_register_cobj_ptr_property(J, w);
}

static void jsB_new_InvasionWarning(js_State* J) {
    const int index = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_invasion_warning(J, index);
}

void js_register_invasion_warning_proto(js_State* J) {
    g_invasion_warning_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_invasion_warning_proto);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, invasion_warning_t, in_use);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, invasion_warning_t, handled);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, invasion_warning_t, image_id);
    proto_def_readonly(J, invasion_warning_proto_pos, "pos");
    jsB_propf(J, js_intern("InvasionWarning.prototype.toString"), invasion_warning_proto_toString, 0);
    js_newcconstructor(J, jsB_new_InvasionWarning, jsB_new_InvasionWarning, js_intern("InvasionWarning"), 1);
    js_defglobal(J, js_intern("InvasionWarning"), JS_DONTENUM);
}
