#pragma once

#include <atomic>
#include <cstddef>
#include <mutex>
#include <type_traits>
#include <vector>

// Process-wide unique instance per type.
//
// Usage:
//   struct my_cache_t { int value = 0; };
//   auto &cache = xvalue<my_cache_t>::ref();
//
// First call default-constructs T, registers it by type index, and returns a reference.
// Later calls return the same reference (no lock after first initialization).
class xvalue_registry {
    static std::vector<void *> &slots() {
        static std::vector<void *> s;
        return s;
    }

    static std::mutex &mutex() {
        static std::mutex m;
        return m;
    }

    static std::atomic<size_t> &next_type_index() {
        static std::atomic<size_t> n{0};
        return n;
    }

    template <typename T>
    static size_t type_index() {
        static const size_t idx = next_type_index().fetch_add(1, std::memory_order_relaxed);
        return idx;
    }

public:
    template <typename T>
    static void register_instance(T *ptr) {
        const size_t idx = type_index<T>();
        std::lock_guard<std::mutex> lock(mutex());
        auto &s = slots();
        if (s.size() <= idx) {
            s.resize(idx + 1, nullptr);
        }
        s[idx] = ptr;
    }

    template <typename T>
    static T *find() {
        const size_t idx = type_index<T>();
        std::lock_guard<std::mutex> lock(mutex());
        auto &s = slots();
        if (idx >= s.size()) {
            return nullptr;
        }
        return static_cast<T *>(s[idx]);
    }
};

template <typename T>
struct xvalue {
    static_assert(std::is_default_constructible_v<T>, "xvalue<T> requires a default-constructible type");

    static T &ref() {
        static T instance;
        static const bool registered = [] {
            xvalue_registry::register_instance(&instance);
            return true;
        }();
        (void)registered;
        return instance;
    }

    static T *find() {
        return xvalue_registry::find<T>();
    }
};
