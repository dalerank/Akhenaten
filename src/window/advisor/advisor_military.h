#pragma once

#include "window/advisors.h"
#include "graphics/elements/ui.h"

namespace ui {
struct advisor_military_window : public advisor_window_t<advisor_military_window> {
    int focus_button_id;

    virtual int handle_mouse(const mouse *m) override;
    virtual int get_tooltip_text() override { return 0; }
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void init() override;

    static advisor_window *instance();
};
}

