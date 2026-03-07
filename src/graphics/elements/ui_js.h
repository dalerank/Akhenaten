#pragma once

#include "core/typename.h"
#include "js/js_struct.h"
#include "js/js_game.h"

namespace ui {
    template<typename T>
    inline void widget::event(const T &ev, xstring evname_str) {
        bvariant_map::scoped js_j;
        js_helper::writer(*js_j, ev);
        widget::event(evname_str, *js_j);
    }

    template<typename T>
    inline void widget::event(const T &ev) {
        type_name_holder<T> evname;
        xstring evname_str(type_simplified_name(evname.value.data()));
        widget::event(ev, evname_str);
    }

    template<typename T, typename ... ES>
    inline void widget::event(const T &ev, ES ... es) {
        xstring evname_str = js_helpers::es_hash_str(es...).c_str();
        widget::event(ev, evname_str);
    }

    template<typename T>
    inline void event(const T &ev, xstring evname_str) {
        bvariant_map::scoped js_j;
        js_helper::writer(*js_j, ev);
        js_call_event_handlers(evname_str, *js_j);
    }

    template<typename T, typename ... ES>
    inline void event(const T &ev, ES ... es) {
        xstring evname_str = js_helpers::es_hash_str(es...).c_str();
        ui::event(ev, evname_str);
    }

    template<typename T>
    inline void event(const T &ev) {
        type_name_holder<T> evname;
        xstring evname_str(type_simplified_name(evname.value.data()));
        ui::event(ev, evname_str);
    }
}