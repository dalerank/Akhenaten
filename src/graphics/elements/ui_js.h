#pragma once

#include "core/typename.h"
#include "js/js_struct.h"

namespace ui {

    template<typename T>
    inline void widget::event(const T &ev) {
        type_name_holder<T> evname;
        pcstr evname_str = type_simplified_name(evname.value.data());
        bvariant_map js_j;
        js_helper::writer(js_j, ev);
        event(evname_str, js_j);
    }

}