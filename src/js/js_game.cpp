#include "js_game.h"

#include "content/vfs.h"
#include "core/log.h"
#include "core/settings_vars.h"
#include "platform/arguments.h"

#include "sound/sound_mission.h"
#include "sound/sound_building.h"
#include "sound/sound_walker.h"

#include "overlays/city_overlay.h"
#include "graphics/image_desc.h"
#include "figure/figure.h"
#include "io/gamefiles/lang.h"
#include "platform/version.hpp"
#include "graphics/screen.h"
#include "core/app.h"
#include "game/game.h"
#include "game/mission.h"
#include "game/game_events.h"
#include "game/settings.h"
#include "city/city_finance.h"
#include "io/gamestate/boilerplate.h"
#include "core/profiler.h"
#include "js.h"
#include "mujs/mujs.h"
#include "mujs/jsi.h"
#include "mujs/jsvalue.h"
#include "mujs/jscompile.h"
#include "graphics/elements/ui.h"

#include <vector>
#include <sstream>
#include <string>

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

void js_loc_native(js_State *J) {
    int p1 = js_tointeger(J, 1);
    int p2 = js_tointeger(J, 2);
    verify_no_crash(p1 >= 0 && p2 >= 0);

    pcstr result = lang_get_string(p1, p2);

    js_pushstring(J, result);
}

void js_game_load_text(js_State *J) {
    pcstr path = js_tostring(J, 1);
    char *text = 0;

    vfs::reader ftext = vfs::file_open(path, "rt");
    if (!ftext) {
        return;
    }

    js_pushstring(J, ftext->begin());
}

void js_game_get_image(js_State *J) {
    if (js_gettop(J) < 1) {
        js_pushnull(J);
        return;
    }

    int tid;
    if (js_isstring(J, 1)) {
        pcstr path = js_tostring(J, 1);
        image_desc desc;
        desc.path = path;
        tid = desc.tid();
    } else if (js_isobject(J, 1) && !js_isarray(J, 1)) {
        js_getproperty(J, 1, "pack");
        int16_t pack = !js_isundefined(J, -1) ? (int16_t)js_tointeger(J, -1) : 0;
        js_pop(J, 1);

        js_getproperty(J, 1, "id");
        int16_t id = !js_isundefined(J, -1) ? (int16_t)js_tointeger(J, -1) : 0;
        js_pop(J, 1);

        js_getproperty(J, 1, "offset");
        int16_t offset = !js_isundefined(J, -1) ? (int16_t)js_tointeger(J, -1) : 0;
        js_pop(J, 1);

        image_desc desc{ pack, id, offset };
        tid = desc.tid();
    } else if (js_isnumber(J, 1) || js_iscnumber(J, 1)) {
        int16_t pack = js_touint32(J, 1);
        int16_t id = (js_isnumber(J, 2) || js_iscnumber(J, 2)) ? js_touint32(J, 2) : 0;
        int16_t offset = (js_isnumber(J, 3) || js_iscnumber(J, 3)) ? js_touint32(J, 3) : 0;

        image_desc desc{ pack, id, offset };
        tid = desc.tid();
    } else {
        js_pushnull(J);
        return;
    }

    const image_t *img = image_get(tid);

    if (!img) {
        js_pushnull(J);
        return;
    }

    js_newobject(J);
    js_pushnumber(J, tid); js_setproperty(J, -2, "tid");
    js_pushnumber(J, img->width); js_setproperty(J, -2, "width");
    js_pushnumber(J, img->height); js_setproperty(J, -2, "height");
}

