log_info("akhenaten: file dialog common started")

function file_dialog_has_text(v) {
    return v !== null && v !== undefined && ("" + v) !== ""
}

function file_dialog_strip_suffix_lower(name, ext) {
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

function file_dialog_basename_from_exts(name, exts) {
    if (!name || name.length === 0)
        return ""

    var base = name
    for (var i = 0; i < exts.length; i++)
        base = file_dialog_strip_suffix_lower(base, exts[i])

    return base
}

function file_dialog_strip_path_extension(src) {
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

function file_dialog_source_for_commit(ev, show_filename, basename_fn) {
    var selected = (ev && ev.files) ? ("" + ev.files.selected_text(1)) : ""
    var live = (ev && ev.filename) ? ("" + ev.filename.value).trim() : ""
    var selBase = file_dialog_has_text(selected) ? basename_fn(selected) : ""
    var liveBase = file_dialog_has_text(live) ? basename_fn(live) : ""

    if (file_dialog_has_text(liveBase) && file_dialog_has_text(selBase) && liveBase !== selBase)
        return live

    if (file_dialog_has_text(selected))
        return selected

    if (file_dialog_has_text(live))
        return live

    return show_filename
}

function file_dialog_savegame_dir() {
    return "Save/" + game.dynasty_name + "/"
}

file_dialog_chrome_base {
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
        btn_cancel: cancel_button({ margin{centerx:50, bottom:-40}, onclick_event: "go_back" })
    }
}
