#pragma once

#include "svector.h"
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>

template<typename T>
struct standart_less {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
};

// Helper: equal algorithm
template<typename InputIterator1, typename InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

//***************************************************************************
/// A flat_map based on a sorted svector with the capacity defined at
/// compile time. This container is best used for tables that are occasionally
/// updated and spend most of their time being searched.
/// Has insertion of O(N) and find of O(logN).
/// Duplicate entries are not allowed.
//***************************************************************************
template <typename TKey, typename TMapped, const size_t MAX_SIZE_, typename TKeyCompare = less<TKey>>
class flat_map {
public:
    typedef std::pair<const TKey, TMapped> value_type;
    typedef TKey              key_type;
    typedef TMapped           mapped_type;
    typedef TKeyCompare       key_compare;
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef size_t            size_type;

    typedef const key_type&    const_key_reference;
    typedef mapped_type&       mapped_reference;
    typedef const mapped_type& const_mapped_reference;

    typedef typename svector<value_type, MAX_SIZE_>::iterator       iterator;
    typedef typename svector<value_type, MAX_SIZE_>::const_iterator const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    static const size_t MAX_SIZE = MAX_SIZE_;

private:
    class compare {
    public:
        bool operator ()(const value_type& element, const key_type& key) const {
            return comp(element.first, key);
        }
        bool operator ()(const key_type& key, const value_type& element) const {
            return comp(key, element.first);
        }
        key_compare comp;
    };

    svector<value_type, MAX_SIZE_> data_;
    key_compare compare_;

    iterator insert_sorted(const_reference value) {
        compare cmp;
        const key_type& key = value.first;

        // Find insertion point using binary search
        iterator first = data_.begin();
        iterator last = data_.end();
        iterator it;
        typename std::iterator_traits<iterator>::difference_type count, step;
        count = last - first;
        while (count > 0) {
            it = first;
            step = count / 2;
            it += step;
            if (cmp(*it, key)) {
                first = ++it;
                count -= step + 1;
            } else {
                count = step;
            }
        }

        // Check for duplicate
        if (first != data_.end() && !cmp(key, first->first)) {
            return first; // Duplicate found
        }

        // Insert at position
        return data_.insert(first, value);
    }

public:
    flat_map() : compare_() {
    }

    flat_map(const flat_map& other) : data_(other.data_), compare_(other.compare_) {
    }

    template <typename TIterator>
    flat_map(TIterator first, TIterator last) : compare_() {
        assign(first, last);
    }

    flat_map(std::initializer_list<value_type> init) : compare_() {
        assign(init.begin(), init.end());
    }

    ~flat_map() {
        clear();
    }


    flat_map& operator = (const flat_map& rhs) {
        if (&rhs != this) {
            data_ = rhs.data_;
            compare_ = rhs.compare_;
        }
        return *this;
    }

    iterator begin() {
        return data_.begin();
    }

    const_iterator begin() const {
        return data_.begin();
    }

    const_iterator cbegin() const {
        return data_.cbegin();
    }

    iterator end() {
        return data_.end();
    }

    const_iterator end() const {
        return data_.end();
    }

    const_iterator cend() const {
        return data_.cend();
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(begin());
    }

    mapped_reference operator [](const_key_reference key) {
        iterator i_element = lower_bound(key);
        compare cmp;
        if ((i_element == end()) || cmp(key, i_element->first)) {
            // Insert default value
            value_type value;
            const_cast<key_type&>(value.first) = key;
            value.second = mapped_type();
            i_element = insert_sorted(value);
        }
        return i_element->second;
    }

    mapped_reference at(const_key_reference key) {
        iterator it = find(key);
        if (it == end()) {
            throw std::out_of_range("flat_map::at");
        }
        return it->second;
    }

    const_mapped_reference at(const_key_reference key) const {
        const_iterator it = find(key);
        if (it == end()) {
            throw std::out_of_range("flat_map::at");
        }
        return it->second;
    }

    std::pair<iterator, bool> insert(const_reference value) {
        iterator i_element = lower_bound(value.first);
        compare cmp;
        if ((i_element != end()) && !cmp(value.first, i_element->first)) {
            return std::make_pair(i_element, false);
        }
        if (full()) {
            return std::make_pair(end(), false);
        }
        iterator inserted = insert_sorted(value);
        return std::make_pair(inserted, true);
    }

