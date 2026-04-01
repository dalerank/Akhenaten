#pragma once

#include "core/xstring.h"

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
