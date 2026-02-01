#include "js.h"

#include "content/dir.h"
#include "core/log.h"
#include "core/profiler.h"
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
#include "content/mods.h"
#include "scenario/scenario.h"
#include "game/mission.h"
#include "widget/debug_console.h"

#include <filesystem>
#include <new>
#include <cstdlib>

#if defined(GAME_PLATFORM_LINUX)
#include <linux/limits.h>
#elif defined(GAME_PLATFORM_MACOSX)
#include <sys/syslimits.h>
#endif

#define MAX_FILES_RELOAD 255


struct {
    svector<vfs::path, 4> scripts_folders;
    vfs::path files2load[MAX_FILES_RELOAD];
    int files2load_num;
    int have_error;
    bstring256 error_str;
    js_State *J;
} vm;

void js_reset_vm_state();

declare_console_command_p(reload_scripts){
    os << "Reloading JavaScript VM from scratch..." << std::endl;

    int scenario_id = g_scenario.campaign_scenario_id();
    mission_id_t missionid(scenario_id);

    js_vm_setup();

    bool reloaded = js_vm_sync(missionid.value());
    os << (reloaded ? "JavaScript VM reloaded successfully!" : "JavaScript VM reloaded (no files to sync)") << std::endl;
}

static void js_vm_log_stacktrace(js_State *J) {
    // Try to get stack trace from error object if it's an Error
    if (js_isobject(J, -1)) {
        if (js_hasproperty(J, -1, "stackTrace")) {
            js_getproperty(J, -1, "stackTrace");
            if (js_isstring(J, -1)) {
                const char *stack_trace = js_tostring(J, -1);
                logs::info("!!! Stack trace: %s", stack_trace);
                js_pop(J, 1);
                return;
            }
            js_pop(J, 1);
        }
    }
    
    // Fallback: try to get stack trace from current state
    // Access internal trace array (this requires accessing internal structure)
    // Note: This is implementation-dependent and may break if mujs internals change
    if (J && J->tracetop >= 0) {
        logs::info("!!! Call stack:");
        for (int n = J->tracetop; n >= 0; --n) {
            const char *name = J->trace[n].name;
            const char *file = J->trace[n].file;
            int line = J->trace[n].line;
            if (line > 0) {
                if (name && name[0]) {
                    logs::info("!!!   at %s (%s:%d)", name, file ? file : "<unknown>", line);
                } else {
                    logs::info("!!!   at %s:%d", file ? file : "<unknown>", line);
                }
            } else {
                logs::info("!!!   at %s (%s)", name ? name : "<anonymous>", file ? file : "<unknown>");
            }
        }
    }
}

// Helper function to dump stack values for debugging
static void js_vm_dump_stack(js_State *J) {
    int stack_size = js_gettop(J);
    logs::info("!!! ==================================================");
    logs::info("!!! Stack Dump (size: %d):", stack_size);
    logs::info("!!! ==================================================");
    
    if (stack_size == 0) {
        logs::info("!!!   <empty stack>");
        logs::info("!!! ==================================================");
        return;
    }
    
    int items_to_show = stack_size < 10 ? stack_size : 10;
    
    for (int i = 0; i < items_to_show; i++) {
        int idx = i - stack_size; // Convert to negative index
        bstring256 value_desc;
        
        if (js_isundefined(J, idx)) {
            value_desc = "undefined";
        } else if (js_isnull(J, idx)) {
            value_desc = "null";
        } else if (js_isboolean(J, idx)) {
            value_desc.printf("boolean: %s", js_toboolean(J, idx) ? "true" : "false");
        } else if (js_isnumber(J, idx)) {
            value_desc.printf("number: %g", js_tonumber(J, idx));
        } else if (js_isstring(J, idx)) {
            const char *str = js_tostring(J, idx);
            if (str && strlen(str) > 50) {
                value_desc.printf("string: \"%.50s...\"", str);
            } else {
                value_desc.printf("string: \"%s\"", str ? str : "");
            }
        } else if (js_isobject(J, idx)) {
            if (js_isarray(J, idx)) {
                value_desc.printf("array (length: %d)", js_getlength(J, idx));
            } else if (js_iscallable(J, idx)) {
                value_desc = "function";
            } else {
                // Try to get some info about the object
                int prop_count = 0;
                bstring256 props_preview;
                
                // Save stack state
                int save_top = js_gettop(J);
                
                // Try to iterate first few properties
                js_pushiterator(J, idx, 0);
                const char *prop_name;
                while (prop_count < 3 && (prop_name = js_nextiterator(J, -1)) != NULL) {
                    if (prop_count > 0) {
                        props_preview.append(", ");
                    }
                    props_preview.append(prop_name);
                    prop_count++;
                }
                js_pop(J, 1); // Remove iterator
                
                // Restore stack state
                while (js_gettop(J) > save_top) {
                    js_pop(J, 1);
                }
                
                if (prop_count > 0) {
                    value_desc.printf("object {%s, ...}", props_preview.c_str());
                } else {
                    value_desc = "object {}";
                }
            }
        } else {
            value_desc = "<unknown type>";
        }
        
        logs::info("!!!   [%d]: %s", i, value_desc.c_str());
    }
    
    if (stack_size > 10) {
        logs::info("!!!   ... (%d more items not shown)", stack_size - 10);
    }
    logs::info("!!! ==================================================");
}

