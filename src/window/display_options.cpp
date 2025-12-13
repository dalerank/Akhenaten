#include "display_options.h"

#include "file_dialog.h"

#include <cassert>

#include "core/app.h"
#include "core/calc.h"
#include "core/encoding.h"
#include "core/string.h"
#include "game/settings.h"
#include "input/input.h"
#include "graphics/screen.h"
#include "graphics/graphics.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "platform/renderer.h"

ui::display_options_window g_display_options_window;

void ui::display_options_window::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);
}

void ui::display_options_window::init(close_callback close_cb) {
    autoconfig_window::init();

    _close_cb = close_cb;

    auto wsize = g_settings.display_size;
    original_resolution = wsize;
    selected_resolution = wsize;
    video_mode selected(wsize.x, wsize.y);

    auto resolutions = ui["resolutions"].dcast_scrollable_list();
    if (resolutions) {
        resolutions->clear();
        resolutions->onrefill([] (std::vector<xstring>& r) {
            auto video_modes = get_video_modes();
            for (const auto &mode : video_modes) {
                r.push_back(mode.str.c_str());
            }            
        });

        resolutions->select_entry(selected.str.c_str());
        resolutions->onclick_item([this] (int selected_idx, int) {
            auto video_modes = get_video_modes();
            auto it = video_modes.begin();
            std::advance(it, selected_idx);
            selected_resolution = { it->x, it->y };
        });
    }

    ui["btnok"].onclick([this] {
        app_window_resize(selected_resolution);
        _close_cb();
    });

    ui["btncancel"].onclick([this] {
        _close_cb();
    });

    bstring128 videoriver("Video: ", get_video_driver().c_str());
    ui["videodriver"] = videoriver;

    ui["btnfullscreen"] = ui::str(42, g_settings.is_fullscreen(e_setting_none) ? 2 : 1);
    ui["btnfullscreen"].onclick([this] {
        app_fullscreen(!g_settings.is_fullscreen(e_setting_none));
        _close_cb();
    });

    ui_scope_property scope;
    ui.format_all(&scope);
}

void ui::display_options_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);    
    ui.draw();
    ui.end_widget();
}

int ui::display_options_window::ui_handle_mouse(const mouse* m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        _close_cb();
    }

    return result;
}

void ui::display_options_window::show(close_callback close_cb) {
    static window_type instance = {
        WINDOW_FILE_DIALOG,
        window_draw_underlying_window,
        [] (int) { g_display_options_window.ui_draw_foreground(0); },
        [] (const mouse *m, const hotkeys *h) { g_display_options_window.ui_handle_mouse(m); }
    };

    g_display_options_window.init(close_cb);
    window_show(&instance);
}