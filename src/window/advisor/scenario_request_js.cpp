#include "advisor_imperial.h"

#include "empire/empire.h"
#include "empire/empire_city.h"
#include "figure/formation.h"
#include "js/js_game.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"
#include "mujs/mujs.h"
#include "city/city.h"
#include "city/military.h"
#include "window/popup_dialog.h"
#include "scenario/distant_battle.h"
#include "scenario/request.h"

#include <cstdio>

extern ui::advisor_imperial_window g_advisor_imperial_window;

namespace {

scenario_request dummy_request;

scenario_request& imperial_request_at(int index) {
    auto v = scenario_get_visible_requests();
    if (index < 0 || index >= static_cast<int>(v.size())) {
        return dummy_request;
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
    const auto& r = imperial_request_at(scenario_request_this_index(J));
    js_pushboolean(J, r.is_valid() ? 1 : 0);
}

static void scenario_request_get_resource_id(js_State* J) {
    const auto& r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, static_cast<int>(r.resource));
}

static void scenario_request_get_raw_amount(js_State* J) {
    const auto& r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, r.amount);
}

static void scenario_request_get_amount_total(js_State* J) {
    const auto& r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, r.resource_amount());
}

static void scenario_request_get_months(js_State* J) {
    const auto& r = imperial_request_at(scenario_request_this_index(J));
    js_pushnumber(J, r.months_to_comply);
}

enum E_STATUS {
    STATUS_NOT_ENOUGH_RESOURCES = -1,
    STATUS_CONFIRM_SEND_LEGIONS = -2,
    STATUS_NO_LEGIONS_SELECTED = -3,
    STATUS_NO_LEGIONS_AVAILABLE = -4,
};

int scenario_request_get_status(int index) {
    scenario_request& request = scenario_request_get_visible(index);
    if (!request.is_valid()) {
        return -1;
    }

    if (request.resource == RESOURCE_DEBEN && g_city.finance.treasury <= request.amount) {
        return STATUS_NOT_ENOUGH_RESOURCES;
    }

    if (request.resource == RESOURCE_TROOPS && g_distant_battle.battle.months_until_battle > 0
        && !g_distant_battle.battle.egyptian_months_to_travel_forth) {
        if (g_city.military.total_batalions <= 0) {
            return STATUS_NO_LEGIONS_AVAILABLE;
        }

        if (g_city.military.kingdome_service_batalions <= 0) {
            return STATUS_NO_LEGIONS_SELECTED;
        }

        return STATUS_CONFIRM_SEND_LEGIONS;
    }

    int stored_in_city = g_city.resource.stored(request.resource);
    if (stored_in_city < request.resource_amount()) {
        return STATUS_NOT_ENOUGH_RESOURCES;
    }

    return request.event_id;
}

void scenario_request_handle(int index) {
    int status = scenario_request_get_status(index);
    if (status < 0) {
        return;
    }

    g_city.military.clear_kingdome_service_batalions();
    switch (status) {
    case STATUS_NO_LEGIONS_AVAILABLE:
        popup_dialog::show_ok("#popup_dialog_no_legions_available");
        break;

    case STATUS_NO_LEGIONS_SELECTED:
        popup_dialog::show_ok("#popup_dialog_no_legions_selected");
        break;

    case STATUS_CONFIRM_SEND_LEGIONS:
        popup_dialog::show_ok("#popup_dialog_send_troops");
        break;

    case STATUS_NOT_ENOUGH_RESOURCES:
        popup_dialog::show_ok("#popup_dialog_not_enough_goods");
        break;

    default:
        popup_dialog::show_yesno("#popup_dialog_send_goods",
          [selected_request_id = index] { scenario_request_dispatch(selected_request_id); });
        break;
    }
}

static void scenario_request_proto_handle(js_State* J) {
    const int index = scenario_request_this_index(J);
    auto& r = imperial_request_at(index);
    if (!r.is_valid()) {
        js_helpers::js_push_void(J);
        return;
    }
    scenario_request_handle(index);
    js_helpers::js_push_void(J);
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

} // namespace

void js_register_imperial_visible_request(js_State *J) {
    g_imperial_visible_request_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_imperial_visible_request_proto);

    def_readonly_prop(J, scenario_request_get_valid, "valid");
    def_readonly_prop(J, scenario_request_get_resource_id, "resource_id");
    def_readonly_prop(J, scenario_request_get_raw_amount, "raw_amount");
    def_readonly_prop(J, scenario_request_get_amount_total, "amount_total");
    def_readonly_prop(J, scenario_request_get_months, "months");

    jsB_propf(J, js_intern("ScenarioRequest.prototype.handle"), scenario_request_proto_handle, 0);
    jsB_propf(J, js_intern("ScenarioRequest.prototype.toString"), scenario_request_proto_toString, 0);

    js_newcconstructor(J, jsB_new_ScenarioRequest, jsB_new_ScenarioRequest, js_intern("ScenarioRequest"), 1);
    js_defglobal(J, js_intern("ScenarioRequest"), JS_DONTENUM);
}

int __imperial_visible_request_count() {
    return static_cast<int>(scenario_get_visible_requests().size());
}
ANK_FUNCTION(__imperial_visible_request_count)

