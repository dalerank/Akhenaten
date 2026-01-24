#pragma once

#include <limits>

//***************************************************************************
/// size_of
///\ingroup types
template <typename T> struct type_size_of : std::integral_constant<size_t, sizeof(T)> {};
template <> struct type_size_of<void> : std::integral_constant<size_t, 1U> {};

template <typename T>
inline constexpr size_t type_size_of_v = etl::size_of<T>::value;

template <typename T1, typename... TRest>
class largest_type {
private:

    // Define 'largest_other' as 'largest_type' with all but the first parameter.
    using largest_other = typename largest_type<TRest...>::type;

public:

    // Set 'type' to be the largest of the first parameter and any of the others.
    // This is recursive.
    using type = typename std::conditional<(type_size_of<T1>::value > type_size_of<largest_other>::value),  // Boolean
        T1,                                                             // TrueType
        largest_other>                                                  // FalseType
        ::type;                                                         // The largest type of the two.

    // The size of the largest type.
    enum {
        size = type_size_of<type>::value
    };
};

//***************************************************************************
/// Template to determine the largest type and size.
/// Defines 'value_type' which is the type of the largest parameter.
/// Defines 'size' which is the size of the largest parameter.
///\ingroup largest
//***************************************************************************
template <typename T1, typename... TRest>
class smallest_type {
private:

    // Define 'smallest_other' as 'smallest_type' with all but the first parameter.
    using smallest_other = typename smallest_type<TRest...>::type;

public:

    // Set 'type' to be the smallest of the first parameter and any of the others.
    // This is recursive.
    using type = typename std::conditional<(type_size_of<T1>::value < type_size_of<smallest_other>::value), // Boolean
        T1,                                                             // TrueType
        smallest_other>                                                 // FalseType
        ::type;                                                         // The smallest type of the two.

    // The size of the smallest type.
    enum {
        size = type_size_of<type>::value
    };
};

//***************************************************************************
// Specialisation for one template parameter.
//***************************************************************************
template <typename T1>
class smallest_type<T1> {
public:

    using type = T1;

    enum {
        size = type_size_of<type>::value
    };
};

template <typename... T>
using smallest_type_t = typename smallest_type<T...>::type;

template <typename... T>
constexpr size_t smallest_type_v = smallest_type<T...>::size;

namespace private_smallest {
    //*************************************************************************
    // Determine the type to hold the number of bits based on the index.
    //*************************************************************************
    template <int index>
    struct best_fit_uint_type;

    //*************************************************************************
    // Less than or equal to 8 bits.
    //*************************************************************************
    template <>
    struct best_fit_uint_type<0> {
        typedef uint_least8_t type;
    };

    //*************************************************************************
    // 9 to 16 bits.
    //*************************************************************************
    template <>
    struct best_fit_uint_type<1> {
        typedef uint_least16_t type;
    };

    //*************************************************************************
    // 17 to 31 bits.
    //*************************************************************************
    template <>
    struct best_fit_uint_type<2> {
        typedef uint_least32_t type;
    };

    //*************************************************************************
    // Greater than 32 bits.
    //*************************************************************************
    template <>
    struct best_fit_uint_type<3> {
        typedef uint_least64_t type;
    };

    //*************************************************************************
    // Determine the type to hold the number of bits based on the index.
    //*************************************************************************
    template <int index>
    struct best_fit_int_type;

    //*************************************************************************
    // Less than or equal to 8 bits.
    //*************************************************************************
    template <>
    struct best_fit_int_type<0> {
        typedef int_least8_t type;
    };

    //*************************************************************************
    // 9 to 16 bits.
    //*************************************************************************
    template <>
    struct best_fit_int_type<1> {
        typedef int_least16_t type;
    };

    //*************************************************************************
    // 17 to 31 bits.
    //*************************************************************************
    template <>
    struct best_fit_int_type<2> {
        typedef int_least32_t type;
    };

