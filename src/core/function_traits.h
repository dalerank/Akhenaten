#pragma once

#include <type_traits>

#include "core/type_list.h"

template <typename T, typename Enable = void>
struct function_traits;

template <typename TReturn, typename... TArgs>
struct function_traits<TReturn(TArgs...), void>
{
public:
    using function_type  = TReturn(TArgs...);
    using return_type    = TReturn;
    using object_type    = void;
    using argument_types = type_list<TArgs...>;

    static constexpr bool   is_function        = true;
    static constexpr bool   is_member_function = false;
    static constexpr bool   is_functor         = false;
    static constexpr bool   is_const           = false;
    static constexpr bool   is_volatile        = false;
    static constexpr bool   is_noexcept        = false;
    static constexpr size_t arity              = sizeof...(TArgs);
    
    static constexpr size_t argument_count     = arity;
};

//***************************************************************************
// Free function pointer
//***************************************************************************
template <typename TReturn, typename... TArgs>
struct function_traits<TReturn(*)(TArgs...), void> : function_traits<TReturn(TArgs...)> {};

//***************************************************************************
// Free function reference
//***************************************************************************
template <typename TReturn, typename... TArgs>
struct function_traits<TReturn(&)(TArgs...), void> : function_traits<TReturn(TArgs...)> {};

//***************************************************************************
// Free noexcept function pointer
//***************************************************************************
template <typename TReturn, typename... TArgs>
struct function_traits<TReturn(*)(TArgs...) noexcept, void> : function_traits<TReturn(TArgs...)>
{
static constexpr bool is_noexcept = true;
};

//***************************************************************************
// Free noexcept function reference.
//***************************************************************************
template <typename TReturn, typename... TArgs>
struct function_traits<TReturn(&)(TArgs...) noexcept, void> : function_traits<TReturn(TArgs...)>
{
static constexpr bool is_noexcept = true;
};

//***************************************************************************
// Member function pointers
//***************************************************************************
template <typename TReturn, typename TObject, typename... TArgs>
struct function_traits<TReturn (TObject::*)(TArgs...), void> : function_traits<TReturn(TArgs...)>
{
using object_type = TObject;
static constexpr bool is_function        = false;
static constexpr bool is_member_function = true;
};

//***************************************************************************
// Const member function pointers
//***************************************************************************
template <typename TReturn, typename TObject, typename... TArgs>
struct function_traits<TReturn (TObject::*)(TArgs...) const, void> : function_traits<TReturn(TObject::*)(TArgs...)>
{
static constexpr bool is_const = true;
};

//***************************************************************************
// Volatile member function pointers
//***************************************************************************
template <typename TReturn, typename TObject, typename... TArgs>
struct function_traits<TReturn (TObject::*)(TArgs...) volatile, void> : function_traits<TReturn(TObject::*)(TArgs...)>
{
static constexpr bool is_volatile = true;
};

//***************************************************************************
// Const volatile member function pointers
//***************************************************************************
template <typename TReturn, typename TObject, typename... TArgs>
struct function_traits<TReturn (TObject::*)(TArgs...) const volatile, void> : function_traits<TReturn(TObject::*)(TArgs...)>
{
static constexpr bool is_const    = true;
static constexpr bool is_volatile = true;
};

//***************************************************************************
// Noexcept member function pointers
//***************************************************************************
template <typename TReturn, typename TObject, typename... TArgs>
struct function_traits<TReturn (TObject::*)(TArgs...) noexcept, void> : function_traits<TReturn(TObject::*)(TArgs...)>
{
static constexpr bool is_noexcept = true;
};

//***************************************************************************
// Const noexcept member function pointers
//***************************************************************************
template <typename TReturn, typename TObject, typename... TArgs>
struct function_traits<TReturn (TObject::*)(TArgs...) const noexcept, void> : function_traits<TReturn(TObject::*)(TArgs...) const>
{
static constexpr bool is_noexcept = true;
};

//***************************************************************************
// Volatile noexcept member function pointers
//***************************************************************************
template <typename TReturn, typename TObject, typename... TArgs>
struct function_traits<TReturn (TObject::*)(TArgs...) volatile noexcept, void> : function_traits<TReturn(TObject::*)(TArgs...) volatile>
{
static constexpr bool is_noexcept = true;
};

