#pragma once

#include "input/mouse.h"
#include "core/string.h"
#include "core/vec2i.h"

void button_none(int param1, int param2);
bool button_inside_clip(vec2i);

template<class T>
bool is_button_hover(const T &button, vec2i context) {
    const mouse& m = mouse::get();
    vec2i bpos = context + button.pos();
    vec2i bsize = button.size();

    if (!button_inside_clip(m)) {
        return false;
    }

    return (   bpos.x <= m.x && bpos.x + bsize.x > m.x
            && bpos.y <= m.y && bpos.y + bsize.y > m.y);
}

namespace ui {
    namespace textured {
        void button_border_draw(vec2i pos, vec2i size, bool has_focus);
    }
}

extern void (*button_border_draw)(vec2i, vec2i, bool);

