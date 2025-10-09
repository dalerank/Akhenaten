#pragma once

#include "window/autoconfig_window.h"

struct event_construction_warning { xstring id; };
struct event_city_warning { xstring id; };

struct window_warnings : autoconfig_window_t<window_warnings> {
    struct warning {
        time_millis time;
        xstring text;
    };

    svector<warning, 16> warnings;
    bool has_warning = false;
    int max_items = 5;
    int timeout_ms = 15000;
    int top_offset = 30;
    int message_width = 25;

    void on_mission_start() override;
    void show(pcstr type);
    void show_custom(pcstr text);
    bool has_warnings();
    pcstr get_warning(int id);
    void clear_all();
    void clear_outdated();
    void show_console(pcstr warning_text);
    int determine_width(pcstr text);
    virtual int get_tooltip_text() override { return 0; }
    virtual int handle_mouse(const mouse *m) override;
    virtual void draw_foreground(UiFlags flags) override;
    virtual void archive_load(archive arch) override;

    template<typename ... Args>
    void show_console_var(pcstr fmt, Args... args) {
        bstring1024 buffer;
        buffer.printf(fmt, args...);
        show_console(buffer);
    }

    warning *new_warning();
};

struct city_warnings {
    svector<xstring, 8> warnings;

    template<typename... Args>
    city_warnings(Args... args) : warnings{args...} {}

    ~city_warnings();

    void add(xstring id) {
        warnings.push_back(id);
    }

    void add_if(bool condition, xstring id) {
        if (condition) {
            add(id);
        }
    }
};

using construction_warnings = city_warnings;

extern window_warnings g_warning_manager;
