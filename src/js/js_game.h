#pragma once

#include "mujs/mujs.h"

#include "js/js_constants.h"
#include "core/bstring.h"
#include "core/core.h"
#include "js/js_defines.h"
#include "core/vec2i.h"
#include "core/archive.h"
#include "core/variant.h"
#include "grid/point.h"

#include <vector>
#include <string>
#include <optional>
#include <mutex>
#include <type_traits>

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
    
    template<>
    inline vec2i js_to_value<vec2i>(js_State *J, int idx) {
        vec2i result;
        if (js_isobject(J, idx) && !js_isarray(J, idx)) {
            js_getproperty(J, idx, "x"); result.x = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);            
            js_getproperty(J, idx, "y"); result.y = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
        } else if (js_isarray(J, idx)) {
            js_getindex(J, idx, 0); result.x = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
            js_getindex(J, idx, 1); result.y = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
        }
        return result;
    }
    
    template<>
    inline tile2i js_to_value<tile2i>(js_State *J, int idx) {
        int x = 0, y = 0;
        if (js_isobject(J, idx) && !js_isarray(J, idx)) {
            js_getproperty(J, idx, "x"); x = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);            
            js_getproperty(J, idx, "y"); y = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
        } else if (js_isarray(J, idx)) {
            js_getindex(J, idx, 0); x = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
            js_getindex(J, idx, 1); y = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
        }
        return tile2i(x, y);
    }
    
    template<>
    inline bvariant js_to_value<bvariant>(js_State *J, int idx) {
        if (js_isundefined(J, idx)) {
            return bvariant(); // none
        } else if (js_isboolean(J, idx)) {
            return bvariant(js_toboolean(J, idx));
        } else if (js_isstring(J, idx)) {
            return bvariant(xstring(js_tostring(J, idx)));
        } else if (js_isnumber(J, idx) || js_iscnumber(J, idx)) {
            double num = js_tonumber(J, idx);
            // Try to preserve integer if possible
            if (num == (int)num) {
                return bvariant((int)num);
            } else {
                return bvariant((float)num);
            }
        } else if (js_isobject(J, idx) && !js_isarray(J, idx)) {
            // Check if it's a vec2i-like object with x and y properties
            js_getproperty(J, idx, "x");
            bool has_x = !js_isundefined(J, -1);
            js_pop(J, 1);
            
            if (has_x) {
                js_getproperty(J, idx, "x");
                int x = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0;
                js_pop(J, 1);
                js_getproperty(J, idx, "y");
                int y = js_isnumber(J, -1) ? (int)js_tonumber(J, -1) : 0;
                js_pop(J, 1);
                return bvariant(vec2i(x, y));
            } else {
                return bvariant(); // none for other objects
            }
        } else {
            return bvariant(); // none
        }
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
    inline void js_push_value<const std::string&>(js_State *J, const std::string& value) {
        js_pushstring(J, value.c_str());
    }

    template<>
    inline void js_push_value<vec2i>(js_State *J, vec2i value) {
        js_newobject(J);
        js_pushnumber(J, value.x); js_setproperty(J, -2, "x");
        js_pushnumber(J, value.y); js_setproperty(J, -2, "y");
    }
    
    template<>
    inline void js_push_value<tile2i>(js_State *J, tile2i value) {
        js_newobject(J);
        js_pushnumber(J, value.x()); js_setproperty(J, -2, "x");
        js_pushnumber(J, value.y()); js_setproperty(J, -2, "y");
    }
    
    template<>
    inline void js_push_value<xstring>(js_State *J, xstring value) {
        js_pushstring(J, value.c_str());
    }
    
    inline void js_push_bvariant(js_State *J, const bvariant &val) {
        switch (val.value_type()) {
        case bvariant::etype_bool:
            js_pushboolean(J, val.as_bool());
            break;
        case bvariant::etype_int32:
            js_pushnumber(J, (double)val.as_int32());
            break;
        case bvariant::etype_uint32:
            js_pushnumber(J, (double)val.as_uint32());
            break;
        case bvariant::etype_u16:
            js_pushnumber(J, (double)val.as_u16());
            break;
        case bvariant::etype_float:
            js_pushnumber(J, (double)val.as_float());
            break;
        case bvariant::etype_str:
            js_pushstring(J, val.as_str().c_str());
            break;
        case bvariant::etype_ptr:
            js_pushnull(J);
            break;
        case bvariant::etype_vec2i: {
            js_newobject(J);
            const vec2i pos = val.as_vec2i();
            js_pushnumber(J, pos.x);
            js_setproperty(J, -2, "x");
            js_pushnumber(J, pos.y);
            js_setproperty(J, -2, "y");
            break;
        }
        case bvariant::etype_none:
        default:
            js_pushundefined(J);
            break;
        }
    }
    
    template<>
    inline void js_push_value<bvariant>(js_State *J, bvariant value) {
        js_push_bvariant(J, value);
    }
    
    template<>
    inline void js_push_value<std::optional<bvariant>>(js_State *J, std::optional<bvariant> value) {
        if (value.has_value()) {
            js_push_bvariant(J, value.value());
        } else {
            js_pushundefined(J);
        }
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

    using jsfunc_iterator_function_cb = void(js_State *);
    using FunctionIterator = FuncLinkedList<jsfunc_iterator_function_cb *>;

} // end namespace config

#define ANK_DECLARE_JSFUNCTION_ITERATOR(func) void func(js_State*); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::FunctionIterator ANK_CONFIG_CC1(func_handler, __LINE__)(func)

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
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) { \
        js_getglobal(J, #fname); bool exists = js_iscallable(J, -1); js_pop(J, 1); \
        if (!exists) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 0); } \
    } void permanent_js2cpp_callback_##fname(js_State *J) { \
        constexpr bool is_void = (std::is_void_v<function_traits<decltype(&func)>::return_type>); \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(); }); \
    }

