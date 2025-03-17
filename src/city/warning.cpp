#include "warning.h"

#include "core/string.h"
#include "game/settings.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "graphics/elements/lang_text.h"

#define MAX_WARNINGS 5
#define TIMEOUT_MS 15000

struct warning {
    int in_use;
    time_millis time;
    xstring text;
};

warning g_warnings[MAX_WARNINGS];

static struct warning* new_warning(void) {
    for (int i = 0; i < MAX_WARNINGS; i++) {
        if (!g_warnings[i].in_use)
            return &g_warnings[i];
    }
    return 0;
}

void city_warning_show_custom(const char *text) {
    if (!g_settings.warnings) {
        return;
    }
    warning* w = new_warning();
    if (!w) {
        return;
    }
    w->in_use = 1;
    w->time = time_get_millis();

    w->text = text;
}

void city_warning_show(pcstr type) {
    xstring text = lang_text_from_key(type);
    city_warning_show_custom(text.c_str());
}

int city_has_warnings() {
    for (int i = 0; i < MAX_WARNINGS; i++) {
        if (g_warnings[i].in_use)
            return 1;
    }
    return 0;
}

pcstr city_warning_get(int id) {
    if (g_warnings[id].in_use)
        return g_warnings[id].text.c_str();

    return 0;
}

void city_warning_clear_all() {
    for (int i = 0; i < MAX_WARNINGS; i++) {
        g_warnings[i].in_use = 0;
    }
}

void city_warning_clear_outdated() {
    for (int i = 0; i < MAX_WARNINGS; i++) {
        if (g_warnings[i].in_use && time_get_millis() - g_warnings[i].time > TIMEOUT_MS) {
            g_warnings[i].in_use = 0;
        }
    }
}

void city_warning_show_console(pcstr warning_text) {
    struct warning* w = new_warning();
    if (!w) {
        return;
    }
    w->in_use = 1;
    w->time = time_get_millis();
    w->text = warning_text;
}