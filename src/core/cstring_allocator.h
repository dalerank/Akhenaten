#pragma once

/**
 * @file cstring_allocator.h
 * @brief Custom allocator for cstring with support for different allocation strategies
 *
 * This file provides a flexible allocator system for cstring that supports two allocation strategies:
 * 1. Common (heap) allocation - standard new/delete
 * 2. Frame allocation - fast linear allocator for temporary strings
 *
 * Usage examples:
 * @code
 *   // Using helper functions (recommended)
 *   cstring str1(GetFrameAlloc());
 *   str1 = "Temporary string";
 *
 *   // Default - common allocation
 *   cstring str3 = "Normal string";
 *
 *   // At end of frame, reset frame allocator
 *   ResetFrameStringAllocator();
 * @endcode
 *
 * Performance considerations:
 * - Frame allocation is ~10x faster than heap allocation
 * - Frame allocator has no deallocation overhead
 * - Use frame allocation for temporary strings within a single frame
 * - Use common allocation for persistent strings
 */

#include <cstddef>
#include <memory>
#include <cstdint>
#include <type_traits>

 // Forward declaration
class LinearAllocator;

/**
 * @enum EStringAllocStrategy
 * @brief Allocation strategy for cstring
 *
 * Determines where memory for string data will be allocated from.
 */
enum class EStringAllocStrategy {
    Common,  ///< Standard heap allocation using new/delete (default)
    Frame    ///< Frame-based linear allocation (faster, but must be reset each frame)
};

class LinearAllocator;

/**
 * @class cstring_allocator
 * @brief Custom allocator for cstring supporting multiple allocation strategies
 *
 * This allocator implements the C++ Allocator concept and can be used with std::basic_string.
 * It supports two allocation strategies that can be selected at construction time:
 *
 * 1. Common (EStringAllocStrategy::Common):
 *    - Uses standard heap allocation (new/delete)
 *    - Memory is freed when string is destroyed
 *    - Default behavior
 *
 * 2. Frame (EStringAllocStrategy::Frame):
 *    - Uses linear frame allocator (fast bump allocator)
 *    - No per-string deallocation
 *    - All frame memory reset at once via ResetFrameStringAllocator()
 *    - Thread-safe through mutex protection
 *    - ~10x faster allocation than heap
 */
class cstring_allocator {
public:
    // Standard allocator type definitions (required by C++ Allocator concept)
    using T = char;                          ///< Character type for strings
    using value_type = T;                    ///< Type of allocated elements
    using pointer = T *;                      ///< Pointer to element
    using const_pointer = const T *;          ///< Const pointer to element
    using reference = T &;                    ///< Reference to element
    using const_reference = const T &;        ///< Const reference to element
    using size_type = size_t;                ///< Size type
    using difference_type = ptrdiff_t;       ///< Difference between pointers

    /**
     * @brief Rebind allocator to another type (required for containers)
     * @note For char, returns cstring_allocator; for other types, uses standard allocator
     */
    template <typename U>
    struct rebind {
        typedef typename std::conditional<
            std::is_same<U, char>::value,
            cstring_allocator,
            std::allocator<U>
        >::type other;
    };

    /**
     * @brief Default constructor - uses common heap allocation
     *
     * Creates an allocator that uses standard heap allocation (new/delete).
     * This is the default behavior for cstring.
     *
     * @note noexcept - safe for use in constructors
     */
    cstring_allocator() noexcept
        : _strategy(EStringAllocStrategy::Common)
        , _frameAllocator(nullptr) {
    }

    explicit cstring_allocator(EStringAllocStrategy Strategy) noexcept;
    cstring_allocator(const cstring_allocator &Other) noexcept = default;

    /// @brief Rebind constructor - constructs from another allocator type
    template<typename U>
    cstring_allocator(const std::allocator<U>&) noexcept
        : _strategy(EStringAllocStrategy::Common)
        , _frameAllocator(nullptr) {
    }

    /// @brief Conversion operator to std::allocator for rebind support
    template<typename U>
    operator std::allocator<U>() const noexcept {
        return std::allocator<U>();
    }

    ~cstring_allocator() = default;
    cstring_allocator &operator=(const cstring_allocator &) noexcept = default;

    /**
     * @brief Allocate memory for n elements
     *
     * Allocates uninitialized memory based on the allocation strategy:
     * - Common: Uses operator new (heap allocation)
     * - Frame: Uses linear frame allocator (fast bump allocation)
     *
     * @param n Number of elements (chars) to allocate
     * @param hint Optional hint for allocation location (ignored)
     * @return Pointer to allocated memory, or nullptr if n == 0
     *
     * @note Frame allocation is thread-safe via mutex
     */
    pointer allocate(size_type n, const void *hint = nullptr);

