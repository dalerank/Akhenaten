/******************************************************************************
Based on original work by Sergey Ryazanov:
"The Impossibly Fast C++ Delegates", 18 Jul 2005
https://www.codeproject.com/articles/11015/the-impossibly-fast-c-delegates

MIT license:
http://en.wikipedia.org/wiki/MIT_License

Original publication: https://www.codeproject.com/Articles/1170503/The-Impossibly-Fast-Cplusplus-Delegates-Fixed
******************************************************************************/

#pragma once

#include <optional>
#include "core/function_traits.h"

template <typename T>
struct is_delegate : std::bool_constant<std::is_base_of<delegate_tag, T>::value> {};

template <typename T>
inline constexpr bool is_delegate_v = is_delegate<T>::value;

template <typename T>
class delegate;

template <typename TReturn, typename... TArgs>
class delegate<TReturn(TArgs...)> final : public delegate_tag {
public:

    using return_type = TReturn;
    using argument_types = type_list<TArgs...>;

    //*************************************************************************
    /// Default constructor.
    //*************************************************************************
    constexpr delegate() noexcept {
    }

    constexpr delegate(const delegate &other) = default;

    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !is_delegate<TLambda>::value, void>>
    constexpr delegate(TLambda &instance) noexcept {
        assign((void *)(&instance), lambda_stub<TLambda>);
    }

    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !is_delegate<TLambda>::value, void>>
    constexpr delegate(const TLambda &instance) noexcept {
        assign((void *)(&instance), const_lambda_stub<TLambda>);
    }

    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !std::is_same<delegate<TReturn(TArgs...)>, TLambda>::value, void>>
    constexpr  delegate(TLambda &&instance) = delete;

    //*************************************************************************
    /// Create from function (Compile time).
    //*************************************************************************
    template <TReturn(*Method)(TArgs...)>
    [[nodiscard]]
    static constexpr delegate create() noexcept {
        return delegate(nullptr, function_stub<Method>);
    }

    //*************************************************************************
    /// Create from Lambda or Functor.
    //*************************************************************************
    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !is_delegate<TLambda>::value, void>>
    [[nodiscard]]
    static constexpr delegate create(TLambda &instance) noexcept {
        return delegate((void *)(&instance), lambda_stub<TLambda>);
    }

    //*************************************************************************
    /// Create from const Lambda or Functor.
    //*************************************************************************
    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !is_delegate<TLambda>::value, void>>
    [[nodiscard]]
    static constexpr delegate create(const TLambda &instance) noexcept {
        return delegate((void *)(&instance), const_lambda_stub<TLambda>);
    }

