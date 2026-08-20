log_info("akhenaten: file dialog save scenario (script UI) started")

function file_dialog_save_scenario_basename_from_list_entry(name) {
    return file_dialog_basename_from_exts(name, ["map"])
}

function file_dialog_save_scenario_set_show_filename(from_user) {
    file_dialog_save_scenario.show_filename = file_dialog_save_scenario_basename_from_list_entry(from_user)
}

function file_dialog_save_scenario_resolve_initial() {
    var last = game.get_last_loaded_file(FILE_TYPE_SCENARIO)
    if (last && last.length > 0)
        return last

    return "scenario"
}

function file_dialog_save_scenario_handle_commit(ev) {
    var source_name = file_dialog_source_for_commit(ev, file_dialog_save_scenario.show_filename, file_dialog_save_scenario_basename_from_list_entry)
    if (!file_dialog_has_text(source_name))
        return

    var normalized = file_dialog_save_scenario_basename_from_list_entry(source_name)
    game.editor_write_scenario("Maps/" + normalized + ".map")
    ui.window_editor_map_show()
    __set_last_loaded_utf8(FILE_TYPE_SCENARIO, normalized)
}

[es=window]
file_dialog_save_scenario {
    pos: [(sw(0) - px(24)) / 2, (sh(0) - px(21)) / 2]
    allow_rmb_goback: false
    draw_underlying: true
    show_filename: ""
    show_filename_applied: ""

    ui: baseui(file_dialog_chrome_base, {
        files: scrollable_list({ pos: [16, 76], size: [20, 13], view_items: 12
                                 use_file_finder: true
                                 dir: "Maps/"
                                 file_ext: "map"
                                 draw_scrollbar_always: true
                                 font_asleep: FONT_NORMAL_BLACK_ON_DARK
                                 font_focus: FONT_NORMAL_YELLOW
                                 font_selected: FONT_NORMAL_WHITE_ON_DARK
                                 onclick_event: "on_select_file"
                                 ondoubleclick_event: "on_double_click_file" })
    })
}

[es=(file_dialog_save_scenario, go_back)]
function file_dialog_save_scenario_es_go_back(window) {
    window_go_back()
}

[es=(file_dialog_save_scenario, on_filename_input)]
function file_dialog_save_scenario_es_on_filename_input(ev) {
    file_dialog_save_scenario_set_show_filename(ev.value)
}

[es=(file_dialog_save_scenario, on_select_file)]
function file_dialog_save_scenario_es_on_select_file(ev) {
    file_dialog_save_scenario_set_show_filename(ev.text)
}

[es=(file_dialog_save_scenario, on_double_click_file)]
function file_dialog_save_scenario_es_on_double_click_file(ev) {
    file_dialog_save_scenario_set_show_filename(ev.text)
    file_dialog_save_scenario_handle_commit(ev)
}

[es=(file_dialog_save_scenario, on_ok)]
function file_dialog_save_scenario_es_on_ok(ev) {
    file_dialog_save_scenario_handle_commit(ev)
}

[es=(file_dialog_save_scenario, ui_draw_foreground)]
function file_dialog_save_scenario_ui_draw_foreground(window) {
    if (file_dialog_save_scenario.show_filename !== file_dialog_save_scenario.show_filename_applied) {
        window.filename.value = file_dialog_save_scenario.show_filename
        file_dialog_save_scenario.show_filename_applied = file_dialog_save_scenario.show_filename
    }
}

[es=(file_dialog_save_scenario, init)]
function file_dialog_save_scenario_on_init(window) {
    window.title.text = __loc(43, 3)
    window.hint.text = __loc(43, 5)
    window.files.change_file_path("Maps/", "map")

    var initial = file_dialog_save_scenario_resolve_initial()
    file_dialog_save_scenario.show_filename = initial
    file_dialog_save_scenario.show_filename_applied = initial
    window.filename.value = initial

    window.files.refresh_file_finder()
}
