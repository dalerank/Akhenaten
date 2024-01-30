#include "popup_dialog.h"

#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "input/input.h"

#define GROUP 5

#define PROCEED_GROUP 43
#define PROCEED_TEXT 5

static void button_ok(int param1, int param2);
static void button_cancel(int param1, int param2);
static void confirm(void);

static image_button buttons[] = {
  {192, 100, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 0, button_ok, button_none, 1, 0, 1},
  {256, 100, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 4, button_cancel, button_none, 0, 0, 1},
};

struct popup_dialog_t {
    int popup_text_offset;
    int custom_text_group;
    int custom_text_id;
    int ok_clicked;
    void (*close_func)(bool accepted);
    e_popup_dialog_btns num_buttons;
};

popup_dialog_t g_popup_dialog;

static int init(int type,
                int custom_text_group,
                int custom_text_id,
                void (*close_func)(bool accepted),
                e_popup_dialog_btns buttons) {
    auto& data = g_popup_dialog;
    if (window_is(WINDOW_POPUP_DIALOG)) {
        // don't show popup over popup
        return 0;
    }
    data.popup_text_offset = type;
    data.custom_text_group = custom_text_group;
    data.custom_text_id = custom_text_id;
    data.ok_clicked = 0;
    data.close_func = close_func;
    data.num_buttons = buttons;
    return 1;
}

static void draw_background(void) {
    auto& data = g_popup_dialog;

    window_draw_underlying_window();
    graphics_set_to_dialog();
    outer_panel_draw(vec2i{80, 80}, 30, 10);
    if (data.popup_text_offset >= 0) {
        lang_text_draw_centered(GROUP, data.popup_text_offset, 80, 100, 480, FONT_LARGE_BLACK_ON_LIGHT);
        if (lang_text_get_width(GROUP, data.popup_text_offset + 1, FONT_NORMAL_BLACK_ON_LIGHT) >= 420)
            lang_text_draw_multiline(GROUP, data.popup_text_offset + 1, vec2i{110, 140}, 420, FONT_NORMAL_BLACK_ON_LIGHT);
        else
            lang_text_draw_centered(GROUP, data.popup_text_offset + 1, 80, 140, 480, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(data.custom_text_group, data.custom_text_id, 80, 100, 480, FONT_LARGE_BLACK_ON_LIGHT);
        lang_text_draw_centered(PROCEED_GROUP, PROCEED_TEXT, 80, 140, 480, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    graphics_reset_dialog();
}
static void draw_foreground(void) {
    auto& data = g_popup_dialog;

    graphics_set_to_dialog();
    if (data.num_buttons > 0) // this can be 0, 1 or 2
        image_buttons_draw(80, 80, buttons, data.num_buttons);
    else
        lang_text_draw_centered(13, 1, 80, 208, 480, FONT_NORMAL_BLACK_ON_LIGHT);
    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_popup_dialog;

    if (data.num_buttons && image_buttons_handle_mouse(mouse_in_dialog(m), 80, 80, buttons, data.num_buttons, 0))
        return;
    if (input_go_back_requested(m, h)) {
        data.close_func(0);
        window_go_back();
    }
    if (h->enter_pressed)
        confirm();
}
static void button_ok(int param1, int param2) {
    confirm();
}
static void button_cancel(int param1, int param2) {
    window_go_back();
    g_popup_dialog.close_func(0);
}
static void confirm(void) {
    window_go_back();
    g_popup_dialog.close_func(1);
}

void window_popup_dialog_show(int type, void (*close_func)(bool accepted), e_popup_dialog_btns has_ok_cancel_buttons) {
    if (init(type, 0, 0, close_func, has_ok_cancel_buttons)) {
        window_type window = {WINDOW_POPUP_DIALOG, draw_background, draw_foreground, handle_input};
        window_show(&window);
    }
}
void window_popup_dialog_show_confirmation(int text_group, int text_id, void (*close_func)(bool accepted)) {
    if (init(POPUP_DIALOG_NONE, text_group, text_id, close_func, e_popup_btns_yesno)) {
        window_type window = {WINDOW_POPUP_DIALOG, draw_background, draw_foreground, handle_input};
        window_show(&window);
    }
}
