#pragma once

#include "mujs/mujs.h"

#include "js/js_constants.h"
#include "core/bstring.h"
#include "core/core.h"
#include "js/js_defines.h"
#include "core/vec2i.h"
#include "core/archive.h"
#include "core/variant.h"

#include <vector>
#include <string>
#include <mutex>

class settings_vars_t;

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
    
    template<typename T>
    inline void js_push_value(js_State *J, T value);
    
    template<>
    inline void js_push_value<int>(js_State *J, int value) {
        js_pushnumber(J, value);
    }
    
    template<>
    inline void js_push_value<float>(js_State *J, float value) {
        js_pushnumber(J, value);
    }
    
    template<>
    inline void js_push_value<double>(js_State *J, double value) {
        js_pushnumber(J, value);
    }
    
    template<>
    inline void js_push_value<bool>(js_State *J, bool value) {
        js_pushboolean(J, value);
    }
    
    template<>
    inline void js_push_value<const char*>(js_State *J, const char* value) {
        js_pushstring(J, value);
    }
    
    template<>
    inline void js_push_value<std::string>(js_State *J, std::string value) {
        js_pushstring(J, value.c_str());
    }
    
    template<>
    inline void js_push_value<xstring>(js_State *J, xstring value) {
        js_pushstring(J, value.c_str());
    }
    
    inline void js_push_void(js_State *J) {
        js_pushundefined(J);
    }

   
    template<typename Func>
    inline void js_invoke_and_push_impl(js_State *J, std::false_type, Func &&func) {
        func();
        js_push_void(J);
    }

    template<typename Func>
    inline void js_invoke_and_push_impl(js_State *J, std::true_type, Func &&func) {
        auto result = func();
        js_push_value(J, result);
    }

    template<bool is_void, typename Func>
    inline void js_invoke_and_push(js_State *J, Func &&func) {
        if constexpr (is_void) {
            js_invoke_and_push_impl(J, std::false_type{}, func);
        } else {
            js_invoke_and_push_impl(J, std::true_type{}, func);
        }
    }

    // Convert JS object to bvariant_map
    inline bvariant_map js_object_to_bvariant_map(js_State *J, int idx) {
        bvariant_map result;
        if (!js_isobject(J, idx) || js_isarray(J, idx)) {
            return result;
        }
        
        js_pushiterator(J, idx, 1); // own properties only
        pcstr key;
        while ((key = js_nextiterator(J, -1))) {
            js_getproperty(J, idx, key);
            bvariant value;
            
            if (js_isboolean(J, -1)) {
                value = bvariant(js_toboolean(J, -1));
            } else if (js_isstring(J, -1)) {
                value = bvariant(xstring(js_tostring(J, -1)));
            } else if (js_isnumber(J, -1) || js_iscnumber(J, 1)) {
                double num = js_tonumber(J, -1);
                // Try to preserve integer if possible
                if (num == (int)num) {
                    value = bvariant((int)num);
                } else {
                    value = bvariant((float)num);
                }
            } else {
                value = bvariant(); // none
            }
            
            result.values[xstring(key)] = value;
            js_pop(J, 1); // pop value
        }
        js_pop(J, 1); // pop iterator
        
        return result;
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

template<typename Func>
struct function_traits;

template<typename R, typename... Args>
struct function_traits<R(*)(Args...)> {
    using return_type = R;
    static constexpr size_t arity = sizeof...(Args);

    template<size_t N>
    struct arg {
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};

template<typename R, typename... Args>
struct function_traits<R(Args...)> : function_traits<R(*)(Args...)> {};

template<typename C, typename R, typename... Args>
struct function_traits<R(C:: *)(Args...)> {
    using return_type = R;
    static constexpr size_t arity = sizeof...(Args);

    template<size_t N>
    struct arg {
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};

template<typename C, typename R, typename... Args>
struct function_traits<R(C:: *)(Args...) const> : function_traits<R(C:: *)(Args...)> {};

#define ANK_FUNCTION_NAMED(fname, func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 0); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { \
        constexpr bool is_void = (std::is_void_v<function_traits<decltype(&func)>::return_type>); \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(); }); \
    }

#define ANK_FUNCTION(func) \
    ANK_FUNCTION_NAMED(func, func)

#define ANK_FUNCTION_NAMED_1(fname, func, type) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 1); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { \
        type param = js_helpers::js_to_value<type>(J, 1); \
        constexpr bool is_void = (std::is_void_v<function_traits<decltype(&func)>::return_type>); \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(param); }); \
    }

#define ANK_FUNCTION_1(func) \
    ANK_FUNCTION_NAMED_1(func, func, function_traits<decltype(&func)>::arg<0>::type)

