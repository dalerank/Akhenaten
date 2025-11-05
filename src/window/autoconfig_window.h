#pragma once

#include "core/xstring.h"
#include "core/typename.h"
#include "graphics/elements/ui.h"

struct autoconfig_window : public ui::widget {
    autoconfig_window(pcstr s);

    virtual int handle_mouse(const mouse *m) = 0;
    virtual int draw_background(UiFlags flags);
    virtual void draw_foreground(UiFlags flags) = 0;
    virtual void ui_draw_foreground(UiFlags flags);
    virtual int get_tooltip_text() = 0;
    virtual void init();
    virtual pcstr get_section() const { return "non_exist_window"; };
    virtual void on_mission_start() {}

    virtual void archive_load(archive arch) override;
    virtual int ui_handle_mouse(const mouse *m);

    bool _is_inited = false;
    xstring help_id;

    static void before_mission_start();
    static void refresh_all();
};

template<typename T>
struct autoconfig_window_t : public autoconfig_window {
    inline pcstr section() const { 
        static type_name_holder<T> _impl;
        static pcstr _section = type_simplified_name(_impl.value.data());
        return _section;
    }

    inline autoconfig_window_t() : autoconfig_window(section()) {
    }

    virtual pcstr get_section() const override { return section(); }
};