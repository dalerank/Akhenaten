#pragma once

#include "mujs/jsi.h"

#include "js/js_constants.h"
#include "js/js_struct.h"
#include "js/js_global_object.h"
#include "mujs/jsvalue.h"
#include "core/bstring.h"
#include "core/core.h"
#include "core/typename.h"
#include "js/js_defines.h"
#include "core/vec2i.h"
#include "core/archive.h"
#include "core/variant.h"
#include "core/svector.h"
#include "core/hvector.h"
#include "core/profiler.h" // ANK_FUNCTION_* expand to OZZY_PROFILER_FUNCTION()
#include "grid/grid.h"
#include "grid/point.h"

#include <algorithm>
#include <vector>
#include <string>
#include <optional>
#include <mutex>
#include <type_traits>
#include <cstdint>
#include <cmath>
#include <cstring>

class settings_vars_t;

// Forward declarations
enum e_resource : uint8_t;

// Helper functions to convert JS values to C++ types
namespace js_helpers {
    template<typename T>
    inline T js_to_value_impl(js_State *J, int idx);

    // Any conversion may run script code (toString/valueOf) and js_throw, whose longjmp
    // skips destructors of the bridge frames holding already-converted arguments.
    template<typename T>
    inline T js_to_value(js_State *J, int idx) {
        static_assert(std::is_trivially_destructible_v<T>,
                      "js_to_value: JS-bound argument types must be trivially destructible (MuJS unwinds with longjmp)");
        return js_to_value_impl<T>(J, idx);
    }

    template<>
    inline int js_to_value_impl<int>(js_State *J, int idx) {
        return js_tointeger(J, idx);
    }

    template<>
    inline unsigned int js_to_value_impl<unsigned int>(js_State *J, int idx) {
        return js_touint32(J, idx);
    }

    template<>
    inline double js_to_value_impl<double>(js_State *J, int idx) {
        return js_tonumber(J, idx);
    }

    template<>
    inline float js_to_value_impl<float>(js_State *J, int idx) {
        return (float)js_tonumber(J, idx);
    }

    template<>
    inline bool js_to_value_impl<bool>(js_State *J, int idx) {
        return js_toboolean(J, idx);
    }

    template<>
    inline const char *js_to_value_impl<const char *>(js_State *J, int idx) {
        auto pp = js_tostring(J, idx);
        return js_strnode_cstr(pp);
    }

    template<>
    inline xstring js_to_value_impl<xstring>(js_State *J, int idx) {
        if (J->isundefined(idx) || J->isnull(idx)) {
            return xstring();
        }
        auto pp = js_tostring(J, idx);
        xstring r;
        r._set(pp);
        return r;
    }

    /** Reference to a JS function stored in the registry (for callbacks). */
    struct js_function_ref {
        xstring ref;
        bool empty() const { return ref.empty(); }
    };

    template<>
    inline js_function_ref js_to_value_impl<js_function_ref>(js_State *J, int idx) {
        if (!J->iscallable(idx)) {
            return js_function_ref{};
        }
        js_copy(J, idx);
        auto pp = js_ref(J);
        xstring r; r._set(pp);
        js_pop(J, 1);
        return js_function_ref{ r };
    }

    extern js_StringNode property_x;
    extern js_StringNode property_y;
    extern js_StringNode property_minx;
    extern js_StringNode property_miny;
    extern js_StringNode property_maxx;
    extern js_StringNode property_maxy;

    template<>
    inline vec2i js_to_value_impl<vec2i>(js_State *J, int idx) {
        vec2i result;
        if (J->isobject(idx) && !J->isarray(idx) && J->toobject(idx)->type == JS_CVEC2I) {
            js_Object *o = J->toobject(idx);
            return vec2i(o->u.vec2.x, o->u.vec2.y);
        }
        if (J->isobject(idx) && !J->isarray(idx)) {
            J->getproperty(idx, property_x);
            result.x = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0;
            js_pop(J, 1);

            J->getproperty(idx, property_y);
            result.y = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0;
            js_pop(J, 1);
        } else if (J->isarray(idx)) {
            js_getindex(J, idx, 0); result.x = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
            js_getindex(J, idx, 1); result.y = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
        }
        return result;
    }

