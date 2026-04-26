#include "js/js_game.h"

#include "core/profiler.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"
#include "mujs/mujs.h"
#include "city/city.h"
#include "scenario/request.h"

#include <cstdio>

static scenario_request imperial_request_at(int index) {
    auto v = scenario_get_visible_requests();
    if (index < 0 || index >= static_cast<int>(v.size())) {
        return {};
    }
    return v[index];
}

static int scenario_request_this_index(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("index"));
    const int index = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return index;
}

static js_Object *g_imperial_visible_request_proto = nullptr;

static void scenario_request_set_readonly(js_State* J) {
    (void)J;
}

static void def_readonly_prop(js_State *J, js_CFunction get, const char *name) {
    js_newcfunction(J, get, js_intern(""), 0);
    js_newcfunction(J, scenario_request_set_readonly, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

static void scenario_request_get_valid(js_State* J) {
    const auto r = imperial_request_at(scenario_request_this_index(J));
    js_pushboolean(J, r.is_valid() ? 1 : 0);
}

static void scenario_request_get_resource_id(js_State* J) {
    const auto r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, static_cast<int>(r.resource));
}

static void scenario_request_get_raw_amount(js_State* J) {
    const auto r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, r.amount);
}

static void scenario_request_get_amount_total(js_State* J) {
    const auto r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, r.resource_amount());
}

static void scenario_request_get_months(js_State* J) {
    const auto r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, r.months_to_comply);
}

static void scenario_request_get_event_id(js_State* J) {
    const auto r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, r.event_id);
}

static void scenario_request_proto_toString(js_State *J) {
    char buf[96];
    snprintf(buf, sizeof buf, "ScenarioRequest(%d)", scenario_request_this_index(J));
    J->pushstring(buf);
}

static void jsB_new_ScenarioRequest(js_State *J) {
    const int index = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : -1;

    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_imperial_visible_request_proto));
    js_pushnumber(J, index);
    js_setproperty(J, -2, js_intern("index"));
}

void __scenario_request_dispatch(int index) {
    scenario_request_dispatch(index);
}
ANK_FUNCTION_1(__scenario_request_dispatch)

void js_register_imperial_visible_request(js_State *J) {
    g_imperial_visible_request_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_imperial_visible_request_proto);

    def_readonly_prop(J, scenario_request_get_valid, "valid");
    def_readonly_prop(J, scenario_request_get_resource_id, "resource_id");
    def_readonly_prop(J, scenario_request_get_raw_amount, "raw_amount");
    def_readonly_prop(J, scenario_request_get_amount_total, "amount_total");
    def_readonly_prop(J, scenario_request_get_months, "months");
    def_readonly_prop(J, scenario_request_get_event_id, "event_id");

    jsB_propf(J, js_intern("ScenarioRequest.prototype.toString"), scenario_request_proto_toString, 0);

    js_newcconstructor(J, jsB_new_ScenarioRequest, jsB_new_ScenarioRequest, js_intern("ScenarioRequest"), 1);
    js_defglobal(J, js_intern("ScenarioRequest"), JS_DONTENUM);
}

int __imperial_visible_request_count() {
    return static_cast<int>(scenario_get_visible_requests().size());
}
ANK_FUNCTION(__imperial_visible_request_count)
