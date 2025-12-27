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

void js_register_mission_objects(js_State *J) {
    js_newobject(J);
    {
        js_pushstring(J, "mission");
        js_setproperty(J, -2, "btype");
    }
    js_setglobal(J, "mission");
}

static void js_mission_var_getter(js_State *J) {
    js_currentfunction(J);
    js_getproperty(J, -1, "__varname");
    const char *name = js_tostring(J, -1);
    js_pop(J, 2);

    if (!name || !g_scenario.vars.is_defined(name)) {
        js_pushundefined(J);
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
    {
        const vec2i &v = std::get<vec2i>(value);
        js_newobject(J);
        js_pushnumber(J, v.x); js_setproperty(J, -2, "x");
        js_pushnumber(J, v.y); js_setproperty(J, -2, "y");
        break;
    }
    case setting_string:
        js_pushstring(J, std::get<xstring>(value).c_str());
        break;
    default:
        js_pushundefined(J);
        break;
    }
}

static void js_mission_var_setter(js_State *J) {
    js_currentfunction(J);
    js_getproperty(J, -1, "__varname");
    const char *name = js_tostring(J, -1);
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
        const char *value = js_tostring(J, 1);
        g_scenario.vars.set_string(name, value);
    } else if (js_isobject(J, 1)) {
        js_getproperty(J, 1, "x");
        js_getproperty(J, 1, "y");

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
    const char *key;
    const std::unordered_set<xstring> systemvars = { "id", "btype", "use_building" };
    while ((key = js_nextiterator(J, -1))) {
        bool is_internal = (key[0] == '_') || (systemvars.count(key) == 0);
        if (!is_internal) {
            properties_to_delete.push_back(key);
        }
    }
    js_pop(J, 1);

    for (const auto &prop : properties_to_delete) {
        js_delproperty(J, -1, prop.c_str());
    }

    g_scenario.vars.foreach_vars([&] (xstring name, const setting_variant &value) {
        // Variable name '%s' conflicts with mission method! Skipping.
        assert(systemvars.count(name) == 0);
        
        bstring128 getter_name("get_", name.c_str());
        bstring128 setter_name("set_", name.c_str());

        js_newcfunction(J, js_mission_var_getter, getter_name.c_str(), 0);
        js_pushstring(J, name.c_str());
        js_setproperty(J, -2, "__varname");

        js_newcfunction(J, js_mission_var_setter, setter_name.c_str(), 1);
        js_pushstring(J, name.c_str());
        js_setproperty(J, -2, "__varname");

        js_defaccessor(J, -3, name.c_str(), 0);
        logs::info("Registered mission variable: %s", name.c_str());
    });

    js_pop(J, 1);
}