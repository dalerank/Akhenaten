#pragma once 

#include "core/eventbus.h"
#include "game/game_events_history.h"

extern events::typed_queue g_city_events;
extern events::typed_queue g_permanent_events;

namespace events {
    template<typename T>
    inline void emit(T &&event) {
        g_city_events.enqueue(std::forward<T>(event));
        g_permanent_events.enqueue(std::forward<T>(event));
        events_history::log_event(std::forward<T>(event));
    }

    template<typename T>
    inline void emit_if(const bool expr, T &&event) {
        if (!expr) {
            return;
        }

        emit(std::forward<T>(event));
    }

    template<typename T>
    inline void subscribe(T subscriber) {
        if (g_city_events.contains(subscriber)) {
            return;
        }

        g_city_events.subscribe(subscriber);
    }

    template<typename T>
    inline void subscribe_permanent(T subscriber) {
        if (g_permanent_events.contains(subscriber)) {
            return;
        }

        g_permanent_events.subscribe(subscriber);
    }

    template<typename T>
    inline void subscribe_if(bool expr, T subscriber) {
        if (expr) {
            g_city_events.subscribe(subscriber);
        }
    }

    template<typename T>
    inline void unsubscribe(T subscriber) {
        bool removed = g_city_events.unsubscribe(subscriber);
        removed |= g_permanent_events.unsubscribe(subscriber);
        assert(removed && "Event subscriber not found! This is a bug.");
    }

    inline void process() {
        g_city_events.process();
        g_permanent_events.process();
    }
} // namespace events

#define ANK_PERMANENT_CALLBACK_IMPL(event, a, unique_id)                                                                               \
    tmp_register_permanent_callback_ ##event ##unique_id();                                                                            \
    ANK_DECLARE_CONFIG_ITERATOR(register_permanent_callback_ ##event ##unique_id);                                                     \
    void permanent_callback_ ##event ##unique_id(event a);                                                                             \
    void register_permanent_callback_ ##event ##unique_id() { events::subscribe_permanent(permanent_callback_ ##event ##unique_id ); } \
    void permanent_callback_ ##event ##unique_id(event a)

#define ANK_PERMANENT_CALLBACK_HELPER0(event, a, unique_id) ANK_PERMANENT_CALLBACK_IMPL(event, a, unique_id)
#define ANK_PERMANENT_CALLBACK_HELPER1(event, a, unique_id) ANK_PERMANENT_CALLBACK_HELPER0(event, a, ANK_CONFIG_CC1(unique_id, __COUNTER__))

#define ANK_PERMANENT_CALLBACK(event, a) ANK_PERMANENT_CALLBACK_HELPER1(event, a, __LINE__)