    template<typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for (; first != last; ++first) {
            insert(*first);
        }
    }

    void insert(std::initializer_list<value_type> ilist) {
        insert(ilist.begin(), ilist.end());
    }

    template<typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args) {
        value_type value(std::forward<Args>(args)...);
        return insert(value);
    }

    iterator erase(iterator position) {
        return data_.erase(position);
    }

    size_type erase(const_key_reference key) {
        iterator it = find(key);
        if (it != end()) {
            erase(it);
            return 1;
        }
        return 0;
    }

    iterator find(const_key_reference key) {
        iterator it = lower_bound(key);
        compare cmp;
        if (it != end() && !cmp(key, it->first)) {
            return it;
        }
        return end();
    }

    const_iterator find(const_key_reference key) const {
        const_iterator it = lower_bound(key);
        compare cmp;
        if (it != end() && !cmp(key, it->first)) {
            return it;
        }
        return end();
    }

    size_type count(const_key_reference key) const {
        return (find(key) != end()) ? 1 : 0;
    }

    iterator lower_bound(const_key_reference key) {
        compare cmp;
        iterator first = data_.begin();
        iterator last = data_.end();
        iterator it;
        typename std::iterator_traits<iterator>::difference_type count, step;
        count = last - first;
        while (count > 0) {
            it = first;
            step = count / 2;
            it += step;
            if (cmp(*it, key)) {
                first = ++it;
                count -= step + 1;
            } else {
                count = step;
            }
        }
        return first;
    }

    const_iterator lower_bound(const_key_reference key) const {
        compare cmp;
        const_iterator first = data_.begin();
        const_iterator last = data_.end();
        const_iterator it;
        typename std::iterator_traits<const_iterator>::difference_type count, step;
        count = last - first;
        while (count > 0) {
            it = first;
            step = count / 2;
            it += step;
            if (cmp(*it, key)) {
                first = ++it;
                count -= step + 1;
            } else {
                count = step;
            }
        }
        return first;
    }

    iterator upper_bound(const_key_reference key) {
        iterator it = lower_bound(key);
        compare cmp;
        if (it != end() && !cmp(key, it->first)) {
            ++it;
        }
        return it;
    }

    const_iterator upper_bound(const_key_reference key) const {
        const_iterator it = lower_bound(key);
        compare cmp;
        if (it != end() && !cmp(key, it->first)) {
            ++it;
        }
        return it;
    }

    std::pair<iterator, iterator> equal_range(const_key_reference key) {
        return std::make_pair(lower_bound(key), upper_bound(key));
    }

    std::pair<const_iterator, const_iterator> equal_range(const_key_reference key) const {
        return std::make_pair(lower_bound(key), upper_bound(key));
    }

    void clear() {
        data_.clear();
    }

    size_type size() const {
        return data_.size();
    }

    bool empty() const {
        return data_.empty();
    }

    bool full() const {
        return data_.full();
    }

    size_type max_size() const {
        return MAX_SIZE_;
    }

    size_type capacity() const {
        return MAX_SIZE_;
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        clear();
        insert(first, last);
    }

    void assign(std::initializer_list<value_type> ilist) {
        clear();
        insert(ilist.begin(), ilist.end());
    }
};

template <typename TKey, typename TMapped, const size_t MAX_SIZE_, typename TKeyCompare>
bool operator ==(const flat_map<TKey, TMapped, MAX_SIZE_, TKeyCompare>& lhs, 
                 const flat_map<TKey, TMapped, MAX_SIZE_, TKeyCompare>& rhs) {
    return (lhs.size() == rhs.size()) && equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename TKey, typename TMapped, const size_t MAX_SIZE_, typename TKeyCompare>
bool operator !=(const flat_map<TKey, TMapped, MAX_SIZE_, TKeyCompare>& lhs, 
                 const flat_map<TKey, TMapped, MAX_SIZE_, TKeyCompare>& rhs) {
    return !(lhs == rhs);
}
