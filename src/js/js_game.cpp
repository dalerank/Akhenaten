#include "js_game.h"

#include "content/vfs.h"
#include "core/log.h"
#include "core/settings_vars.h"

#include "sound/sound_mission.h"
#include "sound/sound_building.h"
#include "sound/sound_walker.h"

#include "overlays/city_overlay.h"
#include "graphics/image_desc.h"
#include "figure/figure.h"
#include "figure/image.h"
#include "io/gamefiles/lang.h"
#include "platform/version.hpp"
#include "graphics/screen.h"
#include "game/game.h"
#include "game/mission.h"

#include "js.h"
#include "mujs/mujs.h"
#include "mujs/jsi.h"
#include "mujs/jsvalue.h"
#include "mujs/jscompile.h"
#include "mujs/mujs.h"

#include <vector>

g_archive g_config_arch{nullptr};

using event_handlers = std::unordered_set<xstring>;
std::unordered_map<xstring, event_handlers> event_type_handlers;

void js_log_info_native(js_State *J) {
    if (js_isundefined(J, 1)) {
        logs::info("log() Try to print undefined object", 0, 0);
    } else {
        logs::info("%s", js_tostring(J, 1));
    }
    js_pushundefined(J);
}

void js_log_warn_native(js_State *J) {
    if (js_isundefined(J, 1)) {
        logs::info("warning() Try to print undefined object", 0, 0);
    } else {
        logs::info("WARN: %s", js_tostring(J, 1));
    }
    js_pushundefined(J);
}

void js_game_load_text(js_State *J) {
    const char *path = js_tostring(J, 1);
    char *text = 0;

    vfs::reader ftext = vfs::file_open(path, "rt");
    if (!ftext) {
        return;
    }
    
    js_pushstring(J, ftext->begin());
}

void js_call_event_handlers(const xstring &event_name, const bvariant_map &object) {
    auto it = event_type_handlers.find(event_name);
    if (it == event_type_handlers.end()) {
        return;
    }

    auto J = js_vm_state();
    if (js_vm_have_error() || J == nullptr) {
        return;
    }

    const event_handlers &handlers = it->second;
    for (const auto &handlerName : handlers) {
        const char *funcname = handlerName.c_str();

        int savetop = js_gettop(J);
        js_getglobal(J, funcname);
        js_pushnull(J); // this

        // Build 1st argument: a plain object with provided properties
        js_newobject(J);
        for (const auto &kv : object) {
            const xstring &key = kv.first;
            const bvariant &val = kv.second;

            switch (val.value_type()) {
            case bvariant::etype_bool:
                js_pushboolean(J, val.as_bool());
                break;
            case bvariant::etype_int32:
                js_pushnumber(J, (double)val.as_int32());
                break;
            case bvariant::etype_uint32:
                js_pushnumber(J, (double)val.as_uint32());
                break;
            case bvariant::etype_u16:
                js_pushnumber(J, (double)val.as_u16());
                break;
            case bvariant::etype_float:
                js_pushnumber(J, (double)val.as_float());
                break;
            case bvariant::etype_str:
                js_pushstring(J, val.as_str().c_str());
                break;
            case bvariant::etype_ptr:
                // No direct pointer transport to JS; pass null
                js_pushnull(J);
                break;
            case bvariant::etype_none:
            default:
                js_pushundefined(J);
                break;
            }

            js_setproperty(J, -2, key.c_str());
        }

        // Call with 1 argument (the object)
        int ok = js_vm_trypcall(J, 1);
        if (!ok) {
            logs::info("Fatal error on call function %s", funcname);
        }

        // Clean up stack: function result and 'this' and function
        js_pop(J, 2);
        if (savetop - js_gettop(J) != 0) {
            logs::info("STACK grow for %s [%d]", funcname, js_gettop(J));
        }
    }
}