    template<>
    inline tile2i js_to_value_impl<tile2i>(js_State *J, int idx) {
        int x = 0, y = 0;
        if (J->isobject(idx) && !J->isarray(idx) && J->toobject(idx)->type == JS_CVEC2I) {
            js_Object *o = J->toobject(idx);
            return tile2i(o->u.vec2.x, o->u.vec2.y);
        }
        if (J->isobject(idx) && !J->isarray(idx)) {
            J->getproperty(idx, property_x);
            x = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0;
            js_pop(J, 1);

            J->getproperty(idx, property_y);
            y = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0;
            js_pop(J, 1);
        } else if (J->isarray(idx)) {
            js_getindex(J, idx, 0); x = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
            js_getindex(J, idx, 1); y = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0; js_pop(J, 1);
        }
        return tile2i(x, y);
    }

    template<>
    inline bvariant js_to_value_impl<bvariant>(js_State *J, int idx) {
        if (J->isundefined(idx)) {
            return bvariant(); // none
        } else if (J->isboolean(idx)) {
            // js_toboolean returns int; cast so we hit bvariant(bool), not bvariant(int32).
            return bvariant(js_toboolean(J, idx) != 0);
        } else if (J->isstring(idx)) {
            xstring str;
            str._set(js_tostring(J, idx));
            return bvariant(str);
        } else if (J->isnumber(idx) || J->iscnumber(idx)) {
            double num = js_tonumber(J, idx);
            // Try to preserve integer if possible
            if (num == (int)num) {
                return bvariant((int)num);
            } else {
                return bvariant((float)num);
            }
        } else if (J->iscvec2i(idx)) {
            js_Object *o = J->toobject(idx);
            return bvariant(vec2i(o->u.vec2.x, o->u.vec2.y));
        } else if (J->isobject(idx) && !J->isarray(idx)) {
            // Check if it's a vec2i-like object with x and y properties
            J->getproperty(idx, property_x);
            bool has_x = !J->isundefined(-1);
            js_pop(J, 1);

            if (has_x) {
                J->getproperty(idx, property_x);
                int x = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0;
                js_pop(J, 1);
                J->getproperty(idx, property_y);
                int y = J->isnumber(-1) ? (int)js_tonumber(J, -1) : 0;
                js_pop(J, 1);
                return bvariant(vec2i(x, y));
            } else {
                return bvariant(); // none for other objects
            }
        } else {
            return bvariant(); // none
        }
    }

    inline bvariant js_bvariant_from_js_stack(js_State *J, int idx) {
        if (J->isundefined(idx) || J->isnull(idx)) {
            return bvariant();
        }
        return js_to_value<bvariant>(J, idx);
    }

    template<>
    inline e_resource js_to_value_impl<e_resource>(js_State *J, int idx) {
        return (e_resource)js_tointeger(J, idx);
    }

