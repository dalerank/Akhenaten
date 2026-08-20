log_info("akhenaten: file dialog load scenario (script UI) started")

var FILE_DIALOG_LOAD_SCENARIO_ERROR_FLASH_MS = 500

function file_dialog_load_scenario_basename_from_list_entry(name) {
    return file_dialog_basename_from_exts(name, ["map"])
}

function file_dialog_load_scenario_resolve_initial() {
    var last = game.get_last_loaded_file(FILE_TYPE_SCENARIO)
    if (last && last.length > 0) {
        var b = file_dialog_strip_path_extension(last)
        if (b && b.length > 0)
            return b
    }

    var kind = game.session_last_loaded_kind
    var mission = game.session_last_loaded_mission
    if (kind === e_session_custom_map && mission && mission.length > 0)
        return file_dialog_strip_path_extension(mission)

    return ""
}

function file_dialog_load_scenario_fullpath(relative) {
    if (!relative || relative.length === 0)
        return ""

    var r = "" + relative
    var head = r.substring(0, 5).toLowerCase()
    if (head === "maps/" || head === "maps\\")
        return r

    return "Maps/" + r
}

function file_dialog_load_scenario_set_show_filename(from_user) {
    file_dialog_load_scenario.show_filename = file_dialog_load_scenario_basename_from_list_entry(from_user)
    file_dialog_load_scenario.error_flash_start_ms = 0
}

function file_dialog_load_scenario_try_load(basename) {
    if (!basename || basename.length === 0)
        return 1

    var full = file_dialog_load_scenario_fullpath(basename)
    if (!game.file_exists(full))
        return 1

    if (!game.editor_load_scenario(full))
        return 2

    ui.window_editor_map_show()
    __set_last_loaded_utf8(FILE_TYPE_SCENARIO, file_dialog_load_scenario_basename_from_list_entry(basename))
    return 0
}

function file_dialog_load_scenario_handle_load(window) {
    var name = file_dialog_load_scenario.show_filename
    var selected_with_ext = (window && window.files) ? window.files.selected_text(1) : ""
    var source_name = file_dialog_has_text(selected_with_ext) ? ("" + selected_with_ext) : name
    if (!file_dialog_has_text(source_name))
        return

    var normalized = file_dialog_load_scenario_basename_from_list_entry(source_name)
    if (normalized !== file_dialog_load_scenario.show_filename) {
        file_dialog_load_scenario.show_filename = normalized
        file_dialog_load_scenario.show_filename_applied = ""
    }

    var r = file_dialog_load_scenario_try_load(source_name)
    if (r !== 0) {
        file_dialog_load_scenario.error_flash_title_id = (r === 2) ? 7 : 2
        file_dialog_load_scenario.error_flash_start_ms = __game_time_millis()
    }
}

[es=window]
file_dialog_load_scenario {
    pos: [(sw(0) - px(24)) / 2, (sh(0) - px(21)) / 2]
    allow_rmb_goback: true
    draw_underlying: true
    show_filename: ""
    show_filename_applied: ""
    error_flash_start_ms: 0
    error_flash_title_id: 2

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

[es=(file_dialog_load_scenario, go_back)]
function file_dialog_load_scenario_es_go_back(window) {
    window_go_back()
}

[es=(file_dialog_load_scenario, on_filename_input)]
function file_dialog_load_scenario_es_on_filename_input(ev) {
    file_dialog_load_scenario_set_show_filename(ev.value)
}

[es=(file_dialog_load_scenario, on_select_file)]
function file_dialog_load_scenario_es_on_select_file(ev) {
    file_dialog_load_scenario_set_show_filename(ev.text)
}

[es=(file_dialog_load_scenario, on_double_click_file)]
function file_dialog_load_scenario_es_on_double_click_file(ev) {
    file_dialog_load_scenario_set_show_filename(ev.text)
    file_dialog_load_scenario_handle_load(ev)
}

[es=(file_dialog_load_scenario, on_ok)]
function file_dialog_load_scenario_on_ok(window) {
    file_dialog_load_scenario_handle_load(window)
}

[es=(file_dialog_load_scenario, ui_draw_foreground)]
function file_dialog_load_scenario_ui_draw_foreground(window) {
    var flash_start = file_dialog_load_scenario.error_flash_start_ms
    var flash_active = flash_start !== 0 && (__game_time_millis() - flash_start) < FILE_DIALOG_LOAD_SCENARIO_ERROR_FLASH_MS
    if (flash_active) {
        window.title.text = __loc(43, file_dialog_load_scenario.error_flash_title_id)
    } else {
        window.title.text = __loc(43, 4)
    }

    if (file_dialog_load_scenario.show_filename !== file_dialog_load_scenario.show_filename_applied) {
        window.filename.value = file_dialog_load_scenario.show_filename
        file_dialog_load_scenario.show_filename_applied = file_dialog_load_scenario.show_filename
    }
}

[es=(file_dialog_load_scenario, init)]
function file_dialog_load_scenario_on_init(window) {
    window.hint.text = __loc(43, 5)
    window.files.change_file_path("Maps/", "map")

    var initial = file_dialog_load_scenario_resolve_initial()
    file_dialog_load_scenario.show_filename = initial
    file_dialog_load_scenario.show_filename_applied = initial
    file_dialog_load_scenario.error_flash_start_ms = 0
    file_dialog_load_scenario.error_flash_title_id = 2
    window.filename.value = initial

    if (initial && initial.length > 0) {
        window.files.select_item(initial)
        window.files.scroll_to_selected()
    }
}
