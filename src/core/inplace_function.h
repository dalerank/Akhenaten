/******************************************************************************
Based on SG14 inplace_function proposal:
https://github.com/WG21-SG14/SG14

Adapted for Akhenaten project.
Provides std::function-like interface with internal buffer (no heap allocation).

Usage example:
    // Basic usage with lambda
    core::inplace_function<void(int, int), 64> callback;
    callback = [](int x, int y) { };
    callback(10, 20);

    // With member function
    struct MyClass {
        void method(int x, int y) { }
    };
    MyClass obj;
    callback = [&obj](int x, int y) { obj.method(x, y); };

    // Check if valid
    if (callback) {
        callback(1, 2);
    }

MIT license compatible.
******************************************************************************/

#pragma once

#include <cstddef>
#include <cstring>
#include <type_traits>
#include <utility>
#include <new>
#include <functional>
#include <stdexcept>
#include "core/function_traits.h"

// Forward declaration
template<typename Signature, std::size_t Capacity = 64>
class inplace_function;

//*************************************************************************
/// inplace_function - function wrapper with internal storage
/// 
/// Similar to std::function but uses internal buffer instead of heap allocation.
/// If the callable object is larger than Capacity, compilation will fail.
/// 
/// @tparam Signature Function signature (e.g., void(int, int))
/// @tparam Capacity Size of internal buffer in bytes (default: 64)
//*************************************************************************
template<typename Return, typename... Args, std::size_t Capacity>
class inplace_function<Return(Args...), Capacity> {
public:
    using return_type = Return;
    using argument_types = type_list<Args...>;

    //*************************************************************************
    /// Default constructor - creates empty function
    //*************************************************************************
    constexpr inplace_function() noexcept
        : invoker_(nullptr)
        , manager_(nullptr) {
    }

    //*************************************************************************
    /// Constructor from callable object (functor, lambda, etc.)
    //*************************************************************************
    template<typename Functor,
        typename = std::enable_if_t<
        !std::is_same_v<std::decay_t<Functor>, inplace_function> &&
        std::is_invocable_r_v<Return, Functor, Args...>
        >>
        inplace_function(Functor &&functor) noexcept(
        std::is_nothrow_copy_constructible_v<std::decay_t<Functor>> ||
        std::is_nothrow_move_constructible_v<std::decay_t<Functor>>
        ) {
        using functor_type = std::decay_t<Functor>;
        static_assert(sizeof(functor_type) <= Capacity,
            "Functor is too large for inplace_function buffer");
        static_assert(alignof(functor_type) <= alignof(storage_type),
            "Functor alignment requirement exceeds buffer alignment");

        new (storage_) functor_type(std::forward<Functor>(functor));
        invoker_ = &invoke_impl<functor_type>;
        manager_ = &manage_impl<functor_type>;
    }

    //*************************************************************************
    /// Copy constructor
    //*************************************************************************
    inplace_function(const inplace_function &other) {
        if (other) {
            other.manager_(operation::copy, other.storage_, storage_);
            invoker_ = other.invoker_;
            manager_ = other.manager_;
        } else {
            invoker_ = nullptr;
            manager_ = nullptr;
        }
    }

    //*************************************************************************
    /// Move constructor
    //*************************************************************************
    inplace_function(inplace_function &&other) noexcept {
        if (other) {
            other.manager_(operation::move, other.storage_, storage_);
            invoker_ = other.invoker_;
            manager_ = other.manager_;
            other.invoker_ = nullptr;
            other.manager_ = nullptr;
        } else {
            invoker_ = nullptr;
            manager_ = nullptr;
        }
    }

    //*************************************************************************
    /// Destructor
    //*************************************************************************
    ~inplace_function() {
        if (manager_) {
            manager_(operation::destroy, storage_, nullptr);
        }
    }

    //*************************************************************************
    /// Copy assignment
    //*************************************************************************
    inplace_function &operator=(const inplace_function &other) {
        if (this != &other) {
            if (manager_) {
                manager_(operation::destroy, storage_, nullptr);
            }
            if (other) {
                other.manager_(operation::copy, other.storage_, storage_);
                invoker_ = other.invoker_;
                manager_ = other.manager_;
            } else {
                invoker_ = nullptr;
                manager_ = nullptr;
            }
        }
        return *this;
    }

    //*************************************************************************
    /// Move assignment
    //*************************************************************************
    inplace_function &operator=(inplace_function &&other) noexcept {
        if (this != &other) {
            if (manager_) {
                manager_(operation::destroy, storage_, nullptr);
            }
            if (other) {
                other.manager_(operation::move, other.storage_, storage_);
                invoker_ = other.invoker_;
                manager_ = other.manager_;
                other.invoker_ = nullptr;
                other.manager_ = nullptr;
            } else {
                invoker_ = nullptr;
                manager_ = nullptr;
            }
        }
        return *this;
    }

