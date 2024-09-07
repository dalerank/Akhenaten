#include "autoconfig_window.h"

#include "core/log.h"
#include "js/js_game.h"

std::vector<autoconfig_window *> g_advisor_windows;

ANK_REGISTER_CONFIG_ITERATOR(config_load_advisor_windows);
void config_load_advisor_windows() {
    for (auto *w : g_advisor_windows) {
        w->load(w->get_section());
    }
}

void register_autoconfig_window(autoconfig_window *w) {
    g_advisor_windows.push_back(w);
}

autoconfig_window::autoconfig_window(pcstr s) {
    assert(!strstr(s, "::"));
    logs::info("Registered window config:%s", s);
    register_autoconfig_window(this);
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

void autoconfig_window::ui_draw_foreground() {
    ui.begin_widget(pos);
    ui.draw();
    ui.end_widget();
}
