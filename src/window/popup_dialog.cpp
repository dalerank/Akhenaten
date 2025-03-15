#include "popup_dialog.h"

#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "input/input.h"

#define PROCEED_GROUP 43
#define PROCEED_TEXT 5

static void button_ok(int param1, int param2);
static void button_cancel(int param1, int param2);
static void confirm(void);

static image_button buttons[] = {
  {192, 100, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 0, button_ok, button_none, 1, 0, 1},
  {256, 100, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 4, button_cancel, button_none, 0, 0, 1},
};

popup_dialog g_popup_dialog;

int popup_dialog_init(const xstring scheme, textid loc, textid custom_text, window_popup_dialog_callback close_func, e_popup_dialog_btns buttons) {
    auto& data = g_popup_dialog;
    data.load(scheme.c_str());
    if (window_is(WINDOW_POPUP_DIALOG)) {
        // don't show popup over popup
        return 0;
    }
    data.text = loc;
    data.custom_text = custom_text;
    data.ok_clicked = 0;
    data.close_func = close_func;
    data.num_buttons = buttons;
    return 1;
}

void popup_dialog::draw_background(int flags) {
    
}

void popup_dialog::draw_foreground(int flags) {
    window_draw_underlying_window(UiFlags_Readonly);

    ui.begin_widget(pos);
    ui.draw();
    ui.end_widget();

    graphics_set_to_dialog();
    //outer_panel_draw(vec2i{80, 80}, 30, 10);
    if (text.valid()) {
        lang_text_draw_centered(text.group, text.id, 80, 100, 480, FONT_LARGE_BLACK_ON_LIGHT);
        if (lang_text_get_width(text.group, text.id + 1, FONT_NORMAL_BLACK_ON_LIGHT) >= 420) {
            lang_text_draw_multiline(text.group, text.id + 1, vec2i{ 110, 140 }, 420, FONT_NORMAL_BLACK_ON_LIGHT);
        } else {
            lang_text_draw_centered(text.group, text.id + 1, 80, 140, 480, FONT_NORMAL_BLACK_ON_LIGHT);
        }
    } else {
        lang_text_draw_centered(custom_text.group, custom_text.id, 80, 100, 480, FONT_LARGE_BLACK_ON_LIGHT);
        lang_text_draw_centered(PROCEED_GROUP, PROCEED_TEXT, 80, 140, 480, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (num_buttons > 0) // this can be 0, 1 or 2
        image_buttons_draw({80, 80}, buttons, num_buttons);
    else
        lang_text_draw_centered(13, 1, 80, 208, 480, FONT_NORMAL_BLACK_ON_LIGHT);

    graphics_reset_dialog();
}

void popup_dialog_handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_popup_dialog;

    if (data.num_buttons && image_buttons_handle_mouse(mouse_in_dialog(m), {80, 80}, buttons, data.num_buttons, 0))
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

void window_popup_dialog_show(pcstr loc_id, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func) {
    window_popup_dialog_show(loc_id, close_func, buttons);
}

void window_yesno_dialog_show(pcstr loc_id, window_popup_dialog_callback close_func) {
    window_popup_dialog_show(loc_id, close_func, e_popup_btns_yesno);
}

void window_yes_dialog_show(pcstr text, window_yes_dialog_callback close_func) {
    window_yesno_dialog_show(text, [=] (bool accepted) {
        if (accepted) { close_func(); }
    });
}

void window_ok_dialog_show(pcstr loc_id, window_yes_dialog_callback close_func) {
    window_popup_dialog_show(loc_id, [=] (bool accepted) {
        if (accepted) { close_func(); }
    }, e_popup_btns_ok);
}

void window_popup_dialog_show(pcstr loc_id, window_popup_dialog_callback close_func, e_popup_dialog_btns buttons) {
    textid text = loc_text_from_key(loc_id);
    window_popup_dialog_show(text, close_func, buttons);
}

void window_popup_dialog_show(textid text, window_popup_dialog_callback close_func, e_popup_dialog_btns buttons) {
    bool ok = popup_dialog_init("window_popup_dialog_yesno", text, {}, close_func, buttons);
    if (!ok) {
        return;
    }
    window_type window = {
        WINDOW_POPUP_DIALOG,
        [] (int flags) { g_popup_dialog.draw_background(flags); },
        [] (int flags) { g_popup_dialog.draw_foreground(flags); },
        popup_dialog_handle_input
    };
    window_show(&window);
}

void window_popup_dialog_show_confirmation(pcstr key, window_popup_dialog_callback close_func) {
    textid text = loc_text_from_key(key);
    window_popup_dialog_show_confirmation(text, close_func);
}

void window_popup_dialog_show_confirmation(textid custom, window_popup_dialog_callback close_func) {
    bool ok = popup_dialog_init("window_popup_dialog_ok", {}, custom, close_func, e_popup_btns_yesno);
    if (!ok) {
        return;
    }

    static window_type window = {
        WINDOW_POPUP_DIALOG,
        [] (int flags) { g_popup_dialog.draw_background(flags); } ,
        [] (int flags) { g_popup_dialog.draw_foreground(flags); },
        popup_dialog_handle_input
    };
    window_show(&window);
}