    //*************************************************************************
    /// Create from instance method (Run time).
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...)>
    [[nodiscard]]
    static constexpr  delegate create(T &instance) noexcept {
        return delegate((void *)(&instance), method_stub<T, Method>);
    }

    //*************************************************************************
    /// Create from instance method (Run time).
    /// Deleted for rvalue references.
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...)>
    [[nodiscard]]
    static constexpr  delegate create(T &&instance) = delete;

    //*************************************************************************
    /// Create from const instance method (Run time).
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...) const>
    [[nodiscard]]
    static constexpr  delegate create(const T &instance) noexcept {
        return delegate((void *)(&instance), const_method_stub<T, Method>);
    }

    //*************************************************************************
    /// Disable create from rvalue instance method (Run time).
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...) const>
    static constexpr  delegate create(T &&instance) = delete;

    //*************************************************************************
    /// Create from instance method (Compile time).
    //*************************************************************************
    template <typename T, T &Instance, TReturn(T:: *Method)(TArgs...)>
    [[nodiscard]]
    static constexpr  delegate create() noexcept {
        return delegate(method_instance_stub<T, Method, Instance>);
    }

    //*************************************************************************
    /// Create from instance method (Compile time).
    /// New API
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...), T &Instance>
    [[nodiscard]]
    static constexpr  delegate create() noexcept {
        return delegate(method_instance_stub<T, Method, Instance>);
    }

    //*************************************************************************
    /// Create from const instance method (Compile time).
    //*************************************************************************
    template <typename T, T const &Instance, TReturn(T:: *Method)(TArgs...) const>
    [[nodiscard]]
    static constexpr  delegate create() noexcept {
        return delegate(const_method_instance_stub<T, Method, Instance>);
    }

    //*************************************************************************
    /// Create from const instance method (Compile time).
    /// New API
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...) const, T const &Instance>
    [[nodiscard]]
    static constexpr  delegate create() noexcept {
        return delegate(const_method_instance_stub<T, Method, Instance>);
    }

    //*************************************************************************
    /// Set from function (Compile time).
    //*************************************************************************
    template <TReturn(*Method)(TArgs...)>
    constexpr  void set() noexcept {
        assign(nullptr, function_stub<Method>);
    }

    //*************************************************************************
    /// Set from Lambda or Functor.
    //*************************************************************************
    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !is_delegate<TLambda>::value, void>>
    constexpr  void set(TLambda &instance) noexcept {
        assign((void *)(&instance), lambda_stub<TLambda>);
    }

    //*************************************************************************
    /// Set from const Lambda or Functor.
    //*************************************************************************
    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !is_delegate<TLambda>::value, void>>
    constexpr  void set(const TLambda &instance) noexcept {
        assign((void *)(&instance), const_lambda_stub<TLambda>);
    }

    //*************************************************************************
    /// Set from instance method (Run time).
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...)>
    constexpr  void set(T &instance) noexcept {
        assign((void *)(&instance), method_stub<T, Method>);
    }

    //*************************************************************************
    /// Set from const instance method (Run time).
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...) const>
    constexpr  void set(T &instance) noexcept {
        assign((void *)(&instance), const_method_stub<T, Method>);
    }

    //*************************************************************************
    /// Set from instance method (Compile time).
    //*************************************************************************
    template <typename T, T &Instance, TReturn(T:: *Method)(TArgs...)>
    constexpr  void set() noexcept {
        assign(nullptr, method_instance_stub<T, Method, Instance>);
    }

    //*************************************************************************
    /// Set from instance method (Compile time).
    /// New API
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...), T &Instance>
    constexpr  void set() noexcept {
        assign(nullptr, method_instance_stub<T, Method, Instance>);
    }

    //*************************************************************************
    /// Set from const instance method (Compile time).
    //*************************************************************************
    template <typename T, T const &Instance, TReturn(T:: *Method)(TArgs...) const>
    constexpr  void set() noexcept {
        assign(nullptr, const_method_instance_stub<T, Method, Instance>);
    }

    //*************************************************************************
    /// Set from const instance method (Compile time).
    /// New API
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...) const, T const &Instance>
    constexpr  void set() noexcept {
        assign(nullptr, const_method_instance_stub<T, Method, Instance>);
    }

    //*************************************************************************
    /// Clear the delegate.
    //*************************************************************************
    constexpr  void clear() noexcept {
        invocation.clear();
    }

    //*************************************************************************
    /// Execute the delegate.
    //*************************************************************************
    template <typename... TCallArgs>
    constexpr
        return_type operator()(TCallArgs&&... args) const {
        static_assert((sizeof...(TCallArgs) == sizeof...(TArgs)), "Incorrect number of parameters passed to delegate");
        static_assert((type_lists_are_convertible<type_list<TCallArgs&&...>, argument_types>::value), "Incompatible parameter types passed to delegate");

        assert(is_valid() && "delegate_uninitialised");

        return (*invocation.stub)(invocation.object, std::forward<TCallArgs>(args)...);
    }

    //*************************************************************************
    /// Execute the delegate if valid.
    /// 'void' return delegate.
    //*************************************************************************
    template <typename TRet = TReturn, typename... TCallArgs>
    constexpr
        typename std::enable_if_t<std::is_same<TRet, void>::value, bool>
        call_if(TCallArgs&&... args) const {
        static_assert((sizeof...(TCallArgs) == sizeof...(TArgs)), "Incorrect number of parameters passed to delegate");
        static_assert((type_lists_are_convertible<type_list<TCallArgs&&...>, argument_types>::value), "Incompatible parameter types passed to delegate");

        if (is_valid()) {
            (*invocation.stub)(invocation.object, std::forward<TCallArgs>(args)...);
            return true;
        } else {
            return false;
        }
    }

    //*************************************************************************
    /// Execute the delegate if valid.
    /// Non 'void' return delegate.
    //*************************************************************************
    template <typename TRet = TReturn, typename... TCallArgs>
    constexpr
        typename std::enable_if_t<!std::is_same<TRet, void>::value, std::optional<TReturn>>
        call_if(TCallArgs&&... args) const {
        static_assert((sizeof...(TCallArgs) == sizeof...(TArgs)), "Incorrect number of parameters passed to delegate");
        static_assert((type_lists_are_convertible<type_list<TCallArgs&&...>, argument_types>::value), "Incompatible parameter types passed to delegate");

        std::optional<TReturn> result;

        if (is_valid()) {
            result = (*invocation.stub)(invocation.object, std::forward<TCallArgs>(args)...);
        }

        return result;
    }

    //*************************************************************************
    /// Execute the delegate if valid or call alternative.
    /// Run time alternative.
    //*************************************************************************
    template <typename TAlternative, typename... TCallArgs>
    constexpr  TReturn call_or(TAlternative &&alternative, TCallArgs&&... args) const {
        static_assert((sizeof...(TCallArgs) == sizeof...(TArgs)), "Incorrect number of parameters passed to delegate");
        static_assert((type_lists_are_convertible<type_list<TCallArgs&&...>, argument_types>::value), "Incompatible parameter types passed to delegate");

        if (is_valid()) {
            return (*invocation.stub)(invocation.object, std::forward<TCallArgs>(args)...);
        } else {
            return std::forward<TAlternative>(alternative)(std::forward<TCallArgs>(args)...);
        }
    }

    //*************************************************************************
    /// Execute the delegate if valid or call alternative.
    /// Compile time alternative.
    //*************************************************************************
    template <TReturn(*Method)(TArgs...), typename... TCallArgs>
    constexpr  TReturn call_or(TCallArgs&&... args) const {
        static_assert((sizeof...(TCallArgs) == sizeof...(TArgs)), "Incorrect number of parameters passed to delegate");
        static_assert((type_lists_are_convertible<type_list<TCallArgs&&...>, argument_types>::value), "Incompatible parameter types passed to delegate");

        if (is_valid()) {
            return (*invocation.stub)(invocation.object, std::forward<TCallArgs>(args)...);
        } else {
            return (Method)(std::forward<TCallArgs>(args)...);
        }
    }

    //*************************************************************************
    /// Assignment
    //*************************************************************************
    delegate &operator =(const delegate &rhs) = default;

    //*************************************************************************
    /// Create from Lambda or Functor.
    //*************************************************************************
    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !is_delegate<TLambda>::value, void>>
    constexpr  delegate &operator =(TLambda &instance) noexcept {
        assign((void *)(&instance), lambda_stub<TLambda>);
        return *this;
    }

    //*************************************************************************
    /// Create from const Lambda or Functor.
    //*************************************************************************
    template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value && !is_delegate<TLambda>::value, void>>
    constexpr  delegate &operator =(const TLambda &instance) noexcept {
        assign((void *)(&instance), const_lambda_stub<TLambda>);
        return *this;
    }

    //*************************************************************************
    /// Checks equality.
    //*************************************************************************
    [[nodiscard]]
    constexpr  bool operator == (const delegate &rhs) const noexcept {
        return invocation == rhs.invocation;
    }

    //*************************************************************************
    /// Returns <b>true</b> if the delegate is valid.
    //*************************************************************************
    constexpr  bool operator != (const delegate &rhs) const noexcept {
        return invocation != rhs.invocation;
    }

    //*************************************************************************
    /// Returns <b>true</b> if the delegate is valid.
    //*************************************************************************
    [[nodiscard]]
    constexpr  bool is_valid() const noexcept {
        return invocation.stub != nullptr;
    }

    //*************************************************************************
    /// Returns <b>true</b> if the delegate is valid.
    //*************************************************************************
    [[nodiscard]]
    constexpr  operator bool() const noexcept {
        return is_valid();
    }

