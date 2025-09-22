#pragma once

#include <array>
#include <algorithm>

template<typename T>
class stable_array {
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
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;

public:
    stable_array() noexcept {
    }

    template <std::size_t N>
    stable_array(element_type(arr)[N]) noexcept
        : _data(arr) {
    }

    template <std::size_t N>
    stable_array(const element_type(&arr)[N]) noexcept
        : _data((element_type*)arr) {
    }

    template <typename U, std::size_t N>
    stable_array(std::array<U, T::max_elements>& arr) noexcept
        : _data(arr) {
    }

    template <typename U, std::size_t N>
    stable_array(const std::array<U, N>& arr) noexcept
        : _data(arr) {
    }

    stable_array(const stable_array& other) noexcept = default;
    stable_array& operator=(const stable_array& other) noexcept = default;

public:
    reference front() const noexcept { return _data[0]; }
    reference back() const noexcept { return _data[size() - 1]; }
    const_reference operator[](size_type idx) const noexcept { return _data[idx]; }
    reference operator[](size_type idx) noexcept { return _data[idx]; }
    const_pointer data() const noexcept { return _data.data(); }
    pointer data() noexcept { return _data.data(); }

    void fill(const T& v) { std::fill_n(data(), size(), v); }

public:
    size_type size() const noexcept { return _data.size(); }
    size_type size_bytes() const noexcept { return size() * sizeof(T); }

public:
    const_iterator begin() const noexcept { return iterator{ data() }; }
    const_iterator end() const noexcept { return iterator{ data() + size() }; }
    
    iterator begin() noexcept { return iterator{ data() }; }
    iterator end() noexcept { return iterator{ data() + size() }; }

    reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() const noexcept { return reverse_iterator(begin()); }

private:
    std::array<T, T::max_elements> _data;
};