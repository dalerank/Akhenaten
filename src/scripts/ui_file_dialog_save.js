log_info("akhenaten: file dialog save (script UI) started")

function file_dialog_save_basename_from_list_entry(name) {
    return file_dialog_basename_from_exts(name, ["svx"])
}

function file_dialog_save_set_show_filename(from_user) {
    file_dialog_save.show_filename = file_dialog_save_basename_from_list_entry(from_user)
}

function file_dialog_save_resolve_initial() {
    var last = game.get_last_loaded_file(FILE_TYPE_SAVED_GAME)
    if (last && last.length > 0)
        return last

    return "savegame"
}

function file_dialog_save_handle_commit(ev) {
    var source_name = file_dialog_source_for_commit(ev, file_dialog_save.show_filename, file_dialog_save_basename_from_list_entry)
    if (!file_dialog_has_text(source_name))
        return

    var normalized = file_dialog_save_basename_from_list_entry(source_name)
    if (!game_allows_player_save()) {
        game_toast_ironwill_save_blocked()
        app_clear_pending_exit_after_save()
        ui.window_city_show()
        return
    }
    game.write_savegame(normalized + ".svx")
    ui.window_city_show()
    __set_last_loaded_utf8(FILE_TYPE_SAVED_GAME, normalized)
    app_finish_exit_after_save()
}

[es=(file_dialog_save, go_back)]
function file_dialog_save_es_go_back(window) {
    app_clear_pending_exit_after_save()
    window_go_back()
}

[es=window]
file_dialog_save {
    pos: [(sw(0) - px(24)) / 2, (sh(0) - px(21)) / 2]
    allow_rmb_goback: false
    draw_underlying: true
    show_filename: ""
    show_filename_applied: ""

    ui: baseui(file_dialog_chrome_base, {})
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
    window.title.text = __loc(43, 0)
    window.hint.text = __loc(43, 5)

    var dir = file_dialog_savegame_dir()
    window.files.change_file_path(dir, "svx")

    var initial = file_dialog_save_resolve_initial()
    file_dialog_save.show_filename = initial
    file_dialog_save.show_filename_applied = initial
    window.filename.value = initial

    window.files.refresh_file_finder()
}
