#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

template <typename T, size_t Capacity>
struct svector {
    struct fake_allocator {
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
    };

public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using allocator_type = fake_allocator;

    svector() = default;

    svector(allocator_type) {
    }

    explicit svector(size_t count, allocator_type = {}) {
        resize(count);
    }

    svector(size_t count, const T& value, allocator_type = {}) {
        assign_impl_val(count, value);
    }

    template <class InputIterator, typename = decltype(*std::declval<InputIterator>())>
    svector(InputIterator first, InputIterator last, allocator_type = {}) {
        assign_impl_iter(first, last);
    }

    svector(std::initializer_list<T> l, allocator_type = {}) {
        assign_impl_ilist(l);
    }

    template<typename Y>
    svector(std::initializer_list<Y> values) {
        for (const auto &v : values) {
            push_back(v);
        }
    }

    svector(const svector& v) {
        for (const auto& i : v) {
            push_back(i);
        }
    }

    template <size_t CapacityB>
    svector(const svector<T, CapacityB>& v) {
        assert(v.size() > Capacity);

        for (const auto& i : v) {
            push_back(i);
        }
    }

    svector(svector&& v) noexcept(std::is_nothrow_move_constructible<T>::value) {
        for (auto i = v.begin(); i != v.end(); ++i) {
            emplace_back(std::move(*i));
        }
        v.clear();
    }

    ~svector() {
        clear();
    }

    svector &operator=(const std::initializer_list<T> &v) {
        clear();
        for (auto& elem : v) {
            push_back(elem);
        }

        return *this;
    }

    svector& operator=(const svector& v) {
        if (this == &v) {
            // prevent self usurp
            return *this;
        }

        clear();
        for (auto& elem : v) {
            push_back(elem);
        }

        return *this;
    }

    svector& operator=(const std::vector<T>& v) {
        if ((void*)this == (void*)&v) {
            // prevent self usurp
            return *this;
        }

        clear();
        for (auto &elem : v) {
            this->push_back(elem);
        }

        return *this;
    }

    template<typename Y>
    svector &operator=(std::initializer_list<Y> values) {
        clear();
        for (auto &elem : values) {
            this->push_back(elem);
        }

        return *this;
    }

    svector& operator=(svector&& v) noexcept(std::is_nothrow_move_assignable<T>::value) {
        clear();
        for (auto i = v.begin(); i != v.end(); ++i) {
            emplace_back(std::move(*i));
        }

        v.clear();
        return *this;
    }

    void assign(size_type count, const T& value) {
        clear();
        assign_impl_val(count, value);
    }

    template <class InputIterator, typename = decltype(*std::declval<InputIterator>())>
    void assign(InputIterator first, InputIterator last) {
        clear();
        assign_impl_iter(first, last);
    }

    void assign(std::initializer_list<T> ilist) {
        clear();
        assign_impl_ilist(ilist);
    }

    const_reference at(size_type i) const {
        return *reinterpret_cast<const T*>(m_data + i);
    }

    reference at(size_type i) {
        return *reinterpret_cast<T*>(m_data + i);
    }

    const_reference operator[](size_type i) const {
        return at(i);
    }

    reference operator[](size_type i) {
        return at(i);
    }

    const_reference front() const {
        return at(0);
    }

    reference front() {
        return at(0);
    }

    const_reference back() const {
        return at(m_size - 1);
    }

    reference back() {
        return at(m_size - 1);
    }

    const_pointer data() const noexcept {
        return reinterpret_cast<const T*>(m_data);
    }

    pointer data() noexcept {
        return reinterpret_cast<T*>(m_data);
    }

    // iterators
    iterator begin() noexcept {
        return data();
    }

    const_iterator begin() const noexcept {
        return data();
    }

    const_iterator cbegin() const noexcept {
        return data();
    }

    iterator end() noexcept {
        return data() + m_size;
    }

    const_iterator end() const noexcept {
        return data() + m_size;
    }

    const_iterator cend() const noexcept {
        return data() + m_size;
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }

    // capacity
    bool empty() const noexcept {
        return m_size == 0;
    }

    size_t size() const noexcept {
        return m_size;
    }

    static constexpr size_t max_size() noexcept {
        return Capacity;
    }

    static constexpr size_t capacity() noexcept {
        return Capacity;
    }

    // modifiers
    void pop_back() {
        shrink_at(end() - 1, 1);
    }

    void clear() noexcept {
        auto e = end();
        for (auto p = begin(); p != e; ++p) {
            p->~T();
        }
        m_size = 0;
    }

    inline bool full() const { return size() >= Capacity; }

    void push_back(const_reference v) {
        assert(size() < Capacity);

        ::new (m_data + m_size) T(v);
        ++m_size;
    }

