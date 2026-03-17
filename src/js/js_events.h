#pragma once

#include "js/js_struct.h"
#include "js/js.h"

namespace js_emit_detail {
    template<typename T> inline constexpr bool always_false_v = false;
    template<typename T>
    inline T val_or_def(const bvariant_map &args, pcstr name);

    template<typename T>
    inline T val_or_def(const bvariant_map &, pcstr) {
        static_assert(always_false_v<T>, "Unsupported script emit field type");
        return {};
    }

    template<>
    inline bool val_or_def<bool>(const bvariant_map &args, pcstr name) {
        return args.bool_or_def(name, false);
    }

    template<>
    inline float val_or_def<float>(const bvariant_map &args, pcstr name) {
        return args.n(name);
    }

    template<>
    inline double val_or_def<double>(const bvariant_map &args, pcstr name) {
        return static_cast<double>(args.n(name));
    }

    template<>
    inline xstring val_or_def<xstring>(const bvariant_map &args, pcstr name) {
        return args.s(name);
    }

    template<>
    inline vec2i val_or_def<vec2i>(const bvariant_map &args, pcstr name) {
        return args.vec2i_or_def(name, { 0, 0 });
    }

    template<>
    inline tile2i val_or_def<tile2i>(const bvariant_map &args, pcstr name) {
        return args.tile2i_or_def(name, { 0, 0 });
    }

    template<typename T>
    inline T val_or_def_enum(const bvariant_map &args, pcstr name) {
        using base_type = std::underlying_type_t<T>;
        return static_cast<T>(args.n(name));
    }

    template<typename T>
    inline T val_or_def_signed_integral(const bvariant_map &args, pcstr name) {
        const bvariant &v = args.value(name);
        switch (v.value_type()) {
        case bvariant::etype_bool:
            return static_cast<T>(v.as_bool() ? 1 : 0);
        case bvariant::etype_u16:
            return static_cast<T>(v.as_u16());
        case bvariant::etype_int32:
            return static_cast<T>(v.as_int32());
        case bvariant::etype_uint32:
            return static_cast<T>(v.as_uint32());
        case bvariant::etype_uint64:
            return static_cast<T>(v.as_uint64());
        case bvariant::etype_float:
        {
            const float n = v.as_float();
            if (!std::isfinite(n)) {
                return static_cast<T>(0);
            }
            return static_cast<T>(n);
        }
        default:
            return static_cast<T>(0);
        }
    }

    template<typename T>
    inline T val_or_def_unsigned_integral(const bvariant_map &args, pcstr name) {
        const bvariant &v = args.value(name);
        switch (v.value_type()) {
        case bvariant::etype_bool:
            return static_cast<T>(v.as_bool() ? 1u : 0u);
        case bvariant::etype_u16:
            return static_cast<T>(v.as_u16());
        case bvariant::etype_int32:
            return static_cast<T>(v.as_int32() < 0 ? 0 : v.as_int32());
        case bvariant::etype_uint32:
            return static_cast<T>(v.as_uint32());
        case bvariant::etype_uint64:
            return static_cast<T>(v.as_uint64());
        case bvariant::etype_float:
        {
            const float n = v.as_float();
            if (!std::isfinite(n) || n < 0.f) {
                return static_cast<T>(0);
            }
            return static_cast<T>(n);
        }
        default:
            return static_cast<T>(0);
        }
    }

    template<typename T>
    inline T value_or_default(const bvariant_map &args, pcstr name) {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
        if constexpr (std::is_enum_v<type>) {
            return val_or_def_enum<type>(args, name);
        } else if constexpr (std::is_integral_v<type> && std::is_signed_v<type> && !std::is_same_v<type, bool>) {
            return val_or_def_signed_integral<type>(args, name);
        } else if constexpr (std::is_integral_v<type> && std::is_unsigned_v<type> && !std::is_same_v<type, bool>) {
            return val_or_def_unsigned_integral<type>(args, name);
        } else {
            return val_or_def<type>(args, name);
        }
    }
}

#define ANK_SCRIPT_EVENT_EMIT_VALUE(v1) js_emit_detail::value_or_default<decltype(EventType::v1)>(args, #v1),
#define ANK_SCRIPT_EVENT_EMIT_VALUES(...) ANK_CONFIG_STRUCT_EXPAND(ANK_CONFIG_STRUCT_PASTE(ANK_SCRIPT_EVENT_EMIT_VALUE, __VA_ARGS__))

template<typename Type>
void script_permanent_callback_t(pcstr name, const Type &ev) {
    bvariant_map::scoped vmap;
    js_helper::writer(*vmap, ev);
    js_call_event_handlers(name, *vmap);
}

template<typename Type>
void script_emit_handler_t(const Type &ev) {
    events::emit(ev);
}

using js_script_emit_handler = void (*)(const bvariant_map &args);
void js_register_script_emit_handler(pcstr event_name, js_script_emit_handler handler);

#define ANK_SCRIPT_EVENT(Type, ...)                                                               \
    ANK_REGISTER_STRUCT_WRITER(Type, __VA_ARGS__)                                                 \
    void ANK_PERMANENT_CALLBACK(Type, ev) { script_permanent_callback_t(#Type, ev); }             \
    void script_emit_handler_ ##Type(const bvariant_map &args) {                                  \
        using EventType = Type;                                                                   \
        script_emit_handler_t(Type{ ANK_SCRIPT_EVENT_EMIT_VALUES(__VA_ARGS__) });                 \
    }                                                                                             \
    ANK_DECLARE_JSFUNCTION_ITERATOR(register_script_emit_ ##Type);                                \
    inline void register_script_emit_ ##Type(js_State *) {                                        \
        js_register_script_emit_handler(#Type, script_emit_handler_ ##Type);                      \
    }
/* END ANK_SCRIPT_EVENT */