    //*************************************************************************
    /// Assignment from callable object
    //*************************************************************************
    template<typename Functor>
    inplace_function &operator=(Functor &&functor) {
        if (manager_) {
            manager_(operation::destroy, storage_, nullptr);
        }
        new (this) inplace_function(std::forward<Functor>(functor));
        return *this;
    }

    //*************************************************************************
    /// Assignment from nullptr (clears the function)
    //*************************************************************************
    inplace_function &operator=(std::nullptr_t) noexcept {
        if (manager_) {
            manager_(operation::destroy, storage_, nullptr);
            invoker_ = nullptr;
            manager_ = nullptr;
        }
        return *this;
    }

    //*************************************************************************
    /// Swap two inplace_functions
    //*************************************************************************
    void swap(inplace_function &other) noexcept {
        if (this == &other) {
            return;
        }

        // Use temporary storage for swap
        alignas(storage_type) char temp_storage[sizeof(storage_type)];

        if (manager_ && other.manager_) {
            // Both are non-empty: swap contents
            manager_(operation::move, storage_, temp_storage);
            other.manager_(operation::move, other.storage_, storage_);
            manager_(operation::move, temp_storage, other.storage_);
            std::swap(invoker_, other.invoker_);
            std::swap(manager_, other.manager_);
        } else if (manager_) {
            // Only this is non-empty: move to other
            manager_(operation::move, storage_, other.storage_);
            other.invoker_ = invoker_;
            other.manager_ = manager_;
            invoker_ = nullptr;
            manager_ = nullptr;
        } else if (other.manager_) {
            // Only other is non-empty: move to this
            other.manager_(operation::move, other.storage_, storage_);
            invoker_ = other.invoker_;
            manager_ = other.manager_;
            other.invoker_ = nullptr;
            other.manager_ = nullptr;
        }
    }

    //*************************************************************************
    /// Call operator
    //*************************************************************************
    Return operator()(Args... args) const {
        if (!invoker_) {
            throw std::bad_function_call();
        }
        return invoker_(storage_, std::forward<Args>(args)...);
    }

    //*************************************************************************
    /// Check if function is valid (non-empty)
    //*************************************************************************
    explicit operator bool() const noexcept {
        return invoker_ != nullptr;
    }

    //*************************************************************************
    /// Check if function is empty
    //*************************************************************************
    bool empty() const noexcept {
        return invoker_ == nullptr;
    }

private:
    // Storage type with proper alignment
    // Use max_align_t alignment (typically 8 or 16 bytes)
    static constexpr std::size_t storage_alignment = alignof(std::max_align_t);
    using storage_type = typename std::aligned_storage<Capacity, storage_alignment>::type;

    // Invoker function pointer type
    using invoker_type = Return(*)(const void *, Args...);

    // Manager function pointer type
    enum class operation { destroy, copy, move };
    using manager_type = void(*)(operation, const void *, void *);

    // Storage buffer with proper alignment
    alignas(storage_alignment) mutable char storage_[Capacity];

    // Function pointers
    invoker_type invoker_;
    manager_type manager_;

    //*************************************************************************
    /// Invoker implementation for a specific functor type
    //*************************************************************************
    template<typename Functor>
    static Return invoke_impl(const void *storage, Args... args) {
        const Functor *functor = static_cast<const Functor *>(storage);
        return (*functor)(std::forward<Args>(args)...);
    }

    //*************************************************************************
    /// Manager implementation for a specific functor type
    //*************************************************************************
    template<typename Functor>
    static void manage_impl(operation op, const void *src, void *dst) {
        switch (op) {
        case operation::destroy:
        {
            const Functor *functor = static_cast<const Functor *>(src);
            functor->~Functor();
        }
        break;
        case operation::copy:
        {
            const Functor *src_functor = static_cast<const Functor *>(src);
            new (dst) Functor(*src_functor);
        }
        break;
        case operation::move:
        {
            const Functor *src_functor = static_cast<const Functor *>(src);
            new (dst) Functor(std::move(*const_cast<Functor *>(src_functor)));
            src_functor->~Functor();
        }
        break;
        }
    }
};

//*************************************************************************
/// Swap function for inplace_function
//*************************************************************************
template<typename Signature, std::size_t Capacity>
void swap(inplace_function<Signature, Capacity> &lhs,
    inplace_function<Signature, Capacity> &rhs) noexcept {
    lhs.swap(rhs);
}

//*************************************************************************
/// Comparison operators
//*************************************************************************
template<typename Signature, std::size_t Capacity>
bool operator==(const inplace_function<Signature, Capacity> &f, std::nullptr_t) noexcept {
    return !f;
}

template<typename Signature, std::size_t Capacity>
bool operator==(std::nullptr_t, const inplace_function<Signature, Capacity> &f) noexcept {
    return !f;
}

template<typename Signature, std::size_t Capacity>
bool operator!=(const inplace_function<Signature, Capacity> &f, std::nullptr_t) noexcept {
    return static_cast<bool>(f);
}

template<typename Signature, std::size_t Capacity>
bool operator!=(std::nullptr_t, const inplace_function<Signature, Capacity> &f) noexcept {
    return static_cast<bool>(f);
}
