#pragma once

#include "input/mouse.h"
#include "core/string.h"
#include "core/vec2i.h"

void button_none(int param1, int param2);

void button_border_draw(int x, int y, int width_pixels, int height_pixels, bool has_focus);
inline void button_border_draw(vec2i pos, vec2i size, bool has_focus) { button_border_draw(pos.x, pos.y, size.x, size.y, has_focus); }

template<class T>
bool is_button_hover(const T &button, vec2i context) {
    const mouse *m = mouse_get();
    vec2i bpos = context + button.pos();
    vec2i bsize = button.size();

    if (!graphics_inside_clip_rectangle(*m)) {
        return false;
    }

    return (   bpos.x <= m->x && bpos.x + bsize.x > m->x
            && bpos.y <= m->y && bpos.y + bsize.y > m->y);
}
