#pragma once

#include "core/variant.h"
#include "core/xstring.h"
#include "core/typename.h"
#include "core/hvector.h"
#include "graphics/elements/ui.h"
#include "js/js_struct.h"

struct window_info{ vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(window_info, pos);

struct autoconfig_window : public ui::widget {
    autoconfig_window(xstring s);

    virtual int handle_mouse(const mouse *m) = 0;
    virtual int draw_background(UiFlags flags);
    virtual void draw_foreground(UiFlags flags) = 0;
    virtual void ui_draw_foreground(UiFlags flags);
    virtual int get_tooltip_text() = 0;
    virtual void init();
    virtual void on_mission_start() {}
    virtual void on_restore();
    virtual bool is_modal() const { return false; }

    virtual void archive_load(archive arch) override;
    virtual int ui_handle_mouse(const mouse *m);
    virtual void go_back();

    void enqueue_event(xstring sub_event, bvariant_map payload);
    void fire_pending_events();

    bool _is_inited = false;
    bool allow_rmb_goback = false;
    bool draw_underlying = false;
    // While on screen, screen-size changes do not re-run the ui_* scripts (which would rebuild this
    // window and drop its unsaved state); the window keeps itself centred instead.
    bool defer_relayout = false;
    xstring help_id;

    struct deferred_event {
        xstring sub_event;
        bvariant_map payload;
    };
    hvector<deferred_event, 8> pending_events_;

    static void before_mission_start();
    static void refresh_all();
    static bool defers_relayout(xstring section);
    static void show(xstring section);
    static autoconfig_window* find(xstring section);
    static void unregister_section(xstring section);
};

template<typename T>
struct autoconfig_window_t : public autoconfig_window {
    virtual xstring section() const override {
        static type_name_holder<T> _impl;
        static xstring _section = type_simplified_name(_impl.value.data());
        return _section;
    }

    inline autoconfig_window_t() : autoconfig_window(section()) {
    }
};