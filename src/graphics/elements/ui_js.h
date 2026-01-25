#pragma once

#include "core/typename.h"
#include "js/js_struct.h"

namespace ui {

    template<typename T>
    inline void widget::event(const T &ev) {
        type_name_holder<T> evname;
        pcstr evname_str = type_simplified_name(evname.value.data());
        auto js_j = bvariant_map::acquire_from_pool();        
        js_helper::writer(*js_j, ev);
        event(evname_str, *js_j);
        bvariant_map::return_to_pool(js_j);
    }

}