template <typename T> struct remove_cvref {
    typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

struct delegate_tag {};


//***************************************************************************
// Const volatile noexcept member function pointers
//***************************************************************************
template <typename TReturn, typename TObject, typename... TArgs>
struct function_traits<TReturn (TObject::*)(TArgs...) const volatile noexcept, void> : function_traits<TReturn(TObject::*)(TArgs...) const volatile>
{
static constexpr bool is_noexcept = true;
};

//***************************************************************************
// Forward cv/ref on the whole type to the unqualified type.
//***************************************************************************
template <typename T>
struct function_traits<T, std::enable_if_t<!std::is_same<T, remove_cvref_t<T>>::value &&
                                            !std::is_class<std::decay_t<T>>::value>> 
    : function_traits<remove_cvref_t<T>>
{
};

//***************************************************************************
// Functors / lambdas: enable only for class types that have a unique operator()
//***************************************************************************
namespace private_function_traits
{
//*********************************
// Helper to get pointer to call operator
//*********************************
template <typename U>
using call_operator_ptr_t = decltype(&U::operator());
}

template <typename T, std::enable_if_t<std::is_class<std::decay_t<T>>::value, int> = 0>
struct has_unique_call_operator {
    //*********************************
    // Test for presence of operator()
    //*********************************
    template <typename U>
    static auto test(int) -> decltype(&U::operator(), std::true_type());

    //*********************************
    // Fallback
    //*********************************
    template <typename>
    static auto test(...) -> std::false_type;

    //*********************************
    // <b>true</b> if operator() exists and is unique
    //*********************************
    static constexpr bool value = decltype(test<std::decay_t<T>>(0))::value;
};

template <typename T>
inline constexpr bool has_unique_call_operator_v = has_unique_call_operator<T>::value;

//***************************************************************************
/// Functors / lambdas specialisation
//***************************************************************************
template <typename T>
struct function_traits<T, std::enable_if_t<std::is_class<std::decay_t<T>>::value && has_unique_call_operator<T>::value>>
: function_traits<private_function_traits::call_operator_ptr_t<std::decay_t<T>> >
{
static constexpr bool is_functor = true;
};

//***************************************************************************
// Out-of-class definitions for the function_traits static members
//***************************************************************************
// free/function primary template
template <typename TReturn, typename... TArgs>
constexpr bool function_traits<TReturn(TArgs...), void>::is_function;

template <typename TReturn, typename... TArgs>
constexpr bool function_traits<TReturn(TArgs...), void>::is_member_function;
  
template <typename TReturn, typename... TArgs>
constexpr bool function_traits<TReturn(TArgs...), void>::is_functor;
  
template <typename TReturn, typename... TArgs>
constexpr bool function_traits<TReturn(TArgs...), void>::is_const;
  
template <typename TReturn, typename... TArgs>
constexpr bool function_traits<TReturn(TArgs...), void>::is_volatile;
  
template <typename TReturn, typename... TArgs>
constexpr bool function_traits<TReturn(TArgs...), void>::is_noexcept;
  
template <typename TReturn, typename... TArgs>
constexpr size_t function_traits<TReturn(TArgs...), void>::arity;

// member-function-pointer specialization
template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...), void>::is_function;

template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...), void>::is_member_function;

// cv/ref-qualified member-function pointer flags
template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...) const, void>::is_const;
  
template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...) volatile, void>::is_volatile;
  
template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...) const volatile, void>::is_const;
  
template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...) const volatile, void>::is_volatile;

template <typename TReturn, typename... TArgs>
constexpr bool function_traits<TReturn(*)(TArgs...) noexcept, void>::is_noexcept;

template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...) noexcept, void>::is_noexcept;

template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...) const noexcept, void>::is_noexcept;

template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...) volatile noexcept, void>::is_noexcept;

template <typename TReturn, typename TObject, typename... TArgs>
constexpr bool function_traits<TReturn (TObject::*)(TArgs...) const volatile noexcept, void>::is_noexcept;

//***************************************************************************
// Functor / lambda specialisation: provide out-of-class definition for is_functor
//***************************************************************************
template <typename T>
constexpr bool function_traits<T, std::enable_if_t<std::is_class<std::decay_t<T>>::value &&has_unique_call_operator<T>::value>>::is_functor;