    template<typename T>
    inline void js_push_value(js_State *J, T value) {
        static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>,
                      "js_push_value: no specialization for this type; add one in js_game.h");
        js_pushnumber(J, (double)value);
    }

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
    inline void js_push_value<const char *>(js_State *J, const char *value) {
        J->pushstring(value);
    }

    template<>
    inline void js_push_value<vec2i>(js_State *J, vec2i value) {
        J->newvec2i(value.x, value.y);
    }

    template<>
    inline void js_push_value<tile2i>(js_State *J, tile2i value) {
        J->newvec2i(value.x(), value.y());
    }

    template<>
    inline void js_push_value<grid_area>(js_State *J, grid_area value) {
        J->newobject();
        js_pushnumber(J, value.tmin_x); js_setproperty(J, -2, property_minx);
        js_pushnumber(J, value.tmin_y); js_setproperty(J, -2, property_miny);
        js_pushnumber(J, value.tmax_x); js_setproperty(J, -2, property_maxx);
        js_pushnumber(J, value.tmax_y); js_setproperty(J, -2, property_maxy);
    }

    template<>
    inline void js_push_value<xstring>(js_State *J, xstring value) {
        J->pushstring((js_StringNode)value._get());
    }

    template<>
    inline void js_push_value<e_resource>(js_State *J, e_resource value) {
        js_pushnumber(J, (int)value);
    }

    template<typename T, size_t Cap>
    inline void js_push_value(js_State *J, const svector<T, Cap> &arr) {
        J->newarray();
        for (size_t i = 0; i < arr.size(); ++i) {
            js_pushnumber(J, (double)arr[i]);
            js_setindex(J, -2, (int)i);
        }
    }

    template<typename T, size_t Cap>
    inline void js_push_value(js_State *J, const hvector<T, Cap> &arr) {
        J->newarray();
        for (size_t i = 0; i < arr.size(); ++i) {
            js_pushnumber(J, (double)arr[i]);
            js_setindex(J, -2, (int)i);
        }
    }

    template<size_t Cap>
    inline void js_push_value(js_State *J, const hvector<vec2i, Cap> &arr) {
        J->newarray();
        for (size_t i = 0; i < arr.size(); ++i) {
            js_push_value<vec2i>(J, arr[i]);
            js_setindex(J, -2, (int)i);
        }
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
            J->pushstring(val.as_str().c_str());
            break;
        case bvariant::etype_ptr:
            js_pushnull(J);
            break;
        case bvariant::etype_vec2i:
        {
            const vec2i pos = val.as_vec2i();
            js_push_value<vec2i>(J, pos);
            break;
        }
        case bvariant::etype_tile2i:
        {
            const tile2i pos = val.as_tile2i();
            js_push_value<tile2i>(J, pos);
            break;
        }
        case bvariant::etype_grid_area:
        {
            const grid_area a = val.as_grid_area();
            J->newobject();
            js_pushnumber(J, a.tmin_x); js_setproperty(J, -2, property_minx);
            js_pushnumber(J, a.tmin_y); js_setproperty(J, -2, property_miny);
            js_pushnumber(J, a.tmax_x); js_setproperty(J, -2, property_maxx);
            js_pushnumber(J, a.tmax_y); js_setproperty(J, -2, property_maxy);
            break;
        }
        case bvariant::etype_none:
        default:
            J->pushundefined();
            break;
        }
    }

    inline void js_push_bvariant_map_as_js_object(js_State *J, const bvariant_map &params) {
        J->newobject();
        for (const auto &kv : params) {
            js_push_bvariant(J, kv.second);
            js_setproperty(J, -2, js_intern(kv.first.c_str()));
        }
    }

    template<>
    inline void js_push_value<bvariant_map>(js_State *J, bvariant_map value) {
        js_push_bvariant_map_as_js_object(J, value);
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
            J->pushundefined();
        }
    }

    inline void js_push_void(js_State *J) {
        J->pushundefined();
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

    inline bvariant js_bvariant_from_js_value(js_State *J, int idx) {
        if (J->isboolean(idx)) {
            return bvariant(js_toboolean(J, idx) != 0);
        }
        if (J->isstring(idx)) {
            xstring pp;
            pp._set(js_tostring(J, idx));
            return bvariant(pp);
        }
        if (J->isnumber(idx) || J->iscnumber(idx)) {
            const double num = js_tonumber(J, idx);
            if (num == (int)num) {
                return bvariant((int)num);
            }
            return bvariant((float)num);
        }
        if (J->isarray(idx)) {
            return bvariant(js_to_value<vec2i>(J, idx));
        }
        if (J->isobject(idx)) {
            js_Object *o = J->toobject(idx);
            if (o && o->type == JS_CVEC2I) {
                return bvariant(js_to_value<vec2i>(J, idx));
            }
            J->getproperty(idx, property_x);
            const bool has_x = J->isnumber(-1);
            js_pop(J, 1);
            J->getproperty(idx, property_y);
            const bool has_y = J->isnumber(-1);
            js_pop(J, 1);
            if (has_x || has_y) {
                return bvariant(js_to_value<vec2i>(J, idx));
            }
        }
        return bvariant();
    }

    // Convert JS object to bvariant_map
    inline bvariant_map js_object_to_bvariant_map(js_State *J, int idx) {
        bvariant_map result;
        if (!J->isobject(idx) || J->isarray(idx)) {
            return result;
        }

        js_pushiterator(J, idx, 1); // own properties only
        js_StringNode key;
        while ((key = js_nextiterator(J, -1))) {
            J->getproperty(idx, key);
            bvariant value = js_bvariant_from_js_value(J, -1);
            xstring keyp;
            keyp._set(key);
            result[keyp] = value;
            js_pop(J, 1); // pop value
        }
        js_pop(J, 1); // pop iterator

        return result;
    }
}

