#include "js.h"

#include "content/dir.h"
#include "core/log.h"
#include "graphics/window.h"
#include "js/js_constants.h"
#include "js/js_defines.h"
#include "js/js_folder_notifier.h"
#include "js/js_game.h"
#include "graphics/elements/panel.h"
#include "mujs/mujs.h"
#include "mujs/jsi.h"
#include "mujs/jsvalue.h"
#include "mujs/jscompile.h"
#include "platform/arguments.h"
#include "platform/platform.h"
#include "core/variant.h"

#include <filesystem>

#if defined(GAME_PLATFORM_LINUX)
#include <linux/limits.h>
#elif defined(GAME_PLATFORM_MACOSX)
#include <sys/syslimits.h>
#endif

#define MAX_FILES_RELOAD 255

using event_handlers = std::unordered_set<xstring>;
struct {
    svector<vfs::path, 4> scripts_folders;
    vfs::path files2load[MAX_FILES_RELOAD];
    int files2load_num;
    int have_error;
    bstring256 error_str;
    js_State *J;
    std::unordered_map<xstring, event_handlers> event_type_handlers;
} vm;

void js_reset_vm_state();

int js_vm_trypcall(js_State *J, int params) {
    if (vm.have_error) {
        return 0;
    }

    int error = js_pcall(vm.J, params);
    if (error) {
        vm.have_error = 1;
        const char *cur_symbol = js_tostring(vm.J, -1);
        const char *start_str = cur_symbol;
        while (*cur_symbol) {
            if (*cur_symbol != '\n') {
                cur_symbol++;
                continue;
            }

            vm.error_str.printf("%.*s", cur_symbol - start_str, start_str);
            start_str = cur_symbol + 1;
            cur_symbol += 2;
            logs::info("!!! pcall error %s", vm.error_str.c_str());
        }
        logs::info("!!! pcall error %s", start_str);
        js_pop(J, 1);
        return 0;
    }

    js_pop(vm.J, -1);
    return 1;
}

int js_vm_load_file_and_exec(pcstr path) {
    if (!path || !*path) {
        return 0;
    }

    pcstr npath = (*path == ':') ? (path + 1) : path;

    vfs::path rpath = path;
    if (!vm.scripts_folders.empty()) {
        rpath = js_vm_get_absolute_path(npath);
    } 

    vfs::reader reader = vfs::file_open(rpath, "rt");
    if (!reader) {
        reader = vfs::file_open(path, "rt");
    }

    if (!reader) {
        logs::info("!!! Cant find script at %s", rpath.c_str());
        return 0;
    }

    const uint32_t fsize = reader->size();
    std::string data = (char *)reader->data();

    int error = js_ploadstring(vm.J, rpath, data.c_str());
    if (error) {
        logs::info("!!! Error on open file %s", js_tostring(vm.J, -1));
        return 0;
    }

    js_getglobal(vm.J, "");
    int ok = js_vm_trypcall(vm.J, 0);
    if (!ok) {
        logs::info("Fatal error on call base after load %s", path);
        //js_pop(internal_J, 1);
        return 0;
    }
    return 1;
}

