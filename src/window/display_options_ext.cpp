#include "display_options.h"

#include "file_dialog.h"

#include <cassert>

#include "core/app.h"
#include "core/calc.h"
#include "core/encoding.h"
#include "core/string.h"
#include "core/time.h"
#include "game/settings.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "platform/renderer.h"

static const time_millis NOT_EXIST_MESSAGE_TIMEOUT = 500;

static void button_fullscreen(int param1, int param2);
static void button_ok_cancel(int is_ok, int param2);
static void on_scroll(void);

static generic_button buttons[] = {
  {148, 80, 224, 20, button_fullscreen, button_none, 1, 0},
};

static image_button image_buttons[] = {
  {344, 335, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 0, button_ok_cancel, button_none, 1, 0, 1},
  {392, 335, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 4, button_ok_cancel, button_none, 0, 0, 1},
};

constexpr uint32_t NUM_FILES_IN_VIEW = 13;

static scrollable_list_ui_params ui_params = [] {
    scrollable_list_ui_params ret;
    ret.x = 144;
    ret.y = 100;
    ret.blocks_x = 20;
    ret.blocks_y = NUM_FILES_IN_VIEW + 1;
    ret.draw_scrollbar_always = true;
    return ret;
}();

struct display_options_ext_t {
    int focus_button_id;

    void (*close_callback)(void);
    vec2i original_resolution;
    vec2i selected_resolution;
    scroll_list_panel* panel = nullptr;
    std::vector<video_mode> video_modes;
};

display_options_ext_t g_display_options_ext;

static void init(void (*close_callback)(void)) {
    auto& data = g_display_options_ext;

    // populate resoltuion list
    g_display_options_ext.focus_button_id = 0;
    g_display_options_ext.close_callback = close_callback;

    data.panel->clear_entry_list();
    data.video_modes = get_video_modes();
    for (const auto& mode : data.video_modes) {
        data.panel->add_entry(mode.str);
    }

    auto wsize = g_settings.display_size;
    data.original_resolution = {wsize.x, wsize.y};
    data.selected_resolution = {wsize.x, wsize.y};

    video_mode selected(wsize.x, wsize.y);
    data.panel->select(selected.str);
}

static void button_fullscreen(int param1, int param2) {
    app_fullscreen(!g_settings.is_fullscreen());
    g_display_options_ext.close_callback();
}

static void draw_foreground() {
    auto& data = g_display_options_ext;
    graphics_set_to_dialog();
    outer_panel_draw(vec2i{128, 40}, 24, 21);

    // title
    lang_text_draw_centered(e_text_display_options, 0, 160, 50, 304, FONT_LARGE_BLACK_ON_LIGHT);
    lang_text_draw(e_text_saving_dialog, 5, 224, 342, FONT_NORMAL_BLACK_ON_LIGHT);

    data.panel->draw();

    label_draw(148, 76, 14, data.focus_button_id == 1 ? 1 : 2);
    lang_text_draw_centered(42, g_settings.is_fullscreen() ? 2 : 1, 148, 80, 224, FONT_NORMAL_BLACK_ON_DARK);

    image_buttons_draw(0, 0, image_buttons, 2);

    graphics_reset_dialog();
}

static void button_ok_cancel(int is_ok, int param2) {
    auto& data = g_display_options_ext;

    if (is_ok) {
        app_window_resize({data.selected_resolution.x, data.selected_resolution.y});
    }
    data.close_callback();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_display_options_ext;

    if (generic_buttons_handle_mouse(mouse_in_dialog(m), 0, 0, buttons, std::size(buttons), &data.focus_button_id)) {
        return;
    }

    const mouse* m_dialog = mouse_in_dialog(m);
    if (data.panel->input_handle(m_dialog)) {
        auto it = data.video_modes.begin();
        std::advance(it, data.panel->get_selected_entry_idx());
        data.selected_resolution = {it->x, it->y};
    }

    if (image_buttons_handle_mouse(m_dialog, 0, 0, image_buttons, 2, 0)) {
        return;
    }
}

void window_display_options_ext_show(void (*close_callback)(void)) {
    if (!g_display_options_ext.panel) {
        g_display_options_ext.panel = new scroll_list_panel(
          NUM_FILES_IN_VIEW, button_none, button_none, button_none, button_none, ui_params, false, "", "");
    }

    window_type window = {WINDOW_FILE_DIALOG, window_draw_underlying_window, draw_foreground, handle_input};

    init(close_callback);
    window_show(&window);
}