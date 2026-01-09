#pragma once

#include "window/window_advisors.h"
#include "graphics/elements/ui.h"

namespace ui {
    struct advisor_health_window : public advisor_window_t<advisor_health_window> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override;
        virtual void init() override {}

        static advisor_window *instance();
    };
}
