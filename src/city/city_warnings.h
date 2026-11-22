#pragma once

#include "core/bstring.h"
#include "core/svector.h"
#include "core/xstring.h"

struct event_construction_warning { xstring id; };
struct event_city_warning { xstring id; };
struct event_city_warning_text {
    xstring text;
};
struct event_city_message_banner {
    xstring text;
    int message_sequence = -1;
};
struct event_city_console_text {
    xstring text;
};

inline void describe_into(bstring256 &s, const event_city_warning &ev) {
    s.printf("city_warning %s", ev.id.c_str());
}

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
