#pragma once

#include "core/xvalue.h"

struct crash_hooks_t {
    bool (*dialog_allowed)() = nullptr;
    void (*show_message)(const char* title, const char* message) = nullptr;
};

inline crash_hooks_t& crash_hooks() {
    return xvalue<crash_hooks_t>::ref();
}
