#pragma once

#include "building/building.h"

struct event_construction_warning { xstring id; };
struct event_city_warning { xstring id; };

struct city_warning_manager {
    struct warning {
        time_millis time;
        xstring text;
    };

    svector<warning, 5> warnings;
    bool has_warning = false;

    void init();
    void show(pcstr type);
    void show_custom(pcstr text);
    bool has_warnings();
    pcstr get_warning(int id);
    void clear_all();
    void clear_outdated();
    void show_console(pcstr warning_text);
    int determine_width(pcstr text);
    void draw(painter &ctx, bool pause);
    bool handle_mouse(const mouse *m);

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

extern city_warning_manager g_warning_manager;