void js_register_game_handlers(xstring missionid) {
    auto J = js_vm_state();
    js_Object *global = J->G;
    if (!global) {
        logs::info("JS: Global object is null");
        return;
    }

    logs::info("JS: Scanning for functions with modifiers...");

    js_Property *prop = global->head;
    int function_count = 0;
    event_type_handlers.clear();

    while (prop) {
        if (prop->value.type == JS_TOBJECT && prop->value.u.object) {
            js_Object *obj = prop->value.u.object;
            if (obj->type == JS_CFUNCTION || obj->type == JS_CSCRIPT) {
                js_Function *func = obj->u.f.function;

                if (func && func->modifiers && prop->name) {
                    logs::info("JS: Function '%s' has modifiers:", prop->name);
                    function_count++;

                    js_FunctionModifier *mod = func->modifiers;
                    while (mod) {
                        logs::info("  - %s: %s", mod->key ? mod->key : "<no-key>", mod->value ? mod->value : "<no-value>");
                        mod = mod->next;
                    }

                    xstring require_mission_id;
                    mod = func->modifiers;
                    while (mod) {
                        if (mod->key && strcmp(mod->key, "mission") == 0) {
                            require_mission_id = mod->value;
                            break;
                        }
                        mod = mod->next;
                    }

                    bool should_handle_this_function = true;
                    if (!!require_mission_id && !!missionid) {
                        should_handle_this_function = (missionid == require_mission_id);
                    }

                    if (should_handle_this_function) {
                        mod = func->modifiers;
                        while (mod) {
                            if (mod->key && strcmp(mod->key, "event") == 0) {
                                auto r = event_type_handlers.insert(std::make_pair(xstring(mod->value), event_handlers{}));
                                auto &handlers = r.first->second;
                                handlers.insert(prop->name);
                            }
                            mod = mod->next;
                        }
                    }
                }
            }
        }
        prop = prop->next;
    }

    logs::info("JS: Found %d functions with modifiers", function_count);
}

static void js_game_screen_w_getter(js_State *J) {
    js_pushnumber(J, screen_width());
}

static void js_game_screen_h_getter(js_State *J) {
    js_pushnumber(J, screen_height());
}

static void js_game_absolute_day_getter(js_State *J) {
    js_pushnumber(J, game.simtime.absolute_day(true));
}

void js_register_game_objects(js_State *J) {
    js_newobject(J);
    {
        js_pushstring(J, get_version().c_str()); 
        js_setproperty(J, -2, "version");

        js_newobject(J);
            js_newcfunction(J, js_game_screen_w_getter, "get_w", 0); js_pushundefined(J);
            js_defaccessor(J, -3, "w", JS_READONLY);

            js_newcfunction(J, js_game_screen_h_getter, "get_h", 0); js_pushundefined(J);
            js_defaccessor(J, -3, "h", JS_READONLY);
        js_setproperty(J, -2, "screen");
        
        js_newcfunction(J, js_game_absolute_day_getter, "get_absolute_day", 0); js_pushundefined(J);
        js_defaccessor(J, -2, "absolute_day", JS_READONLY);
    }
    js_setglobal(J, "game");
}

void js_register_game_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_log_info_native, "__log_info_native", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_log_warn_native, "__log_warning_native", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_load_text, "load_text", 1);
    
    animation_t::global_hashtime = game.frame;
    for (config::FunctionIterator *s = config::FunctionIterator::tail; s; s = s->next) {
        s->func(J);
    }
}

void js_unref_function(xstring onclick_ref) {
    js_State *J = js_vm_state();
    assert(J);
    if (!onclick_ref.empty()) {
        js_unref(J, onclick_ref .c_str());
    }
}

void js_call_function(xstring js_ref) {
    if (js_ref.empty()) {
        return;
    }

    js_State *J = js_vm_state();
    assert(J);

    // Get the function from registry using the reference
    js_getregistry(J, js_ref.c_str());
    if (js_iscallable(J, -1)) {
        js_pushnull(J);  // 'this' context
        int result = js_pcall(J, 0);
        if (result != 0) {
            logs::error("JS onclick callback error: %s", js_tostring(J, -1));
            js_pop(J, 1);
        }
    } else {
        js_pop(J, 1);
    }
}

void config::refresh(archive arch) {
    g_config_arch = {arch.state};
    animation_t::global_hashtime = game.frame;
    for (ArchiveIterator *s = ArchiveIterator::tail; s; s = s->next) {
        s->func();
    }
}

archive config::load(pcstr filename) {
    vfs::path fspath = vfs::content_path(filename);
    js_vm_load_file_and_exec(fspath);
    return {js_vm_state()};
}
