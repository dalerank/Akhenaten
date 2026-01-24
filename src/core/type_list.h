#pragma once

#include <algorithm>
#include <limits>

#include "core/type_largest.h"

//***************************************************************************
/// Defines a no-position constant.
//***************************************************************************
static const size_t type_list_npos = std::numeric_limits<size_t>::max();

//***************************************************************************
/// Type list forward declaration.
//***************************************************************************
template <typename... TTypes>
struct type_list;

//***************************************************************************
/// The empty type list.
//***************************************************************************
template <>
struct type_list<> {
    static constexpr size_t size = 0U;
    using index_sequence_type = std::make_index_sequence<0>; ///< The index_sequence type for this type_list.
private:
    type_list() = delete;
    type_list(const type_list &) = delete;
    type_list &operator =(const type_list &) = delete;
};

namespace private_type_list {
    // helper to solve the issue that recursed-rest can't be put directly in type_list::tail definition
    template <typename... TTypes>
    struct recursion_helper {
        using type = type_list<TTypes...>;
    };
}

//***************************************************************************
/// Recursive type list implementation for multiple types.
//***************************************************************************
template <typename THead, typename... TTail>
struct type_list<THead, TTail...> : type_list<TTail...> {
    using head = THead;
    using tail = typename private_type_list::recursion_helper<TTail...>::type;
    static constexpr size_t size = sizeof...(TTail) + 1U;
    using index_sequence_type = std::make_index_sequence<sizeof...(TTail) + 1U>; ///< The index_sequence type for this type_list.
private:
    type_list() = delete;
    type_list(const type_list &) = delete;
    type_list &operator =(const type_list &) = delete;
};

//***************************************************************************
/// Type list implementation for one type.
//***************************************************************************
template <typename THead>
struct type_list<THead> : type_list<> {
    using head = THead;
    using tail = typename private_type_list::recursion_helper<>::type;

    static constexpr size_t size = 1U;

    using index_sequence_type = std::make_index_sequence<1>; ///< The index_sequence type for this type_list.

private:

    type_list() = delete;
    type_list(const type_list &) = delete;
    type_list &operator =(const type_list &) = delete;
};

//***************************************************************************
/// Type list size.
//***************************************************************************
template <typename TTypes>
struct type_list_size;

template <typename... TTypes>
struct type_list_size<type_list<TTypes...>> : public std::integral_constant<size_t, sizeof...(TTypes)> {};

template <typename... TTypes>
inline constexpr size_t type_list_size_v = type_list_size<std::type_list<TTypes...>>::value;

//***************************************************************************
/// Defines type as the type found at Index in the type_list.
/// Static asserts if Index is out of range.
//***************************************************************************
template <typename TTypeList, size_t Index>
struct type_list_type_at_index {
    static_assert(Index < type_list_size<TTypeList>::value, "std::type_list_type_at_index out of range");
    static_assert((std::is_base_of<type_list<>, TTypeList>::value), "TTypeList must be an std::type_list");

    using type = typename type_list_type_at_index<typename TTypeList::tail, Index - 1>::type;
};

template <typename TTypeList>
struct type_list_type_at_index<TTypeList, 0> {
    using type = typename TTypeList::head;
};

template <typename TTypeList, size_t Index>
using type_list_type_at_index_t = typename type_list_type_at_index<TTypeList, Index>::type;

//***************************************************************************
/// Defines an integral constant that is the index of the specified type in the type_list.
/// If the type is not in the type_list, then defined as std::type_list_npos.
//***************************************************************************
template <typename TTypeList, typename T>
struct type_list_index_of_type
    : public std::integral_constant<size_t, std::is_same<typename TTypeList::head, T>::value ? 0 :
    (type_list_index_of_type<typename TTypeList::tail, T>::value == type_list_npos ? type_list_npos :
    type_list_index_of_type<typename TTypeList::tail, T>::value + 1)> {
    static_assert((std::is_base_of<type_list<>, TTypeList>::value), "TTypeList must be an std::type_list");
};

