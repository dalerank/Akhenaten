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

[es=(display_options_window, init)]
function display_options_window_init(window) {
    window.resolutions.clear()
    var n = display_options_video_modes_count()
    for (var i = 0; i < n; i++) {
        window.resolutions.add_item(display_options_video_get_mode(i))
    }
    var cur = __game_settings.display_size.x + " x " + __game_settings.display_size.y
    window.resolutions.select_item(cur)

    window.videodriver.text = __display_options_video_driver_caption()
    window.btnfullscreen.text = __loc(42, __display_options_is_fullscreen() ? 2 : 1)
}

[es=(display_options_window, toggle_fullscreen)]
function display_options_window_toggle_fullscreen() {
    emit event_app_toggle_fullscreen{ value: 0 }
    window_go_back()
}

[es=(display_options_window, apply_resolution)]
function display_options_window_es_apply_resolution(window) {
    var label = window.resolutions.selected_text(0)
    var sz = display_options_mode_size_for_label(label)
    if (sz.x > 0 && sz.y > 0) {
        emit event_display_options_apply_resolution{ w: sz.x, h: sz.y }
    }
}

[es=window]
display_options_window {
    allow_rmb_goback : true
    draw_underlying: true
    pos [(sw(0) - px(24))/2, (sh(0) - px(21))/2]

    ui {
        background  : outer_panel({size[24, 21] })
        title       : header({pos[10, 10], size[px(24), 20], text:"#display_options_title", align:"center"})

        btnfullscreen : button({pos[16, 46], size[224, 20], onclick_event: "toggle_fullscreen" })
        videodriver : text({pos[px(24)/2 + 60, 50]})

        resolutions : scrollable_list({pos[16, 70], size[20, 14],  view_items:13, draw_scrollbar_always:true})

        save_changes: text({margin{left:px(24)/2 - 80, bottom:-35}, text[43, 5]})

        btnok       : ok_button({margin{left:px(24)/2 + 10, bottom:-40}, onclick_event: "apply_resolution" })
        btncancel   : cancel_button({margin{left:px(24)/2 + 60, bottom:-40}, onclick: window_go_back })
    }
}