#define ANK_FUNCTION(func) \
    ANK_FUNCTION_NAMED(func, func)

// Template function version of ANK_FUNCTION_1
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_1_callback_impl(js_State* J) {
    // std::decay_t converts function types to function pointer types
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = function_traits<func_ptr_type>;
    using param_type = typename traits:: template arg<0>::type;
    using return_type = typename traits::return_type;
    
    param_type param = js_helpers::js_to_value<param_type>(J, 1);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&]() { return Func(param); });
}

// Template function to register callback with 1 parameter
template<auto Func>
inline void ank_register_callback_1(js_State* J, pcstr name) {
    auto callback_impl = [](js_State *J) { ank_function_1_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = js_iscallable(J, -1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 1);
    }
}

#define ANK_FUNCTION_1(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { ank_register_callback_1<&func>(J, #func); }

// Template function version of ANK_FUNCTION_2
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_2_callback_impl(js_State* J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = function_traits<func_ptr_type>;
    using param1_type = typename traits:: template arg<0>::type;
    using param2_type = typename traits:: template arg<1>::type;
    using return_type = typename traits::return_type;
    
    param1_type param1 = js_helpers::js_to_value<param1_type>(J, 1);
    param2_type param2 = js_helpers::js_to_value<param2_type>(J, 2);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&]() { return Func(param1, param2); });
}

// Template function to register callback with 2 parameters
template<auto Func>
inline void ank_register_callback_2(js_State* J, pcstr name) {
    auto callback_impl = [](js_State *J) { ank_function_2_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = js_iscallable(J, -1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 2);
    }
}

#define ANK_FUNCTION_2(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { ank_register_callback_2<&func>(J, #func); }

// Template function version of ANK_FUNCTION_3
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_3_callback_impl(js_State* J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = function_traits<func_ptr_type>;
    using param1_type = typename traits:: template arg<0>::type;
    using param2_type = typename traits:: template arg<1>::type;
    using param3_type = typename traits:: template arg<2>::type;
    using return_type = typename traits::return_type;
    
    param1_type param1 = js_helpers::js_to_value<param1_type>(J, 1);
    param2_type param2 = js_helpers::js_to_value<param2_type>(J, 2);
    param3_type param3 = js_helpers::js_to_value<param3_type>(J, 3);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&]() { return Func(param1, param2, param3); });
}

