#pragma once

#include "fixed_memory_resource.h"
#include <vector>
#include <memory_resource>
#include <cstddef>
#include <initializer_list>
#include <type_traits>

// A hybrid vector that uses std::pmr::vector with a fixed_memory_resource.
// Initial allocations come from a fixed stack buffer, with later allocations using heap memory.
// This provides the convenience of std::vector with the performance benefits of stack allocation for small sizes.
//
// Usage:
//     hvector<int, 100> vec;  // Can hold up to 100 ints in stack buffer before using heap
//     vec.push_back(42);
template<typename T, size_t Prealocated, bool WarnOnFull = true>
class hvector {
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = typename std::pmr::vector<T>::iterator;
    using const_iterator = typename std::pmr::vector<T>::const_iterator;
    using reverse_iterator = typename std::pmr::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::pmr::vector<T>::const_reverse_iterator;
    using allocator_type = std::pmr::polymorphic_allocator<T>;

    static constexpr size_t fixed_capacity = Prealocated;

    hvector() : _resource(), _vec(&_resource) {
        _vec.reserve(fixed_capacity);
    }

    hvector(size_type count, const T& value) : _resource(), _vec(count, value, &_resource) {
    }

    template<typename InputIterator, typename = decltype(*std::declval<InputIterator>())>
    hvector(InputIterator first, InputIterator last) : _resource(), _vec(first, last, &_resource) {
    }

    hvector(std::initializer_list<T> init) : _resource(), _vec(init, &_resource) {
    }

    hvector(const hvector& other) : _resource(), _vec(other._vec, &_resource) {
    }

    hvector(hvector&& other) noexcept(std::is_nothrow_move_constructible<T>::value)
        : _resource(), _vec(std::move(other._vec), &_resource) {
    }

    ~hvector() = default;

    hvector& operator=(const hvector& other) {
        if (this != &other) {
            _vec = other._vec;
        }
        return *this;
    }

    hvector& operator=(hvector&& other) noexcept(std::is_nothrow_move_assignable<T>::value) {
        if (this != &other) {
            _vec = std::move(other._vec);
        }
        return *this;
    }

    hvector& operator=(std::initializer_list<T> ilist) {
        _vec = ilist;
        return *this;
    }

    void assign(size_type count, const T& value) {
        _vec.assign(count, value);
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        _vec.assign(first, last);
    }

    void assign(std::initializer_list<T> ilist) {
        _vec.assign(ilist);
    }

    reference at(size_type pos) {
        return _vec.at(pos);
    }

    const_reference at(size_type pos) const {
        return _vec.at(pos);
    }

    reference operator[](size_type pos) {
        return _vec[pos];
    }

    const_reference operator[](size_type pos) const {
        return _vec[pos];
    }

    reference front() {
        return _vec.front();
    }

    const_reference front() const {
        return _vec.front();
    }

    reference back() {
        return _vec.back();
    }

    const_reference back() const {
        return _vec.back();
    }

    pointer data() noexcept {
        return _vec.data();
    }

    const_pointer data() const noexcept {
        return _vec.data();
    }

    iterator begin() noexcept {
        return _vec.begin();
    }

    const_iterator begin() const noexcept {
        return _vec.begin();
    }

    const_iterator cbegin() const noexcept {
        return _vec.cbegin();
    }

    iterator end() noexcept {
        return _vec.end();
    }

    const_iterator end() const noexcept {
        return _vec.end();
    }

    const_iterator cend() const noexcept {
        return _vec.cend();
    }

    reverse_iterator rbegin() noexcept {
        return _vec.rbegin();
    }

    const_reverse_iterator rbegin() const noexcept {
        return _vec.rbegin();
    }

    const_reverse_iterator crbegin() const noexcept {
        return _vec.crbegin();
    }

    reverse_iterator rend() noexcept {
        return _vec.rend();
    }

    const_reverse_iterator rend() const noexcept {
        return _vec.rend();
    }

    const_reverse_iterator crend() const noexcept {
        return _vec.crend();
    }

    bool empty() const noexcept {
        return _vec.empty();
    }

    size_type size() const noexcept {
        return _vec.size();
    }

    size_type max_size() const noexcept {
        return _vec.max_size();
    }

    void reserve(size_type new_cap) {
        _vec.reserve(new_cap);
    }

    size_type capacity() const noexcept {
        return _vec.capacity();
    }

    void shrink_to_fit() {
        _vec.shrink_to_fit();
    }

    void clear() noexcept {
        _vec.clear();
    }

    iterator insert(const_iterator pos, const T& value) {
        return _vec.insert(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) {
        return _vec.insert(pos, std::move(value));
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        return _vec.insert(pos, count, value);
    }

    template<typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
        return _vec.insert(pos, first, last);
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return _vec.insert(pos, ilist);
    }

    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        return _vec.emplace(pos, std::forward<Args>(args)...);
    }

    iterator erase(const_iterator pos) {
        return _vec.erase(pos);
    }

    iterator erase(const_iterator first, const_iterator last) {
        return _vec.erase(first, last);
    }

    void push_back(const T& value) {
        _vec.push_back(value);
    }

    void push_back(T&& value) {
        _vec.push_back(std::move(value));
    }

    template<typename... Args>
    reference emplace_back(Args&&... args) {
        return _vec.emplace_back(std::forward<Args>(args)...);
    }

    void pop_back() {
        _vec.pop_back();
    }

    void resize(size_type count) {
        _vec.resize(count);
    }

    void resize(size_type count, const T& value) {
        _vec.resize(count, value);
    }

    void swap(hvector& other) noexcept {
        _vec.swap(other._vec);
    }

    allocator_type get_allocator() const noexcept {
        return _vec.get_allocator();
    }

private:
    fixed_memory_resource<T, fixed_capacity, WarnOnFull> _resource;
    std::pmr::vector<T> _vec;
};

template<typename T, size_t ItemCount, bool WarnOnFull>
bool operator==(const hvector<T, ItemCount, WarnOnFull>& lhs,
                const hvector<T, ItemCount, WarnOnFull>& rhs) {
    return lhs.size() == rhs.size() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, size_t ItemCount, bool WarnOnFull>
bool operator!=(const hvector<T, ItemCount, WarnOnFull>& lhs,
                const hvector<T, ItemCount, WarnOnFull>& rhs) {
    return !(lhs == rhs);
}

template<typename T, size_t ItemCount, bool WarnOnFull>
bool operator<(const hvector<T, ItemCount, WarnOnFull>& lhs,
               const hvector<T, ItemCount, WarnOnFull>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, size_t ItemCount, bool WarnOnFull>
bool operator<=(const hvector<T, ItemCount, WarnOnFull>& lhs,
                const hvector<T, ItemCount, WarnOnFull>& rhs) {
    return !(rhs < lhs);
}

template<typename T, size_t ItemCount, bool WarnOnFull>
bool operator>(const hvector<T, ItemCount, WarnOnFull>& lhs,
               const hvector<T, ItemCount, WarnOnFull>& rhs) {
    return rhs < lhs;
}

template<typename T, size_t ItemCount, bool WarnOnFull>
bool operator>=(const hvector<T, ItemCount, WarnOnFull>& lhs,
                const hvector<T, ItemCount, WarnOnFull>& rhs) {
    return !(lhs < rhs);
}

template<typename T, size_t ItemCount, bool WarnOnFull>
void swap(hvector<T, ItemCount, WarnOnFull>& lhs,
          hvector<T, ItemCount, WarnOnFull>& rhs) noexcept {
    lhs.swap(rhs);
}

