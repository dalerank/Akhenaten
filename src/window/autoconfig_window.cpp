#include "autoconfig_window.h"

#include "core/log.h"
#include "js/js_game.h"

std::vector<autoconfig_window *> g_advisor_windows;

ANK_REGISTER_CONFIG_ITERATOR(config_load_advisor_windows);
void config_load_advisor_windows() {
    for (auto *w : g_advisor_windows) {
        w->load(w->section.c_str());
    }
}

void register_autoconfig_window(autoconfig_window *w) {
    g_advisor_windows.push_back(w);
}

autoconfig_window::autoconfig_window(pcstr s) {
    bstring128 c(s);
    pcstr colonstr = strstr(c, "::");
    if (colonstr) { // avoid namespace
        c = colonstr + 2;
    }
    char *nstr = strstr(c, "\n");
    if (nstr) { // avoid last symbol
        *nstr = '\0';
    }
    section = c;
    logs::info("Registered window config:%s", s);
    register_autoconfig_window(this);
}

void autoconfig_window::load(archive arch, pcstr section) {
    ui::widget::load(arch, section);
}

int autoconfig_window::ui_handle_mouse(const mouse *m) {
    return ui::handle_mouse(m);
}
