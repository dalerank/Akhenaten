#pragma once

#include "mujs/jsi.h"

#include <cstddef>
#include <utility>

/** Typed CPTROFF (offset) bindings: the JS_PTR_* slot comes from the C++ field type (js_cptr_type_of). */
namespace js_bound_offset {

template<typename FieldT>
void bind_offset_field(js_State *J, js_StringNode name, size_t byte_offset) {
    J->bind_offset_property<FieldT>(name, byte_offset);
}

} // namespace js_bound_offset

/** Interned script name may differ from the C++ member name (fourth argument). */
#if defined(__clang__)
#define JS_REGISTER_BOUND_OFFSET_MEMBER(J, Struct, member, jsName)                                    \
    _Pragma("clang diagnostic push")                                                                \
    _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"")                                      \
    ::js_bound_offset::bind_offset_field<decltype(std::declval<Struct>().member)>((J), (jsName), offsetof(Struct, member)); \
    _Pragma("clang diagnostic pop")
#elif defined(__GNUC__)
#define JS_REGISTER_BOUND_OFFSET_MEMBER(J, Struct, member, jsName)                                    \
    _Pragma("GCC diagnostic push")                                                                  \
    _Pragma("GCC diagnostic ignored \"-Winvalid-offsetof\"")                                        \
    ::js_bound_offset::bind_offset_field<decltype(std::declval<Struct>().member)>((J), (jsName), offsetof(Struct, member)); \
    _Pragma("GCC diagnostic pop")
#else
#define JS_REGISTER_BOUND_OFFSET_MEMBER(J, Struct, member, jsName) \
    ::js_bound_offset::bind_offset_field<decltype(std::declval<Struct>().member)>((J), (jsName), offsetof(Struct, member))
#endif

/** Script property name is js_intern(#member) (same spelling as the C++ field). */
#define JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, Struct, member) \
    JS_REGISTER_BOUND_OFFSET_MEMBER(J, Struct, member, js_intern(#member))
