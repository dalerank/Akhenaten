log_info("akhenaten: file dialog delete (script UI) started")

var FILE_DIALOG_DELETE_ERROR_FLASH_MS = 500
var FILE_DIALOG_DELETE_EXTS = ["sav", "svx"]

function file_dialog_delete_basename_from_list_entry(name) {
    return file_dialog_basename_from_exts(name, FILE_DIALOG_DELETE_EXTS)
}

function file_dialog_delete_resolve_initial() {
    var last = game.get_last_loaded_file(FILE_TYPE_SAVED_GAME)
    if (last && last.length > 0)
        return file_dialog_delete_basename_from_list_entry(last)

    return "savegame"
}

function file_dialog_delete_set_show_filename(from_user) {
    file_dialog_delete.show_filename = file_dialog_delete_basename_from_list_entry(from_user)
    file_dialog_delete.error_flash_start_ms = 0
}

function file_dialog_delete_disk_path(basename_no_ext, ext) {
    return file_dialog_savegame_dir() + basename_no_ext + "." + ext
}

function file_dialog_delete_find_existing_short_name(basename_no_ext) {
    for (var i = 0; i < FILE_DIALOG_DELETE_EXTS.length; i++) {
        var path = file_dialog_delete_disk_path(basename_no_ext, FILE_DIALOG_DELETE_EXTS[i])
        if (game.file_exists(path))
            return basename_no_ext + "." + FILE_DIALOG_DELETE_EXTS[i]
    }

    return ""
}

function file_dialog_delete_try_delete(source_name) {
    if (!file_dialog_has_text(source_name))
        return 1

    var basename = file_dialog_delete_basename_from_list_entry(source_name)
    if (!file_dialog_has_text(basename))
        return 1

    var short_name = file_dialog_delete_find_existing_short_name(basename)
    if (!file_dialog_has_text(short_name))
        return 1

    if (!game.delete_savegame(short_name))
        return 2

    __set_last_loaded_utf8(FILE_TYPE_SAVED_GAME, basename)
    return 0
}

function file_dialog_delete_handle_commit(window) {
    var source_name = file_dialog_source_for_commit(window, file_dialog_delete.show_filename, file_dialog_delete_basename_from_list_entry)
    var r = file_dialog_delete_try_delete(source_name)
    if (r !== 0) {
        file_dialog_delete.error_flash_start_ms = __game_time_millis()
        return
    }

    var dir = file_dialog_savegame_dir()
    window.files.change_file_path(dir, FILE_DIALOG_DELETE_EXTS[0])
    for (var i = 1; i < FILE_DIALOG_DELETE_EXTS.length; i++)
        window.files.append_files_with_extension(dir, FILE_DIALOG_DELETE_EXTS[i])
}

[es=window]
file_dialog_delete {
    pos: [(sw(0) - px(24)) / 2, (sh(0) - px(21)) / 2]
    allow_rmb_goback: true
    draw_underlying: true
    show_filename: ""
    show_filename_applied: ""
    error_flash_start_ms: 0

    ui: baseui(file_dialog_chrome_base, {
        files: scrollable_list({ pos: [16, 76], size: [20, 13], view_items: 12
                                 use_file_finder: true
                                 dir: "Save/"
                                 file_ext: "folders"
                                 draw_scrollbar_always: true
                                 font_asleep: FONT_NORMAL_BLACK_ON_DARK
                                 font_focus: FONT_NORMAL_YELLOW
                                 font_selected: FONT_NORMAL_WHITE_ON_DARK
                                 onclick_event: "on_select_file" })
    })
}

[es=(file_dialog_delete, go_back)]
function file_dialog_delete_es_go_back(window) {
    window_go_back()
}

[es=(file_dialog_delete, on_filename_input)]
function file_dialog_delete_es_on_filename_input(ev) {
    file_dialog_delete_set_show_filename(ev.value)
}

[es=(file_dialog_delete, on_select_file)]
function file_dialog_delete_es_on_select_file(ev) {
    file_dialog_delete_set_show_filename(ev.text)
}

[es=(file_dialog_delete, on_ok)]
function file_dialog_delete_es_on_ok(window) {
    file_dialog_delete_handle_commit(window)
}

[es=(file_dialog_delete, ui_draw_foreground)]
function file_dialog_delete_ui_draw_foreground(window) {
    var flash_start = file_dialog_delete.error_flash_start_ms
    var flash_active = flash_start !== 0 && (__game_time_millis() - flash_start) < FILE_DIALOG_DELETE_ERROR_FLASH_MS

    window.title.text = __loc(43, 304)
    window.title.pos = flash_active ? [0, 2] : [0, 14]

    if (file_dialog_delete.show_filename !== file_dialog_delete.show_filename_applied) {
        window.filename.value = file_dialog_delete.show_filename
        file_dialog_delete.show_filename_applied = file_dialog_delete.show_filename
    }
}

[es=(file_dialog_delete, init)]
function file_dialog_delete_on_init(window) {
    window.title.text = __loc(43, 304)
    window.hint.text = __loc(43, 5)

    var dir = file_dialog_savegame_dir()
    window.files.change_file_path(dir, FILE_DIALOG_DELETE_EXTS[0])
    for (var i = 1; i < FILE_DIALOG_DELETE_EXTS.length; i++)
        window.files.append_files_with_extension(dir, FILE_DIALOG_DELETE_EXTS[i])

    var initial = file_dialog_delete_resolve_initial()
    file_dialog_delete.show_filename = initial
    file_dialog_delete.show_filename_applied = initial
    file_dialog_delete.error_flash_start_ms = 0
    window.filename.value = initial
}
