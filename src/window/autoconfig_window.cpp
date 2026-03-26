#include "autoconfig_window.h"

#include "core/log.h"
#include "js/js_game.h"
#include "game/game_events.h"
#include "window/message_dialog.h"
#include "core/profiler.h"
#include "graphics/elements/ui_js.h"
#include "graphics/window.h"
#include "js/js_struct.h"
#include "js/js_events.h"
#include "input/input.h"
#include "input/mouse.h"
#include <algorithm>
#include <unordered_map>
#include <mutex>

using autoconfig_windows = std::unordered_map<xstring, autoconfig_window *>;
autoconfig_windows* g_autoconfig_windows = nullptr;

struct window_info{ vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(window_info, pos);

struct event_show_window { xstring id; };
ANK_SCRIPT_EVENT(event_show_window, id)
void ANK_PERMANENT_CALLBACK(event_show_window, ev) {
    autoconfig_window::show(ev.id);
}

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

autoconfig_window::autoconfig_window(xstring s) {
    assert(!strstr(s.c_str(), "::"));
    logs::info("Registered window config:%s", s.c_str());
    autoconfig_registry()[s] = this;
}

void autoconfig_window::on_restore() {
    ui.begin_widget(pos);
    ui.event(window_info{ pos }, get_section(), __func__);
    ui.end_widget();
}

void autoconfig_window::archive_load(archive arch) {
    ui::widget::archive_load(arch);

    assert(elements.size() > 0);
    _is_inited = false;
    help_id = arch.r_string("help_id");
    allow_rmb_goback = arch.r_bool("allow_rmb_goback");
    draw_underlying = arch.r_bool("draw_underlying", false);
}

int autoconfig_window::ui_handle_mouse(const mouse *m) {
    ui.begin_widget(pos);
    bool handled = ui::handle_mouse(m);

    if (allow_rmb_goback && (is_modal() || !handled)) {
        const hotkeys *h = hotkey_state();
        if (input_go_back_requested(m, h)) {
            window_go_back();
            ui.end_widget();
            return 1;
        }
    }

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        ui.event(window_info{ pos }, get_section(), "go_back");
    }

    ui.end_widget();

    if (is_modal()) {
        mouse::ref().reset_up_state();
        mouse::ref().reset_scroll();
        return 1;
    }

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

    if (draw_underlying) {
        window_draw_underlying_window(UiFlags_Readonly);
    }

    ui.begin_widget(pos);
    ui.draw(flags);
    ui.event(window_info{ pos }, get_section(), __func__);
    ui.end_widget();
}

void autoconfig_window::init() {
    ui.begin_widget(pos);
    ui.event(window_info{ pos }, get_section(), __func__);

    window_message_setup_help_id(help_id);
    _is_inited = true;
    ui.end_widget();
}

static autoconfig_window* get_window_current(xstring name) {
    auto it = autoconfig_registry().find(name);
    return (it != autoconfig_registry().end()) ? it->second : nullptr;
}

void autoconfig_window::show(xstring section) {
    auto it = autoconfig_registry().find(section);
    if (it == autoconfig_registry().end()) {
        logs::error("autoconfig_window_show: unknown section '%s'", section.c_str());
        return;
    }
    autoconfig_window* w = it->second;
    window_type s_script_window_type = {
       section,
       [section] (int flags) { auto *w = get_window_current(section); if (w) w->draw_background(flags); },
       [section] (int flags) { auto *w = get_window_current(section); if (w) w->ui_draw_foreground(flags); },
       [section] (const mouse *m, const hotkeys *h) { auto *w = get_window_current(section); if (w) w->ui_handle_mouse(m); }
    };
    w->init();
    window_show(&s_script_window_type);
}

void autoconfig_window::unregister_section(xstring section) {
    autoconfig_registry().erase(section);
}