namespace config {

    using jsfunc_iterator_function_cb = void(js_State *);
    using FunctionIterator = FuncLinkedList<jsfunc_iterator_function_cb *, ConfigTag>;

    struct ESIteratorEntry {
        xstring es_type;
        void (*regnew)(pcstr name);
        void (*clear)();
        ESIteratorEntry *next;
        static ESIteratorEntry *tail;
        ESIteratorEntry(pcstr t, void (*cb)(pcstr), void (*cl)()) : es_type(t), regnew(cb), clear(cl) {
            next = tail;
            tail = this;
        }
    };

    struct ModifierIteratorEntry {
        xstring modifier_key;
        void (*callback)(js_State *J, pcstr name, pcstr value);
        ModifierIteratorEntry *next;
        static ModifierIteratorEntry *tail;
        ModifierIteratorEntry(pcstr key, void (*cb)(js_State *, pcstr, pcstr)) : modifier_key(key), callback(cb) {
            next = tail;
            tail = this;
        }
    };

} // end namespace config

#define ANK_REGISTER_ES_ITERATOR(es_type, func, clear) \
    static config::ESIteratorEntry ANK_CONFIG_CC1(es_iter_entry, __LINE__)(#es_type, func, clear);

#define ANK_REGISTER_MODIFIER_ITERATOR(modifier_key, func) \
    static config::ModifierIteratorEntry ANK_CONFIG_CC1(mod_iter_entry, __LINE__)(#modifier_key, func);

#define ANK_DECLARE_JSFUNCTION_ITERATOR(func) void func(js_State*); \
    namespace config {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static config::FunctionIterator ANK_CONFIG_CC1(func_handler, __LINE__)(func)

template<typename Func>
struct js_function_traits;

template<typename R, typename... Args>
struct js_function_traits<R(*)(Args...)> {
    using return_type = R;
    static constexpr size_t arity = sizeof...(Args);

    template<size_t N>
    struct arg {
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};

template<typename R, typename... Args>
struct js_function_traits<R(Args...)> : js_function_traits<R(*)(Args...)> {};

template<typename C, typename R, typename... Args>
struct js_function_traits<R(C:: *)(Args...)> {
    using return_type = R;
    static constexpr size_t arity = sizeof...(Args);

    template<size_t N>
    struct arg {
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};

template<typename C, typename R, typename... Args>
struct js_function_traits<R(C:: *)(Args...) const> : js_function_traits<R(C:: *)(Args...)> {};

#define ANK_FUNCTION_NAMED(fname, func)                                                                         \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##fname);                                          \
    void permanent_js2cpp_callback_##fname(js_State* J); void register_js2cpp_callback_##fname(js_State* J) {   \
        js_getglobal(J, #fname); bool exists = J->iscallable(-1); js_pop(J, 1);                                 \
        if (!exists) { REGISTER_GLOBAL_FUNCTION(J, permanent_js2cpp_callback_##fname, #fname, 0); }  \
    } void permanent_js2cpp_callback_##fname(js_State *J) {                                                     \
        constexpr bool is_void = (std::is_void_v<js_function_traits<decltype(&func)>::return_type>);            \
        js_helpers::js_invoke_and_push<is_void>(J, [&]() { return func(); });                                   \
    }

#define ANK_FUNCTION(func) \
    ANK_FUNCTION_NAMED(func, func)

/** Register a C variable as a global JS variable (JS_CPTR); the JS_PTR_* slot comes from its type.
 *  Scripts read/write it in place. */
#define ANK_BOUND(js_name, cptr) \
    static void ANK_CONFIG_CC1(ank_bound_reg_, __LINE__)(js_State * J) { J->bind_global(js_intern(#js_name), &(cptr)); } \
    ANK_DECLARE_JSFUNCTION_ITERATOR(ANK_CONFIG_CC1(ank_bound_reg_, __LINE__));

/** Register a global JS object (JsName) whose listed fields bind as JS_CPTR ints (same storage as ANK_BOUND).
 *  Fields must map to int-sized storage (enums, int8_t, etc. via (int*) cast in implementation). */
#define ANK_GLOBAL_OBJECT(ContainerExpr, JsName, ...)                                                               \
    static void ank_register_global_obj_##JsName(js_State *J) {                                                     \
        js_getglobal(J, #JsName);                                                                                   \
        const bool already_registered = J->isobject(-1);                                                            \
        js_pop(J, 1);                                                                                               \
        if (already_registered) return;                                                                             \
        J->newobject();                        /* stack: [obj]      */                                             \
        js_dup(J);                              /* stack: [obj, obj] */                                             \
        js_defglobal(J, js_intern(#JsName), 0); /* stores top, pops  → stack: [obj] */                              \
        ANK_GLOBAL_OBJ_PASTE(ContainerExpr, __VA_ARGS__);  /* attaches CPTR props to [obj] */                       \
        js_pop(J, 1);                           /* stack: []         */                                             \
    }                                                                                                               \
    ANK_DECLARE_JSFUNCTION_ITERATOR(ank_register_global_obj_##JsName);

// Template function version of ANK_FUNCTION_RAW
// This template function handles the callback logic (extracted from macro)
template <auto Func>
inline void ank_function_raw_callback_impl(js_State* J) {
    // std::decay_t converts function types to function pointer types
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
    using return_type = typename traits::return_type;

    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&]() { return Func(J); });
}

// Template function to register callback with 1 parameter
template <auto Func>
inline void ank_register_callback_raw(js_State* J, pcstr name) {
    auto callback_impl = [](js_State* J) { ank_function_raw_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 1);
    }
}

#define ANK_FUNCTION_RAW(func)                                        \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) {        \
        OZZY_PROFILER_FUNCTION();                                     \
        ank_register_callback_raw<&func>(J, #func);                   \
    }

// Template function version of ANK_FUNCTION_1
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_1_callback_impl(js_State *J) {
    // std::decay_t converts function types to function pointer types
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
    using param_type = typename traits:: template arg<0>::type;
    using return_type = typename traits::return_type;

    param_type param = js_helpers::js_to_value<param_type>(J, 1);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&] () { return Func(param); });
}

// Template function to register callback with 1 parameter
template<auto Func>
inline void ank_register_callback_1(js_State *J, pcstr name) {
    auto callback_impl = [] (js_State *J) { ank_function_1_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 1);
    }
}

#define ANK_FUNCTION_1(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { OZZY_PROFILER_FUNCTION(); ank_register_callback_1<&func>(J, #func); }

// Template function version of ANK_FUNCTION_2
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_2_callback_impl(js_State *J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
    using param1_type = typename traits:: template arg<0>::type;
    using param2_type = typename traits:: template arg<1>::type;
    using return_type = typename traits::return_type;

    param1_type param1 = js_helpers::js_to_value<param1_type>(J, 1);
    param2_type param2 = js_helpers::js_to_value<param2_type>(J, 2);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&] () { return Func(param1, param2); });
}

// Template function to register callback with 2 parameters
template<auto Func>
inline void ank_register_callback_2(js_State *J, pcstr name) {
    auto callback_impl = [] (js_State *J) { ank_function_2_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 2);
    }
}

#define ANK_FUNCTION_2(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { OZZY_PROFILER_FUNCTION(); ank_register_callback_2<&func>(J, #func); }

// Template function version of ANK_FUNCTION_3
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_3_callback_impl(js_State *J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
    using param1_type = typename traits:: template arg<0>::type;
    using param2_type = typename traits:: template arg<1>::type;
    using param3_type = typename traits:: template arg<2>::type;
    using return_type = typename traits::return_type;

    param1_type param1 = js_helpers::js_to_value<param1_type>(J, 1);
    param2_type param2 = js_helpers::js_to_value<param2_type>(J, 2);
    param3_type param3 = js_helpers::js_to_value<param3_type>(J, 3);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&] () { return Func(param1, param2, param3); });
}

// Template function to register callback with 3 parameters
template<auto Func>
inline void ank_register_callback_3(js_State *J, pcstr name) {
    auto callback_impl = [] (js_State *J) { ank_function_3_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 3);
    }
}

