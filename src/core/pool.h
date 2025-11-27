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
#include "generic_pool.h"

//*************************************************************************
/// A templated pool implementation that uses a fixed size pool.
///\ingroup pool
//*************************************************************************
template <typename T, const size_t VSize>
class pool : public generic_pool<sizeof(T), std::alignment_of<T>::value, VSize> {
private:
    typedef generic_pool<sizeof(T), std::alignment_of<T>::value, VSize> base_t;

public:

    using base_t::SIZE;
    using base_t::ALIGNMENT;
    using base_t::TYPE_SIZE;

    //*************************************************************************
    /// Constructor
    //*************************************************************************
    pool() {
    }

    //*************************************************************************
    /// Allocate an object from the pool.
    /// If asserts or exceptions are enabled and there are no more free items an
    /// Static asserts if the specified type is too large for the pool.
    //*************************************************************************
    T *allocate() {
        return base_t::template allocate<T>();
    }

    template <typename... Args>
    T *create(Args&&... args) {
        return base_t::template create<T>(std::forward<Args>(args)...);
    }

    //*************************************************************************
    /// Releases the object.
    /// Undefined behaviour if the pool does not contain a 'U' object derived from 'U'.
    /// \param p_object A pointer to the object to be destroyed.
    //*************************************************************************
    template <typename U>
    void release(const U *const p_object) {
        static_assert((std::is_same<U, T>::value || std::is_base_of<U, T>::value) && "Pool does not contain this type");
        base_t::release(p_object);
    }

    //*************************************************************************
    /// Destroys the object.
    /// Undefined behaviour if the pool does not contain a 'U' object derived from 'U'.
    /// \param p_object A pointer to the object to be destroyed.
    //*************************************************************************
    template <typename U>
    void destroy(const U *const p_object) {
        static_assert((std::is_base_of<U, T>::value) && "Pool does not contain this type");
        base_t::destroy(p_object);
    }

private:

    // Should not be copied.
    pool(const pool &) = delete;
    pool &operator =(const pool &) = delete;
};

//*************************************************************************
/// A templated pool implementation that uses a fixed size pool.
/// The storage for the pool is supplied externally.
///\ingroup pool
//*************************************************************************
template <typename T>
class pool_ext : public generic_pool_ext<sizeof(T), std::alignment_of<T>::value> {
private:
    typedef generic_pool_ext<sizeof(T), std::alignment_of<T>::value> base_t;

public:
    using base_t::ALIGNMENT;
    using base_t::TYPE_SIZE;

    //*************************************************************************
    /// Constructor
    //*************************************************************************
    pool_ext(typename base_t::element *buffer, size_t size)
        : base_t(buffer, size) {
    }

    //*************************************************************************
    /// Allocate an object from the pool.
    /// Uses the default constructor.
    /// If asserts or exceptions are enabled and there are no more free items an
    /// Static asserts if the specified type is too large for the pool.
    //*************************************************************************
    T *allocate() {
        return base_t::template allocate<T>();
    }

    //*************************************************************************
    /// Allocate storage for an object from the pool and create with variadic parameters.
    /// If asserts or exceptions are enabled and there are no more free items an
    //*************************************************************************
    template <typename... Args>
    T *create(Args&&... args) {
        return base_t::template create<T>(std::forward<Args>(args)...);
    }

    //*************************************************************************
    /// Releases the object.
    /// Undefined behaviour if the pool does not contain a 'U' object derived from 'U'.
    /// \param p_object A pointer to the object to be destroyed.
    //*************************************************************************
    template <typename U>
    void release(const U *const p_object) {
        static_assert((std::is_same<U, T>::value || std:::is_base_of<U, T>::value) && "Pool does not contain this type");
        base_t::release(p_object);
    }

    //*************************************************************************
    /// Destroys the object.
    /// Undefined behaviour if the pool does not contain a 'U' object derived from 'U'.
    /// \param p_object A pointer to the object to be destroyed.
    //*************************************************************************
    template <typename U>
    void destroy(const U *const p_object) {
        static_assert((std::is_base_of<U, T>::value) && "Pool does not contain this type");
        base_t::destroy(p_object);
    }

private:
    // Should not be copied.
    pool_ext(const pool_ext &) = delete;
    pool_ext &operator=(const pool_ext &) = delete;
};

