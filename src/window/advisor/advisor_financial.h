#pragma once

#include "window/advisors.h"
#include "graphics/elements/ui.h"

namespace ui {
struct advisor_financial_window : public advisor_window_t<advisor_financial_window> {
    short row_text_x = 0;
    short row_last_year_x = 0;
    short row_this_year_x = 0;
    short line_start_x = 0;
    short line_size_x = 0;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override;
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override {};
    virtual int draw_background(UiFlags flags) override;
    virtual void init() override {}

    void draw_row(pcstr text, int &y, int value_last_year, int value_this_year);

    virtual void load(archive arch, pcstr section) override;

    static advisor_window *instance();
};
}
