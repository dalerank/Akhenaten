#pragma once

#include "core/xstring.h"
#include "core/typename.h"
#include "graphics/elements/ui.h"

struct autoconfig_window : public ui::widget {
    autoconfig_window(xstring s);

    virtual int handle_mouse(const mouse *m) = 0;
    virtual int draw_background(UiFlags flags);
    virtual void draw_foreground(UiFlags flags) = 0;
    virtual void ui_draw_foreground(UiFlags flags);
    virtual int get_tooltip_text() = 0;
    virtual void init();
    virtual xstring get_section() const override { verify_no_crash(false); return "non_exist_window"; };
    virtual void on_mission_start() {}
    virtual void on_restore();

    virtual void archive_load(archive arch) override;
    virtual int ui_handle_mouse(const mouse *m);

    bool _is_inited = false;
    bool allow_rmb_goback = false;
    bool draw_underlying = false;
    xstring help_id;

    static void before_mission_start();
    static void refresh_all();
    static void show(xstring section);
    static void unregister_section(xstring section);
};

template<typename T>
struct autoconfig_window_t : public autoconfig_window {
    inline xstring section() const {
        static type_name_holder<T> _impl;
        static xstring _section = type_simplified_name(_impl.value.data());
        return _section;
    }

    inline autoconfig_window_t() : autoconfig_window(section()) {
    }

    virtual xstring get_section() const override { return section(); }
};