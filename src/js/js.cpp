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
#include "core/interlocked.h"
#include "core/variant.h"
#include "content/mods.h"
#include "scenario/scenario.h"
#include "game/mission.h"
#include "widget/debug_console.h"

#include "js/js_debugger.h"
#include "js/js_self_tests.h"

#include <filesystem>
#include <new>
#include <cstdlib>
#include <cstring>
#include <memory_resource>

#if defined(GAME_PLATFORM_LINUX)
#include <linux/limits.h>
#include <malloc.h>
#elif defined(GAME_PLATFORM_MACOSX)
#include <sys/syslimits.h>
#include <malloc/malloc.h>
#elif defined(GAME_PLATFORM_ANDROID)
#include <malloc.h>
#endif

struct {
    const size_t FRAME_ALLOC_BUFFER_SIZE = 64 * 1024;
    svector<vfs::path, 4> scripts_folders;
    hvector<vfs::path, 16> files2load;
    int have_error;
    bstring256 error_str;
    js_State *J;
    char *frame_alloc_buffer = nullptr;
    std::pmr::monotonic_buffer_resource frame_alloc_ctx;
} vm;

namespace
{
    volatile std::uint64_t g_mujs_heap_bytes = 0;

    void mujs_heap_add_bytes(size_t n)
    {
        threading::xchgadd(&g_mujs_heap_bytes, static_cast<std::uint64_t>(n));
    }

    void mujs_heap_sub_bytes(size_t n)
    {
        threading::xchgadd(&g_mujs_heap_bytes, static_cast<std::uint64_t>(0 - static_cast<std::uint64_t>(n)));
    }

    size_t mujs_malloc_block_size(void *ptr)
    {
        if (!ptr) {
            return 0;
        }
#if defined(GAME_PLATFORM_WIN)
        return _msize(ptr);
#elif defined(GAME_PLATFORM_MACOSX)
        return malloc_size(ptr);
#elif defined(GAME_PLATFORM_LINUX) || defined(GAME_PLATFORM_ANDROID)
        return malloc_usable_size(ptr);
#else
        return 0;
#endif
    }
} // namespace

uint64_t js_mujs_heap_bytes()
{
    return g_mujs_heap_bytes;
}

void js_reset_vm_state();

declare_console_command_p(reload_scripts){
    os << "Reloading JavaScript VM from scratch..." << std::endl;

    int scenario_id = g_scenario.campaign_scenario_id();
    mission_id_t missionid(scenario_id);

    js_vm_setup();

    bool reloaded = js_vm_sync(missionid.value());
    os << (reloaded ? "JavaScript VM reloaded successfully!" : "JavaScript VM reloaded (no files to sync)") << std::endl;
}

declare_console_command_p(js_debugger){
    std::string subcmd;
    is >> subcmd;

    if (subcmd == "start") {
        int port = 4711;
        is >> port; // optional — keeps default 4711 on parse failure
        if (g_mujs_debugger.is_running()) {
            os << "JS Debugger is already running on port " << g_mujs_debugger.port() << std::endl;
        } else {
            g_mujs_debugger.start(vm.J, port);
            os << "JS Debugger started — attach VSCode on localhost:" << port << " (type: mujs)" << std::endl;
        }
    } else if (subcmd == "stop") {
        if (!g_mujs_debugger.is_running()) {
            os << "JS Debugger is not running" << std::endl;
        } else {
            g_mujs_debugger.stop();
            os << "JS Debugger stopped" << std::endl;
        }
    } else if (subcmd == "status") {
        if (g_mujs_debugger.is_running()) {
            os << "JS Debugger: running on port " << g_mujs_debugger.port() << std::endl;
        } else {
            os << "JS Debugger: stopped" << std::endl;
        }
    } else if (subcmd == "verbose") {
        std::string onoff;
        is >> onoff;
        bool enable = (onoff != "off");
        g_mujs_debugger.set_verbose(enable);
        os << "JS Debugger verbose trace: " << (enable ? "ON" : "OFF") << std::endl;
        os << "(each JS line will be logged — use 'js_debugger verbose off' to stop)" << std::endl;
    } else {
        os << "Usage: js_debugger <start [port]|stop|status|verbose [on|off]>" << std::endl;
        os << "  start [port]  — start DAP server (default port 4711)" << std::endl;
        os << "  stop          — stop DAP server, resume game if paused" << std::endl;
        os << "  status        — show current state" << std::endl;
        os << "  verbose [off] — log every JS line (diagnosis for missing breakpoints)" << std::endl;
    }
}

static js_StringNode property_stackTrace = js_intern("stackTrace");