int js_vm_trypcall(js_State *J, int params) {
    if (vm.have_error) {
        return 0;
    }

    int error = js_pcall(J, params);
    if (error) {
        vm.have_error = 1;
        const char *error_msg = js_tostring(J, -1);
        
        // Log error type if it's an Error object
        if (js_isobject(J, -1)) {
            if (js_hasproperty(J, -1, "name")) {
                js_getproperty(J, -1, "name");
                const char *error_name = js_tostring(J, -1);
                logs::info("!!! Error type: %s", error_name ? error_name : "<unknown>");
                js_pop(J, 1);
            }
        }
        
        // Log full error message (MuJS now provides detailed context)
        const char *cur_symbol = error_msg;
        const char *start_str = cur_symbol;
        bstring256 temp_str;
        while (*cur_symbol) {
            if (*cur_symbol != '\n') {
                cur_symbol++;
                continue;
            }

            temp_str.printf("%.*s", cur_symbol - start_str, start_str);
            start_str = cur_symbol + 1;
            cur_symbol += 2;
            logs::info("!!! %s", temp_str.c_str());
        }
        logs::info("!!! %s", start_str);
        
        // Log stack trace
        js_vm_log_stacktrace(J);
        
        // Dump stack values for additional debugging info
        js_vm_dump_stack(J);
        
        vm.error_str = error_msg;
        js_pop(J, 1);
        return 0;
    }

    js_pop(J, 1);
    return 1;
}

bool js_vm_have_error() {
    return vm.have_error;
}

int js_vm_load_file_and_exec(pcstr path) {
    if (!path || !*path) {
        return 0;
    }

    pcstr npath = (*path == ':') ? (path + 1) : path;

    auto r = mods_find_script(npath, true);
    if (!!r.reader) {
        const uint32_t fsize = r.reader->size();
        std::string data = (char *)r.reader->data();

        int error = js_ploadstring(vm.J, r.path.c_str(), data.c_str());
        if (error) {
            logs::info("!!! Error on open file %s", js_tostring(vm.J, -1));
            return 0;
        }

        js_getglobal(vm.J, "");
        int ok = js_vm_trypcall(vm.J, 0);
        if (!ok) {
            logs::info("Fatal error on call base after load %s", r.path.c_str());
            if (vm.error_str.len() > 0) {
                logs::info("Error details: %s", vm.error_str.c_str());
            } else if (js_gettop(vm.J) > 0) {
                pcstr error_msg = js_tostring(vm.J, -1);
                if (error_msg && *error_msg) {
                    logs::info("Error details: %s", error_msg);
                }
            }
            return 0;
        }
        return 1;
    }

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
        if (vm.error_str.len() > 0) {
            logs::info("Error details: %s", vm.error_str.c_str());
        } else if (js_gettop(vm.J) > 0) {
            pcstr error_msg = js_tostring(vm.J, -1);
            if (error_msg && *error_msg) {
                logs::info("Error details: %s", error_msg);
            }
        }
        //js_pop(internal_J, 1);
        return 0;
    }
    return 1;
}