#define ANK_FUNCTION_3(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { OZZY_PROFILER_FUNCTION(); ank_register_callback_3<&func>(J, #func); }

// Template function version of ANK_FUNCTION_4
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_4_callback_impl(js_State *J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
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
    js_helpers::js_invoke_and_push<is_void>(J, [&] () { return Func(param1, param2, param3, param4); });
}

// Template function to register callback with 4 parameters
template<auto Func>
inline void ank_register_callback_4(js_State *J, pcstr name) {
    auto callback_impl = [] (js_State *J) { ank_function_4_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 4);
    }
}

#define ANK_FUNCTION_4(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { OZZY_PROFILER_FUNCTION(); ank_register_callback_4<&func>(J, #func); }

// Template function version of ANK_FUNCTION_5
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_5_callback_impl(js_State *J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
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
    js_helpers::js_invoke_and_push<is_void>(J, [&] () { return Func(param1, param2, param3, param4, param5); });
}

// Template function to register callback with 5 parameters
template<auto Func>
inline void ank_register_callback_5(js_State *J, pcstr name) {
    auto callback_impl = [] (js_State *J) { ank_function_5_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 5);
    }
}

#define ANK_FUNCTION_5(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { OZZY_PROFILER_FUNCTION(); ank_register_callback_5<&func>(J, #func); }

