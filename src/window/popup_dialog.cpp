#include "popup_dialog.h"

#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "input/input.h"
#include "input/mouse.h"

static popup_dialog g_popup_dialog_ok("window_popup_dialog_ok");
static popup_dialog g_popup_dialog_yesno("window_popup_dialog_yesno");

popup_dialog::popup_dialog(pcstr section)
    : autoconfig_window(section)
    , section_name(section) {
}

bool popup_dialog::is_open() {
    return g_window_manager.window_is("window_popup_dialog_ok")
        || g_window_manager.window_is("window_popup_dialog_yesno");
}

void popup_dialog::accept() {
    auto cb = close_func;
    window_go_back();
    if (cb) {
        cb(true);
    }
}

void popup_dialog::reject() {
    auto cb = close_func;
    window_go_back();
    if (cb) {
        cb(false);
    }
}

void popup_dialog::prepare(xstring header, xstring cbody, window_popup_dialog_callback close_cb, e_popup_dialog_btns buttons) {
    close_func = close_cb;
    num_buttons = buttons;

    ui["btn_yes"].onclick([this] { accept(); });
    ui["btn_no"].onclick([this] { reject(); });
    ui["btn_close"].onclick([this] { reject(); });

    if (!num_buttons) {
        ui["btn_yes"].enabled = false;
        ui["btn_no"].enabled = false;
    } else {
        ui["btn_yes"].enabled = true;
        ui["btn_no"].enabled = (num_buttons == e_popup_btns_yesno);
    }
    // Buttonless (OK) dialogs close with the X button instead of the "right-click to continue" hint.
    ui["btn_close"].enabled = !num_buttons;
    ui["label_tip"].enabled = false;

    ui["header"] = header;
    ui["text"] = cbody;
    if (cbody.empty()) {
        ui["text"] = "#popup_dialog_proceed";
    }

    _is_inited = false;
}

int popup_dialog::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();

    if (num_buttons || ui["btn_close"].enabled) {
        ui.begin_widget(pos);
        ui::handle_mouse(m);
        ui.end_widget();
    }

    if (input_go_back_requested(m, h)) {
        reject();
        return 1;
    }

    if (h->enter_pressed) {
        accept();
        return 1;
    }

    mouse::ref().reset_up_state();
    mouse::ref().reset_scroll();
    return 1;
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
    if (is_open()) {
        return;
    }

    popup_dialog &dlg = (buttons == e_popup_btns_yesno) ? g_popup_dialog_yesno : g_popup_dialog_ok;
    dlg.prepare(text, custom, close_func, buttons);
    autoconfig_window::show(dlg.get_section());
}
