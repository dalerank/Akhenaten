log_info("akhenaten: ui speed options window started")

[es=(speed_options_window, init)]
function speed_options_window_es_init(window) {
    var w = speed_options_window
    w.original_game_speed = Math.round(game_features.gameopt_game_speed)
    w.original_scroll_speed = Math.round(game_features.gameopt_scroll_speed)
    w.original_clouds_speed = Math.round(game_features.gameopt_clouds_speed)
    w.original_middle_mouse_camera_pan = game_features.gameopt_middle_mouse_camera_pan === true
    w.original_middle_mouse_pan_speed = Math.round(game_features.gameopt_middle_mouse_pan_speed)
}

[es=(speed_options_window, ui_draw_foreground)]
function speed_options_window_es_draw(window) {
    window.game_speed_value.text = Math.round(game_features.gameopt_game_speed) + "%"
    window.scroll_speed_value.text = Math.round(game_features.gameopt_scroll_speed) + "%"
    window.clouds_speed_value.text = Math.round(game_features.gameopt_clouds_speed) + "%"
    window.middle_pan_speed_value.text = Math.round(game_features.gameopt_middle_mouse_pan_speed) + "%"
}

[es=modal_window]
speed_options_window {
    allow_rmb_goback : true
    draw_underlying : true
    pos [(sw(0) - px(20))/2, (sh(0) - px(22))/2]

    original_game_speed : 0
    original_scroll_speed : 0
    original_clouds_speed : 0
    original_middle_mouse_camera_pan : false
    original_middle_mouse_pan_speed : 0

    ui {
        background         : outer_panel({size[20, 22]})
        title              : header({pos[0, 16], size[px(20), 20], text[45, 0], align:"center"})

        game_speed_label   : text({text[45, 2], pos[32, 66], font: FONT_SMALL_PLAIN})
        game_speed_value   : text({pos[248, 66], font: FONT_SMALL_PLAIN})

        arrow_game_down    : arrowdown({pos[192, 60], tiny:false, allow_repeat: true })
        arrow_game_up      : arrowup({pos[216, 60], tiny:false, allow_repeat: true })

        scroll_speed_label : text({text[45, 3], pos[32, 102], font: FONT_SMALL_PLAIN})
        scroll_speed_value : text({pos[248, 102], font: FONT_SMALL_PLAIN})

        arrow_scroll_down  : arrowdown({pos[192, 96], tiny:false, allow_repeat: true })
        arrow_scroll_up    : arrowup({pos[216, 96], tiny:false, allow_repeat: true })

        clouds_speed_label : text({text[45, 5], pos[32, 138], font: FONT_SMALL_PLAIN})
        clouds_speed_value : text({pos[248, 138], font: FONT_SMALL_PLAIN})

        arrow_clouds_down  : arrowdown({pos[192, 132], tiny:false, allow_repeat: true })
        arrow_clouds_up    : arrowup({pos[216, 132], tiny:false, allow_repeat: true })

        middle_pan_speed_label : text({text[45, 7], pos[32, 174], font: FONT_SMALL_PLAIN})
        middle_pan_speed_value : text({pos[248, 174], font: FONT_SMALL_PLAIN})
        arrow_middle_pan_down  : arrowdown({pos[192, 168], tiny:false, allow_repeat: true })
        arrow_middle_pan_up    : arrowup({pos[216, 168], tiny:false, allow_repeat: true })

        middle_mouse_label : text({text[45, 6], pos[32, 210], font: FONT_SMALL_PLAIN})
        middle_mouse_pan   : checkbox({ pos[248, 204], checkedfn: function () { return game_features.gameopt_middle_mouse_camera_pan === true } })

        btnok              : ok_button({margin{left:px(20)/2 - 40, bottom:-40} })
        btncancel          : cancel_button({margin{left:px(20)/2 + 20, bottom:-40} })
    }
}

[es=(speed_options_window, btnok)]
function speed_options_window_btnok(window) {
    window_go_back()
}

[es=(speed_options_window, btncancel)]
function speed_options_window_btncancel(window) {
    var w = speed_options_window
    game_features.gameopt_game_speed = w.original_game_speed
    emit event_update_game_tick_timer{ reserved: 0 }
    game_features.gameopt_scroll_speed = w.original_scroll_speed
    game_features.gameopt_clouds_speed = w.original_clouds_speed
    game_features.gameopt_middle_mouse_camera_pan = w.original_middle_mouse_camera_pan
    game_features.gameopt_middle_mouse_pan_speed = w.original_middle_mouse_pan_speed
    window_go_back()
}

[es=(speed_options_window, arrow_game_down)]
function speed_options_arrow_game_down(window) {
    emit event_change_gamespeed{ increase: false }
}

[es=(speed_options_window, arrow_game_up)]
function speed_options_arrow_game_up(window) {
    emit event_change_gamespeed{ increase: true }
}

[es=(speed_options_window, arrow_scroll_down)]
function speed_options_arrow_scroll_down(window) {
    emit event_change_scroll_speed{ increase: false }
}

[es=(speed_options_window, arrow_scroll_up)]
function speed_options_arrow_scroll_up(window) {
    emit event_change_scroll_speed{ increase: true }
}

[es=(speed_options_window, arrow_clouds_down)]
function speed_options_arrow_clouds_down(window) {
    emit event_change_clouds_speed{ increase: false }
}

[es=(speed_options_window, arrow_clouds_up)]
function speed_options_arrow_clouds_up(window) {
    emit event_change_clouds_speed{ increase: true }
}

[es=(speed_options_window, arrow_middle_pan_down)]
function speed_options_arrow_middle_pan_down(window) {
    emit event_change_middle_mouse_pan_speed{ increase: false }
}

[es=(speed_options_window, arrow_middle_pan_up)]
function speed_options_arrow_middle_pan_up(window) {
    emit event_change_middle_mouse_pan_speed{ increase: true }
}

[es=(speed_options_window, middle_mouse_pan)]
function speed_options_middle_mouse_pan(window) {
    game_features.gameopt_middle_mouse_camera_pan = !game_features.gameopt_middle_mouse_camera_pan
}
