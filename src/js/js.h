#pragma once

#include "content/vfs.h"
#include "core/variant.h"

struct js_State;

void js_vm_setup();
bool js_vm_sync();
js_State *js_vm_state();
int js_vm_exec_function_args(const char *funcname, const char *szTypes, ...);
int js_vm_exec_function(const char *funcname);
void js_vm_reload_file(const char *path);
int js_vm_load_file_and_exec(pcstr path);

void js_vm_add_scripts_folder(vfs::path folder);
void js_call_event_handlers(const xstring &event_name, const bvariant_map &object);

vfs::path js_vm_get_absolute_path(vfs::path file);