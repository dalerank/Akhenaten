#include "js.h"
#include "mujs/mujs.h"
#include "mujs/jsi.h"
#include "mujs/jsvalue.h"
#include "mujs/jscompile.h"
#include "mujs/mujs.h"

#include "core/log.h"
#include "scenario/scenario.h"
#include "city/city_building_menu_ctrl.h"
#include "city/city_message.h"
#include "js/js_game.h"

static js_StringNode property_varname = js_intern("__varname");
static js_StringNode property_x = js_intern("x");
static js_StringNode property_y = js_intern("y");
static js_StringNode property_minx = js_intern("minx");
static js_StringNode property_miny = js_intern("miny");
static js_StringNode property_maxx = js_intern("maxx");
static js_StringNode property_maxy = js_intern("maxy");
static js_StringNode property_btype = js_intern("btype");

void js_register_mission_objects(js_State *J) {
    js_newobject(J);
    {
        J->pushstring("mission");
        js_setproperty(J, -2, property_btype);
    }
    js_setglobal(J, "mission");
}

static void js_mission_var_getter(js_State *J) {
    js_currentfunction(J);
    J->getproperty(-1, property_varname);
    xstring name = js_tostring(J, -1)->value.c_str();
    js_pop(J, 2);

    if (!name || !g_scenario.vars.is_defined(name)) {
        J->pushundefined();
        return;
    }

    setting_variant value = g_scenario.vars.get(name);

    switch (value.index()) {
    case setting_bool:
        js_pushboolean(J, std::get<bool>(value));
        break;
    case setting_float:
        js_pushnumber(J, std::get<float>(value));
        break;
    case setting_vec2i:
        js_helpers::js_push_value<vec2i>(J, std::get<vec2i>(value));
        break;
    case setting_string:
        J->pushstring(std::get<xstring>(value).c_str());
        break;
    default:
        J->pushundefined();
        break;
    }
}

static void js_mission_var_setter(js_State *J) {
    js_currentfunction(J);
    J->getproperty(-1, property_varname);
    xstring name = js_tostring(J, -1)->value.c_str();
    js_pop(J, 2);

    if (!name || !g_scenario.vars.is_defined(name)) {
        return;
    }

    if (js_isboolean(J, 1)) {
        bool value = js_toboolean(J, 1);
        g_scenario.vars.set_bool(name, value);
    } else if (js_isnumber(J, 1)) {
        float value = (float)js_tonumber(J, 1);
        g_scenario.vars.set_float(name, value);
    } else if (js_isstring(J, 1)) {
        auto value = js_tostring(J, 1);
        g_scenario.vars.set_string(name, value->value.c_str());
    } else if (J->isobject(1)) {
        J->getproperty(1, property_x);
        J->getproperty(1, property_y);

        if (js_isnumber(J, -2) && js_isnumber(J, -1)) {
            int x = (int)js_tonumber(J, -2);
            int y = (int)js_tonumber(J, -1);
            g_scenario.vars.set(name, setting_variant(vec2i{ x, y }));
        }

        js_pop(J, 2);
    }
}

void js_register_mission_vars(const settings_vars_t &vars) {
    js_State *J = js_vm_state();
    if (!J) {
        return;
    }

    js_getglobal(J, "mission");

    svector<xstring, 64> properties_to_delete;
    js_pushiterator(J, -1, 1);
    js_StringNode key;
    const std::unordered_set<xstring> systemvars = { "id", "btype", "use_building" };
    while ((key = js_nextiterator(J, -1))) {
        pcstr key_str = js_strnode_cstr(key);
        bool is_internal = (key_str[0] == '_') || (systemvars.count(key_str) == 0);
        if (!is_internal) {
            properties_to_delete.push_back(key_str);
        }
    }
    js_pop(J, 1);

    for (const auto &prop : properties_to_delete) {
        js_delproperty(J, -1, (js_StringNode)(prop._get()));
    }

    g_scenario.vars.foreach_vars([&] (xstring name, const setting_variant &value) {
        // Variable name '%s' conflicts with mission method! Skipping.
        assert(systemvars.count(name) == 0);
        
        bstring128 getter_name("get_", name.c_str());
        bstring128 setter_name("set_", name.c_str());

        js_newcfunction(J, js_mission_var_getter, getter_name.c_str(), 0);
        J->pushstring(name.c_str());
        js_setproperty(J, -2, property_varname);

        js_newcfunction(J, js_mission_var_setter, setter_name.c_str(), 1);
        J->pushstring(name.c_str());
        js_setproperty(J, -2, property_varname);

        js_defaccessor(J, -3, (js_StringNode)(name._get()), 0);
        logs::info("Registered mission variable: %s", name.c_str());
    });

    js_pop(J, 1);
}