#pragma once

#include "content/vfs.h"
#include "core/variant.h"

#include <cstdint>

struct js_State;
struct mission_id_t;

void js_vm_setup();
void js_vm_shutdown();
xstring js_toxstring(js_State* J, int idx);

/** False if no script reloads were queued (files2load empty). */
bool js_vm_sync(const xstring& mission_id);
js_State *js_vm_state();
int js_vm_exec_function_args(pcstr funcname, const char *szTypes, ...);
int js_vm_exec_function(pcstr funcname);
void js_vm_reload_file(pcstr path);
/** Re-run every loaded ui_*.js once the screen size settles: window layouts read it when their script runs. */
void js_vm_request_ui_relayout();
int js_vm_load_file_and_exec(pcstr path);

void js_vm_add_scripts_folder(vfs::path folder);
void js_call_event_handlers(const xstring &event_name, const bvariant_map &object);
int js_vm_trypcall(js_State *J, int params);
int js_vm_trypcall_keep_result(js_State *J, int params);
bool js_vm_have_error();

void js_vm_reset_error();
bool js_vm_global_is_callable(js_State *J, const char *name);
int js_vm_stack_depth_if_idle();
int js_vm_force_idle_stack();
void js_vm_frame_begin();
void js_vm_frame_end();

/** Bytes allocated for the JS VM via mujs main heap (malloc/realloc through js_alloc_wrapper). */
uint64_t js_mujs_heap_bytes();

vfs::path js_vm_get_absolute_path(vfs::path file);