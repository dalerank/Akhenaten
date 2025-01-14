#pragma once

#include <array>   // std::array
#include <cstddef> // std::size_t
#include <cstdint>
#include <iterator> // std::iterator_traits

template <typename T>
class span {
public:
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    using pointer = element_type*;
    using const_pointer = const element_type*;
    using reference = element_type&;
    using const_reference = const element_type&;

    using iterator = T*;
    using reverse_iterator = std::reverse_iterator<iterator>;

public:
    constexpr span() noexcept
      : m_storage(nullptr),
        m_size(0) {
    }

    template <typename It>
    constexpr span(It it, size_type count) noexcept
      : m_storage(it),
        m_size(count) {
    }

    template <typename It>
    constexpr span(It it, It end) noexcept
      : m_storage(it),
        m_size(end - it) {
    }

    template <std::size_t N>
    constexpr span(element_type (&arr)[N]) noexcept
      : m_storage(arr),
        m_size(N) {
    }

    template <typename U, std::size_t N>
    constexpr span(std::array<U, N>& arr) noexcept
      : m_storage(arr.begin()),
        m_size(N) {
    }

    constexpr span(const span& other) noexcept = default;

    span& operator=(const span& other) noexcept = default;

public:
    constexpr reference front() const noexcept;
    constexpr reference back() const noexcept;
    constexpr reference operator[](size_type idx) const noexcept;
    constexpr pointer data() const noexcept;

public:
    constexpr size_type size() const noexcept;
    constexpr size_type size_bytes() const noexcept;
    constexpr bool empty() const noexcept;

public:
    constexpr iterator begin() const noexcept;
    constexpr iterator end() const noexcept;
    constexpr iterator begin() noexcept;
    constexpr iterator end() noexcept;
    constexpr reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator rend() const noexcept;

private:
    size_t m_size;
    T* m_storage;
};

template<typename T>
using span_const = const span<T>;

template <typename T, std::size_t N>
inline constexpr auto make_span(T (&arr)[N]) {
    return std::span<T>(arr);
}

template <typename T, std::size_t N>
inline constexpr auto make_span(const T (&arr)[N]) {
    return std::span_const<T>(arr);
}

template <typename T>
inline constexpr auto make_span(T* arr, size_t N) {
    return std::span<T>(arr, N);
}

template <typename T>
inline constexpr auto make_span(T &arr) {
    return std::span<T>(arr.data(), arr.size());
}

template <typename T, std::size_t N>
inline constexpr auto make_span(const std::array<T, N> arr) {
    return std::span_const<T>((T*)arr.data(), arr.size());
}

template <typename ... Args>
inline constexpr auto make_array(const Args... args) {
    using T = std::common_type_t<Args...>;
    std::array<T, sizeof...(args)> result = {args...};
    return result;
}

template <typename T>
inline constexpr typename std::span<T>::reference std::span<T>::front() const noexcept {
    return data()[0];
}

template <typename T>
inline constexpr typename std::span<T>::reference std::span<T>::back() const noexcept {
    return data()[size() - 1];
}

template <typename T>
inline constexpr typename std::span<T>::reference std::span<T>::operator[](size_type idx) const noexcept {
    return data()[idx];
}

template <typename T>
inline constexpr typename std::span<T>::pointer std::span<T>::data() const noexcept {
    return m_storage;
}

template <typename T>
inline constexpr typename std::span<T>::size_type std::span<T>::size() const noexcept {
    return m_size;
}

template <typename T>
inline constexpr typename std::span<T>::size_type std::span<T>::size_bytes() const noexcept {
    return size() * sizeof(T);
}

template <typename T>
inline constexpr bool std::span<T>::empty() const noexcept {
    return size() == 0u;
}

//------------------------------------------------------------------------------
// Iterators
//------------------------------------------------------------------------------

template <typename T>
inline constexpr typename std::span<T>::iterator std::span<T>::begin() const noexcept {
    return iterator{data()};
}

template <typename T>
inline constexpr typename std::span<T>::iterator std::span<T>::end() const noexcept {
    return iterator{data() + size()};
}

template <typename T>
inline constexpr typename std::span<T>::iterator std::span<T>::begin() noexcept {
    return iterator{data()};
}

template <typename T>
inline constexpr typename std::span<T>::iterator std::span<T>::end() noexcept {
    return iterator{data() + size()};
}

template <typename T>
inline constexpr typename std::span<T>::reverse_iterator std::span<T>::rbegin() const noexcept {
    return reverse_iterator(end());
}

template <typename T>
inline constexpr typename std::span<T>::reverse_iterator std::span<T>::rend() const noexcept {
    return reverse_iterator(begin());
}
