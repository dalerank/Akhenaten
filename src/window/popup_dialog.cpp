#include "popup_dialog.h"

#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "input/input.h"

popup_dialog g_popup_dialog;

bool popup_dialog::init(const xstring scheme, xstring header, xstring cbody, window_popup_dialog_callback close_cb, e_popup_dialog_btns buttons) {
    if (window_is(WINDOW_POPUP_DIALOG)) {
        // don't show popup over popup
        return false;
    }

    load(scheme.c_str());

    text = header;
    this->body = cbody;
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

    ui["header"] = text;
    ui["text"] = cbody;
    if (cbody.empty()) {
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

void popup_dialog::show(pcstr loc_id, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func) {
    pcstr text = lang_text_from_key(loc_id);
    show("", text, buttons, close_func);
}

void popup_dialog::show(textid text, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func) {
    xstring header = lang_get_xstring(text.group, text.id);
    show(header, "", buttons, close_func);
}

void popup_dialog::show(textid text, textid custom, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func) {
    xstring header = lang_get_xstring(text.group, text.id);
    xstring str = lang_get_xstring(custom.group, custom.id);
    show(header, str, buttons, close_func);
}

void popup_dialog::show(xstring text, xstring custom, e_popup_dialog_btns buttons, window_popup_dialog_callback close_func) {
    constexpr pcstr configs[] = { "window_popup_dialog_ok", "window_popup_dialog_ok", "window_popup_dialog_yesno" };
    bool ok = g_popup_dialog.init(configs[buttons], text, custom, close_func, buttons);
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
