#pragma once

#include "content/vfs.h"
#include "core/variant.h"

struct js_State;
struct mission_id_t;

void js_vm_setup();
bool js_vm_sync(const xstring& mission_id);
js_State *js_vm_state();
int js_vm_exec_function_args(pcstr funcname, const char *szTypes, ...);
int js_vm_exec_function(pcstr funcname);
void js_vm_reload_file(pcstr path);
int js_vm_load_file_and_exec(pcstr path);

void js_vm_add_scripts_folder(vfs::path folder);
void js_call_event_handlers(const xstring &event_name, const bvariant_map &object);
int js_vm_trypcall(js_State *J, int params);
bool js_vm_have_error();
void js_vm_frame_begin();

vfs::path js_vm_get_absolute_path(vfs::path file);