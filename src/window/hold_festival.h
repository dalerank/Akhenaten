#pragma once

#include "graphics/elements/ui.h"

void window_hold_festival_show(void);

namespace ui {
    struct hold_festival_window : public widget {
        int focus_button_id;

        using widget::load;
    };
}