static void js_vm_log_stacktrace(js_State *J) {
    // Try to get stack trace from error object if it's an Error
    if (J->isobject(-1)) {
        if (J->hasproperty(-1, property_stackTrace)) {
            J->getproperty(-1, property_stackTrace);
            if (js_isstring(J, -1)) {
                auto stack_trace = js_tostring(J, -1);
                logs::info("!!! Stack trace: %s", stack_trace->value.c_str());
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
            auto str = js_tostring(J, idx);
            if (str->value.length() > 50) {
                value_desc.printf("string: \"%.50s...\"", str->value.c_str());
            } else {
                value_desc.printf("string: \"%s\"", str->value.c_str());
            }
        } else if (J->isobject(idx)) {
            if (js_isarray(J, idx)) {
                value_desc.printf("array (length: %d)", js_getlength(J, idx));
            } else if (J->iscallable(idx)) {
                value_desc = "function";
            } else {
                // Try to get some info about the object
                int prop_count = 0;
                bstring256 props_preview;
                
                // Save stack state
                int save_top = js_gettop(J);
                
                // Try to iterate first few properties
                js_pushiterator(J, idx, 0);
                js_StringNode prop_name;
                while (prop_count < 3 && (prop_name = js_nextiterator(J, -1)) != NULL) {
                    if (prop_count > 0) {
                        props_preview.append(", ");
                    }
                    props_preview.append(prop_name->value.c_str());
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

static js_StringNode property_name = js_intern("name");
static js_StringNode property_message = js_intern("message");

int js_vm_trypcall(js_State *J, int params) {
    if (vm.have_error) {
        return 0;
    }

    int error = J->pcall(params);
    if (error) {
        vm.have_error = 1;
        auto error_msg = js_tostring(J, -1);

        // Log error type if it's an Error object
        if (J->isobject(-1)) {
            if (J->hasproperty(-1, property_name)) {
                J->getproperty(-1, property_name);
                auto error_name = js_tostring(J, -1);
                pcstr en = js_strnode_cstr(error_name);
                logs::info("!!! Error type: %s", en && en[0] ? en : "<unknown>");
                js_pop(J, 1);
            }
        }

        // Log full error message (MuJS now provides detailed context)
        const char *cur_symbol = error_msg->value.c_str();
        const char *start_str = cur_symbol;
        bstring256 error_msg_copy;
        while (*cur_symbol) {
            if (*cur_symbol != '\n') {
                cur_symbol++;
                continue;
            }

            error_msg_copy.printf("%.*s", cur_symbol - start_str, start_str);
            start_str = cur_symbol + 1;
            cur_symbol += 2;
            logs::info("!!! %s", error_msg_copy.c_str());
        }
        logs::info("!!! %s", start_str);

        // Log stack trace
        js_vm_log_stacktrace(J);

        // Dump stack values for additional debugging info
        js_vm_dump_stack(J);

        vm.error_str = error_msg_copy;
        js_pop(J, 1);
        return 0;
    }

    js_pop(J, 1);
    return 1;
}

bool js_vm_have_error() {
    return vm.have_error;
}

static void copy_js_value_text(js_State *J, js_Value *v, char *out, size_t outsz) {
    if (!out || !outsz) {
        return;
    }
    out[0] = '\0';
    if (!v) {
        return;
    }
    switch (v->type) {
    case JS_TSHRSTR:
        snprintf(out, outsz, "%s", js_strnode_cstr(v->u.shrstr));
        return;
    default:
        break;
    }
    snprintf(out, outsz, "%s", js_strnode_cstr(jsV_tostring(J, v)));
}

/** Own properties only; enumeration list stays valid when AA-tree lookup is wrong for a key. */
static js_Property *find_own_prop_by_name_cstr(js_Object *o, pcstr key) {
    for (js_Property *p = o->head; p; p = p->next) {
        pcstr pn = js_strnode_cstr(p->name);
        if (pn && !strcmp(pn, key)) {
            return p;
        }
    }
    return nullptr;
}

/** js_ploadstring failed; stack[-1] is the thrown value. Read Error name/message without invoking toString. */
static void js_vm_log_script_parse_or_compile_failure(js_State *J, pcstr path_label) {
    char buf[768];
    buf[0] = '\0';

    if (js_gettop(J) > 0) {
        js_Value *topv = js_tovalue(J, -1);
        if (topv->type == JS_TOBJECT && topv->u.object->type == JS_CERROR) {
            char namebuf[96];
            char msgbuf[640];
            namebuf[0] = '\0';
            msgbuf[0] = '\0';

            js_Object *eo = topv->u.object;

            if (js_Property *ref = find_own_prop_by_name_cstr(eo, "name")) {
                if (!ref->getter) {
                    copy_js_value_text(J, &ref->value, namebuf, sizeof namebuf);
                }
            }
            if (!namebuf[0]) {
                if (js_Property *ref = eo->vgetproperty(property_name)) {
                    if (!ref->getter) {
                        copy_js_value_text(J, &ref->value, namebuf, sizeof namebuf);
                    }
                }
            }

            if (js_Property *ref = find_own_prop_by_name_cstr(eo, "message")) {
                if (!ref->getter) {
                    copy_js_value_text(J, &ref->value, msgbuf, sizeof msgbuf);
                }
            }
            if (!msgbuf[0]) {
                if (js_Property *ref = eo->vgetproperty(property_message)) {
                    if (!ref->getter) {
                        copy_js_value_text(J, &ref->value, msgbuf, sizeof msgbuf);
                    }
                }
            }
            if (!msgbuf[0]) {
                if (js_Property *ref = find_own_prop_by_name_cstr(eo, "stackTrace")) {
                    if (!ref->getter) {
                        copy_js_value_text(J, &ref->value, msgbuf, sizeof msgbuf);
                    }
                }
            }

            if (msgbuf[0]) {
                if (namebuf[0]) {
                    snprintf(buf, sizeof buf, "%s: %s", namebuf, msgbuf);
                } else {
                    snprintf(buf, sizeof buf, "%s", msgbuf);
                }
            } else if (namebuf[0]) {
                snprintf(buf, sizeof buf, "%s", namebuf);
            }
        }

        if (!buf[0]) {
            js_StringNode s = js_tostring(J, -1);
            snprintf(buf, sizeof buf, "%s", js_strnode_cstr(s));
            if (!buf[0]) {
                snprintf(buf, sizeof buf, "unknown error");
            }
        }

        js_pop(J, 1);
    } else {
        snprintf(buf, sizeof buf, "unknown error");
    }

    logs::info("!!! Script load failed (%s): %s", path_label, buf);
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
            js_vm_log_script_parse_or_compile_failure(vm.J, r.path.c_str());
            return 0;
        }

        js_getglobal(vm.J, "");
        int ok = js_vm_trypcall(vm.J, 0);
        if (!ok) {
            logs::info("Fatal error on call base after load %s", r.path.c_str());
            if (vm.error_str.len() > 0) {
                logs::info("Error details: %s", vm.error_str.c_str());
            } else if (js_gettop(vm.J) > 0) {
                auto error_msg = js_tostring(vm.J, -1);
                if (!error_msg->value.empty()) {
                    logs::info("Error details: %s", error_msg->value.c_str());
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
        js_vm_log_script_parse_or_compile_failure(vm.J, rpath.c_str());
        return 0;
    }

    js_getglobal(vm.J, "");
    int ok = js_vm_trypcall(vm.J, 0);
    if (!ok) {
        logs::info("Fatal error on call base after load %s", path);
        if (vm.error_str.len() > 0) {
            logs::info("Error details: %s", vm.error_str.c_str());
        } else if (js_gettop(vm.J) > 0) {
            auto error_msg = js_tostring(vm.J, -1);
            if (!error_msg->value.empty()) {
                logs::info("Error details: %s", js_strnode_cstr(error_msg));
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

void js_vm_shutdown() {
    if (!vm.J) {
        return;
    }
    js_freestate(vm.J);
    vm.J = nullptr;
}

bool js_vm_sync(const xstring &mission_id) {
    if (vm.files2load.empty()) {
        return false;
    }

    if (vm.have_error) {
        js_reset_vm_state();
    }

    // Iterate by index so newly appended imports (from js_game_import) are also processed
    for (int i = 0; i < (int)vm.files2load.size(); i++) {
        logs::info("JS: script reloaded %s", vm.files2load[i].c_str());
        js_vm_load_file_and_exec(vm.files2load[i]);
    }

    vm.files2load.clear();

    js_register_game_handlers(mission_id);
    js_register_entity_systems();

    config::refresh(vm.J);

    vm.have_error = 0;
    return true;
}

void js_vm_reload_file(pcstr path) {
    vm.files2load.push_back(vfs::path(path));
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
                vm.J->pushstring(msg);
                break;
            case 's':
                vm.J->pushstring(va_arg(vl, char *));
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
            auto error_msg = js_tostring(vm.J, -1);
            if (!error_msg->value.empty()) {
                logs::info("Error details: %s", error_msg->value.c_str());
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
    auto scriptName = js_tostring(J, 1);

    vm.files2load.push_back(vfs::path(scriptName->value.c_str()));
}

void js_game_panic(js_State *J) {
    logs::info("JSE !!! Uncaught exception: %s", js_strnode_cstr(js_tostring(J, -1)));
}

int js_game_import(js_State *J, pcstr filename) {
    vm.files2load.push_back(vfs::path(":", filename, ".js"));
    return 0;
}

void js_register_vm_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, js_vm_load_module, "include", 1);
}

#if defined(TRACY_MEMORY_ENABLE)
extern bool TracyProfilerAvailable;
#endif
void *js_alloc_wrapper(void *actx, void *ptr, int size) {
    (void)actx;

    if (size == 0) {
        if (ptr) {
            const size_t freed = mujs_malloc_block_size(ptr);
            mujs_heap_sub_bytes(freed);
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
        void *new_ptr = malloc((size_t)size);
#if defined(TRACY_MEMORY_ENABLE)
        if (new_ptr && TracyProfilerAvailable) {
            TracyAllocS(new_ptr, size, 20);
        }
#endif
        if (new_ptr) {
            mujs_heap_add_bytes(mujs_malloc_block_size(new_ptr));
        }
        return new_ptr;
    }

    void *old_ptr = ptr;
    const size_t old_sz = mujs_malloc_block_size(old_ptr);
    void *new_ptr = realloc(old_ptr, (size_t)size);

#if defined(TRACY_MEMORY_ENABLE)
    if (TracyProfilerAvailable && new_ptr) {
        TracyFreeS(old_ptr, 20);
        TracyAllocS(new_ptr, size, 20);
    }
#endif

    if (!new_ptr && size > 0) {
        return nullptr;
    }

    mujs_heap_sub_bytes(old_sz);
    if (new_ptr) {
        mujs_heap_add_bytes(mujs_malloc_block_size(new_ptr));
    }

    return new_ptr;
}

void *js_frame_alloc_wrapper(void *actx, void *ptr, int size) {
    if (size == 0) {
        (void)actx;
        (void)ptr;
        return nullptr;
    }

    if (!ptr) {
        size_t alloc_size = static_cast<size_t>(size);
        return vm.frame_alloc_ctx.allocate(alloc_size, alignof(std::max_align_t));
    }

    void *new_ptr = js_frame_alloc_wrapper(actx, nullptr, size);
    return new_ptr;
}

void js_reset_vm_state() {
    if (vm.J) {
        js_freestate(vm.J);
        vm.J = NULL;
    }

    vm.files2load.clear();
    vm.have_error = 0;
    vm.frame_alloc_ctx.release();

    vm.J = js_newstate(js_alloc_wrapper, nullptr, JS_STRICT);
    js_set_framealloc(vm.J, js_frame_alloc_wrapper, nullptr);
    js_atpanic(vm.J, js_game_panic);
    js_registerimport(vm.J, js_game_import);
    js_registeremit(vm.J, js_game_emit);

    js_register_vm_functions(vm.J);
    js_register_game_functions(vm.J);
    js_register_game_objects(vm.J);
    js_register_mission_objects(vm.J);
    js_register_empire_objects(vm.J);
    js_register_city_objects(vm.J);
    js_register_building(vm.J);
    js_register_imperial_visible_request(vm.J);
    js_register_house(vm.J);
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

    // After a VM reset the js_State pointer changes — always re-register the hook.
    // The hook itself is a no-op when the debugger server is not running.
    g_mujs_debugger.update_state(vm.J);
    js_setdebughook(vm.J, [](js_State *J, const char *file, int line, void *) {
        g_mujs_debugger.on_line(J, file, line);
    }, nullptr);

    mujs_run_self_tests(vm.J);
}

void js_vm_frame_begin() {
    vm.frame_alloc_ctx.release();
    if (vm.J && vm.J->gccounter > JS_GCLIMIT * 10) {
        vm.J->gccounter = 0;
        vm.J->gc(0);
    }
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
    if (!vm.frame_alloc_buffer) {
        vm.frame_alloc_buffer = (char*)malloc(vm.FRAME_ALLOC_BUFFER_SIZE);
    }
    vm.frame_alloc_ctx.~monotonic_buffer_resource();
    new (&vm.frame_alloc_ctx)std::pmr::monotonic_buffer_resource( vm.frame_alloc_buffer,  vm.FRAME_ALLOC_BUFFER_SIZE, std::pmr::get_default_resource());
    js_reset_vm_state();

    vfs::path abspath = js_vm_get_absolute_path("");
    vfs::path modules_file(abspath, "/modules.js");
    bool scripts_folder_exists = std::filesystem::exists(modules_file.c_str());
    if (scripts_folder_exists) {
        js_vm_notifier_watch_directory_init(abspath);
    }
}