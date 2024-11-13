#include "autoconfig_window.h"

#include "core/log.h"
#include "js/js_game.h"
#include <mutex>

using autoconfig_windows = std::vector<autoconfig_window *>;
autoconfig_windows* g_autoconfig_windows = nullptr;

autoconfig_windows* autoconfig_registry() {
    if (!g_autoconfig_windows) {
        static std::mutex registry_locker;

        std::scoped_lock _(registry_locker);
        if (!g_autoconfig_windows) {
            g_autoconfig_windows = new std::vector<autoconfig_window *>;
        }
    }

    return g_autoconfig_windows;
}

ANK_REGISTER_CONFIG_ITERATOR(config_load_autoconfig_windows);
void config_load_autoconfig_windows() {
    auto *registry = autoconfig_registry();
    for (auto *w : *registry) {
        w->load(w->get_section());
    }
}

autoconfig_window::autoconfig_window(pcstr s) {
    assert(!strstr(s, "::"));
    logs::info("Registered window config:%s", s);
    auto *registry = autoconfig_registry();
    registry->push_back(this);
}

void autoconfig_window::load(archive arch, pcstr section) {
    ui::widget::load(arch, section);
}

int autoconfig_window::ui_handle_mouse(const mouse *m) {
    ui.begin_widget(pos);
    int result = ui::handle_mouse(m);
    ui.end_widget();

    return result;
}

void autoconfig_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}
