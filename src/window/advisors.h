#pragma once

#include "city/constants.h"
#include "graphics/elements/ui.h"
#include "core/typename.h"
#include "core/log.h"
#include "window/autoconfig_window.h"

struct mouse;

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
