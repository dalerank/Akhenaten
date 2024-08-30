#pragma once

#include "core/xstring.h"
#include "graphics/elements/ui.h"

struct autoconfig_window : public ui::widget {
    xstring section;

    inline autoconfig_window(pcstr s);

    virtual int handle_mouse(const mouse *m) = 0;
    virtual int draw_background() = 0;
    virtual void draw_foreground() = 0;
    virtual void ui_draw_foreground() {}
    virtual int get_tooltip_text() = 0;
    virtual void init() = 0;

    using ui::widget::load;
    virtual void load(archive arch, pcstr section = "ui") override;
    virtual int ui_handle_mouse(const mouse *m);
};
