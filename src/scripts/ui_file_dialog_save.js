log_info("akhenaten: file dialog save (script UI) started")

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

function file_dialog_save_on_select(p) {
    if (!p || !p.text)
        return

    file_dialog_save.show_filename = file_dialog_save_basename_from_list_entry(p.text)
}

function file_dialog_save_on_double_click(p) {
    file_dialog_save_on_select(p)
    file_dialog_save_on_ok()
}

function file_dialog_save_on_ok() {
    var name = file_dialog_save.show_filename
    if (!name || name.length === 0)
        return
    __file_dialog_save_commit(name)
}

function file_dialog_save_on_cancel() {
    window_go_back()
}

function file_dialog_save_on_filename_input(p) {
    file_dialog_save.show_filename = (p && p.value) ? p.value : ""
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
                          oninput: file_dialog_save_on_filename_input })

        files: scrollable_list({ pos: [16, 76], size: [20, 13], view_items: 12
                                 use_file_finder: true
                                 dir: "Save/"
                                 file_ext: "svx"
                                 draw_scrollbar_always: true
                                 font_asleep: FONT_NORMAL_BLACK_ON_DARK
                                 font_focus: FONT_NORMAL_YELLOW
                                 font_selected: FONT_NORMAL_WHITE_ON_DARK
                                 onclick_item: file_dialog_save_on_select
                                 ondoubleclick_item: file_dialog_save_on_double_click })

        hint: text({ margin{centerx:-80, bottom:-35}, align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, text: "" })

        btn_ok: ok_button({ margin{centerx:0, bottom:-40}, onclick: file_dialog_save_on_ok })
        btn_cancel: cancel_button({ margin{centerx:50, bottom:-40}, onclick: file_dialog_save_on_cancel })
    }
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