private:

    using stub_type = TReturn(*)(void *object, TArgs...);

    //*************************************************************************
    // Callable compatibility: detects if C (or const C) is invocable with (TArgs...) and returns a type
    // convertible to TReturn. Works with generic lambdas and functors.
    template <typename TCallableType, typename = void>
    struct is_invocable_with
        : std::false_type {};

    template <typename TCallableType>
    struct is_invocable_with<TCallableType, std::void_t<decltype(std::declval<TCallableType &>()(std::declval<TArgs>()...))>>
        : std::bool_constant<std::is_convertible<decltype(std::declval<TCallableType &>()(std::declval<TArgs>()...)), TReturn>::value> {};

    template <typename TCallableType, typename = void>
    struct is_invocable_with_const : std::false_type {};

    template <typename TCallableType>
    struct is_invocable_with_const<TCallableType, std::void_t<decltype(std::declval<const TCallableType &>()(std::declval<TArgs>()...))>>
        : std::bool_constant<std::is_convertible<decltype(std::declval<const TCallableType &>()(std::declval<TArgs>()...)), TReturn>::value> {};

    template <typename TCallableType>
    struct is_compatible_callable
        : std::bool_constant<is_invocable_with<TCallableType>::value || is_invocable_with_const<TCallableType>::value> {};

    //*************************************************************************
    /// The internal invocation object.
    //*************************************************************************
    struct invocation_element {
        invocation_element() = default;

        //***********************************************************************
        constexpr  invocation_element(void *object_, stub_type stub_) noexcept
            : object(object_)
            , stub(stub_) {
        }

        //***********************************************************************
        constexpr  bool operator ==(const invocation_element &rhs) const noexcept {
            return (rhs.stub == stub) && (rhs.object == object);
        }

        //***********************************************************************
        constexpr  bool operator !=(const invocation_element &rhs) const noexcept {
            return (rhs.stub != stub) || (rhs.object != object);
        }

        //***********************************************************************
        constexpr  void clear() noexcept {
            object = nullptr;
            stub = nullptr;
        }

        //***********************************************************************
        void *object = nullptr;
        stub_type stub = nullptr;
    };

    //*************************************************************************
    /// Constructs a delegate from an object and stub.
    //*************************************************************************
    constexpr  delegate(void *object, stub_type stub) noexcept
        : invocation(object, stub) {
    }

    //*************************************************************************
    /// Constructs a delegate from a stub.
    //*************************************************************************
    constexpr  delegate(stub_type stub) noexcept
        : invocation(nullptr, stub) {
    }

    //*************************************************************************
    /// Assign from an object and stub.
    //*************************************************************************
    constexpr  void assign(void *object, stub_type stub) noexcept {
        invocation.object = object;
        invocation.stub = stub;
    }

    //*************************************************************************
    /// Stub call for a member function. Run time instance.
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...)>
    static constexpr  TReturn method_stub(void *object, TArgs... args) {
        T *p = static_cast<T *>(object);
        return (p->*Method)(std::forward<TArgs>(args)...);
    }

    //*************************************************************************
    /// Stub call for a const member function. Run time instance.
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...) const>
    static constexpr  TReturn const_method_stub(void *object, TArgs... args) {
        T *const p = static_cast<T *>(object);
        return (p->*Method)(std::forward<TArgs>(args)...);
    }

    //*************************************************************************
    /// Stub call for a member function. Compile time instance.
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...), T &Instance>
    static constexpr  TReturn method_instance_stub(void *, TArgs... args) {
        return (Instance.*Method)(std::forward<TArgs>(args)...);
    }

    //*************************************************************************
    /// Stub call for a const member function. Compile time instance.
    //*************************************************************************
    template <typename T, TReturn(T:: *Method)(TArgs...) const, const T &Instance>
    static constexpr  TReturn const_method_instance_stub(void *, TArgs... args) {
        return (Instance.*Method)(std::forward<TArgs>(args)...);
    }

