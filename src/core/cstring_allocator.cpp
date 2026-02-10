#include "core/cstring_allocator.h"

#include <cstdlib>
#include <cstring>
#include <mutex>
#include <new>

// Static allocator and mutex for frame-based string allocation
namespace {
    static LinearAllocator *s_frameStringAllocator = nullptr;
    static std::mutex s_frameStringAllocatorMutex;
}

// ================================================================================================
// LinearAllocator Implementation
// ================================================================================================

/**
 * @class LinearAllocator
 * @brief Simple linear (bump) allocator for frame-based allocation
 */
class LinearAllocator {
public:
    explicit LinearAllocator(size_t size)
        : _size(size) {
        _buffer = static_cast<uint8_t *>(::operator new(size));
        if (!_buffer) {
            throw std::bad_alloc();
        }
        _current = _buffer;
    }
    ~LinearAllocator() {
        ::operator delete(_buffer);
    }

    void *allocate(size_t bytes, size_t alignment) {
        if (bytes == 0) {
            return nullptr;
        }

        // Calculate aligned pointer
        uintptr_t currentAddr = reinterpret_cast<uintptr_t>(_current);
        uintptr_t alignedAddr = (currentAddr + alignment - 1) & ~(alignment - 1);
        size_t padding = alignedAddr - currentAddr;

        // Check if we have enough space
        if (static_cast<size_t>(_current - _buffer) + padding + bytes > _size) {
            return nullptr; // Out of memory
        }

        _current = reinterpret_cast<uint8_t *>(alignedAddr) + bytes;
        return reinterpret_cast<void *>(alignedAddr);
    }
    void releaseQuick() { // Reset the allocator (doesn't call destructors)
        _current = _buffer;
    }

    void reset() { // Reset the allocator
        releaseQuick();
    }

    size_t usedSize() const { return _current - _buffer; }
    size_t totalSize() const { return _size; }

private:
    uint8_t *_buffer;
    uint8_t *_current;
    size_t _size;

    LinearAllocator(const LinearAllocator &) = delete;
    LinearAllocator &operator=(const LinearAllocator &) = delete;
};

// ================================================================================================
// cstring_allocator Implementation
// ================================================================================================


/**
* @brief Constructor with explicit allocation strategy
*
* Creates an allocator with specified strategy.
* If Frame strategy is selected, automatically connects to frame allocator.
*
* @param strategy Allocation strategy (Common or Frame)
*
* @note noexcept - safe for use in constructors
*/
cstring_allocator::cstring_allocator(EStringAllocStrategy Strategy) noexcept
    : _strategy(Strategy)
    , _frameAllocator(nullptr) {
    if (_strategy == EStringAllocStrategy::Frame) {
        _frameAllocator = s_frameStringAllocator;
    }
}

cstring_allocator::pointer cstring_allocator::allocate(size_type n, const void *hint) {
    (void)hint;
    if (n == 0) {
        return nullptr;
    }

    const size_type bytes = n * sizeof(T);

    if (_strategy == EStringAllocStrategy::Frame && _frameAllocator) {
        // Frame allocation - thread-safe via mutex
        std::lock_guard<std::mutex> lock(s_frameStringAllocatorMutex);
        void *pPtr = _frameAllocator->allocate(bytes, alignof(T));
        return static_cast<pointer>(pPtr);
    }

    // Common heap allocation
    return static_cast<pointer>(::operator new(bytes));
}

void cstring_allocator::deallocate(pointer pPtr, size_type n) noexcept {
    (void)n;

    if (_strategy == EStringAllocStrategy::Frame) {
        // Frame allocator - no deallocation needed
        return;
    }

    // Common heap deallocation
    ::operator delete(pPtr);
}

// ================================================================================================
// Global Functions
// ================================================================================================

void initialize_frame_string_allocator() {
    static bool s_initialized = false;
    if (!s_initialized) {
        // 1 MB frame allocator for temporary strings
        constexpr size_t FRAME_STRING_ALLOCATOR_SIZE = 1024 * 1024;
        s_frameStringAllocator = new LinearAllocator(FRAME_STRING_ALLOCATOR_SIZE);
        s_initialized = true;
    }
}

void reset_frame_string_allocator() {
    if (s_frameStringAllocator) {
        std::lock_guard<std::mutex> lock(s_frameStringAllocatorMutex);
        s_frameStringAllocator->releaseQuick();
    }
}