template <typename T>
struct type_list_index_of_type<type_list<>, T>
    : public std::integral_constant<size_t, type_list_npos> {};

template <typename TTypeList, typename T>
inline constexpr size_t type_list_index_of_v = type_list_index_of_type<TTypeList, T>::value;

namespace private_type_traits {
    //***************************************************************************
    // Helper to count occurrences of a type in a list of types
    template<typename T, typename... TTypes>
    struct count_type;

    // Base case: zero occurrences
    template<typename T>
    struct count_type<T> : std::integral_constant<size_t, 0> {};

    // Recursive case: increment count if head is the same as T, otherwise continue with tail
    template<typename T, typename THead, typename... TTail>
    struct count_type<T, THead, TTail...> : std::integral_constant<size_t, (std::is_same<T, THead>::value ? 1 : 0) + count_type<T, TTail...>::value> {};
}

template<typename T, typename... TTypes>
struct type_has_duplicates_of
    : std::integral_constant<bool, (private_type_traits::count_type<T, TTypes...>::value > 1)>
{
};

template <typename T, typename... TRest>
inline constexpr bool type_has_duplicates_of_v = type_has_duplicates_of<T, TRest...>::value;

//***************************************************************************
/// Defines a bool constant that is true if the type_list has duplicates of the specified type, otherwise false.
//***************************************************************************
template <typename TTypeList, typename T>
struct type_list_has_duplicates_of;

template <typename T, typename... TTypes>
struct type_list_has_duplicates_of<type_list<TTypes...>, T>
    : public type_has_duplicates_of<T, TTypes...> {};

template <typename T>
struct type_list_has_duplicates_of<type_list<>, T>
    : public std::integral_constant<bool, false> {};

template <typename TTypeList, typename T>
inline constexpr bool type_list_has_duplicates_of_v = type_list_has_duplicates_of<TTypeList, T>::value;

//***************************************************************************
/// Defines an integral constant that is maximum sizeof all types in the type_list.
/// If the type_list is empty, then defined as 0.
//***************************************************************************
template <typename T>
struct type_list_max_size;

template <typename... TTypes>
struct type_list_max_size<type_list<TTypes...>>
    : public std::integral_constant<size_t, type_largest<TTypes...>::size> {};

template <>
struct type_list_max_size<type_list<>>
    : public std::integral_constant<size_t, 0> {};

template <typename TTypeList>
inline constexpr size_t type_list_max_size_v = type_list_max_size<TTypeList>::value;

//***************************************************************************
/// Defines an integral constant that is maximum alignment all types in the type_list.
/// If the type_list is empty, then defined as 1.
//***************************************************************************
template <typename T>
struct type_list_max_alignment;

template <typename... TTypes>
struct type_list_max_alignment<type_list<TTypes...>>
    : public std::integral_constant<size_t, type_largest<TTypes...>::alignment> {};

template <>
struct type_list_max_alignment<type_list<>>
    : public std::integral_constant<size_t, 1> {};

template <typename TTypeList>
inline constexpr size_t type_list_max_alignment_v = type_list_max_alignment<TTypeList>::value;

//***************************************************************************
/// Declares a new type_list by selecting types from a given type_list, according to an index sequence.
//***************************************************************************
template <typename TTypeList, size_t... Indices>
struct type_list_select {
    static_assert((std::is_base_of<type_list<>, TTypeList>::value), "TTypeList must be an std::type_list");

    using type = type_list<type_list_type_at_index_t<TTypeList, Indices>...>;
};

template <typename TTypeList, size_t... Indices>
using type_list_select_t = typename type_list_select<TTypeList, Indices...>::type;

//***************************************************************************
/// Concatenates two or more type_lists.
//***************************************************************************
template <typename... TTypes>
struct type_list_cat;