// Template function version of ANK_FUNCTION_6
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_6_callback_impl(js_State *J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
    using param1_type = typename traits:: template arg<0>::type;
    using param2_type = typename traits:: template arg<1>::type;
    using param3_type = typename traits:: template arg<2>::type;
    using param4_type = typename traits:: template arg<3>::type;
    using param5_type = typename traits:: template arg<4>::type;
    using param6_type = typename traits:: template arg<5>::type;
    using return_type = typename traits::return_type;

    param1_type param1 = js_helpers::js_to_value<param1_type>(J, 1);
    param2_type param2 = js_helpers::js_to_value<param2_type>(J, 2);
    param3_type param3 = js_helpers::js_to_value<param3_type>(J, 3);
    param4_type param4 = js_helpers::js_to_value<param4_type>(J, 4);
    param5_type param5 = js_helpers::js_to_value<param5_type>(J, 5);
    param6_type param6 = js_helpers::js_to_value<param6_type>(J, 6);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&] () { return Func(param1, param2, param3, param4, param5, param6); });
}

// Template function to register callback with 6 parameters
template<auto Func>
inline void ank_register_callback_6(js_State *J, pcstr name) {
    auto callback_impl = [] (js_State *J) { ank_function_6_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 6);
    }
}

#define ANK_FUNCTION_6(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { OZZY_PROFILER_FUNCTION(); ank_register_callback_6<&func>(J, #func); }

