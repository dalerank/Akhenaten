log_info("akhenaten: file dialog delete (script UI) started")

var FILE_DIALOG_DELETE_ERROR_FLASH_MS = 500

function has_text(v) {
    return v !== null && v !== undefined && ("" + v) !== ""
}

function file_dialog_delete_resolve_files_dir(pending_type) {
    if (pending_type === FILE_TYPE_SCENARIO)
        return "Maps/"

    return "Save/" + game.dynasty_name + "/"
}

function file_dialog_delete_list_extensions(pending_type) {
    return pending_type === FILE_TYPE_SCENARIO ? ["map"] : ["sav", "svx"]
}

function file_dialog_delete_resolve_initial(pending_type) {
    var last = game.get_last_loaded_file(pending_type)
    if (last && last.length > 0)
        return file_dialog_delete_basename_from_list_entry(last)

    return pending_type === FILE_TYPE_SCENARIO ? "scenario" : "savegame"
}

function file_dialog_delete_strip_suffix_lower(name, ext) {
    if (!name || !ext || ext.length === 0)
        return name

    var suffix = "." + ext
    var n = name.length
    var m = suffix.length
    if (n <= m)
        return name

    if (name.substring(n - m).toLowerCase() !== suffix.toLowerCase())
        return name

    return name.substring(0, n - m)
}

function file_dialog_delete_basename_from_list_entry(name) {
    if (!name || name.length === 0)
        return ""

    var exts = file_dialog_delete_list_extensions(file_dialog_delete.pending_type)
    var base = name
    for (var i = 0; i < exts.length; i++)
        base = file_dialog_delete_strip_suffix_lower(base, exts[i])

    return base
}

function file_dialog_delete_set_show_filename(from_user) {
    file_dialog_delete.show_filename = file_dialog_delete_basename_from_list_entry(from_user)
    file_dialog_delete.error_flash_start_ms = 0
}

function file_dialog_delete_source_for_commit(ev) {
    var selected = (ev && ev.files) ? ("" + ev.files.selected_text(1)) : ""
    var live = (ev && ev.filename) ? ("" + ev.filename.value).trim() : ""
    var selBase = has_text(selected) ? file_dialog_delete_basename_from_list_entry(selected) : ""
    var liveBase = has_text(live) ? file_dialog_delete_basename_from_list_entry(live) : ""

    if (has_text(liveBase) && has_text(selBase) && liveBase !== selBase)
        return live

    if (has_text(selected))
        return selected

    if (has_text(live))
        return live

    return file_dialog_delete.show_filename
}

function file_dialog_delete_disk_path(basename_no_ext, ext) {
    var pending = file_dialog_delete.pending_type
    if (pending === FILE_TYPE_SCENARIO)
        return "Maps/" + basename_no_ext + "." + ext

    return "Save/" + game.dynasty_name + "/" + basename_no_ext + "." + ext
}

function file_dialog_delete_find_existing_short_name(basename_no_ext) {
    var exts = file_dialog_delete_list_extensions(file_dialog_delete.pending_type)
    for (var i = 0; i < exts.length; i++) {
        var path = file_dialog_delete_disk_path(basename_no_ext, exts[i])
        if (game.file_exists(path))
            return basename_no_ext + "." + exts[i]
    }

    return ""
}

function file_dialog_delete_try_delete(source_name) {
    if (!has_text(source_name))
        return 1

    var basename = file_dialog_delete_basename_from_list_entry(source_name)
    if (!has_text(basename))
        return 1

    var short_name = file_dialog_delete_find_existing_short_name(basename)
    if (!has_text(short_name))
        return 1

    var pending = file_dialog_delete.pending_type
    var ok = false
    if (pending === FILE_TYPE_SCENARIO)
        ok = game.delete_map(short_name)
    else
        ok = game.delete_savegame(short_name)

    if (!ok)
        return 2

    __set_last_loaded_utf8(pending, basename)
    return 0
}

function file_dialog_delete_handle_commit(window) {
    var source_name = file_dialog_delete_source_for_commit(window)
    var r = file_dialog_delete_try_delete(source_name)
    if (r !== 0) {
        file_dialog_delete.error_flash_start_ms = __game_time_millis()
        return
    }

    var dir = file_dialog_delete_resolve_files_dir(file_dialog_delete.pending_type)
    var exts = file_dialog_delete_list_extensions(file_dialog_delete.pending_type)
    window.files.change_file_path(dir, exts[0])
    for (var i = 1; i < exts.length; i++)
        window.files.append_files_with_extension(dir, exts[i])
}

function file_dialog_delete_on_cancel() {
    window_go_back()
}

[es=window]
file_dialog_delete {
    pos: [(sw(0) - px(24)) / 2, (sh(0) - px(21)) / 2]
    allow_rmb_goback: true
    draw_underlying: true
    file_type: 0
    pending_type: FILE_TYPE_SAVED_GAME
    show_filename: ""
    show_filename_applied: ""
    error_flash_start_ms: 0

    ui {
        background: outer_panel({ size: [24, 21] })
        title: text({ pos: [0, 14], size: [px(24), 22], align: "center", font: FONT_LARGE_BLACK_ON_LIGHT, text: "" })
        filename: input({ pos: [16, 44], size: [20, 2], font: FONT_NORMAL_WHITE_ON_DARK, max_length: 63, allow_punctuation: 1
                          oninput_event: "on_filename_input" })

        files: scrollable_list({ pos: [16, 76], size: [20, 13], view_items: 12
                                 use_file_finder: true
                                 dir: "Save/"
                                 file_ext: "folders"
                                 draw_scrollbar_always: true
                                 font_asleep: FONT_NORMAL_BLACK_ON_DARK
                                 font_focus: FONT_NORMAL_YELLOW
                                 font_selected: FONT_NORMAL_WHITE_ON_DARK
                                 onclick_event: "on_select_file" })

        hint: text({ margin{centerx:-80, bottom:-35}, align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, text: "" })
        btn_ok: ok_button({ margin{centerx:0, bottom:-40}, onclick_event: "on_ok" })
        btn_cancel: cancel_button({ margin{centerx:50, bottom:-40}, onclick: file_dialog_delete_on_cancel })
    }
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
    file_dialog_delete.pending_type = game.pending_delete_type
    window.file_type = file_dialog_delete.pending_type

    window.title.text = __loc(43, 304)
    window.hint.text = __loc(43, 5)

    var dir = file_dialog_delete_resolve_files_dir(file_dialog_delete.pending_type)
    var exts = file_dialog_delete_list_extensions(file_dialog_delete.pending_type)
    window.files.change_file_path(dir, exts[0])
    for (var i = 1; i < exts.length; i++)
        window.files.append_files_with_extension(dir, exts[i])

    var initial = file_dialog_delete_resolve_initial(file_dialog_delete.pending_type)
    file_dialog_delete.show_filename = initial
    file_dialog_delete.show_filename_applied = initial
    file_dialog_delete.error_flash_start_ms = 0
    window.filename.value = initial
}