    void push_back(T&& v) {
        assert(size() < Capacity);

        ::new (m_data + m_size) T(std::move(v));
        ++m_size;
    }

    template <typename... Args>
    reference emplace_back(Args&&... args) {
        assert(size() < Capacity);

        ::new (m_data + m_size) T(std::forward<Args>(args)...);
        ++m_size;
        return back();
    }

    iterator insert(const_iterator position, const value_type& val) {
        auto pos = grow_at(position, 1);
        ::new (pos) T(val);
        return pos;
    }

    iterator insert(const_iterator position, value_type&& val) {
        auto pos = grow_at(position, 1);
        ::new (pos) T(std::move(val));
        return pos;
    }

    iterator insert(const_iterator position, size_type count, const value_type& val) {
        auto pos = grow_at(position, count);
        for (size_type i = 0; i < count; ++i) {
            ::new (pos + i) T(val);
        }
        return pos;
    }

    template <typename InputIterator, typename = decltype(*std::declval<InputIterator>())>
    iterator insert(const_iterator position, InputIterator first, InputIterator last) {
        auto pos = grow_at(position, last - first);
        auto np = pos;
        for (auto p = first; p != last; ++p, ++np) {
            ::new (np) T(*p);
        }
        return pos;
    }

    iterator insert(const_iterator position, std::initializer_list<T> ilist) {
        auto pos = grow_at(position, ilist.size());
        size_type i = 0;
        for (auto& elem : ilist) {
            ::new (pos + i) T(std::move(elem));
            ++i;
        }
        return pos;
    }

    template <typename... Args>
    iterator emplace(const_iterator position, Args&&... args) {
        auto pos = grow_at(position, 1);
        ::new (pos) T(std::forward<Args>(args)...);
        return pos;
    }

    iterator erase(const_iterator position) {
        return shrink_at(position, 1);
    }

    iterator erase(const_iterator first, const_iterator last) {
        return shrink_at(first, last - first);
    }

    void resize(size_type n) {
        assert(n < Capacity);

        while (m_size > n) {
            pop_back();
        }

        while (n > m_size) {
            emplace_back();
        }
    }

    void resize(size_type n, const value_type& v) {
        assert(n < Capacity);

        while (m_size > n) {
            pop_back();
        }

        while (n > m_size) {
            push_back(v);
        }
    }

    void swap(svector& v) {
        svector* longer;
        svector* shorter;

        if (v.m_size > m_size) {
            longer = &v;
            shorter = this;
        } else {
            longer = this;
            shorter = &v;
        }

        for (size_t i = 0; i < shorter->size(); ++i) {
            std::swap(shorter->at(i), longer->at(i));
        }

        auto short_size = shorter->m_size;

        for (size_t i = shorter->size(); i < longer->size(); ++i) {
            shorter->emplace_back(std::move(longer->at(i)));
            longer->at(i).~T();
        }

        longer->m_size = short_size;
    }

private:
    void assign_impl_val(size_t count, const T& value) {
        verify_no_crash(count < Capacity);

        for (size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    template <class InputIterator>
    void assign_impl_iter(InputIterator first, InputIterator last) {
        verify_no_crash(long(last - first) < long(Capacity));

        for (auto i = first; i != last; ++i) {
            push_back(*i);
        }
    }

    void assign_impl_ilist(std::initializer_list<T> l) {
        verify_no_crash(l.size() <= Capacity);

        for (auto&& i : l) {
            push_back(i);
        }
    }

    T* grow_at(const T* cp, size_t by) {
        assert(size() + by <= Capacity);
        assert(cp);

        auto position = const_cast<T*>(cp);
        if (by == 0)
            return position;

        for (auto p = end() - 1; p >= position; --p) {
            ::new (p + by) T(std::move(*p));
            p->~T();
        }
        m_size += by;

        return position;
    }

    T* shrink_at(const T* cp, size_t num) {
        assert(cp);

        auto position = const_cast<T*>(cp);

        const auto s = size();
        if (s - num == 0) {
            clear();
            return begin();
        }
        assert(num < size());

        const auto myend = end();
        for (auto p = position, np = position + num; np != myend; ++p, ++np) {
            p->~T();
            ::new (p) T(std::move(*np));
        }

        for (auto p = myend - num; p != myend; ++p) {
            p->~T();
        }

        m_size -= num;

        return position;
    }

    typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type m_data[Capacity];
    size_t m_size = 0;
};

namespace std {
    template<typename _Container, typename _Predicate>
    typename _Container::size_type
        erase_if(_Container& __cont, _Predicate __pred) {
        typename _Container::size_type __num = 0;
        for (auto __iter = __cont.begin(); __iter != __cont.end();) {
            if (__pred(*__iter)) {
                __iter = __cont.erase(__iter);
                ++__num;
            } else {
                ++__iter;
            }
        }
        return __num;
    }
}