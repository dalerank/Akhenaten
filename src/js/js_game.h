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

// Helper functions to convert JS values to C++ types
namespace js_helpers {
    template<typename T>
    inline T js_to_value(js_State *J, int idx);
    
    template<>
    inline int js_to_value<int>(js_State *J, int idx) {
        return js_tointeger(J, idx);
    }
    
    template<>
    inline double js_to_value<double>(js_State *J, int idx) {
        return js_tonumber(J, idx);
    }
    
    template<>
    inline float js_to_value<float>(js_State *J, int idx) {
        return (float)js_tonumber(J, idx);
    }
    
    template<>
    inline bool js_to_value<bool>(js_State *J, int idx) {
        return js_toboolean(J, idx);
    }
    
    template<>
    inline const char* js_to_value<const char*>(js_State *J, int idx) {
        return js_tostring(J, idx);
    }
    
    template<>
    inline std::string js_to_value<std::string>(js_State *J, int idx) {
        return std::string(js_tostring(J, idx));
    }
    
    template<>
    inline xstring js_to_value<xstring>(js_State *J, int idx) {
        return xstring(js_tostring(J, idx));
    }
}

namespace config {

void refresh(archive);
archive load(pcstr filename);

using config_iterator_function_cb = void ();
using ArchiveIterator = FuncLinkedList<config_iterator_function_cb*>;

struct type_enum{};
using config_iterator_enum_function_cb = void(type_enum);
using EnumIterator = FuncLinkedList<config_iterator_enum_function_cb*>;

using jsfunc_iterator_function_cb = void(js_State*);
using FunctionIterator = FuncLinkedList<jsfunc_iterator_function_cb *>;

} // end namespace config

#define ANK_DECLARE_CONFIG_ITERATOR(func) void func(); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::ArchiveIterator ANK_CONFIG_CC1(config_handler, __LINE__)(func)

#define ANK_DECLARE_JSFUNCTION_ITERATOR(func) void func(js_State*); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::FunctionIterator ANK_CONFIG_CC1(func_handler, __LINE__)(func)

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

#define ANK_FUNCTION_NAMED(fname, func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 0); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { func(); }

#define ANK_FUNCTION(func) \
    ANK_FUNCTION_NAMED(func, func)

#define ANK_FUNCTION_NAMED_1(fname, func, type) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 1); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { type param = js_helpers::js_to_value<type>(J, 1); func(param); js_pushundefined(J); }

#define ANK_FUNCTION_1(func, type) \
    ANK_FUNCTION_NAMED_1(func, func, type)

#define ANK_FUNCTION_NAMED_2(fname, func, type1, type2) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 2); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { type1 param1 = js_helpers::js_to_value<type1>(J, 1); type2 param2 = js_helpers::js_to_value<type2>(J, 2); func(param1, param2); js_pushundefined(J); }

#define ANK_FUNCTION_NAMED_3(fname, func, type1, type2, type3) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 3); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { type1 param1 = js_helpers::js_to_value<type1>(J, 1); type2 param2 = js_helpers::js_to_value<type2>(J, 2); type3 param3 = js_helpers::js_to_value<type3>(J, 3); func(param1, param2, param3); js_pushundefined(J); }

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
void js_unref_function(xstring onclick_ref);
void js_call_function(xstring onclick_ref);