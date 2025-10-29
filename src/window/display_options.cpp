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

constexpr uint32_t NUM_FILES_IN_VIEW = 13;

ui::display_options_window g_display_options_window;

void ui::display_options_window::init(close_callback close_cb) {
    if (!panel) {
        scrollable_list_ui_params ui_params;
        ui_params.blocks_x = 20;
        ui_params.blocks_y = NUM_FILES_IN_VIEW + 1;
        ui_params.draw_scrollbar_always = true;

        panel = new scroll_list_panel(NUM_FILES_IN_VIEW, 
                                      button_none, 
                                      button_none, 
                                      button_none, 
                                      button_none, 
                                      ui_params, false, "", "");
    }

    focus_button_id = 0;
    _close_cb = close_cb;

    panel->clear_entry_list();
    video_modes = get_video_modes();
    for (const auto& mode : video_modes) {
        panel->add_entry(mode.str);
    }

    auto wsize = g_settings.display_size;
    original_resolution = wsize;
    selected_resolution = wsize;

    video_mode selected(wsize.x, wsize.y);
    panel->select(selected.str);

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
}

void ui::display_options_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    
    ui.draw();

    panel->ui_params.pos = ui["resolutions"].screen_pos();
    panel->draw();

    ui.end_widget();
}

int ui::display_options_window::ui_handle_mouse(const mouse* m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    ui.begin_widget(pos);
    vec2i scrpos = ui["background"].screen_pos();
    mouse m_dialog = *m;
    m_dialog.x -= (scrpos.x + ui["background"].pos.x);
    m_dialog.y -= (scrpos.y + ui["background"].pos.y);
    if (panel->input_handle(&m_dialog)) {
        auto it = video_modes.begin();
        std::advance(it, panel->get_selected_entry_idx());
        selected_resolution = {it->x, it->y};
    }
    ui.end_widget();

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