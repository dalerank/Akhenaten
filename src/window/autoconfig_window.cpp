#include "autoconfig_window.h"

#include "core/log.h"
#include "js/js_game.h"
#include "window/message_dialog.h"
#include "graphics/window.h"
#include "input/input.h"
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


static void autoconfig_center_window(autoconfig_window *w) {
    if (!w) {
        return;
    }

    // Only recenter windows that have an explicit background element.
    if (!w->contains("background")) {
        return;
    }

    auto &bg = (*w)["background"];
    vec2i bsize = bg.pxsize();
    if (bsize.x <= 0 || bsize.y <= 0) {
        return;
    }

    w->pos.x = (screen_width() - bsize.x) / 2;
    w->pos.y = (screen_height() - bsize.y) / 2;

    // Даем окну шанс обновить свою внутреннюю геометрию (скроллбары и т.п.)
    // после изменения позиции/размера.
    w->on_resolution_changed_instance();
}

void autoconfig_window::refresh_all() {
    config_load_autoconfig_windows();

    // После перезагрузки конфигов сразу рассчитываем позиции окон
    // под текущее разрешение.
    for (auto *w : autoconfig_registry()) {
        autoconfig_center_window(w);
    }
}

void autoconfig_window::on_resolution_changed() {
    for (auto *w : autoconfig_registry()) {
        autoconfig_center_window(w);
    }
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
    allow_rmb_goback = arch.r_string("allow_rmb_goback");

    // При первичной загрузке окна сразу подгоняем его позицию
    // под текущее разрешение, чтобы не зависеть от "жестких"
    // координат из конфигов (рассчитанных под базовое окно).
    autoconfig_center_window(this);
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
    
    ui.end_widget();

    return handled ? 1 : 0;
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
