#pragma once

#include "core/xstring.h"
#include "core/typename.h"
#include "graphics/elements/ui.h"

struct autoconfig_window : public ui::widget {
    autoconfig_window(pcstr s);

    virtual int handle_mouse(const mouse *m) = 0;
    virtual int draw_background() = 0;
    virtual void draw_foreground() = 0;
    virtual void ui_draw_foreground();
    virtual int get_tooltip_text() = 0;
    virtual void init() = 0;
    virtual pcstr get_section() const = 0;

    using ui::widget::load;
    virtual void load(archive arch, pcstr section = "ui") override;
    virtual int ui_handle_mouse(const mouse *m);
};

template<typename T>
struct autoconfig_window_t : public autoconfig_window {
    inline pcstr section() const { 
        static type_name_holder<T> _impl;
        static pcstr _section = strstr(_impl.value.data(), "::") ? strstr(_impl.value.data(), "::") + 2 
                                : strstr(_impl.value.data(), "struct ") ? strstr(_impl.value.data(), "struct ") + 7
                                : _impl.value.data();
        return _section;
    }

    inline autoconfig_window_t() : autoconfig_window(section()) {
    }

    virtual pcstr get_section() const override { return section(); }
};
