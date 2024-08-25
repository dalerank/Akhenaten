#include "display_options.h"

#include "file_dialog.h"

#include <cassert>

#include "core/app.h"
#include "core/calc.h"
#include "core/encoding.h"
#include "core/string.h"
#include "core/time.h"
#include "game/settings.h"
#include "graphics/screen.h"
#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "platform/renderer.h"

constexpr uint32_t NUM_FILES_IN_VIEW = 13;

ui::window_display_options ui::window_display_options::window;

void ui::window_display_options::init(close_callback close_cb) {
    if (!panel) {
        scrollable_list_ui_params ui_params;
        ui_params.x = 144;
        ui_params.y = 100;
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
}

void ui::window_display_options::draw_foreground() {
    graphics_set_to_dialog();
    outer_panel_draw({128, 40}, 24, 21);

    // title
    lang_text_draw_centered(e_text_display_options, 0, 160, 50, 304, FONT_LARGE_BLACK_ON_LIGHT);
    lang_text_draw(e_text_saving_dialog, 5, 224, 342, FONT_NORMAL_BLACK_ON_LIGHT);

    panel->draw();
    graphics_reset_dialog();

    ui::begin_widget(screen_dialog_offset());
    pcstr fullscreen_text = (pcstr)lang_get_string(42, g_settings.is_fullscreen(e_setting_none) ? 2 : 1);
    ui::button(fullscreen_text, {148, 76}, {224, 20})
        .onclick([this] (int, int) {
            app_fullscreen(!g_settings.is_fullscreen(e_setting_none));
            _close_cb();
        });

    ui::imgok_button({344, 335}, [this] (int, int) {
        app_window_resize(selected_resolution);
        _close_cb();
    });

    ui::imgcancel_button({392, 335}, [this] (int, int) {
        _close_cb();
    });

    ui::end_widget();
}

void ui::window_display_options::handle_input(const mouse* m, const hotkeys* h) {
    bool button_id = ui::handle_mouse(m);

    const mouse* m_dialog = mouse_in_dialog(m);
    if (panel->input_handle(m_dialog)) {
        auto it = video_modes.begin();
        std::advance(it, panel->get_selected_entry_idx());
        selected_resolution = {it->x, it->y};
    }
}

void ui::window_display_options::show(close_callback close_cb) {
    static window_type instance = {
        WINDOW_FILE_DIALOG,
        window_draw_underlying_window,
        [] { window.draw_foreground(); },
        [] (const mouse *m, const hotkeys *h) { window.handle_input(m, h); }
    };

    init(close_cb);
    window_show(&instance);
}