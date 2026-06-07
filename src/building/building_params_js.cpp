#include "building/building.h"
#include "building/building_static_params.h"
#include "building/building_type.h"
#include "core/profiler.h"
#include "grid/building.h"
#include "js/js_game.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"

#include <cstdio>

static int building_params_this_type(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("type"));
    if (js_isundefined(J, -1) || js_isnull(J, -1)) {
        js_pop(J, 1);
        return BUILDING_NONE;
    }

    const int type = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return type;
}

static const building_static_params *building_params_for_type(int type) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return nullptr;
    }
    return &building_static_params::get((e_building_type)type);
}

std::optional<bvariant> __building_get_params_property(int bid, pcstr property) {
    building *b = building_get(bid);
    if (!b) {
        return {};
    }
    return archive_helper::get(b->params(), property, true);
}
ANK_FUNCTION_2(__building_get_params_property)

std::optional<bvariant> __building_get_static_params_property(int type, pcstr property) {
    const building_static_params *params = building_params_for_type(type);
    if (!params) {
        return {};
    }
    return archive_helper::get(*params, property, true);
}
ANK_FUNCTION_2(__building_get_static_params_property)

int building_static_first_img_for_type(int type, xstring anim_key) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }
    return building_static_params::get((e_building_type)type).first_img(anim_key);
}

int __building_static_first_img(int type, xstring anim_key) {
    return building_static_first_img_for_type(type, anim_key);
}
ANK_FUNCTION_2(__building_static_first_img)

static js_Object *g_building_params_proto = nullptr;

static void building_params_proto___property_getter(js_State *J) {
    const building_static_params *params = building_params_for_type(building_params_this_type(J));
    if (!params) {
        J->pushundefined();
        return;
    }

    pcstr prop = js_strnode_cstr(js_tostring(J, 1));
    auto opt = archive_helper::get(*params, prop, true);
    js_helpers::js_push_value<std::optional<bvariant>>(J, opt);
}

static void building_params_proto___cost(js_State *J) {
    const building_static_params *params = building_params_for_type(building_params_this_type(J));
    js_helpers::js_push_value(J, params ? (int)params->get_cost() : 0);
}

static void building_params_proto_first_img(js_State *J) {
    const int type = building_params_this_type(J);
    const xstring anim_key = js_helpers::js_to_value<xstring>(J, 1);
    js_helpers::js_push_value(J, building_static_first_img_for_type(type, anim_key));
}

static void building_params_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "BuildingParams(type=%d)", building_params_this_type(J));
    J->pushstring(buf);
}

static void jsB_BuildingParams_for_type(js_State *J) {
    const int type = js_gettop(J) > 0 ? (int)js_tointeger(J, 1) : BUILDING_NONE;
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_building_params_proto));
    js_pushnumber(J, (double)type);
    js_setproperty(J, -2, js_intern("type"));
}

void js_register_building_params(js_State *J) {
    g_building_params_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_building_params_proto);

    jsB_propf(J, js_intern("BuildingParams.prototype.__property_getter"), building_params_proto___property_getter, 1);
    jsB_propf(J, js_intern("BuildingParams.prototype.__cost"), building_params_proto___cost, 0);
    jsB_propf(J, js_intern("BuildingParams.prototype.first_img"), building_params_proto_first_img, 1);
    jsB_propf(J, js_intern("BuildingParams.prototype.toString"), building_params_proto_toString, 0);

    js_newcconstructor(J, jsB_BuildingParams_for_type, jsB_BuildingParams_for_type, js_intern("BuildingParams"), 1);
    jsB_propf(J, js_intern("BuildingParams.for_type"), jsB_BuildingParams_for_type, 1);
    js_defglobal(J, js_intern("BuildingParams"), JS_DONTENUM);
}
