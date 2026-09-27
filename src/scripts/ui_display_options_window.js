log_info("akhenaten: ui display options window started")

/** Matches a listbox label from display_options_video_get_mode; same format as video_mode ("w x h"). */
function display_options_mode_size_for_label(label) {
    if (!label || label.length === 0) {
        return { x: 0, y: 0 }
    }
    var n = display_options_video_modes_count()
    for (var i = 0; i < n; i++) {
        if (display_options_video_get_mode(i) !== label) {
            continue
        }
        var parts = label.split(" x ")
        if (parts.length !== 2) {
            return { x: 0, y: 0 }
        }
        var x = parseInt(parts[0], 10)
        var y = parseInt(parts[1], 10)
        if (isNaN(x) || isNaN(y)) {
            return { x: 0, y: 0 }
        }
        return { x: x, y: y }
    }
    return { x: 0, y: 0 }
}

function display_options_window_size_label() {
    var sz = __display_options_get_window_size()
    return sz.x + " x " + sz.y
}

function display_options_apply_scale(pct) {
    var w = display_options_window
    return __display_options_set_scale(Math.clamp(pct, w.scale_min, w.scale_max))
}

function display_options_sync_resolution_selection(window) {
    if (!window.resolutions.enabled) {
        return
    }
    window.resolutions.select_item(display_options_window_size_label())
}

[es=(display_options_window, init)]
function display_options_window_init(window) {
    var android = __platform_is_android()
    var fullscreen_only = __game_is_fullscreen_only()
    var w = display_options_window

    w.orig_scale = __display_options_get_scale()
    w.resolution_changed = 0

    window.resolutions.enabled = !android && !fullscreen_only
    window.btnfullscreen.enabled = !fullscreen_only
    window.videodriver.enabled = !android

    if (!android && !fullscreen_only) {
        window.resolutions.clear()
        var n = display_options_video_modes_count()
        for (var i = 0; i < n; i++) {
            window.resolutions.add_item(display_options_video_get_mode(i))
        }
        display_options_sync_resolution_selection(window)
    }

    if (!fullscreen_only) {
        window.btnfullscreen.text = __loc(42, __display_options_is_fullscreen() ? 2 : 1)
    }
    if (!android) {
        window.videodriver.text = __display_options_video_driver_caption()
    }
}

[es=(display_options_window, ui_draw_foreground)]
function display_options_window_es_draw(window) {
    window.scale_pct.text = String(__display_options_get_scale()) + "%"
}

[es=(display_options_window, toggle_fullscreen)]
function display_options_window_toggle_fullscreen() {
    emit event_app_toggle_fullscreen{ value: 0 }
    window_go_back()
}

[es=(display_options_window, resolution_selected)]
function display_options_window_resolution_selected(window) {
    display_options_window.resolution_changed = 1
}

[es=(display_options_window, apply_resolution)]
function display_options_window_es_apply_resolution(window) {
    var w = display_options_window
    var scale_changed = (__display_options_get_scale() != w.orig_scale)
    if (w.resolution_changed && !__platform_is_android() && !__game_is_fullscreen_only()) {
        var label = window.resolutions.selected_text(0)
        var sz = display_options_mode_size_for_label(label)
        if (sz.x > 0 && sz.y > 0) {
            emit event_display_options_apply_resolution{ w: sz.x, h: sz.y }
        }
    }
    w.orig_scale = __display_options_get_scale()
    w.resolution_changed = 0
    __display_options_save()
    window_go_back()
    if (scale_changed) {
        ui.show_ok("#display_options_restart_required")
    }
}

[es=(display_options_window, arrow_scale_down)]
function display_options_window_arrow_scale_down(window) {
    var w = display_options_window
    display_options_apply_scale(__display_options_get_scale() - w.scale_step)
    display_options_sync_resolution_selection(window)
}

[es=(display_options_window, arrow_scale_up)]
function display_options_window_arrow_scale_up(window) {
    var w = display_options_window
    display_options_apply_scale(__display_options_get_scale() + w.scale_step)
    display_options_sync_resolution_selection(window)
}

[es=(display_options_window, go_back)]
function display_options_window_go_back(window) {
    var w = display_options_window
    if (w.orig_scale != __display_options_get_scale()) {
        display_options_apply_scale(w.orig_scale)
    }
    w.resolution_changed = 0
    window_go_back()
}

[es=window]
display_options_window {
    allow_rmb_goback : true
    draw_underlying: true
    pos [(sw(0) - px(24))/2, (sh(0) - px(21))/2]

    orig_scale : 100
    resolution_changed : 0
    scale_step : 5
    scale_min : 50
    scale_max : 300

    ui {
        background  : outer_panel({size[24, 21] })
        title       : header({pos[10, 10], size[px(24), 20], text:"#display_options_title", align:"center"})

        btnfullscreen : button({pos[16, 46], size[224, 20], onclick_event: "toggle_fullscreen" })
        videodriver : text({pos[px(24)/2 + 60, 50]})

        lbl_scale       : text({pos[16, 78], text:"#display_options_ui_scale", font: FONT_NORMAL_BLACK_ON_LIGHT})
        arrow_scale_down: arrowdown({pos[264, 74], tiny:false, allow_repeat: true })
        arrow_scale_up  : arrowup({pos[288, 74], tiny:false, allow_repeat: true })
        scale_pct       : text({pos[326, 78], font: FONT_SMALL_PLAIN})

        resolutions : scrollable_list({pos[16, 100], size[20, 12], view_items:11, draw_scrollbar_always:true, onclick_event: "resolution_selected"})

        save_changes: text({margin{left:px(24)/2 - 80, bottom:-35}, text[43, 5]})

        btnok       : ok_button({margin{left:px(24)/2 + 10, bottom:-40}, onclick_event: "apply_resolution" })
        btncancel   : cancel_button({margin{left:px(24)/2 + 60, bottom:-40}, onclick_event: "go_back" })
    }
}
