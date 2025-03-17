#pragma once

#include <stdint.h>
#include "core/bstring.h"

void city_warning_show(pcstr type);
void city_warning_show_custom(const char *text);

int city_has_warnings();

pcstr city_warning_get(int i);

void city_warning_clear_all();
void city_warning_clear_outdated();

void city_warning_show_console(pcstr warning_text);

template<typename ... Args>
void city_warning_show_console_var(pcstr fmt, Args... args) {
    bstring1024 buffer;
    buffer.printf(fmt, args...);
    city_warning_show_console(buffer);
}