js_State *js_vm_state() {
    return vm.J;
}

bool js_vm_sync(const xstring &mission_id) {
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

    js_register_game_handlers(mission_id);
    js_scan_and_register_windows();

    config::refresh(vm.J);

    vm.files2load_num = 0;
    vm.have_error = 0;
    return true;
}

void js_vm_reload_file(pcstr path) {
    vm.files2load[vm.files2load_num] = path;
    vm.files2load_num++;
}

int js_vm_exec_function_args(pcstr funcname, const char *szTypes, ...) {
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
        if (vm.error_str.len() > 0) {
            logs::info("Error details: %s", vm.error_str.c_str());
        } else if (js_gettop(vm.J) > 0) {
            pcstr error_msg = js_tostring(vm.J, -1);
            if (error_msg && *error_msg) {
                logs::info("Error details: %s", error_msg);
            }
        }
        return 0;
    }

    js_pop(vm.J, 2);
    if( savetop - js_gettop(vm.J) != 0 ) {
        logs::info( "STACK grow for %s [%d]", funcname, js_gettop(vm.J) );
    }
    return ok;
}

int js_vm_exec_function(pcstr funcname) {
    return js_vm_exec_function_args(funcname, "");
}

void js_vm_load_module(js_State *J) {
    pcstr scriptName = js_tostring(J, 1);

    vm.files2load[vm.files2load_num] = scriptName;
    vm.files2load_num++;
}

void js_game_panic(js_State *J) {
    logs::info("JSE !!! Uncaught exception: %s", js_tostring(J, -1));
}

int js_game_import(js_State *J, pcstr filename) {
    vm.files2load[vm.files2load_num] = vfs::path(":", filename, ".js");
    vm.files2load_num++;

    return 0;
}

void js_register_vm_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_vm_load_module, "include", 1);
}

#if defined(TRACY_MEMORY_ENABLE)
extern bool TracyProfilerAvailable;
#endif
void *js_alloc_wrapper(void *actx, void *ptr, int size) {
    if (size == 0) {
        if (ptr) {
#if defined(TRACY_MEMORY_ENABLE)
            if (TracyProfilerAvailable) {
                TracyFreeS(ptr, 20);
            }
#endif
            free(ptr);
        }
        return nullptr;
    }

    if (!ptr) {
        void *new_ptr = malloc(size);
#if defined(TRACY_MEMORY_ENABLE)
        if (new_ptr && TracyProfilerAvailable) {
            TracyAllocS(new_ptr, size, 20);
        }
#endif
        return new_ptr;
    }

    void *old_ptr = ptr;
    void *new_ptr = realloc(ptr, size);

#if defined(TRACY_MEMORY_ENABLE)
    if (TracyProfilerAvailable && new_ptr) {
        TracyFreeS(old_ptr, 20);
        TracyAllocS(new_ptr, size, 20);
    }
#endif

    if (!new_ptr && size > 0) {
        return nullptr;
    }
    return new_ptr;
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

    vm.J = js_newstate(js_alloc_wrapper, nullptr, JS_STRICT);
    js_atpanic(vm.J, js_game_panic);
    js_registerimport(vm.J, js_game_import);

    js_register_vm_functions(vm.J);
    js_register_game_functions(vm.J);
    js_register_game_objects(vm.J);
    js_register_mission_objects(vm.J);
    js_register_empire_objects(vm.J);
    js_register_city_objects(vm.J);
    js_register_ui_objects(vm.J);
    //js_register_mouse_functions(vm.J);
    //js_register_hotkey_functions(vm.J);
    js_register_game_constants(vm.J);
    js_register_game_handlers({});
    js_register_menu(vm.J);

    int ok = js_vm_load_file_and_exec(":modules.js");
    if (ok) {
        int stack_top = js_gettop(vm.J);
        if (stack_top > 0) {
            js_pop(vm.J, stack_top);
        }
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