#if !(defined(ETL_COMPILER_GCC) && (__GNUC__ <= 8))
    //*************************************************************************
    /// Stub call for a function operator. Compile time instance.
    //*************************************************************************
    template <typename T, T &Instance>
    static constexpr  TReturn operator_instance_stub(void *, TArgs... args) {
        return Instance.operator()(std::forward<TArgs>(args)...);
    }
#endif

    //*************************************************************************
    /// Stub call for a free function.
    //*************************************************************************
    template <TReturn(*Method)(TArgs...)>
    static constexpr  TReturn function_stub(void *, TArgs... args) {
        return (Method)(std::forward<TArgs>(args)...);
    }

    //*************************************************************************
    /// Stub call for a lambda or functor function.
    //*************************************************************************
    template <typename TLambda>
    static constexpr  TReturn lambda_stub(void *object, TArgs... arg) {
        static_assert(is_compatible_callable<TLambda>::value, "std::delegate: bound lambda/functor is not compatible with the delegate signature");

        TLambda *p = static_cast<TLambda *>(object);
        return (p->operator())(std::forward<TArgs>(arg)...);
    }

    //*************************************************************************
    /// Stub call for a const lambda or functor function.
    //*************************************************************************
    template <typename TLambda>
    static constexpr  TReturn const_lambda_stub(void *object, TArgs... arg) {
        static_assert(is_compatible_callable<TLambda>::value, "std::delegate: bound lambda/functor is not compatible with the delegate signature");

        const TLambda *p = static_cast<const TLambda *>(object);
        return (p->operator())(std::forward<TArgs>(arg)...);
    }

    //*************************************************************************
    /// The invocation object.
    //*************************************************************************
    invocation_element invocation;
};