// Template function to register callback with 3 parameters
template<auto Func>
inline void ank_register_callback_3(js_State* J, pcstr name) {
    auto callback_impl = [](js_State *J) { ank_function_3_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = js_iscallable(J, -1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 3);
    }
}

#define ANK_FUNCTION_3(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { ank_register_callback_3<&func>(J, #func); }

// Template function version of ANK_FUNCTION_4
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_4_callback_impl(js_State* J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = function_traits<func_ptr_type>;
    using param1_type = typename traits:: template arg<0>::type;
    using param2_type = typename traits:: template arg<1>::type;
    using param3_type = typename traits:: template arg<2>::type;
    using param4_type = typename traits:: template arg<3>::type;
    using return_type = typename traits::return_type;
    
    param1_type param1 = js_helpers::js_to_value<param1_type>(J, 1);
    param2_type param2 = js_helpers::js_to_value<param2_type>(J, 2);
    param3_type param3 = js_helpers::js_to_value<param3_type>(J, 3);
    param4_type param4 = js_helpers::js_to_value<param4_type>(J, 4);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&]() { return Func(param1, param2, param3, param4); });
}

// Template function to register callback with 4 parameters
template<auto Func>
inline void ank_register_callback_4(js_State* J, pcstr name) {
    auto callback_impl = [](js_State *J) { ank_function_4_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = js_iscallable(J, -1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 4);
    }
}

#define ANK_FUNCTION_4(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { ank_register_callback_4<&func>(J, #func); }

// Template function version of ANK_FUNCTION_5
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_5_callback_impl(js_State* J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = function_traits<func_ptr_type>;
    using param1_type = typename traits:: template arg<0>::type;
    using param2_type = typename traits:: template arg<1>::type;
    using param3_type = typename traits:: template arg<2>::type;
    using param4_type = typename traits:: template arg<3>::type;
    using param5_type = typename traits:: template arg<4>::type;
    using return_type = typename traits::return_type;
    
    param1_type param1 = js_helpers::js_to_value<param1_type>(J, 1);
    param2_type param2 = js_helpers::js_to_value<param2_type>(J, 2);
    param3_type param3 = js_helpers::js_to_value<param3_type>(J, 3);
    param4_type param4 = js_helpers::js_to_value<param4_type>(J, 4);
    param5_type param5 = js_helpers::js_to_value<param5_type>(J, 5);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&]() { return Func(param1, param2, param3, param4, param5); });
}

// Template function to register callback with 5 parameters
template<auto Func>
inline void ank_register_callback_5(js_State* J, pcstr name) {
    auto callback_impl = [](js_State *J) { ank_function_5_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = js_iscallable(J, -1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 5);
    }
}

#define ANK_FUNCTION_5(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { ank_register_callback_5<&func>(J, #func); }

// Template function version of ANK_FUNCTION_UNIFIED
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_unified_callback_impl(js_State* J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = function_traits<func_ptr_type>;
    using return_type = typename traits::return_type;
    
    bvariant_map params = js_helpers::js_object_to_bvariant_map(J, 1);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&]() { return Func(params); });
}

// Template function to register unified callback
template<auto Func>
inline void ank_register_callback_unified(js_State* J, pcstr name) {
    auto callback_impl = [](js_State *J) { ank_function_unified_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = js_iscallable(J, -1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 1);
    }
}

#define ANK_FUNCTION_UNIFIED(func)                                                      \
    func(const bvariant_map&);                                                          \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func);                   \
    inline void register_js2cpp_callback_##func(js_State* J) {                          \
        ank_register_callback_unified<&func>(J, #func);                                 \
    }                                                                                   \
    function_traits<decltype(&func)>::return_type func

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
void js_register_empire_objects(js_State *J);
void js_register_mission_objects(js_State *J);
void js_register_city_objects(js_State *J);
void js_register_ui_objects(js_State *J);
void js_register_mission_vars(const settings_vars_t &vars);
void js_unref_function(xstring onclick_ref);
void js_call_function(xstring onclick_ref);
pcstr js_call_function_with_result(xstring js_ref, int param1, int param2);
void js_register_game_handlers(xstring missionid);