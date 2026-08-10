log_info("akhenaten: hotkey editor window started")

function hotkey_editor_key_text() {
    return __hotkey_key_display_name(window_hotkey_editor.key, window_hotkey_editor.modifiers)
}

function hotkey_editor_close(ok) {
    var action = window_hotkey_editor.action
    var is_alt = window_hotkey_editor.is_alt
    var key = window_hotkey_editor.key
    var modifiers = window_hotkey_editor.modifiers
    window_go_back()
    if (ok) {
        emit event_hotkey_editor_result{ action: action, is_alt: is_alt, key: key, modifiers: modifiers }
    }
}

function hotkey_editor_show(action, is_alt) {
    window_hotkey_editor.action = action
    window_hotkey_editor.is_alt = is_alt ? 1 : 0
    window_hotkey_editor.key = KEY_NONE
    window_hotkey_editor.modifiers = KEY_MOD_NONE
    window_show_by_id("window_hotkey_editor")
}

[es=event_hotkey_editor_key]
function hotkey_editor_on_key(ev) {
    if (!ui.window_is("window_hotkey_editor")) {
        return
    }

    if (ev.pressed) {
        if (ev.key === KEY_ENTER && ev.modifiers === KEY_MOD_NONE) {
            hotkey_editor_close(true)
            return
        }
        if (ev.key === KEY_ESCAPE && ev.modifiers === KEY_MOD_NONE) {
            hotkey_editor_close(false)
            return
        }
        if (ev.key !== KEY_NONE) {
            window_hotkey_editor.key = ev.key
        }
        window_hotkey_editor.modifiers = ev.modifiers
        return
    }

    if (window_hotkey_editor.key === KEY_NONE && ev.key === KEY_NONE) {
        window_hotkey_editor.modifiers = ev.modifiers
    }
}

[es=modal_window]
window_hotkey_editor {
    pos: [(sw(0) - px(19)) / 2, (sh(0) - px(9)) / 2]
    draw_underlying: true
    allow_rmb_goback: true
    action: 0
    is_alt: 0
    key: 0
    modifiers: 0
    ui {
        background: outer_panel({ size[19, 9] })
        title: text_center({
            pos[8, 16], size[px(19) - 16, 24],
            text: "#TR_HOTKEY_EDIT_TITLE",
            font: FONT_LARGE_BLACK_ON_LIGHT
        })
        key_panel: inner_panel({ pos[24, 56], size[16, 2] })
        key_text: text_center({
            pos[24, 65], size[256, 20],
            textfn: hotkey_editor_key_text,
            font: FONT_NORMAL_WHITE_ON_DARK
        })
        btn_cancel: button({
            pos[24, 100], size[120, 24],
            text: "#TR_BUTTON_CANCEL",
            font: FONT_NORMAL_BLACK_ON_LIGHT,
            onclick: function() { hotkey_editor_close(false) }
        })
        btn_ok: button({
            pos[160, 100], size[120, 24],
            text: "#TR_BUTTON_OK",
            font: FONT_NORMAL_BLACK_ON_LIGHT,
            onclick: function() { hotkey_editor_close(true) }
        })
    }
}
