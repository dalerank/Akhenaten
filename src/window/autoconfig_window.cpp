#include "autoconfig_window.h"

#include "core/log.h"
#include "js/js_game.h"
#include "window/message_dialog.h"
#include <mutex>

using autoconfig_windows = std::vector<autoconfig_window *>;
autoconfig_windows* g_autoconfig_windows = nullptr;

autoconfig_windows& autoconfig_registry() {
    if (!g_autoconfig_windows) {
        static std::mutex registry_locker;

        std::scoped_lock _(registry_locker);
        if (!g_autoconfig_windows) {
            g_autoconfig_windows = new std::vector<autoconfig_window *>;
        }
    }

    return *g_autoconfig_windows;
}

void ANK_REGISTER_CONFIG_ITERATOR(config_load_autoconfig_windows) {
    for (auto *w : autoconfig_registry()) {
        w->load(w->get_section());
    }
}


void autoconfig_window::refresh_all() {
    config_load_autoconfig_windows();
}

autoconfig_window::autoconfig_window(pcstr s) {
    assert(!strstr(s, "::"));
    logs::info("Registered window config:%s", s);
    autoconfig_registry().push_back(this);
}

void autoconfig_window::archive_load(archive arch) {
    ui::widget::archive_load(arch);

    assert(elements.size() > 0);
    _is_inited = false;
    help_id = arch.r_string("help_id");
}

int autoconfig_window::ui_handle_mouse(const mouse *m) {
    ui.begin_widget(pos);
    int result = ui::handle_mouse(m);
    ui.end_widget();

    return result;
}

void autoconfig_window::before_mission_start() {
    for (auto *w : autoconfig_registry()) {
        w->on_mission_start();
    }
}

int autoconfig_window::draw_background(UiFlags flags) {
    if (!_is_inited) {
        init();
        _is_inited = true;
    }
    return 0;
}

void autoconfig_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

void autoconfig_window::init() {
    window_message_setup_help_id(help_id);
    _is_inited = true;
}
