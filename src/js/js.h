#pragma once

#include "content/vfs.h"
#include "core/variant.h"

#include <cstdint>

struct js_State;
struct mission_id_t;

void js_vm_setup();
void js_vm_shutdown();


/** False if no script reloads were queued (files2load empty). */
bool js_vm_sync(const xstring& mission_id);
js_State *js_vm_state();
int js_vm_exec_function_args(pcstr funcname, const char *szTypes, ...);
int js_vm_exec_function(pcstr funcname);
void js_vm_reload_file(pcstr path);
int js_vm_load_file_and_exec(pcstr path);

void js_vm_add_scripts_folder(vfs::path folder);
void js_call_event_handlers(const xstring &event_name, const bvariant_map &object);
int js_vm_trypcall(js_State *J, int params);
/** Same as js_vm_trypcall but does NOT pop the function's return value on
 * success; the caller is responsible for inspecting and popping it. On
 * failure the error has already been logged and the stack is back to where
 * pcall left it. Returns 1 on success, 0 on failure. */
int js_vm_trypcall_keep_result(js_State *J, int params);
bool js_vm_have_error();
/** Clear the sticky `vm.have_error` flag. js_vm_trypcall short-circuits to 0
 * while the flag is set, so any code that wants to keep running after a
 * caught script exception (e.g. the integral-tests driver) must reset it
 * between independent calls. */
void js_vm_reset_error();
/** Return true if a global with `name` exists and is callable. Wraps the
 * internal js_State::iscallable so callers do not need to include mujs/jsi.h. */
bool js_vm_global_is_callable(js_State *J, const char *name);
void js_vm_frame_begin();

/** Bytes allocated for the JS VM via mujs main heap (malloc/realloc through js_alloc_wrapper). */
uint64_t js_mujs_heap_bytes();

vfs::path js_vm_get_absolute_path(vfs::path file);