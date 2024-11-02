#pragma once

#include <cstddef>

// Magic value used to indicate that there is no cache entry for this particular
// conversion yet. Should be a fairly high value to avoid collisions.
constexpr ptrdiff_t DCAST_NO_OFFSET = 0x7FFFFFFFFFFFFFFFL;

#include <memory>
#include <assert.h>

using class_obj_ptr = const uintptr_t*;
using v_table_ptr = const uintptr_t*;

#ifdef _MSC_VER
#define FORCELINLINE __forceinline
#else
#define FORCELINLINE inline
#endif

template < typename T >
FORCELINLINE v_table_ptr smart_cast_get_vtable(const T* ptr) {
    // __vftable is at [ptr + 0]
    return reinterpret_cast<v_table_ptr>(*reinterpret_cast<class_obj_ptr>(ptr));
}

// Converts T&, const T&, volatile const T& etc to T, used for enable_if
// Could also abuse std::decay for this.
template < typename _Ty >
using clean_type_t = typename std::remove_cv_t<std::remove_reference_t<std::remove_pointer_t< _Ty >>>;

// smart cast for T*
// Should be nothrow but this decreases performance. In practice this is not
// an issue.
template < typename _To, typename _From >
FORCELINLINE _To smart_cast(_From* ptr) {
    // Not required, dynamic_cast already produces a compile-time error in this case
    // static_assert(std::is_polymorphic<_From>::value, "Type is not polymorphic!");

    if (!ptr) {
        return nullptr;
    }

    thread_local static ptrdiff_t offset = DCAST_NO_OFFSET;
    thread_local static v_table_ptr src_vtable_ptr;

    v_table_ptr this_vtable = smart_cast_get_vtable(ptr);
    if (offset != DCAST_NO_OFFSET && src_vtable_ptr == this_vtable) {
        // In case we have a cache hit, casting the pointer is straightforward
        char* new_ptr = reinterpret_cast<char*>(ptr) + offset;
        return reinterpret_cast<_To>(new_ptr);
    } else {
        // Need to construct cache entry
        auto result = dynamic_cast<_To>(ptr);
        if (result == nullptr) {
            return nullptr;
        }

        src_vtable_ptr = this_vtable;
        offset = reinterpret_cast<const char*>(result) - reinterpret_cast<const char*>(ptr);
        return result;
    }
};

// const T*
template < typename _To, typename _From >
FORCELINLINE const _To smart_cast(const _From* ptr) {
    _From* nonconst_ptr = const_cast<_From*>(ptr);
    _To casted_ptr = smart_cast<_To>(nonconst_ptr);
    return const_cast<const _To>(casted_ptr);
};

// T&
template < typename _To, typename _From, typename = std::enable_if_t<!std::is_same<clean_type_t<_To>, clean_type_t<_From&>>::value>>
FORCELINLINE _To smart_cast(_From& ref) {
    using _ToPtr = std::add_pointer_t<std::remove_reference_t<_To>>;
    auto casted_ptr = smart_cast<_ToPtr>(&ref);
    assert(casted_ptr);

    return *casted_ptr;
};

// const T&
template < typename _To, typename _From, typename = std::enable_if_t<!std::is_same<clean_type_t<_To>, clean_type_t<_From&>>::value>>
FORCELINLINE _To fast_dynamic_cast(const _From& ref) {
    using _ToPtr = std::add_pointer_t<std::remove_reference_t<_To>>;
    auto casted_ptr = smart_cast<_ToPtr>(const_cast<_From*>(&ref));
    assert(casted_ptr);
    return *casted_ptr;
};

// std::dynamic_pointer_cast
template < typename _To, typename _From >
FORCELINLINE std::shared_ptr<_To> smart_pointer_cast(const std::shared_ptr<_From>& ptr) {
    // Do not use std::move, since this might actually prevent RVO on MSVC 2015 and upwards
    return std::shared_ptr<_To>(ptr, fast_dynamic_cast<_To*>(ptr.get()));
}

// T -> T
template < typename _To >
FORCELINLINE _To smart_cast(_To ptr) { return ptr; }