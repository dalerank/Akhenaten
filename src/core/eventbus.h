#pragma once

#include "events/eventqueue.h"
#include "events/anyid.h"
#include "events/anydata.h"
#include <typeindex>

namespace events {

    template <typename T>
    struct TypeIndexDigesterCpp11 {
        template <typename U>
        auto operator() (const U &) const
            -> typename std::enable_if<!std::is_same<U, std::type_info>::value, std::type_index>::type {
            return std::type_index(typeid(T));
        }

        template <typename U>
        auto operator() (const U &typeInfo) const
            -> typename std::enable_if<std::is_same<U, std::type_info>::value, std::type_index>::type {
            return std::type_index(typeInfo);
        }
    };

    constexpr std::size_t eventMaxSize = 128;
    using typed_queue = eventpp::EventQueue<
        eventpp::AnyId<TypeIndexDigesterCpp11>,
        void(const eventpp::AnyData<eventMaxSize> &)
    >;

}