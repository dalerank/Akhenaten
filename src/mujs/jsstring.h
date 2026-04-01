#pragma once

#include "core/xstring.h"

#include <cstdint>

/** Interned identifier / literal string (global xstring pool). */
using js_StringNode = xstring_value*;

struct js_State;

js_StringNode js_intern(pcstr s);

inline pcstr js_strnode_cstr(const js_StringNode s) {
    if (!s) {
        return "";
    }
    const char *p = s->value.c_str();
    return p ? p : "";
}

inline int js_stringnode_cmp(js_StringNode a, js_StringNode b) {
    const auto ua = reinterpret_cast<std::uintptr_t>(a);
    const auto ub = reinterpret_cast<std::uintptr_t>(b);
    if (ua == ub) {
        return 0;
    }
    return ua < ub ? -1 : 1;
}
