log_info("akhenaten: file dialog load (script UI) started")

var FILE_DIALOG_LOAD_ERROR_FLASH_MS = 500

function strip_extension(src) {
    if (!src || src.length === 0)
        return ""

    var s = src
    var li = Math.max(s.lastIndexOf("/"), s.lastIndexOf("\\"))
    if (li >= 0)
        s = s.substring(li + 1)

    var dot = s.indexOf(".")
    if (dot >= 0)
        s = s.substring(0, dot)

    return s
}

function resolve_initial_basename(pending_type) {
    var last = game.get_last_loaded_file(pending_type)
    if (last && last.length > 0) {
        var b = strip_extension(last)
        if (b && b.length > 0)
            return b
    }

    var kind = game.session_last_loaded_kind
    var mission = game.session_last_loaded_mission
    var is_scenario = (pending_type === FILE_TYPE_SCENARIO)
    if (!is_scenario) {
        if (kind === e_session_save && mission && mission.length > 0) {
            var b2 = strip_extension(mission)
            if (b2 && b2.length > 0)
                return b2
        }

        var lastWrite = game_features.gameopt_last_save_filename
        if (lastWrite && lastWrite.length > 0)
            return strip_extension(lastWrite)
        return ""
    }

    if (kind === e_session_custom_map && mission && mission.length > 0)
        return strip_extension(mission)

    return ""
}

function resolve_files_dir(pending_type) {
    if (pending_type === FILE_TYPE_SCENARIO)
        return "Maps/"

    return "Save/" + game.dynasty_name + "/"
}

function resolve_list_primary_ext(pending_type) {
    return pending_type === FILE_TYPE_SCENARIO ? "map" : "sav"
}

function resolve_list_secondary_ext(pending_type) {
    return pending_type === FILE_TYPE_SCENARIO ? "" : "svx"
}