// Template function version of ANK_FUNCTION_7
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_7_callback_impl(js_State *J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
    using param1_type = typename traits:: template arg<0>::type;
    using param2_type = typename traits:: template arg<1>::type;
    using param3_type = typename traits:: template arg<2>::type;
    using param4_type = typename traits:: template arg<3>::type;
    using param5_type = typename traits:: template arg<4>::type;
    using param6_type = typename traits:: template arg<5>::type;
    using param7_type = typename traits:: template arg<6>::type;
    using return_type = typename traits::return_type;

    param1_type param1 = js_helpers::js_to_value<param1_type>(J, 1);
    param2_type param2 = js_helpers::js_to_value<param2_type>(J, 2);
    param3_type param3 = js_helpers::js_to_value<param3_type>(J, 3);
    param4_type param4 = js_helpers::js_to_value<param4_type>(J, 4);
    param5_type param5 = js_helpers::js_to_value<param5_type>(J, 5);
    param6_type param6 = js_helpers::js_to_value<param6_type>(J, 6);
    param7_type param7 = js_helpers::js_to_value<param7_type>(J, 7);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&] () { return Func(param1, param2, param3, param4, param5, param6, param7); });
}

// Template function to register callback with 7 parameters
template<auto Func>
inline void ank_register_callback_7(js_State *J, pcstr name) {
    auto callback_impl = [] (js_State *J) { ank_function_7_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, callback_impl, name, 7);
    }
}

#define ANK_FUNCTION_7(func) \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_js2cpp_callback_##func); \
    inline void register_js2cpp_callback_##func(js_State* J) { OZZY_PROFILER_FUNCTION(); ank_register_callback_7<&func>(J, #func); }

// Template function version of ANK_FUNCTION_UNIFIED
// This template function handles the callback logic (extracted from macro)
template<auto Func>
inline void ank_function_unified_callback_impl(js_State *J) {
    using func_ptr_type = std::decay_t<decltype(Func)>;
    using traits = js_function_traits<func_ptr_type>;
    using return_type = typename traits::return_type;

    bvariant_map params = js_helpers::js_object_to_bvariant_map(J, 1);
    constexpr bool is_void = std::is_void_v<return_type>;
    js_helpers::js_invoke_and_push<is_void>(J, [&] () { return Func(params); });
}