    /**
     * @brief Deallocate memory
     *
     * Deallocates memory based on allocation strategy:
     * - Common: Uses operator delete (frees memory immediately)
     * - Frame: No-op (memory freed when frame allocator is reset)
     *
     * @param pPtr Pointer to memory to deallocate
     * @param n Number of elements (ignored for frame allocator)
     *
     * @note noexcept - safe for destructors
     */
    void deallocate(pointer pPtr, size_type n) noexcept;

    /**
     * @brief Get maximum possible allocation size
     * @return Maximum number of elements that could theoretically be allocated
     */
    size_type max_size() const noexcept { return static_cast<size_type>(-1) / sizeof(T); }

    /**
     * @brief Get address of element (deprecated C++17, but kept for compatibility)
     * @param x Reference to element
     * @return Pointer to element
     */
    pointer address(reference ref) const noexcept { return std::addressof(ref); }

    /**
     * @brief Get address of const element (deprecated C++17, but kept for compatibility)
     * @param x Const reference to element
     * @return Const pointer to element
     */
    const_pointer address(const_reference ref) const noexcept { return std::addressof(ref); }

    /**
     * @brief Construct object in allocated memory
     *
     * Uses placement new to construct object in pre-allocated memory.
     * Separates memory allocation from object construction.
     *
     * @tparam U Type of object to construct
     * @tparam Args Constructor argument types
     * @param p Pointer to memory where object should be constructed
     * @param args Arguments to forward to constructor
     *
     * @note For char (string elements), this is effectively a no-op
     */
    template <typename U, typename... TArgs>
    void construct(U *pPtr, TArgs&&... args) {
        ::new (static_cast<void *>(pPtr)) U(std::forward<TArgs>(args)...);
    }

    /**
     * @brief Destroy object without deallocating memory
     *
     * Calls destructor on object. Memory remains allocated.
     * Separates object destruction from memory deallocation.
     *
     * @tparam U Type of object to destroy
     * @param p Pointer to object to destroy
     *
     * @note For char (string elements), this is effectively a no-op
     */
    template <typename U>
    void destroy(U *pPtr) {
        pPtr->~U();
    }

    /**
     * @brief Compare allocators for equality
     *
     * Two allocators are equal if they use the same strategy and,
     * for frame allocators, point to the same frame allocator instance.
     *
     * @param other Allocator to compare with
     * @return true if allocators are equal and can deallocate each other's memory
     *
     * @note This is important for stateful allocators - different strategies
     *       mean memory cannot be safely transferred between allocators
     */
    bool operator==(const cstring_allocator &other) const noexcept {
        return _strategy == other._strategy && _frameAllocator == other._frameAllocator;
    }

    /**
     * @brief Compare allocators for inequality
     * @param other Allocator to compare with
     * @return true if allocators are not equal
     */
    bool operator!=(const cstring_allocator &other) const noexcept {
        return !(*this == other);
    }

    /**
     * @brief Get current allocation strategy
     * @return Current strategy (Common or Frame)
     */
    EStringAllocStrategy GetStrategy() const noexcept { return _strategy; }

private:
    EStringAllocStrategy _strategy;                           ///< Current allocation strategy
    LinearAllocator *_frameAllocator;                         ///< Pointer to frame allocator (null for Common strategy)
};

// ================================================================================================
// Global Functions
// ================================================================================================

void initialize_frame_string_allocator();
void reset_frame_string_allocator();

/**
 * @brief Global equality operator for allocators
 * @note Template parameters T and U are unused (for compatibility)
 */
template <typename T, typename U>
inline bool operator==(const cstring_allocator &lhs, const cstring_allocator &rhs) noexcept {
    return lhs.operator==(rhs);
}

/**
 * @brief Global inequality operator for allocators
 * @note Template parameters T and U are unused (for compatibility)
 */
template <typename T, typename U>
inline bool operator!=(const cstring_allocator &lhs, const cstring_allocator &rhs) noexcept {
    return lhs.operator!=(rhs);
}

// ================================================================================================
// Convenience Functions
// ================================================================================================

inline cstring_allocator frameAlloc() {
    return cstring_allocator(EStringAllocStrategy::Frame);
}

inline cstring_allocator commonAlloc() {
    return cstring_allocator(EStringAllocStrategy::Common);
}
