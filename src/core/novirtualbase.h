#pragma once

#include <type_traits>

template<typename T>
struct has_virtual_functions {
    static constexpr bool value = std::is_polymorphic_v<T>;
};

template<typename Derived>
struct no_virtual_base_t {
    ~no_virtual_base_t() = default;

protected:
    no_virtual_base_t() {
        static_assert(!has_virtual_functions<Derived>::value, "Derived class cannot have virtual functions!");
        static_assert(sizeof(Derived) == sizeof(no_virtual_base_t<Derived>) || !std::is_polymorphic_v<Derived>, "Virtual functions detected in derived class!");
        static_assert(std::is_base_of_v<no_virtual_base_t<Derived>, Derived>, "Must inherit from no_virtual_base_t<Derived>");
    }

    no_virtual_base_t(const no_virtual_base_t &) = default;
    no_virtual_base_t &operator=(const no_virtual_base_t &) = default;

    no_virtual_base_t(no_virtual_base_t &&) = default;
    no_virtual_base_t &operator=(no_virtual_base_t &&) = default;
};