// Template function to register unified callback
template<auto Func>
inline void ank_register_callback_unified(js_State *J, pcstr name) {
    auto callback_impl = [] (js_State *J) { ank_function_unified_callback_impl<Func>(J); };
    js_getglobal(J, name);
    bool exists = J->iscallable(-1);
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
    js_function_traits<decltype(&func)>::return_type func

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
void js_register_sound_object(js_State* J);
void js_register_empire_objects(js_State *J);
void js_register_empire_object_proto(js_State* J);
void js_register_empire_city_map_proto(js_State* J);
void js_register_empire_city_proto(js_State* J);
void js_register_empire_trader_proto(js_State* J);
void js_register_invasion_warning_proto(js_State* J);
void js_register_mission_objects(js_State *J);
void js_register_city_objects(js_State *J);
void js_register_figure(js_State *J);
void js_register_figure_trade_proto(js_State *J);
void js_register_figure_transport_ship_proto(js_State *J);
void js_register_figure_warship_proto(js_State *J);
void js_register_figure_params(js_State *J);
void js_register_building(js_State *J);
void js_register_building_params(js_State *J);
void js_register_imperial_visible_request(js_State *J);
void js_register_house(js_State *J);
void js_register_enemy_army(js_State *J);
void js_register_temple_complex_building(js_State *J);
void js_register_storage_yard(js_State *J);
void js_register_monument(js_State *J);
void js_register_debug_props_functions(js_State* J);
js_Object *js_get_building_prototype(void);
void js_register_ui_objects(js_State *J);
void js_register_mission_vars(const settings_vars_t &vars);
void js_unref_function(xstring onclick_ref);
void js_call_function(xstring onclick_ref);
void js_call_function_bool(xstring js_ref, bool param);
bvariant js_call_function(xstring js_ref, int param1, int param2);
bvariant js_call_function(xstring js_ref, const bvariant_map &params);
int js_game_emit(js_State *J, pcstr event_name);
int js_game_emit_es(xstring es, xstring sub_event, bvariant_map args);
void js_register_game_handlers(xstring missionid);
void js_call_event_handlers(const xstring &event_name, const bvariant_map &object);
bool js_has_event_handlers(const xstring &event_name);

void js_register_entity_systems();
void js_register_console_command(js_State *J);

template<typename T>
inline void js_event(const T &ev, const xstring &evname_str) {
    if (!js_has_event_handlers(evname_str)) {
        return;
    }

    bvariant_map::scoped js_j;
    js_helper::writer(*js_j, ev);
    js_call_event_handlers(evname_str, *js_j);
}

namespace js_helpers {
    /** One identifier of a composite key. bstring64 truncates silently, and es_hash_str
     *  cannot detect it afterwards (it measures the parts it was handed), so check here.
     *  The parser applies the same 63-char limit to script-side identifiers. */
    inline bstring64 es2str_checked(pcstr es) {
        // An unset xstring yields a null c_str(); callers treat that as an empty
        // component and filter the miss themselves, so only guard against truncation.
        if (!es) {
            return { "" };
        }
        verify_no_crash_var(strlen(es) < (size_t)bstring64::capacity,
                            "es2str: identifier '%s' does not fit in %d bytes",
                            es, (int)bstring64::capacity);
        return { es };
    }

    inline bstring64 es2str(pcstr es) { return es2str_checked(es); }
    inline bstring64 es2str(const xstring &es) { return es2str_checked(es.c_str()); }
    inline bstring64 es2str(const cstring &es) { return es2str_checked(es.c_str()); }

    template<size_t N>
    inline bstring64 es2str(const char (&es)[N]) { return es2str_checked(es); }

    template<typename ES>
    inline bstring64 es2str(const ES &) {
        type_name_holder<ES> esname;
        auto buf = type_enclosing_function_name(esname.value.data());
        return es2str_checked(buf);
    }

    /** Composite [es=(a, b)] key: identifiers sorted, joined with '+'.
     *  Must stay byte-identical to what parse_modifier_tuple_value builds in the parser,
     *  which joins into a 512-byte buffer. bstring::append truncates silently, so a key
     *  that does not fit here would register a handler under one name and dispatch it
     *  under another, with no diagnostic — check the length instead of losing it. */
    template<size_t S = 128, typename ... ES>
    bstring<S> es_hash_str(ES ... es) {
        // Each identifier fits in bstring64 (the parser caps one at 63 chars); only the
        // joined result needs the wider buffer.
        hvector<bstring64, 4> parts;
        (parts.push_back(es2str(es)), ...);
        auto cstr_compare = [] (pcstr s1, pcstr s2) { return strcmp(s1, s2) < 0; };
        std::sort(parts.begin(), parts.end(), cstr_compare);
        size_t needed = parts.empty() ? 0 : parts.size() - 1;
        for (const auto &p : parts) {
            needed += strlen(p.c_str());
        }
        verify_no_crash_var(needed < S, "es_hash_str: key needs %d bytes, capacity %d", (int)needed, (int)S);
        bstring<S> result;
        bool first = true;
        for (const auto &p : parts) {
            if (!first) {
                result.append("+");
            }
            result.append(p.c_str());
            first = false;
        }
        return result;
    }
}

template<typename T, typename ... ES>
inline void js_event(const T &ev, ES ... es) {
    js_event(ev, xstring(js_helpers::es_hash_str(es...)));
}

template<typename T>
inline void js_event(const T &ev) {
    type_name_holder<T> evname;
    js_event(ev, xstring(type_simplified_name(evname.value.data())));
}