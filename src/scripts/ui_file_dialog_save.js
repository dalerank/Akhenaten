log_info("akhenaten: file dialog save (script UI) started")

function has_text(v) {
    return v !== null && v !== undefined && ("" + v) !== ""
}

function file_dialog_save_basename_from_list_entry(name) {
    if (!name || name.length === 0)
        return ""
    var ext = __file_dialog_save_get_files_ext_utf8()
    if (!ext || ext.length === 0)
        return name
    var dot = "."
    var suffix = dot + ext
    var n = name.length
    var m = suffix.length
    if (n <= m)
        return name
    if (name.substring(n - m).toLowerCase() !== suffix.toLowerCase())
        return name
    return name.substring(0, n - m)
}

function file_dialog_save_set_show_filename(from_user) {
    file_dialog_save.show_filename = file_dialog_save_basename_from_list_entry(from_user)
}

function file_dialog_save_source_for_commit(ev) {
    var selected = (ev && ev.files) ? ("" + ev.files.selected_text(1)) : ""
    var live = (ev && ev.filename) ? ("" + ev.filename.value).trim() : ""
    var selBase = has_text(selected) ? file_dialog_save_basename_from_list_entry(selected) : ""
    var liveBase = has_text(live) ? file_dialog_save_basename_from_list_entry(live) : ""

    if (has_text(liveBase) && has_text(selBase) && liveBase !== selBase)
        return live
    if (has_text(selected))
        return selected
    if (has_text(live))
        return live
    return file_dialog_save.show_filename
}

function file_dialog_save_handle_commit(ev) {
    var source_name = file_dialog_save_source_for_commit(ev)
    if (!has_text(source_name))
        return
    var normalized = file_dialog_save_basename_from_list_entry(source_name)
     __file_dialog_save_commit(normalized)
}

function file_dialog_save_on_cancel() {
    window_go_back()
}

[es=window]
file_dialog_save {
    pos: [(sw(0) - px(24)) / 2, (sh(0) - px(21)) / 2]
    allow_rmb_goback: true
    draw_underlying: true
    file_type: 0
    show_filename: ""
    show_filename_applied : ""

    ui {
        background: outer_panel({ size: [24, 21] })

        title: text({ pos: [0, 14], size: [px(24), 22], align: "center", font: FONT_LARGE_BLACK_ON_LIGHT, text: "" })

        filename: input({ pos: [16, 44], size: [20, 2], font: FONT_NORMAL_WHITE_ON_DARK, max_length: 63, allow_punctuation: 1
                          oninput_event: "on_filename_input" })

        files: scrollable_list({ pos: [16, 76], size: [20, 13], view_items: 12
                                 use_file_finder: true
                                 dir: "Save/"
                                 file_ext: "svx"
                                 draw_scrollbar_always: true
                                 font_asleep: FONT_NORMAL_BLACK_ON_DARK
                                 font_focus: FONT_NORMAL_YELLOW
                                 font_selected: FONT_NORMAL_WHITE_ON_DARK
                                 onclick_event: "on_select_file"
                                 ondoubleclick_event: "on_double_click_file" })

        hint: text({ margin{centerx:-80, bottom:-35}, align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, text: "" })

        btn_ok: ok_button({ margin{centerx:0, bottom:-40}, onclick_event: "on_ok" })
        btn_cancel: cancel_button({ margin{centerx:50, bottom:-40}, onclick: file_dialog_save_on_cancel })
    }
}

[es=(file_dialog_save, on_filename_input)]
function file_dialog_save_es_on_filename_input(ev) {
    file_dialog_save_set_show_filename(ev.value)
}

[es=(file_dialog_save, on_select_file)]
function file_dialog_save_es_on_select_file(ev) {
    file_dialog_save_set_show_filename(ev.text)
}

[es=(file_dialog_save, on_double_click_file)]
function file_dialog_save_es_on_double_click_file(ev) {
    file_dialog_save_set_show_filename(ev.text)
    file_dialog_save_handle_commit(ev)
}

[es=(file_dialog_save, on_ok)]
function file_dialog_save_es_on_ok(ev) {
    file_dialog_save_handle_commit(ev)
}

[es=(file_dialog_save, ui_draw_foreground)]
function file_dialog_save_ui_draw_foreground(window) {
    if (file_dialog_save.show_filename !== file_dialog_save.show_filename_applied) {
        window.filename.value = file_dialog_save.show_filename
        file_dialog_save.show_filename_applied = file_dialog_save.show_filename
    }
}

[es=(file_dialog_save, init)]
function file_dialog_save_on_init(window) {
    window.file_type = __file_dialog_save_get_pending_type()

    var is_scenario = (window.file_type === FILE_TYPE_SCENARIO)
    window.title.text = __loc(43, is_scenario ? 3 : 0)
    window.hint.text = __loc(43, 5)

    window.files.change_file_path(__file_dialog_save_get_files_dir_utf8(), __file_dialog_save_get_files_ext_utf8())

    var initial = __file_dialog_save_get_initial_filename_utf8()
    file_dialog_save.show_filename = initial
    file_dialog_save.show_filename_applied = initial
    window.filename.value = initial

    window.files.refresh_file_finder()
}
