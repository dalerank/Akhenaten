#pragma once

#include <utility>

template <typename dest_type>
struct smart_cast_dcast_helper;

#define IMPL_GEN_SMART_CAST(type, dcastfun)       \
    template <>                                   \
    struct smart_cast_dcast_helper<type*> {       \
        template <typename src_type>              \
        static inline type* cast(src_type& src) { \
            return src.dcastfun();                \
        }                                         \
    };

#define GENERATE_SMART_CAST(type) IMPL_GEN_SMART_CAST(type, dcast_##type)
#define GENERATE_SMART_CAST_CUSTOM(type, custom) IMPL_GEN_SMART_CAST(type, dcast_##custom)
#define GENERATE_SMART_CAST_NS(ns, type) IMPL_GEN_SMART_CAST(ns::type, dcast_##ns##_##type)
#define GENERATE_SMART_CAST_NS_SHORT(ns, type) IMPL_GEN_SMART_CAST(ns::type, dcast_##type)

template <typename dest_type, typename src_type, bool dest_is_base_of_src>
struct smart_cast_helper;

template <typename same_type>
struct smart_cast_helper<same_type *, same_type, false> {
    // smart_cast to the same type - simply return pointer to src
    static inline same_type *cast(same_type &src) { return &src; }
};

template <typename dest_type, typename src_type>
struct smart_cast_helper<dest_type *, src_type, true> {
    // smart_cast to base class - use implicit conversion from src_type * to dest_type *
    static inline dest_type *cast(src_type &src) { return &src; }
};

template <typename dest_type, typename src_type>
struct smart_cast_helper<dest_type *, src_type, false> {
    // smart_cast to some other dest_type which is not base of src_type - delegate to smart_cast_dcast_helper
    static inline dest_type *cast(src_type &src) { return smart_cast_dcast_helper<dest_type *>::cast(src); }
};

template <typename dest_type, typename src_type>
inline typename std::enable_if_t<std::is_pointer_v<dest_type>, dest_type> smart_cast(src_type &&src) {
    // src is a reference to a pointer or a reference to something that acts like a pointer;
    // result of its dereferencing (*src) should be a reference to a value which is pointed to by src;
    // decltype(*src) with its reference stripped off is the type of that (possibly, cv-qualified) pointee value
    using src_value = std::remove_reference_t<decltype(*src)>;
    using src_value_nocv = std::remove_cv_t<src_value> ;

    // dest_type is definitely a raw pointer, so remove_pointer yields the type of its (possibly, cv-qualified) pointee value
    using dest_value = std::remove_pointer_t<dest_type> ;
    using dest_value_nocv = std::remove_cv_t<dest_value>;

    // copy all cv-qualifiers from src_value to dest_value_nocv and declare a pointer to that resulting type
    // which is the "least cv-qualified" type we can return (having taken src_value's qualifiers into account)
    using dest_type_cv_protected = std::add_cv_t<dest_value_nocv> *;

    // if src is not null, use a smart_cast_helper (which doesn't imply any cv-qualifiers at all) to perform the cast
    // and get the "unprotected" result
    if (!src) {
        return nullptr;
    }

    src_value_nocv &argument = const_cast<src_value_nocv &>(*src);
    dest_value_nocv *result = smart_cast_helper<dest_value_nocv *, src_value_nocv, std::is_base_of_v<dest_value_nocv, src_value_nocv>>::cast(argument);
    // add cv-qualifiers from src_value to the result and attempt to return it;
    // this return statement will fail to compile if dest_type_cv_protected cannot be implicitly converted to dest_type,
    // meaning that such a conversion would lose some of src_value's cv-qualifiers
    return result;
}

template <typename dest_type, typename src_type>
inline typename std::enable_if_t<std::is_lvalue_reference_v<dest_type>, dest_type> smart_cast(src_type &&src) {
    typedef typename std::remove_reference_t<dest_type> dest_value;
    dest_value *result = smart_cast<dest_value *>(&src);
    assert(result);
    return *result;
}
