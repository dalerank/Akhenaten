/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2014 John Wellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#pragma once

#include "ipool.h"

//*************************************************************************
/// A templated abstract pool implementation that uses a fixed size pool.
///\ingroup pool
//*************************************************************************
template <size_t VTypeSize, size_t VAlignment, size_t VSize>
class generic_pool : public ipool
{
public:
    static constexpr size_t SIZE      = VSize;
    static constexpr size_t ALIGNMENT = VAlignment;
    static constexpr size_t TYPE_SIZE = VTypeSize;

    //*************************************************************************
    /// Constructor
    //*************************************************************************
    generic_pool()
        : ipool(reinterpret_cast<char*>(&buffer[0]), Element_Size, VSize)
    {
    }

    //*************************************************************************
    /// Allocate an object from the pool.
    /// If asserts or exceptions are enabled and there are no more free items an
    /// etl::pool_no_allocation if thrown, otherwise a null pointer is returned.
    /// Static asserts if the specified type is too large for the pool.
    //*************************************************************************
    template <typename U>
    U* allocate()
    {
        static_assert(std::alignment_of<U>::value <= VAlignment, "Type has incompatible alignment");
        static_assert(sizeof(U) <= VTypeSize, "Type too large for pool");
        return ipool::allocate<U>();
    }


    //*************************************************************************
    /// Emplace with variadic constructor parameters.
    //*************************************************************************
    template <typename U, typename... Args>
    U* create(Args&&... args)
    {
        static_assert(std::alignment_of<U>::value <= VAlignment, "Type has incompatible alignment");
        static_assert(sizeof(U) <= VTypeSize, "Type too large for pool");
        return ipool::create<U>(std::forward<Args>(args)...);
    }

    //*************************************************************************
    /// Destroys the object.
    /// Undefined behaviour if the pool does not contain a 'U'.
    /// \param p_object A pointer to the object to be destroyed.
    //*************************************************************************
    template <typename U>
    void destroy(const U* const p_object)
    {
        static_assert(std::alignment_of<U>::value <= VAlignment, "Type has incompatible alignment");
        static_assert(sizeof(U) <= VTypeSize, "Type too large for pool");
        ipool::destroy(p_object);
    }

    private:

    // The pool element.
    union Element
    {
        char*     next;              ///< Pointer to the next free element.
        char      value[VTypeSize]; ///< Storage for value type.
        typename  type_with_alignment<VAlignment>::type dummy; ///< Dummy item to get correct alignment.
    };

    ///< The memory for the pool of objects.
    typename std::aligned_storage<sizeof(Element), std::alignment_of<Element>::value>::type buffer[VSize];

    static constexpr uint32_t Element_Size = sizeof(Element);

    // Should not be copied.
    generic_pool(const generic_pool &) = delete;
    generic_pool& operator =(const generic_pool&) = delete;
    };

    template <size_t VTypeSize, size_t VAlignment, size_t VSize>
    constexpr size_t generic_pool<VTypeSize, VAlignment, VSize>::SIZE;
  
    template <size_t VTypeSize, size_t VAlignment, size_t VSize>
    constexpr size_t generic_pool<VTypeSize, VAlignment, VSize>::ALIGNMENT;
  
    template <size_t VTypeSize, size_t VAlignment, size_t VSize>
    constexpr size_t generic_pool<VTypeSize, VAlignment, VSize>::TYPE_SIZE;

    //*************************************************************************
    /// A templated abstract pool implementation that uses a fixed size pool.
    /// The storage for the pool is supplied externally.
    ///\ingroup pool
    //*************************************************************************
    template <size_t VTypeSize, size_t VAlignment>
    class generic_pool_ext : public ipool 
    {
    private:
    // The pool element.
    union element_internal 
    {
        char* next;                                                 ///< Pointer to the next free element.
        char value[VTypeSize];                                      ///< Storage for value type.
        typename type_with_alignment<VAlignment>::type dummy;  ///< Dummy item to get correct alignment.
    };

    static const size_t ELEMENT_INTERNAL_SIZE = sizeof(element_internal);

public:
    static constexpr size_t ALIGNMENT = VAlignment;
    static constexpr size_t TYPE_SIZE = VTypeSize;

    typedef typename std::aligned_storage<sizeof(element_internal), std::alignment_of<element_internal>::value>::type element;

    //*************************************************************************
    /// Constructor
    //*************************************************************************
    generic_pool_ext(element* buffer, size_t size) 
        : ipool(reinterpret_cast<char*>(&buffer[0]), ELEMENT_INTERNAL_SIZE, size) 
    {
    }

    //*************************************************************************
    /// Allocate an object from the pool.
    /// If asserts or exceptions are enabled and there are no more free items an
    /// etl::pool_no_allocation if thrown, otherwise a null pointer is returned.
    /// Static asserts if the specified type is too large for the pool.
    //*************************************************************************
    template <typename U>
    U* allocate()
    {
        static_assert(std::alignment_of<U>::value <= VAlignment, "Type has incompatible alignment");
        static_assert(sizeof(U) <= VTypeSize, "Type too large for pool");
        return ipool::allocate<U>();
    }

    //*************************************************************************
    /// Emplace with variadic constructor parameters.
    //*************************************************************************
    template <typename U, typename... Args>
    U* create(Args&&... args)
    {
        static_assert(etl::alignment_of<U>::value <= VAlignment, "Type has incompatible alignment");
        static_assert(sizeof(U) <= VTypeSize, "Type too large for pool");
        return ipool::create<U>(etl::forward<Args>(args)...);
    }

    //*************************************************************************
    /// Destroys the object.
    /// Undefined behaviour if the pool does not contain a 'U'.
    /// \param p_object A pointer to the object to be destroyed.
    //*************************************************************************
    template <typename U>
    void destroy(const U* const p_object)
    {
        static_assert(std::alignment_of<U>::value <= VAlignment, "Type has incompatible alignment");
        static_assert(sizeof(U) <= VTypeSize, "Type too large for pool");
        ipool::destroy(p_object);
    }

    private:
    // Should not be copied.
    generic_pool_ext(const generic_pool_ext&) = delete;
    generic_pool_ext& operator=(const generic_pool_ext&) = delete;
};

template <size_t VTypeSize, size_t VAlignment>
constexpr size_t generic_pool_ext<VTypeSize, VAlignment>::ALIGNMENT;

template <size_t VTypeSize, size_t VAlignment>
constexpr size_t generic_pool_ext<VTypeSize, VAlignment>::TYPE_SIZE;

