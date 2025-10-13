#pragma once

#include "mujs/mujs.h"

#include "js/js_constants.h"
#include "core/bstring.h"
#include "core/core.h"
#include "js/js_defines.h"
#include "core/vec2i.h"
#include "core/archive.h"

#include <vector>
#include <string>

namespace config {

void refresh(archive);
archive load(pcstr filename);

using config_iterator_function_cb = void ();
using ArchiveIterator = FuncLinkedList<config_iterator_function_cb*>;

struct type_enum{};
using config_iterator_enum_function_cb = void(type_enum);
using EnumIterator = FuncLinkedList<config_iterator_enum_function_cb*>;

} // end namespace config

#define ANK_DECLARE_CONFIG_ITERATOR(func) void func(); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::ArchiveIterator ANK_CONFIG_CC1(config_handler, __LINE__)(func)

#define ANK_REGISTER_CONFIG_ITERATOR(func) func(); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::ArchiveIterator ANK_CONFIG_CC1(config_handler, __LINE__)(func); void func() 

#define ANK_CONFIG_OBJECT_VARIABLE(a) \
    ANK_DECLARE_CONFIG_ITERATOR(config_load_ ## a); \
    void config_load_ ## a() { a.archive_unload(); const bool ok = g_config_arch.r_section(a.archive_section(), [] (archive arch) { a.archive_load(arch); }); assert(ok && "Variable not exist in config:" #a); a.archive_init(); }

#define ANK_CONFIG_OBJECT_VARIABLE_N(a, name)                   \
    ANK_DECLARE_CONFIG_ITERATOR(config_load_ ## a);             \
    void config_load_ ## a() {                                  \
        call_unload_if_exists(a);                               \
        const bool ok = g_config_arch.r(name, a);               \
        call_init_if_exists(a);                                 \
        { assert(ok && "Variable not exist in config:" name); } \
    }

#define ANK_CONFIG_ARRAY_VARIABLE(a, name) \
    ANK_DECLARE_CONFIG_ITERATOR(config_load_ ## a); \
    void config_load_ ## a() { a.archive_unload(); g_config_arch.r_array(name, [] (archive arch) { auto &it = a.emplace_back(); a.archive_load(it, arch); }); a.archive_init(); }

#define ANK_CONFIG_OBJECTS_VARIABLE(a, name) \
    ANK_DECLARE_CONFIG_ITERATOR(config_load_ ## a); \
    void config_load_ ## a() { g_config_arch.r(name, a); call_init_if_exists(a); }

#define ANK_ARRAY_VARIABLE(a) a; \
    ANK_CONFIG_ARRAY_VARIABLE(a, #a)

#define ANK_OBJECTS_VARIABLE(a) a; \
    ANK_CONFIG_OBJECTS_VARIABLE(a, #a)

#define ANK_VARIABLE(a) a; \
    ANK_CONFIG_OBJECT_VARIABLE_N(a, #a)

#define ANK_VARIABLE_N(a, name) a; \
    ANK_CONFIG_OBJECT_VARIABLE_N(a, name)

#define ANK_PERMANENT_CALLBACK(event, a) \
    tmp_register_permanent_callback_ ##event(); \
    ANK_DECLARE_CONFIG_ITERATOR(register_permanent_callback_ ##event); \
    void permanent_callback_ ##event(event a); \
    void register_permanent_callback_ ##event() { events::subscribe_permanent(permanent_callback_ ##event); } \
    void permanent_callback_ ##event(event a)

#define ANK_CONFIG_ENUM(enumt) enumt; \
    void register_enum_##enumt(config::type_enum); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(register_enum_##enumt) = 1;} \
    static config::EnumIterator ANK_CONFIG_CC1(config_handler, __LINE__)(register_enum_##enumt); void register_enum_##enumt(config::type_enum) { js_register_tokens(enumt); }

#define REPLICATE_STATIC_PARAMS_FROM_CONFIG(class_name)                   \
    class_name::model_type model_##class_name;                            \
    ANK_DECLARE_CONFIG_ITERATOR(config_load_model ## class_name);         \
    void config_load_model ## class_name() {                              \
        call_unload_if_exists(model_##class_name);                        \
        class_name::model_type::static_params_load();                     \
        call_init_if_exists(model_##class_name);                          \
    }

void js_register_game_functions(js_State *J);
void js_register_game_objects(js_State *J);