void js_call_event_handlers(const xstring& event_name, const bvariant_map& object) {
    auto it = vm.event_type_handlers.find(event_name);
    if (it == vm.event_type_handlers.end()) {
        return;
    }

    if (vm.have_error || vm.J == nullptr) {
        return;
    }

    const event_handlers &handlers = it->second;
    for (const auto &handlerName : handlers) {
        const char *funcname = handlerName.c_str();

        int savetop = js_gettop(vm.J);
        js_getglobal(vm.J, funcname);
        js_pushnull(vm.J); // this

        // Build 1st argument: a plain object with provided properties
        js_newobject(vm.J);
        for (const auto &kv : object) {
            const xstring &key = kv.first;
            const bvariant &val = kv.second;

            switch (val.value_type()) {
            case bvariant::etype_bool:
                js_pushboolean(vm.J, val.as_bool());
                break;
            case bvariant::etype_int32:
                js_pushnumber(vm.J, (double)val.as_int32());
                break;
            case bvariant::etype_uint32:
                js_pushnumber(vm.J, (double)val.as_uint32());
                break;
            case bvariant::etype_u16:
                js_pushnumber(vm.J, (double)val.as_u16());
                break;
            case bvariant::etype_float:
                js_pushnumber(vm.J, (double)val.as_float());
                break;
            case bvariant::etype_str:
                js_pushstring(vm.J, val.as_str().c_str());
                break;
            case bvariant::etype_ptr:
                // No direct pointer transport to JS; pass null
                js_pushnull(vm.J);
                break;
            case bvariant::etype_none:
            default:
                js_pushundefined(vm.J);
                break;
            }

            js_setproperty(vm.J, -2, key.c_str());
        }

        // Call with 1 argument (the object)
        int ok = js_vm_trypcall(vm.J, 1);
        if (!ok) {
            logs::info("Fatal error on call function %s", funcname);
        }

        // Clean up stack: function result and 'this' and function
        js_pop(vm.J, 2);
        if (savetop - js_gettop(vm.J) != 0) {
            logs::info("STACK grow for %s [%d]", funcname, js_gettop(vm.J));
        }
    }
}

void js_register_modified_functions(js_State *J) {
    js_Object *global = J->G;
    if (!global) {
        logs::info("JS: Global object is null");
        return;
    }

    logs::info("JS: Scanning for functions with modifiers...");

    js_Property *prop = global->head;
    int function_count = 0;

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
                        if (mod->key && strcmp(mod->key, "event") == 0) {
                            auto r = vm.event_type_handlers.insert(std::make_pair(xstring(mod->value), event_handlers{}));
                            auto &handlers = r.first->second;
                            handlers.insert(prop->name);
                        }
                        mod = mod->next;
                    }
                }
            }
        }
        prop = prop->next;
    }

    logs::info("JS: Found %d functions with modifiers", function_count);
}

js_State *js_vm_state() {
    return vm.J;
}

bool js_vm_sync() {
    if (!vm.files2load_num) {
        return false;
    }

    if (vm.have_error) {
        js_reset_vm_state();
    }

    if (vm.files2load_num > 0) {
        for (int i = 0; i < vm.files2load_num; i++) {
            logs::info("JS: script reloaded %s", vm.files2load[i].c_str());
            js_vm_load_file_and_exec(vm.files2load[i]);
        }
    }

    for (int i = 0; i < MAX_FILES_RELOAD; ++i) {
        vm.files2load[i].clear();
    }

    config::refresh(vm.J);
    js_register_modified_functions(vm.J);

    vm.files2load_num = 0;
    vm.have_error = 0;
    return true;
}

void js_vm_reload_file(const char *path) {
    vm.files2load[vm.files2load_num] = path;
    vm.files2load_num++;
}

int js_vm_exec_function_args(const char *funcname, const char *szTypes, ...) {
    if (vm.have_error)
        return 0;
    int i, ok, savetop;
    char msg[2] = { 0, 0 };
    va_list vl;

    if (vm.J == 0)
        return 1;

    //log_info("script-if:// exec function ", funcname, 0);

    savetop = js_gettop(vm.J);
    js_getglobal(vm.J, funcname);
    js_pushnull(vm.J);

    //  szTypes is the last argument specified; you must access
    //  all others using the variable-argument macros.
    va_start( vl, szTypes );

    // Step through the list.
    for( i = 0; szTypes[i] != '\0'; ++i ) {
        switch( szTypes[i] ) {   // Type to expect.
            case 'i':
                js_pushnumber(vm.J, va_arg(vl, int));
                break;
            case 'f':
                js_pushnumber(vm.J, va_arg(vl, double));
                break;
            case 'c':
                msg[0] = va_arg(vl, int);
                js_pushstring(vm.J, msg);
                break;
            case 's':
                js_pushstring(vm.J, va_arg(vl, char *));
                break;

            default:
                js_pushnull(vm.J);
                logs::info("!!! Undefined value for js.pcall engine_js_push when find ");
                break;
        }
    }
    va_end( vl );

    ok = js_vm_trypcall(vm.J, (int)strlen(szTypes));
    if (!ok) {
        logs::info("Fatal error on call function %s", funcname);
        return 0;
    }

    js_pop(vm.J, 2);
    if( savetop - js_gettop(vm.J) != 0 ) {
        logs::info( "STACK grow for %s [%d]", funcname, js_gettop(vm.J) );
    }
    return ok;
}

