#pragma once

#include "mujs/mujs.h"

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

/**
 * Typed CPTROFF (offset) bindings: picks js_register_bound_*_offset_property from the C++ field type.
 * Unscoped enums are bound as JS_PTR_INT when sizeof(enum) == sizeof(int).
 */
namespace js_bound_offset {

template<typename FieldT>
void bind_offset_field(js_State *J, js_StringNode name, size_t byte_offset) {
    using T = std::remove_cv_t<FieldT>;
    if constexpr (std::is_same_v<T, bool>) {
        js_register_bound_bool_offset_property(J, name, byte_offset);
    } else if constexpr (std::is_same_v<T, float>) {
        js_register_bound_float_offset_property(J, name, byte_offset);
    } else if constexpr (std::is_same_v<T, int8_t> || std::is_same_v<T, int8_t>) {
        js_register_bound_int8_offset_property(J, name, byte_offset);
    } else if constexpr (std::is_same_v<T, uint8_t> || std::is_same_v<T, uint8_t>) {
        js_register_bound_uint8_offset_property(J, name, byte_offset);
    } else if constexpr (std::is_same_v<T, int16_t> || std::is_same_v<T, int16_t>) {
        js_register_bound_int16_offset_property(J, name, byte_offset);
    } else if constexpr (std::is_same_v<T, uint16_t> || std::is_same_v<T, uint16_t>) {
        js_register_bound_uint16_offset_property(J, name, byte_offset);
    } else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, unsigned int> || std::is_same_v<T, int32_t> ||
                         std::is_same_v<T, uint32_t>) {
        js_register_bound_int_offset_property(J, name, byte_offset);
    } else if constexpr (std::is_enum_v<T>) {
        static_assert(sizeof(T) == sizeof(int), "js_bound_offset: enum field must be int-sized for JS_PTR_INT binding");
        js_register_bound_int_offset_property(J, name, byte_offset);
    } else {
        static_assert(sizeof(T) == 0, "js_bound_offset: unsupported field type — extend bind_offset_field");
    }
}

} // namespace js_bound_offset

/** Interned script name may differ from the C++ member name (fourth argument). */
#define JS_REGISTER_BOUND_OFFSET_MEMBER(J, Struct, member, jsName) \
    ::js_bound_offset::bind_offset_field<decltype(std::declval<Struct>().member)>((J), (jsName), offsetof(Struct, member))

/** Script property name is js_intern(#member) (same spelling as the C++ field). */
#define JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, Struct, member) \
    JS_REGISTER_BOUND_OFFSET_MEMBER(J, Struct, member, js_intern(#member))
