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

popup_dialog g_popup_dialog;

bool popup_dialog::init(const xstring scheme, textid loc, textid custom_text, window_popup_dialog_callback close_cb, e_popup_dialog_btns buttons) {
    load(scheme.c_str());
    if (window_is(WINDOW_POPUP_DIALOG)) {
        // don't show popup over popup
        return false;
    }

    text = loc;
    this->custom_text = custom_text;
    ok_clicked = 0;
    this->close_func = close_cb;
    num_buttons = buttons;

    ui["btn_yes"].onclick([this] {
        window_go_back();
        this->close_func(1);
    });

    ui["btn_no"].onclick([this] {
        window_go_back();
        this->close_func(0);
    });

    return true;
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

    if (!num_buttons) { // this can be 0, 1 or 2 
        lang_text_draw_centered(13, 1, 80, 208, 480, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    graphics_reset_dialog();
}

void popup_dialog::handle_input(const mouse* m, const hotkeys* h) {
    if (num_buttons) {
        ui.begin_widget(pos);
        int button_id = ui::handle_mouse(m);
        ui.end_widget();
    }

    if (input_go_back_requested(m, h)) {
        window_go_back();
        this->close_func(0);
    }

    if (h->enter_pressed) {
        window_go_back();
        this->close_func(1);
    }
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
    bool ok = g_popup_dialog.init("window_popup_dialog_yesno", text, {}, close_func, buttons);
    if (!ok) {
        return;
    }

    static window_type window = {
        WINDOW_POPUP_DIALOG,
        [] (int flags) { g_popup_dialog.draw_background(flags); },
        [] (int flags) { g_popup_dialog.draw_foreground(flags); },
        [] (auto m, auto h) { g_popup_dialog.handle_input(m, h); }
    };

    window_show(&window);
}

void window_popup_dialog_show_confirmation(pcstr key, window_popup_dialog_callback close_func) {
    textid text = loc_text_from_key(key);
    window_popup_dialog_show_confirmation(text, close_func);
}

void window_popup_dialog_show_confirmation(textid custom, window_popup_dialog_callback close_func) {
    bool ok = g_popup_dialog.init("window_popup_dialog_ok", {}, custom, close_func, e_popup_btns_yesno);
    if (!ok) {
        return;
    }

    static window_type window = {
        WINDOW_POPUP_DIALOG,
        [] (int flags) { g_popup_dialog.draw_background(flags); } ,
        [] (int flags) { g_popup_dialog.draw_foreground(flags); },
        [] (auto m, auto h) { g_popup_dialog.handle_input(m, h); }
    };

    window_show(&window);
}
