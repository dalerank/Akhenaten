#include "popup_dialog.h"

#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "input/input.h"

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

    if (!num_buttons) {
        ui["btn_yes"].enabled = false;
        ui["btn_no"].enabled = false;
    }
    ui["label_tip"] = num_buttons ? textid{ 0, 0 } : textid{ 13, 1 };
    ui["label_tip"].enabled = !num_buttons;

    if (text.valid()) {
        ui["header"] = text;
        ui["text"] = textid{ text.group, (uint16_t)(text.id + 1) };
    } else {
        ui["header"] = custom_text;
        ui["text"] = "#popup_dialog_proceed";
    }

    return true;
}

void popup_dialog::draw_background(int flags) {
}

void popup_dialog::draw_foreground(int flags) {
    window_draw_underlying_window(UiFlags_Readonly);

    ui.begin_widget(pos);
    ui.draw();
    ui.end_widget();
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
