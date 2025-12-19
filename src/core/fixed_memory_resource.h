#pragma once

#include <memory>
#include <memory_resource>

// A fixed memory resource where initial allocations come from a fixed buffer, with later allocations just doing new / delete.
// Used with locally defined std::pmr types to allow intial container allocations to come from stack memory. (eg std::pmr::vector that is just a temporary buffer)
//
// This is similar to a std::pmr::monotonic_buffer_resource, but does not try and maintain custom buffers once the static one is full. (There were bugs in some implementations that lead to this custom one.)
//
// Pass a type and a count that will typically be used in the allocations for sizing the fixed buffer
// eg. fixed_memory_resource<int, 100> buffer;
//     std::pmr::vector<int> vec(&buffer);
//     vec.reserve(100);
template<
    typename T,
    size_t ItemCount,
    bool WarnOnFull = true,
    size_t FixedSize = ItemCount * sizeof(T) + 32>
class fixed_memory_resource : public std::pmr::memory_resource {
public:
    fixed_memory_resource() = default;
    fixed_memory_resource(const fixed_memory_resource & obj) = delete;
    fixed_memory_resource & operator=(const fixed_memory_resource & obj) = delete;
    fixed_memory_resource(fixed_memory_resource && obj) = delete;
    fixed_memory_resource & operator=(fixed_memory_resource && obj) = delete;

    void* do_allocate(size_t bytes, size_t align) override {
        if (bytes == 0) {
            bytes = 1; // Ensures we don't return the same pointer twice.
        }

        // Check for free memory in the fixed buffer - else just call new
        void* currBuffer = &_fixed_buffer[FixedSize - _available_fixed_size];
        if (std::align(align, bytes, currBuffer, _available_fixed_size) == nullptr) {
            if constexpr (WarnOnFull) {
                printf(
                    "Local stack buffer exceeded - Max:%zu Free:%zu Alloc:%zu\n",
                    FixedSize,
                    _available_fixed_size,
                    bytes);
            }
            return ::operator new(bytes, static_cast<std::align_val_t>(align));
        }
        _available_fixed_size -= bytes;
        return currBuffer;
    }

    void do_deallocate(void* ptr, size_t bytes, size_t align) override {
        if (ptr < &_fixed_buffer[0] || ptr >= &_fixed_buffer[FixedSize]) {
            ::operator delete(ptr, bytes, static_cast<std::align_val_t>(align));
        }
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    alignas(T) uint8_t _fixed_buffer[FixedSize]; // Internal fixed-size buffer
    size_t _available_fixed_size = FixedSize; // Current available size
};