#define ANK_FUNCTION_NAMED_2(fname, func, type1, type2) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 2); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { \
        type1 param1 = js_helpers::js_to_value<type1>(J, 1); \
        type2 param2 = js_helpers::js_to_value<type2>(J, 2); \
        constexpr bool is_void = (std::is_void_v<function_traits<decltype(&func)>::return_type>); \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(param1, param2); }); \
    }

#define ANK_FUNCTION_2(func) \
     ANK_FUNCTION_NAMED_2(func, func, function_traits<decltype(&func)>::arg<0>::type, function_traits<decltype(&func)>::arg<1>::type)

#define ANK_FUNCTION_NAMED_3(fname, func, type1, type2, type3) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 3); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { \
        type1 param1 = js_helpers::js_to_value<type1>(J, 1); \
        type2 param2 = js_helpers::js_to_value<type2>(J, 2); \
        type3 param3 = js_helpers::js_to_value<type3>(J, 3); \
        constexpr bool is_void = (std::is_void_v<function_traits<decltype(&func)>::return_type>); \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(param1, param2, param3); }); \
    }

#define ANK_FUNCTION_3(func) \
    ANK_FUNCTION_NAMED_3(func, func, function_traits<decltype(&func)>::arg<0>::type, function_traits<decltype(&func)>::arg<1>::type, function_traits<decltype(&func)>::arg<2>::type)

#define ANK_FUNCTION_NAMED_4(fname, func, type1, type2, type3, type4) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 4); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { \
        type1 param1 = js_helpers::js_to_value<type1>(J, 1); \
        type2 param2 = js_helpers::js_to_value<type2>(J, 2); \
        type3 param3 = js_helpers::js_to_value<type3>(J, 3); \
        type3 param4 = js_helpers::js_to_value<type4>(J, 4); \
        constexpr bool is_void = (std::is_void_v<function_traits<decltype(&func)>::return_type>); \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(param1, param2, param3, param4); }); \
    }

#define ANK_FUNCTION_4(func) \
    ANK_FUNCTION_NAMED_4(func, func, function_traits<decltype(&func)>::arg<0>::type, function_traits<decltype(&func)>::arg<1>::type, function_traits<decltype(&func)>::arg<2>::type, function_traits<decltype(&func)>::arg<3>::type)

#define ANK_FUNCTION_3(func) \
    ANK_FUNCTION_NAMED_3(func, func, function_traits<decltype(&func)>::arg<0>::type, function_traits<decltype(&func)>::arg<1>::type, function_traits<decltype(&func)>::arg<2>::type)

#define ANK_FUNCTION_NAMED_5(fname, func, type1, type2, type3, type4, type5) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname); \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { static std::once_flag flag; std::call_once(flag, [] (js_State* J) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 5); }, J); } \
    void permanent_js2cpp_callback_##fname(js_State *J) { \
        type1 param1 = js_helpers::js_to_value<type1>(J, 1); \
        type2 param2 = js_helpers::js_to_value<type2>(J, 2); \
        type3 param3 = js_helpers::js_to_value<type3>(J, 3); \
        type3 param4 = js_helpers::js_to_value<type4>(J, 4); \
        type3 param5 = js_helpers::js_to_value<type5>(J, 5); \
        constexpr bool is_void = (std::is_void_v<function_traits<decltype(&func)>::return_type>); \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(param1, param2, param3, param4, param5); }); \
    }

#define ANK_FUNCTION_5(func) \
     ANK_FUNCTION_NAMED_5(func, func, function_traits<decltype(&func)>::arg<0>::type, function_traits<decltype(&func)>::arg<1>::type, function_traits<decltype(&func)>::arg<2>::type, function_traits<decltype(&func)>::arg<3>::type,  function_traits<decltype(&func)>::arg<4>::type)

#define ANK_FUNCTION_UNIFIED(func)                                                      \
    func(const bvariant_map&);                                                          \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func);                   \
    void permanent_js2cpp_callback_##func(js_State* J);                                 \
    void register_js2cpp_callback_##func(js_State* J) {                                 \
        static std::once_flag flag;                                                     \
        std::call_once(flag, [] (js_State* J) {                                         \
            REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##func, #func, 1);    \
        }, J);                                                                          \
    }                                                                                   \
    void permanent_js2cpp_callback_##func(js_State *J) {                                \
        bvariant_map params = js_helpers::js_object_to_bvariant_map(J, 1);              \
        constexpr bool is_void = (std::is_void_v<function_traits<decltype(&func)>::return_type>); \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(params); });     \
    }                                                                                   \
    function_traits<decltype(&func)>::return_type func


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
void js_register_mission_objects(js_State *J);
void js_register_mission_vars(const settings_vars_t &vars);
void js_unref_function(xstring onclick_ref);
void js_call_function(xstring onclick_ref);
pcstr js_call_function_with_result(xstring js_ref, int param1, int param2);
void js_register_game_handlers(xstring missionid);