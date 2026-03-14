#include "autoconfig_window.h"

#include "core/log.h"
#include "js/js_game.h"
#include "window/message_dialog.h"
#include "core/profiler.h"
#include "graphics/elements/ui_js.h"
#include "js/js_struct.h"
#include "graphics/window.h"
#include "input/input.h"
#include <algorithm>
#include <mutex>
#include <map>

using autoconfig_windows = std::map<xstring, autoconfig_window *>;
autoconfig_windows* g_autoconfig_windows = nullptr;

struct window_info{ vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(window_info, pos);

autoconfig_windows& autoconfig_registry() {
    if (!g_autoconfig_windows) {
        static std::mutex registry_locker;

        std::scoped_lock _(registry_locker);
        if (!g_autoconfig_windows) {
            g_autoconfig_windows = new autoconfig_windows;
        }
    }

    return *g_autoconfig_windows;
}

void ANK_REGISTER_CONFIG_ITERATOR(config_load_autoconfig_windows) {
    for (auto& w : autoconfig_registry()) {
        w.second->load(w.second->get_section());
    }
}

void autoconfig_window::refresh_all() {
    config_load_autoconfig_windows();
}

autoconfig_window::autoconfig_window(pcstr s) {
    assert(!strstr(s, "::"));
    logs::info("Registered window config:%s", s);
    autoconfig_registry()[s] = this;
}

void autoconfig_window::archive_load(archive arch) {
    ui::widget::archive_load(arch);

    assert(elements.size() > 0);
    _is_inited = false;
    help_id = arch.r_string("help_id");
    allow_rmb_goback = arch.r_string("allow_rmb_goback");
}

int autoconfig_window::ui_handle_mouse(const mouse *m) {
    ui.begin_widget(pos);
    bool handled = ui::handle_mouse(m);

    if (allow_rmb_goback && !handled) {
        const hotkeys *h = hotkey_state();
        if (input_go_back_requested(m, h)) {
            window_go_back();
            ui.end_widget();
            return 0;
        }
    }

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        ui.event(window_info{ pos }, get_section(), "go_back");
    }

    ui.end_widget();

    return handled ? 1 : 0;
}

void autoconfig_window::before_mission_start() {
    for (auto& w : autoconfig_registry()) {
        w.second->on_mission_start();
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
    OZZY_PROFILER_FUNCTION();

    ui.begin_widget(pos);
    ui.draw(flags);
    ui.event(window_info{ pos }, get_section(), __func__);
    ui.end_widget();
}

void autoconfig_window::init() {
    ui.event(window_info{ pos }, get_section(), __func__);

    window_message_setup_help_id(help_id);
    _is_inited = true;
}

void autoconfig_window::show_by_section(pcstr section) {
    auto it = autoconfig_registry().find(section);
    if (it == autoconfig_registry().end()) {
        logs::error("autoconfig_window_show: unknown section '%s'", section);
        return;
    }
    autoconfig_window* w = it->second;
    static autoconfig_window* s_current = nullptr;
    static window_type s_type = {
        WINDOW_GAME_SELECTION,
        [] (int flags) { if (s_current) s_current->draw_background(flags); },
        [] (int flags) { if (s_current) s_current->ui_draw_foreground(flags); },
        [] (const mouse* m, const hotkeys* h) { if (s_current) s_current->ui_handle_mouse(m); }
    };
    s_current = w;
    w->init();
    window_show(&s_type);
}

void autoconfig_window::unregister_section(pcstr section) {
    autoconfig_registry().erase(section);
}
