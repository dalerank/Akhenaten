#pragma once

#include "mujs/mujs.h"

#include "core/bstring.h"
#include "core/core.h"
#include "js/js_defines.h"
#include "core/vec2i.h"
#include "core/archive.h"

#include <vector>
#include <string>

void js_register_game_functions(js_State *J);
void js_register_game_objects(js_State *J);

namespace config {

void refresh(archive);
archive load(pcstr filename);

using config_iterator_function_cb = void ();
using ArchiveIterator = FuncLinkedList<config_iterator_function_cb*>;

} // end namespace config

#define ANK_REGISTER_CONFIG_ITERATOR(func) void func(); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::ArchiveIterator ANK_CONFIG_CC1(config_handler, __LINE__)(func)

#define ANK_REGISTER_CONFIG_OBJECT_VARIABLE(a, name) \
    ANK_REGISTER_CONFIG_ITERATOR(config_load_ ## a); \
    void config_load_ ## a() { a.archive_unload(); const bool ok = g_config_arch.r_section(name, [] (archive arch) { a.archive_load(arch); }); assert(ok && "Variable not exist in config:" name); a.archive_init(); }

#define ANK_REGISTER_CONFIG_ARRAY_VARIABLE(a, name) \
    ANK_REGISTER_CONFIG_ITERATOR(config_load_ ## a); \
    void config_load_ ## a() { a.archive_unload(); g_config_arch.r_array(name, [] (archive arch) { auto &it = a.emplace_back(); a.archive_load(it, arch); }); a.archive_init(); }

#define ANK_REGISTER_CONFIG_OBJECTS_VARIABLE(a, name) \
    ANK_REGISTER_CONFIG_ITERATOR(config_load_ ## a); \
    void config_load_ ## a() { a.archive_unload(); g_config_arch.r_objects(name, [] (archive arch) { a.archive_load(arch); }); a.archive_init(); }

#define ANK_ARRAY_VARIABLE(a) a; \
    ANK_REGISTER_CONFIG_ARRAY_VARIABLE(a, #a)

#define ANK_OBJECTS_VARIABLE(a) a; \
    ANK_REGISTER_CONFIG_OBJECTS_VARIABLE(a, #a)

#define ANK_VARIABLE(a) a; \
    ANK_REGISTER_CONFIG_OBJECT_VARIABLE(a, #a)

#define ANK_VARIABLE_N(a, name) a; \
    ANK_REGISTER_CONFIG_OBJECT_VARIABLE(a, name)

#define ANK_PERMANENT_CALLBACK(event, a) \
    tmp_register_permanent_callback_ ##event(); \
    ANK_REGISTER_CONFIG_ITERATOR(register_permanent_callback_ ##event); \
    void permanent_callback_ ##event(event a); \
    void register_permanent_callback_ ##event() { events::subscribe_permanent(permanent_callback_ ##event); } \
    void permanent_callback_ ##event(event a)
    