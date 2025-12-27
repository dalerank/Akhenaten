#pragma once

#include <unordered_map>
#include <functional>

#include "core/variant.h"
#include "js/js_struct.h"

#define ANK_SCRIPT_EVENT(Type, ...)                                                               \
    ANK_REGISTER_STRUCT_WRITER(Type, __VA_ARGS__)                                                 \
    void ANK_PERMANENT_CALLBACK(Type, ev) { bvariant_map vmap; js_helper::writer(vmap, ev); js_call_event_handlers(#Type, vmap); }

