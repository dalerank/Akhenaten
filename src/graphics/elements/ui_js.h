#pragma once

#include "core/typename.h"
#include "js/js_struct.h"
#include "js/js_game.h"

namespace ui {
    template<typename T>
    inline void widget::event(xstring evname_str, const T &ev) {
        bvariant_map::scoped js_j;
        js_helper::writer(*js_j, ev);
        event(evname_str, *js_j);
    }

    template<typename T>
    inline void widget::event(const T &ev) {
        type_name_holder<T> evname;
        xstring evname_str(type_simplified_name(evname.value.data()));
        widget::event(evname_str, ev);
    }

    template<typename T>
    inline void event(xstring evname_str, const T &ev) {
        bvariant_map::scoped js_j;
        js_helper::writer(*js_j, ev);
        js_call_event_handlers(evname_str, *js_j);
    }

    template<typename T>
    inline void event(const T &ev) {
        type_name_holder<T> evname;
        xstring evname_str(type_simplified_name(evname.value.data()));
        ui::event(evname_str, ev);
    }
}