//*************************************************************************
/// Make a delegate from a free function.
//*************************************************************************
template <auto Function>
[[nodiscard]]
constexpr auto make_delegate() noexcept {
    using function_type = typename std::function_traits<decltype(Function)>::function_type;

    return delegate<function_type>::template create<Function>();
}

//*************************************************************************
/// Make a delegate from a functor or lambda function.
//*************************************************************************
template <typename TLambda, typename = std::enable_if_t<std::is_class<TLambda>::value, void>>
[[nodiscard]]
constexpr auto make_delegate(TLambda &instance) noexcept {
    using function_type = typename std::function_traits<decltype(&TLambda::operator())>::function_type;

    return delegate<function_type>(instance);
}

//*************************************************************************
/// Make a delegate from a functor, compile time.
//*************************************************************************
template <typename T, T &Instance>
[[nodiscard]]
constexpr auto make_delegate() noexcept {
    using function_type = typename std::function_traits<decltype(&T::operator())>::function_type;

    return delegate<function_type>::template create<T, Instance>();
}

//*************************************************************************
/// Make a delegate from a member function at compile time.
//*************************************************************************
template <typename T, auto Method, T &Instance, typename = std::enable_if_t<!function_traits<decltype(Method)>::is_const>>
[[nodiscard]]
constexpr auto make_delegate() noexcept {
    using function_type = typename std::function_traits<decltype(Method)>::function_type;

    return delegate<function_type>::template create<T, Method, Instance>();
}

//*************************************************************************
/// Make a delegate from a const member function at compile time.
//*************************************************************************
template <typename T, auto Method, const T &Instance, typename = std::enable_if_t<function_traits<decltype(Method)>::is_const>>
[[nodiscard]]
constexpr auto make_delegate() noexcept {
    using function_type = typename std::function_traits<decltype(Method)>::function_type;

    return delegate<function_type>::template create<T, Method, Instance>();
}

//*************************************************************************
/// Make a delegate from a member function at run time.
//*************************************************************************
template <typename T, auto Method>
[[nodiscard]]
constexpr auto make_delegate(T &instance) noexcept {
    using function_type = typename std::function_traits<decltype(Method)>::function_type;

    return delegate<function_type>::template create<T, Method>(instance);
}

//*************************************************************************
/// Make a delegate from a member function at run time.
//*************************************************************************
template <typename T, auto Method>
[[nodiscard]]
constexpr auto make_delegate(const T &instance) noexcept {
    using function_type = typename std::function_traits<decltype(Method)>::function_type;

    return delegate<function_type>::template create<T, Method>(instance);
}