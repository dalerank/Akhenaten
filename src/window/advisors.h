#pragma once

#include "city/constants.h"
#include "graphics/elements/ui.h"
#include "core/typename.h"
#include "core/log.h"

struct mouse;
struct autoconfig_window;

void register_autoconfig_window(autoconfig_window *w);

struct autoconfig_window : public ui::widget {
    bstring128 section;

    inline autoconfig_window(pcstr s) : section(s) {
        pcstr colonstr = strstr(section, "::");
        if (colonstr) { // avoid namespace
            section = colonstr + 2;
        }
        char* nstr = strstr(section, "\n");
        if (nstr) { // avoid last symbol
            *nstr = '\0';
        }
        logs::info("Registered window config:%s", s);
        register_autoconfig_window(this);
    }

    virtual int draw_background() = 0;
    virtual void draw_foreground() = 0;
    virtual void ui_draw_foreground() {}
    virtual int handle_mouse(const mouse *m) = 0;
    virtual int get_tooltip_text() = 0;
    virtual void init() = 0;

    using ui::widget::load;

    virtual void load(archive arch, pcstr section = "ui") override {
        ui::widget::load(arch, section);
    }

    virtual int ui_handle_mouse(const mouse *m) {
        return ui::handle_mouse(m);
    }
};

using advisor_window = autoconfig_window;

template<typename T>
struct advisor_window_t : public advisor_window {
    inline advisor_window_t() : advisor_window(type_name<T>().data()) {
    }
};

int window_advisors_get_advisor();
bool is_advisor_available(e_advisor advisor);
void window_advisors_show();
void window_advisors_show_checked();
int window_advisors_show_advisor(e_advisor advisor);
