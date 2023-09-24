#pragma once

#include "content/vfs.h"

void js_vm_setup();
void js_vm_sync();
int js_vm_exec_function_args(const char *funcname, const char *szTypes, ...);
int js_vm_exec_function(const char *funcname);
void js_vm_reload_file(const char *path);

void js_vm_set_scripts_folder(vfs::path folder);

vfs::path js_vm_get_absolute_path(vfs::path file);