function strip_suffix_lower(name, ext) {
    if (!name || !ext || ext.length === 0)
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

function file_dialog_load_fullpath(relative) {
    if (!relative || relative.length === 0)
        return ""

    var head = relative.length >= 5 ? relative.substring(0, 5) : ""
    var headLower = head.toLowerCase()
    if (headLower === "save/" || headLower === "save\\" || headLower === "maps/" || headLower === "maps\\")
        return relative

    if (file_dialog_load.pending_type === FILE_TYPE_SCENARIO)
        return "Maps/" + relative

    return "Save/" + game.dynasty_name + "/" + relative
}

function file_dialog_load_basename_from_list_entry(name) {
    if (!name || name.length === 0)
        return ""

    var e1 = resolve_list_primary_ext(file_dialog_load.pending_type)
    var e2 = resolve_list_secondary_ext(file_dialog_load.pending_type)
    var base = strip_suffix_lower(name, e1)
    if (e2 && e2.length > 0)
        base = strip_suffix_lower(base, e2)

    return base
}

function file_dialog_load_try_load(basename) {
    if (!basename || basename.length === 0)
        return 1

    var pending = file_dialog_load.pending_type
    var ext1 = resolve_list_primary_ext(pending)
    var ext2 = resolve_list_secondary_ext(pending)

    var full = file_dialog_load_fullpath(basename + "." + ext1)
    if (!game.file_exists(full) && ext2 && ext2.length > 0)
        full = file_dialog_load_fullpath(basename + "." + ext2)

    if (!game.file_exists(full))
        return 1

    if (pending === FILE_TYPE_SAVED_GAME) {
        if (!game.load_savegame(full))
            return 2

        ui.window_city_show()
    } else if (pending === FILE_TYPE_SCENARIO) {
        if (!game.editor_load_scenario(full))
            return 2

        ui.window_editor_map_show()
    } else {
        return 2
    }

    __set_last_loaded_utf8(pending, basename)
    return 0
}

function file_dialog_load_on_filename_input(p) {
    file_dialog_load.show_filename = (p && p.value) ? p.value : ""
    file_dialog_load.error_flash_start_ms = 0
}

function file_dialog_load_apply_list_selection(p) {
    if (!p || !p.text)
        return

    file_dialog_load.show_filename = file_dialog_load_basename_from_list_entry(p.text)
    file_dialog_load.error_flash_start_ms = 0
}

function file_dialog_load_handle_load(window) {
    var name = file_dialog_load.show_filename
    if (!name || name.length === 0)
        return

    var r = file_dialog_load_try_load(name)
    if (r !== 0) {
        file_dialog_load.error_flash_title_id = (r === 2) ? 7 : 2
        file_dialog_load.error_flash_start_ms = __game_time_millis()
    }
}

[es=window]
file_dialog_load {
    pos: [(sw(0) - px(24)) / 2, (sh(0) - px(21)) / 2]
    allow_rmb_goback: true
    draw_underlying: true
    file_type: 0
    pending_type: FILE_TYPE_SAVED_GAME
    show_filename: ""
    show_filename_applied : ""
    error_flash_start_ms: 0
    error_flash_title_id: 2

    ui {
        background: outer_panel({ size: [24, 21] })

        title: text({ pos: [0, 14], size: [px(24), 22], align: "center", font: FONT_LARGE_BLACK_ON_LIGHT, text: "" })

        filename: input({ pos: [16, 44], size: [20, 2], font: FONT_NORMAL_WHITE_ON_DARK, max_length: 63, allow_punctuation: 1
                          oninput: file_dialog_load_on_filename_input })

        files: scrollable_list({ pos: [16, 76], size: [20, 13], view_items: 12
                                 use_file_finder: true
                                 dir: "Save/"
                                 file_ext: "folders"
                                 draw_scrollbar_always: true
                                 font_asleep: FONT_NORMAL_BLACK_ON_DARK
                                 font_focus: FONT_NORMAL_YELLOW
                                 font_selected: FONT_NORMAL_WHITE_ON_DARK
                                 onclick_event: "on_select_file"
                                 ondoubleclick_event: "on_double_click_file" })

        hint: text({ margin{centerx:-80, bottom:-35}, align: "center", font: FONT_NORMAL_BLACK_ON_LIGHT, text: "" })

        btn_ok: ok_button({ margin{centerx:0, bottom:-40}, onclick_event: "on_ok" })
        btn_cancel: cancel_button({ margin{centerx:50, bottom:-40}, onclick: window_go_back })
    }
}

[es=(file_dialog_load, on_select_file)]
function file_dialog_load_es_on_select_file(window) {
    file_dialog_load_apply_list_selection(window)
}

[es=(file_dialog_load, on_double_click_file)]
function file_dialog_load_es_on_double_click_file(window) {
    file_dialog_load_apply_list_selection(window)
    file_dialog_load_handle_load(window)
}

[es=(file_dialog_load, on_ok)]
function file_dialog_load_on_ok(window) {
    file_dialog_load_handle_load(window)
}

[es=(file_dialog_load, ui_draw_foreground)]
function file_dialog_load_ui_draw_foreground(window) {
    var is_scenario = (window.file_type === FILE_TYPE_SCENARIO)

    var flash_start = file_dialog_load.error_flash_start_ms
    var flash_active = flash_start !== 0 && (__game_time_millis() - flash_start) < FILE_DIALOG_LOAD_ERROR_FLASH_MS
    if (flash_active) {
        window.title.text = __loc(43, file_dialog_load.error_flash_title_id)
    } else {
        window.title.text = __loc(43, is_scenario ? 4 : 1)
    }

    if (file_dialog_load.show_filename !== file_dialog_load.show_filename_applied) {
        window.filename.value = file_dialog_load.show_filename
        file_dialog_load.show_filename_applied = file_dialog_load.show_filename
    }
}

[es=(file_dialog_load, init)]
function file_dialog_load_on_init(window) {
    window.file_type = game.pending_load_type
    file_dialog_load.pending_type = window.file_type

    window.hint.text = __loc(43, 5)

    var dir = resolve_files_dir(window.file_type)
    var ext1 = resolve_list_primary_ext(window.file_type)
    var ext2 = resolve_list_secondary_ext(window.file_type)

    window.files.change_file_path(dir, ext1)
    if (ext2 && ext2.length > 0)
        window.files.append_files_with_extension(dir, ext2)

    var initial = resolve_initial_basename(window.file_type)
    file_dialog_load.show_filename = initial
    file_dialog_load.show_filename_applied = initial
    file_dialog_load.error_flash_start_ms = 0
    file_dialog_load.error_flash_title_id = 2
    window.filename.value = initial

    if (initial && initial.length > 0) {
        window.files.select_item(initial)
        window.files.scroll_to_selected()
    }
}
