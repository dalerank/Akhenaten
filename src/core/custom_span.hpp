#pragma once

#include <array>   // std::array
#include <cstddef> // std::size_t
#include <cstdint>
#include <iterator> // std::iterator_traits

template <typename T>
class xspan {
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
    constexpr xspan() noexcept
      : m_storage(nullptr), m_size(0) {
    }

    template <typename It>
    constexpr xspan(It it, size_type count) noexcept
      : m_storage(it), m_size(count) {
    }

    template <typename It>
    constexpr xspan(It it, It end) noexcept
      : m_storage(it), m_size(end - it) {
    }

    template <std::size_t N>
    constexpr xspan(element_type (arr)[N]) noexcept
      : m_storage(arr), m_size(N) {
    }

    template <std::size_t N>
    constexpr xspan(const element_type (&arr)[N]) noexcept
        : m_storage((element_type*)arr), m_size(N) {
    }

    template <typename U, std::size_t N>
    constexpr xspan(std::array<U, N>& arr) noexcept
      : m_storage(arr.data()), m_size(N) {
    }

    template <typename U, std::size_t N>
    constexpr xspan(const std::array<U, N> &arr) noexcept
        : m_storage((T*)arr.data()), m_size(N) {
    }

    constexpr xspan(const xspan & other) noexcept = default;
    xspan & operator=(const xspan & other) noexcept = default;

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
using span_const = const xspan<T>;

template <typename T, std::size_t N>
inline constexpr xspan<T> make_span(T (&arr)[N]) {
    return xspan<T>(arr);
}

template <typename T, std::size_t N>
inline constexpr span_const<T> make_span(const T (&arr)[N]) {
    return span_const<T>(arr);
}

template <typename T>
inline constexpr xspan<T> make_span(T* arr, size_t N) {
    return xspan<T>(arr, N);
}

template <typename T, typename V = typename T::value_type>
inline constexpr xspan<V> make_span(T &arr) {
    return xspan<V>(arr.data(), arr.size());
}

template <typename T, typename V = typename T::value_type>
inline constexpr span_const<V> make_span(const T &arr) {
    return span_const<V>((V*)arr.data(), arr.size());
}

template <typename T, std::size_t N>
inline constexpr span_const<T> make_span(const std::array<T, N> arr) {
    return span_const<T>((T*)arr.data(), arr.size());
}

template <typename ... Args>
inline constexpr auto make_array(const Args... args) {
    using T = std::common_type_t<Args...>;
    std::array<T, sizeof...(args)> result = {args...};
    return result;
}

template <typename T>
inline constexpr typename xspan<T>::reference xspan<T>::front() const noexcept {
    return data()[0];
}

template <typename T>
inline constexpr typename xspan<T>::reference xspan<T>::back() const noexcept {
    return data()[size() - 1];
}

template <typename T>
inline constexpr typename xspan<T>::reference xspan<T>::operator[](size_type idx) const noexcept {
    return data()[idx];
}

template <typename T>
inline constexpr typename xspan<T>::pointer xspan<T>::data() const noexcept {
    return m_storage;
}

template <typename T>
inline constexpr typename xspan<T>::size_type xspan<T>::size() const noexcept {
    return m_size;
}

template <typename T>
inline constexpr typename xspan<T>::size_type xspan<T>::size_bytes() const noexcept {
    return size() * sizeof(T);
}

template <typename T>
inline constexpr bool xspan<T>::empty() const noexcept {
    return size() == 0u;
}

//------------------------------------------------------------------------------
// Iterators
//------------------------------------------------------------------------------

template <typename T>
inline constexpr typename xspan<T>::iterator xspan<T>::begin() const noexcept {
    return iterator{data()};
}

template <typename T>
inline constexpr typename xspan<T>::iterator xspan<T>::end() const noexcept {
    return iterator{data() + size()};
}

template <typename T>
inline constexpr typename xspan<T>::iterator xspan<T>::begin() noexcept {
    return iterator{data()};
}

template <typename T>
inline constexpr typename xspan<T>::iterator xspan<T>::end() noexcept {
    return iterator{data() + size()};
}

template <typename T>
inline constexpr typename xspan<T>::reverse_iterator xspan<T>::rbegin() const noexcept {
    return reverse_iterator(end());
}

template <typename T>
inline constexpr typename xspan<T>::reverse_iterator xspan<T>::rend() const noexcept {
    return reverse_iterator(begin());
}