int js_vm_exec_function(const char *funcname) {
    return js_vm_exec_function_args(funcname, "");
}

void js_vm_load_module(js_State *J) {
    const char *scriptName = js_tostring(J, 1);

    vm.files2load[vm.files2load_num] = scriptName;
    vm.files2load_num++;
}

void js_game_panic(js_State *J) {
    logs::info("JSE !!! Uncaught exception: %s", js_tostring(J, -1));
}

int js_game_import(js_State *J, const char* filename) {
    vm.files2load[vm.files2load_num] = vfs::path(":", filename, ".js");
    vm.files2load_num++;

    return 0;
}

void js_register_vm_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_vm_load_module, "include", 1);
}

void js_reset_vm_state() {
    if (vm.J) {
        js_freestate(vm.J);
        vm.J = NULL;
    }

    for (int i = 0; i < MAX_FILES_RELOAD; ++i) {
        vm.files2load[i].clear();
    }
    vm.files2load_num = 0;
    vm.have_error = 0;

    vm.J = js_newstate(NULL, NULL, JS_STRICT);
    js_atpanic(vm.J, js_game_panic);
    js_registerimport(vm.J, js_game_import);

    js_register_vm_functions(vm.J);
    js_register_game_functions(vm.J);
    js_register_game_objects(vm.J);
    //js_register_mouse_functions(vm.J);
    //js_register_hotkey_functions(vm.J);
    js_register_game_constants(vm.J);
    js_register_city_advisors(vm.J);
    js_register_modified_functions(vm.J);
    js_register_menu(vm.J);

    int ok = js_vm_load_file_and_exec(":modules.js");
    if (ok) {
        js_pop(vm.J, 2); //restore stack after call js-function
    }
    logs::info( "STACK state %d", js_gettop(vm.J));
}

void js_vm_add_scripts_folder(vfs::path folder) {
    vm.scripts_folders.push_back(folder);
}

vfs::path js_vm_get_absolute_path(vfs::path path) {
#if defined(GAME_PLATFORM_WIN)
    bool is_absolute_path = path.data()[1] == ':' && path.len() > 2;
#else
    bool is_absolute_path = path.data()[0] == '/' && path.len() > 1;
#endif
    if (is_absolute_path) {
        return path;
    }

    vfs::path buffer;
    for (const auto &folder : vm.scripts_folders) {
        if (!!folder) {
            vfs::path conpath(folder, "/", path);
            if (g_args.is_logjsfiles()) {
                logs::info("js:get_absolute_path %s", conpath.c_str());
            }

#if defined(GAME_PLATFORM_WIN)
            pstr p = _fullpath(buffer, conpath, buffer.capacity);
#elif defined(GAME_PLATFORM_LINUX) || defined(GAME_PLATFORM_MACOSX)
            char resolved[PATH_MAX];
            if (!realpath(conpath, resolved)) {
                continue;
            }
            buffer = resolved;
#endif
            buffer.replace('\\', '/');

            if (!std::filesystem::exists(buffer.c_str())) {
                continue;
            }

            return buffer;
        }
    }

    buffer = vfs::content_path(path);
    if (std::filesystem::exists(buffer.c_str())) {
        return buffer;
    }

    return path;
}

void js_vm_setup() {
    vm.J = nullptr;
    js_reset_vm_state();

    vfs::path abspath = js_vm_get_absolute_path("");
    vfs::path modules_file(abspath, "/modules.js");
    bool scripts_folder_exists = std::filesystem::exists(modules_file.c_str());
    if (scripts_folder_exists) {
        js_vm_notifier_watch_directory_init(abspath);
    }
}
