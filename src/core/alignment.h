///\file

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

#include <type_traits>
#include <utility>
#include <algorithm>
#include <stdint.h>

//*****************************************************************************
/// Check that 'p' has 'required_alignment'.
//*****************************************************************************
inline bool is_aligned(const void *p, size_t required_alignment) {
    uintptr_t address = reinterpret_cast<uintptr_t>(p);
    return (address % required_alignment) == 0U;
}

//*****************************************************************************
/// Check that 'p' has 'Alignment'.
//*****************************************************************************
template <size_t Alignment>
bool is_aligned(const void *p) {
    uintptr_t address = reinterpret_cast<uintptr_t>(p);
    return (address % Alignment) == 0U;
}

//*****************************************************************************
/// Check that 'p' has the alignment of 'T'.
//*****************************************************************************
template <typename T>
bool is_aligned(const void *p) {
    return is_aligned<std::alignment_of<T>::value>(p);
}

namespace private_alignment {
    //***************************************************************************
    // Matcher.
    //***************************************************************************
    template <bool Is_Match, size_t Alignment, typename... TRest>
    struct type_with_alignment_matcher;

    // Matching alignment.
    template <size_t Alignment, typename T1, typename... TRest>
    struct type_with_alignment_matcher<true, Alignment, T1, TRest...> {
        typedef T1 type;
    };

    // Non-matching alignment
    template <size_t Alignment, typename T1, typename T2, typename... TRest>
    struct type_with_alignment_matcher <false, Alignment, T1, T2, TRest...> {
        typedef typename type_with_alignment_matcher < Alignment <= std::alignment_of<T2>::value, Alignment, T2, TRest... > ::type type;
    };

    // Non-matching alignment, none left.
    template <size_t Alignment, typename T1>
    struct type_with_alignment_matcher <false, Alignment, T1> {
        typedef char type;
    };

    //***************************************************************************
    // Helper.
    //***************************************************************************
    template <size_t Alignment, typename T1, typename... T>
    struct type_with_alignment_helper {
        typedef typename type_with_alignment_matcher<Alignment <= std::alignment_of<T1>::value, Alignment, T1, T...>::type type;
    };
}

//***************************************************************************
/// Gets a type that has the same as the specified alignment.
///\ingroup alignment
//***************************************************************************
template <size_t Alignment>
struct type_with_alignment {
    typedef struct { alignas(Alignment) char dummy; } type;
    static_assert(std::alignment_of<type>::value == Alignment && "Unable to create the type with the specified alignment");
};