template <typename... TTypes1, typename... TTypes2, typename... TTail>
struct type_list_cat<type_list<TTypes1...>, type_list<TTypes2...>, TTail...> {
    using type = typename type_list_cat<type_list<TTypes1..., TTypes2...>, TTail...>::type;
};

template <typename T>
struct type_list_cat<T> {
    using type = T;
};

template <typename... TypeLists>
using type_list_cat_t = typename type_list_cat<TypeLists...>::type;

//***************************************************************************
/// Checks that two type lists are convertible.
/// Static asserts if the type lists are not the same length.
//***************************************************************************
// Primary template
template <typename TFromList, typename TToList>
struct type_lists_are_convertible;

// Specialization: both lists empty, convertible
template <>
struct type_lists_are_convertible<type_list<>, type_list<>>
    : public std::true_type {};

// Recursive case: check head types, then recurse
template <typename TFromHead, typename... TFromTail, typename TToHead, typename... TToTail>
struct type_lists_are_convertible<type_list<TFromHead, TFromTail...>, type_list<TToHead, TToTail...>>
    : public std::bool_constant<std::is_convertible<TFromHead, TToHead>::value &&
    type_lists_are_convertible<type_list<TFromTail...>, type_list<TToTail...>>::value> {
    static_assert(sizeof...(TFromTail) == sizeof...(TToTail), "Type lists are not the same length");
};

template <typename TFromList, typename TToList>
inline constexpr bool type_lists_are_convertible_v = type_lists_are_convertible<TFromList, TToList>::value;

template <typename...>
struct type_disjunction : public std::false_type {};

template <typename T1, typename... Tn>
struct type_disjunction<T1, Tn...> : public std::conditional_t<bool(T1::value), T1, type_disjunction<Tn...>> {};

template <typename T1> struct type_disjunction<T1> : public T1 {};

template <typename... T>
inline constexpr bool type_disjunction_v = type_disjunction<T...>::value;

//***************************************************************************
/// Template to determine if a type is a base of all types in a specified list.
///\ingroup types
template <typename T, typename... TRest>
struct type_is_one_of : type_disjunction<std::is_same<T, TRest>...> {};

template <typename T, typename... TRest>
inline constexpr bool type_is_one_of_v = type_is_one_of<T, TRest...>::value;

//*********************************************
// count_of
template <typename T, typename... TTypes>
struct type_count_of;

template <typename T, typename U, typename... URest>
struct type_count_of<T, U, URest...> : std::integral_constant<size_t, std::is_same<T, U>::value + type_count_of<T, URest...>::value> {};

template <typename T>
struct type_count_of<T> : std::integral_constant<size_t, 0> {};

template <typename T, typename... TTypes>
inline constexpr size_t type_count_of_v = type_count_of<T, TTypes...>::value;

//***************************************************************************
/// Defines a bool constant that is true if the type_list contains the specified type, otherwise false.
//***************************************************************************
template <typename TTypeList, typename T>
struct type_list_contains;

template <typename T, typename... TTypes>
struct type_list_contains<type_list<TTypes...>, T>
    : public std::integral_constant<bool, type_is_one_of<T, TTypes...>::value> {};

template <typename T>
struct type_list_contains<type_list<>, T>
    : public std::integral_constant<bool, false> {};

template <typename TTypeList, typename T>
inline constexpr bool type_list_contains_v = type_list_contains<TTypeList, T>::value;

//***************************************************************************
/// Defines an integral constant that is the count of the number of times a type is in the type list.
//***************************************************************************
template <typename TTypeList, typename T>
struct type_list_count_of;

template <typename T, typename... TTypes>
struct type_list_count_of<type_list<TTypes...>, T>
    : public type_count_of<T, TTypes...> {};

template <typename T>
struct type_list_count_of<type_list<>, T>
    : public std::integral_constant<size_t, 0> {};

template <typename TTypeList, typename T>
inline constexpr size_t type_list_count_of_v = type_list_count_of<TTypeList, T>::value;