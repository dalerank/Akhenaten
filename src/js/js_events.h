#pragma once

#include <unordered_map>
#include <functional>

#include "core/variant.h"
#include "city/city_population.h"

#define ANK_SCRIPT_STRUCT_EXPAND( x ) x
#define ANK_SCRIPT_STRUCT_GET_MACRO(_1, _2, _3, _4, _5, _6, NAME,...) NAME
#define ANK_SCRIPT_STRUCT_PASTE(...) ANK_SCRIPT_STRUCT_EXPAND(ANK_SCRIPT_STRUCT_GET_MACRO(__VA_ARGS__, \
        ANK_SCRIPT_STRUCT_PASTE6, \
        ANK_SCRIPT_STRUCT_PASTE5, \
        ANK_SCRIPT_STRUCT_PASTE4, \
        ANK_SCRIPT_STRUCT_PASTE3, \
        ANK_SCRIPT_STRUCT_PASTE2, \
        ANK_SCRIPT_STRUCT_PASTE1)(__VA_ARGS__))

#define ANK_SCRIPT_STRUCT_PASTE2(func, v1) func(v1)
#define ANK_SCRIPT_STRUCT_PASTE3(func, v1, v2) ANK_SCRIPT_STRUCT_PASTE2(func, v1) ANK_SCRIPT_STRUCT_PASTE2(func, v2)
#define ANK_SCRIPT_STRUCT_PASTE4(func, v1, v2, v3) ANK_SCRIPT_STRUCT_PASTE2(func, v1)  ANK_SCRIPT_STRUCT_PASTE3(func, v2, v3)
#define ANK_SCRIPT_STRUCT_PASTE5(func, v1, v2, v3, v4) ANK_SCRIPT_STRUCT_PASTE2(func, v1) ANK_SCRIPT_STRUCT_PASTE4(func, v2, v3, v4)
#define ANK_SCRIPT_STRUCT_PASTE6(func, v1, v2, v3, v4, v5) ANK_SCRIPT_STRUCT_PASTE2(func, v1) ANK_SCRIPT_STRUCT_PASTE5(func, v2, v3, v4, v5)
#define ANK_SCRIPT_STRUCT_PASTE7(func, v1, v2, v3, v4, v5, v6) ANK_SCRIPT_STRUCT_PASTE2(func, v1) ANK_SCRIPT_STRUCT_PASTE6(func, v2, v3, v4, v5, v6)

#define ANK_SCRIPT_STRUCT_FROM(v1) js_j[#v1] = bvariant(js_t.v1); 

namespace js_helper {
    template<typename T>
    inline void writer(bvariant_map &js_j, T &js_t);
}

#define ANK_SCRIPT_EVENT(Type, ...)                                                               \
namespace js_helper {                                                                             \
    template<>                                                                                    \
    inline void writer<Type>(bvariant_map& js_j, Type& js_t) {                                    \
        ANK_SCRIPT_STRUCT_EXPAND(ANK_SCRIPT_STRUCT_PASTE(ANK_SCRIPT_STRUCT_FROM, __VA_ARGS__));   \
    }                                                                                             \
} void ANK_PERMANENT_CALLBACK(Type, ev) { bvariant_map vmap; js_helper::writer(vmap, ev); js_call_event_handlers(#Type, vmap); }