bool js_has_event_handlers(const xstring &event_name) {
    auto it = event_type_handlers.find(event_name);
    return (it != event_type_handlers.end());
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

        verify_no_crash(js_iscallable(J, -1));
        if (!js_iscallable(J, -1)) {
            logs::info("JS event handler '%s' is not callable, skipping", funcname);
            js_pop(J, 1);
            continue;
        }

        js_pushnull(J); // this

        js_newobject(J);

        // First pass: add regular properties
        bool has_ui_elements = false;
        for (const auto &kv : object) {
            const xstring &key = kv.first;
            const bvariant &val = kv.second;

            // Skip UI element markers in first pass
            bstring64 keystr = key.c_str();
            if (keystr.starts_with("__ui_elem_")) {
                has_ui_elements = true;
                continue;
            }

            switch (val.value_type()) {
            case bvariant::etype_bool: js_pushboolean(J, val.as_bool()); break;
            case bvariant::etype_int32: js_pushnumber(J, (double)val.as_int32()); break;
            case bvariant::etype_uint32: js_pushnumber(J, (double)val.as_uint32()); break;
            case bvariant::etype_u16: js_pushnumber(J, (double)val.as_u16()); break;
            case bvariant::etype_float: js_pushnumber(J, (double)val.as_float()); break;
            case bvariant::etype_str: js_pushstring(J, val.as_str().c_str()); break;
            case bvariant::etype_ptr:
                // No direct pointer transport to JS; pass null
                js_pushnull(J);
                break;

            case bvariant::etype_vec2i:
                js_newobject(J);
                {
                    const vec2i pos = val.as_vec2i();
                    js_pushnumber(J, pos.x);
                    js_setproperty(J, -2, "x");
                    js_pushnumber(J, pos.y);
                    js_setproperty(J, -2, "y");
                }
                break;
            case bvariant::etype_none:
            default:
                js_pushundefined(J);
                break;
            }

            js_setproperty(J, -2, key.c_str());
        }

        if (has_ui_elements) {
            for (const auto &kv : object) {
                const xstring &key = kv.first;
                const bvariant &val = kv.second;

                bstring64 keystr = key.c_str();
                if (keystr.starts_with("__ui_elem_")) {
                    auto element_id = keystr.substr(10, -1); // Remove "__ui_elem_" prefix

                    // Call helper function to create proxy object
                    js_getglobal(J, "ui_create_element_proxy");
                    verify_no_crash(js_iscallable(J, -1));
                    js_pushnull(J);  // 'this' context
                    js_pushstring(J, element_id.c_str());

                    int result = js_pcall(J, 1);
                    if (result != 0) {
                        logs::error("JS ui_create_element_proxy() callback error: %s", js_tostring(J, -1));
                        js_pop(J, 1);
                        continue;
                    }

                    // Set the element as property (without __ui_elem_ prefix)
                    js_setproperty(J, -2, element_id.c_str());
                }
            }
        }

        // Call with 1 argument (the object)
        int ok = js_vm_trypcall(J, 1);
        if (!ok) {
            logs::info("Fatal error on call function %s", funcname);
        }

        int current_top = js_gettop(J);
        if (current_top > savetop) {
            js_pop(J, current_top - savetop);
        } else if (current_top < savetop) {
            // Stack underflow - this shouldn't happen, but log it
            logs::info("STACK underflow for %s [%d] (expected %d)", funcname, current_top, savetop);
        }

        // Verify stack is correct
        int final_top = js_gettop(J);
        if (final_top != savetop) {
            logs::info("STACK mismatch for %s [%d] (expected %d) - forcing cleanup", funcname, final_top, savetop);
            // Force cleanup to prevent stack overflow
            while (js_gettop(J) > savetop) {
                js_pop(J, 1);
            }
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
                    if (g_args.is_log_js_handlers()) {
                        logs::info("JS: Function '%s' has modifiers:", prop->name);
                    }
                    function_count++;

                    js_FunctionModifier *mod = func->modifiers;
                    while (mod) {
                        if (g_args.is_log_js_handlers()) {
                            logs::info("  - %s: %s", mod->key ? mod->key : "<no-key>", mod->value ? mod->value : "<no-value>");
                        }
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
                    // If function has a mission modifier, it must match the current mission
                    // If function has no mission modifier, it's a global handler (register for all missions)
                    if (!!require_mission_id) {
                        // Function has a mission modifier - only register if it matches current mission
                        if (!!missionid) {
                            should_handle_this_function = (missionid == require_mission_id);
                        } else {
                            // No current mission, but function requires one - don't register
                            should_handle_this_function = false;
                        }
                    }
                    // If no mission modifier, function is global - register it (should_handle_this_function stays true)

                    if (should_handle_this_function) {
                        mod = func->modifiers;
                        auto is_es = [] (pcstr k) { return strcmp(k, "event") == 0 || strcmp(k, "es") == 0; };
                        while (mod) {
                            if (mod->key && is_es(mod->key)) {
                                auto r = event_type_handlers.insert(std::make_pair(xstring(mod->value),  event_handlers{}));
                                auto &handlers = r.first->second;
                                handlers.insert(prop->name);
                                if (g_args.is_log_js_handlers()) {
                                    logs::info("JS: Registered handler '%s' for event '%s' (mission: '%s')", prop->name, mod->value, missionid.c_str());
                                }
                            } else if (mod->key) {
                                for (config::ModifierIteratorEntry *e = config::ModifierIteratorEntry::tail; e; e = e->next) {
                                    if (e->modifier_key && strcmp(mod->key, e->modifier_key) == 0) {
                                        pcstr value = mod->value ? mod->value : prop->name;
                                        e->callback(J, prop->name, value);
                                        if (g_args.is_log_js_handlers()) {
                                            logs::info("JS: Modifier '%s' -> '%s' (name=%s)", mod->key, value, prop->name);
                                        }
                                        break;
                                    }
                                }
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

config::ESIteratorEntry *config::ESIteratorEntry::tail = nullptr;
config::ModifierIteratorEntry *config::ModifierIteratorEntry::tail = nullptr;

void js_register_entity_systems() {
    for (config::ESIteratorEntry *e = config::ESIteratorEntry::tail; e; e = e->next) {
        e->clear();
    }

    js_State *J = js_vm_state();
    if (!J || !J->G) {
        return;
    }

    js_Property *prop = J->G->head;
    int window_count = 0;

    while (prop) {
        if (prop->value.type == JS_TOBJECT && prop->value.u.object && prop->name) {
            js_Object *obj = prop->value.u.object;

            if (obj->type == JS_COBJECT) {
                pcstr name = prop->name;
                js_getglobal(J, name);

                if (js_hasobject_modifier(J, -1, "es")) {
                    pcstr es_value = js_getobject_modifier(J, -1, "es");
                    for (config::ESIteratorEntry *e = config::ESIteratorEntry::tail; e; e = e->next) {
                        if (e->es_type && es_value && strcmp(es_value, e->es_type) == 0) {
                            window_count++;
                            e->regnew(name);
                            logs::info("JS: Registered '%s' [es=%s]", name, e->es_type);
                            break;
                        }
                    }
                }

                js_pop(J, 1);
            }
        }

        prop = prop->next;
    }

    logs::info("JS: Registered %d dynamic windows", window_count);
}

int __game_screen_width() { return screen_width(); } ANK_FUNCTION(__game_screen_width);
int __game_screen_height() { return screen_height(); } ANK_FUNCTION(__game_screen_height)
int __game_absolute_day() { return game.simtime.absolute_day(true); } ANK_FUNCTION(__game_absolute_day)
xstring __game_version() { return get_version().c_str(); } ANK_FUNCTION(__game_version)
void __game_increase_game_speed() { game.increase_game_speed(); } ANK_FUNCTION(__game_increase_game_speed)
void __game_decrease_game_speed() { game.decrease_game_speed(); } ANK_FUNCTION(__game_decrease_game_speed)
void __game_increase_scroll_speed() { game.increase_scroll_speed(); } ANK_FUNCTION(__game_increase_scroll_speed)
void __game_decrease_scroll_speed() { game.decrease_scroll_speed(); } ANK_FUNCTION(__game_decrease_scroll_speed)
void __game_set_game_speed(int v) { game.game_speed = v; } ANK_FUNCTION_1(__game_set_game_speed)
void __game_set_scroll_speed(int v) { game.scroll_speed = v; } ANK_FUNCTION_1(__game_set_scroll_speed)
void __game_request_exit() { app_request_exit(); } ANK_FUNCTION(__game_request_exit)
void __game_set_player_name(pcstr name) { g_settings.set_player_name((const uint8_t *)name); } ANK_FUNCTION_1(__game_set_player_name)
bool __game_load_savegame(pcstr filename) { return GamestateIO::load_savegame(filename); } ANK_FUNCTION_1(__game_load_savegame)

std::optional<bvariant> __game_get_property(pcstr property) {
    return archive_helper::get(game, property, true);
}
ANK_FUNCTION_1(__game_get_property)

void js_register_game_objects(js_State *J) {
}

void js_register_game_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_log_info_native, "__log_info_native", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_log_warn_native, "__log_warning_native", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_loc_native, "__loc", 2);
    REGISTER_GLOBAL_FUNCTION(J, js_game_load_text, "load_text", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_game_get_image, "get_image", 1);
    REGISTER_GLOBAL_FUNCTION(J, js_register_console_command, "__register_console_command", 3);

    animation_t::global_hashtime = game.frame;
    for (config::FunctionIterator *s = config::FunctionIterator::tail; s; s = s->next) {
        s->func(J);
    }
}

void js_unref_function(xstring onclick_ref) {
    if (!onclick_ref.empty()) {
        js_State *J = js_vm_state();
        assert(J);
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

void js_call_function_bool(xstring js_ref, bool param) {
    if (js_ref.empty()) {
        return;
    }

    js_State *J = js_vm_state();
    verify_no_crash(J);

    js_getregistry(J, js_ref.c_str());
    if (js_iscallable(J, -1)) {
        js_pushnull(J);
        js_pushboolean(J, param);
        int result = js_pcall(J, 1);
        if (result != 0) {
            logs::error("JS dialog callback error: %s", js_tostring(J, -1));
            js_pop(J, 1);
        }
    } else {
        js_pop(J, 1);
    }
}

pcstr js_call_function_with_result(xstring js_ref, int param1, int param2) {
    if (js_ref.empty()) {
        return "";
    }

    js_State *J = js_vm_state();
    assert(J);

    // Get the function from registry using the reference
    js_getregistry(J, js_ref.c_str());
    if (js_iscallable(J, -1)) {
        js_pushnull(J);  // 'this' context
        js_pushnumber(J, (double)param1);
        js_pushnumber(J, (double)param2);
        int result = js_pcall(J, 2);
        if (result != 0) {
            logs::error("JS textfn callback error: %s", js_tostring(J, -1));
            js_pop(J, 1);
            return "";
        }

        pcstr result_str = "";
        if (js_isstring(J, -1)) {
            result_str = js_tostring(J, -1);
        } else if (!js_isundefined(J, -1) && !js_isnull(J, -1)) {
            result_str = js_tostring(J, -1);
        }
        js_pop(J, 1);  // Pop the result
        return result_str;
    } else {
        js_pop(J, 1);
    }

    return "";
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