    //*************************************************************************
    // Greater than 32 bits.
    //*************************************************************************
    template <>
    struct best_fit_int_type<3> {
        typedef int_least64_t type;
    };
}

//***************************************************************************
/// Template to determine the smallest unsigned int type that can contain a
/// value with the specified number of bits.
/// Defines 'type' which is the type of the smallest unsigned integer.
///\ingroup smallest
//***************************************************************************
template <size_t NBITS>
struct smallest_uint_for_bits {
private:

    // Determines the index of the best unsigned type for the required number of bits.
    static const int TYPE_INDEX = ((NBITS > 8) ? 1 : 0) +
        ((NBITS > 16) ? 1 : 0) +
        ((NBITS > 32) ? 1 : 0);

public:

    typedef typename private_smallest::best_fit_uint_type<TYPE_INDEX>::type type;
};

template <size_t NBITS>
const int smallest_uint_for_bits<NBITS>::TYPE_INDEX;

template <size_t NBITS>
using smallest_uint_for_bits_t = typename smallest_uint_for_bits<NBITS>::type;

//***************************************************************************
/// Template to determine the smallest signed int type that can contain a
/// value with the specified number of bits.
/// Defines 'type' which is the type of the smallest signed integer.
///\ingroup smallest
//***************************************************************************
template <size_t NBITS>
struct smallest_int_for_bits {
private:

    // Determines the index of the best unsigned type for the required number of bits.
    static const int TYPE_INDEX = ((NBITS > 8) ? 1 : 0) +
        ((NBITS > 16) ? 1 : 0) +
        ((NBITS > 32) ? 1 : 0);

public:

    typedef typename private_smallest::best_fit_int_type<TYPE_INDEX>::type type;
};

template <size_t NBITS>
const int smallest_int_for_bits<NBITS>::TYPE_INDEX;

template <size_t NBITS>
using smallest_int_for_bits_t = typename smallest_int_for_bits<NBITS>::type;

//***************************************************************************
/// Template to determine the smallest unsigned int type that can contain the
/// specified unsigned value.
/// Defines 'type' which is the type of the smallest unsigned integer.
///\ingroup smallest
//***************************************************************************
template <uintmax_t VALUE>
struct smallest_uint_for_value {
private:

    // Determines the index of the best unsigned type for the required value.
    static const int TYPE_INDEX = ((VALUE > UINT_LEAST8_MAX) ? 1 : 0) +
        ((VALUE > UINT16_MAX) ? 1 : 0) +
        ((VALUE > UINT32_MAX) ? 1 : 0);

public:

    typedef typename private_smallest::best_fit_uint_type<TYPE_INDEX>::type type;
};

template <uintmax_t VALUE>
const int smallest_uint_for_value<VALUE>::TYPE_INDEX;

template <uintmax_t VALUE>
using smallest_uint_for_value_t = typename smallest_uint_for_value<VALUE>::type;

//***************************************************************************
/// Template to determine the smallest int type that can contain the
/// specified signed value.
/// Defines 'type' which is the type of the smallest signed integer.
///\ingroup smallest
//***************************************************************************
template <intmax_t VALUE>
struct smallest_int_for_value {
private:

    // Determines the index of the best signed type for the required value.
    static const int TYPE_INDEX = (((VALUE > intmax_t(INT_LEAST8_MAX)) || (VALUE < intmax_t(INT_LEAST8_MIN))) ? 1 : 0) +
        (((VALUE > intmax_t(INT16_MAX)) || (VALUE < intmax_t(INT16_MIN))) ? 1 : 0) +
        (((VALUE > intmax_t(INT32_MAX)) || (VALUE < intmax_t(INT32_MIN))) ? 1 : 0);

public:

    typedef typename private_smallest::best_fit_int_type<TYPE_INDEX>::type type;
};

template <intmax_t VALUE>
const int smallest_int_for_value<VALUE>::TYPE_INDEX;

template <intmax_t VALUE>
using smallest_int_for_value_t = typename smallest_int_for_value<VALUE>::type;
