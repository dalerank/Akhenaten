#pragma once

#include "core/type_smallest.h"

//***************************************************************************
// Specialisation for one template parameter.
//***************************************************************************
template <typename T1>
class largest_type<T1> {
public:
    using type = T1;
    enum {
        size = type_size_of<type>::value
    };
};

template <typename... T>
using largest_type_t = typename largest_type<T...>::type;

template <typename... T>
constexpr size_t largest_type_v = largest_type<T...>::size;
template <typename T1, typename... TRest>
struct type_largest_alignment {
    // Define 'largest_other' as 'largest_type' with all but the first parameter.
    using largest_other = typename type_largest_alignment<TRest...>::type;

    // Set 'type' to be the largest of the first parameter and any of the others.
    // This is recursive.
    using type = typename std::conditional<(std::alignment_of<T1>::value > std::alignment_of<largest_other>::value), // Boolean
        T1,                                                                      // TrueType
        largest_other>                                                           // FalseType
        ::type;                                                                  // The largest type of the two.

    // The largest alignment.
    enum {
        value = std::alignment_of<type>::value
    };
};

//***************************************************************************
// Specialisation for one template parameter.
//***************************************************************************
template <typename T1>
struct type_largest_alignment<T1> {
    typedef T1 type;

    enum {
        value = std::alignment_of<type>::value
    };
};

template <typename... T>
inline constexpr size_t type_largest_alignment_v = type_largest_alignment<T...>::value;

//***************************************************************************
/// Defines a type that is as larger or larger than the specified type.
/// Will return the specified type is there is not a larger type.
///\\ingroup largest
//***************************************************************************
template <typename T>
struct larger_int_type {
    static_assert(std::is_integral<T>::value, "Must be an integral type");

    typedef typename smallest_int_for_bits<std::numeric_limits<typename std::make_signed<T>::type>::bits + 1>::type type;
};

template <typename T>
using larger_int_type_t = typename larger_int_type<T>::type;

//***************************************************************************
/// Defines a type that is as larger or larger than the specified type.
/// Will return the specified type is there is not a larger type.
///\ingroup largest
//***************************************************************************
template <typename T>
struct larger_uint_type {
    static_assert(std::is_integral<T>::value, "Must be an integral type");

    typedef typename smallest_uint_for_bits<std::numeric_limits<typename std::make_unsigned<T>::type>::bits + 1>::type type;
};

template <typename T>
using larger_uint_type_t = typename larger_uint_type<T>::type;

//***************************************************************************
/// Defines a type that is as larger or larger than the specified type.
/// Will return the specified type is there is not a larger type.
/// The returned type will be of the same sign.
///\ingroup largest
//***************************************************************************
template <typename T, bool IS_SIGNED = std::is_signed<T>::value>
struct larger_type;

template <typename T>
struct larger_type<T, false> {
    static_assert(std::is_integral<T>::value, "Must be an integral type");

    typedef typename smallest_uint_for_bits<std::numeric_limits<T>::bits + 1>::type type;
};

template <typename T>
struct larger_type<T, true> {
    static_assert(std::is_integral<T>::value, "Must be an integral type");

    typedef typename smallest_int_for_bits<std::numeric_limits<T>::bits + 1>::type type;
};

template <typename T>
using larger_type_t = typename larger_type<T>::type;

//***************************************************************************
/// Template to determine the largest type, size and alignment.
/// Defines <b>value</b> which is the largest type, size and alignment of all the parameters.
///\ingroup largest
//***************************************************************************
template <typename... T>
struct type_largest {
    using type = typename largest_type<T...>::type;

    enum {
        size = largest_type<T...>::size,
        alignment = type_largest_alignment<T...>::value
    };
};

template <typename... T>
using type_largest_t = typename type_largest<T...>::type;

template <typename... T>
inline constexpr size_t type_largest_size = type_largest<T...>::size;

