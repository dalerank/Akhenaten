log_info("akhenaten: ui speed options window started")

speed_options_window {
    pos [(sw(0) - px(20))/2, (sh(0) - px(14))/2]

    original_game_speed : 0
    original_scroll_speed : 0

    ui {
        background         : outer_panel({size[20, 14]})
        title              : header({pos[0, 16], size[px(20), 20], text[45, 0], align:"center"})

        game_speed_label   : text({text[45, 2], pos[32, 66], font: FONT_SMALL_PLAIN})
        game_speed_value   : text({pos[248, 66], font: FONT_SMALL_PLAIN})

        arrow_game_down    : arrowdown({pos[192, 60], tiny:false, onclick: __game_decrease_game_speed })
        arrow_game_up      : arrowup({pos[216, 60], tiny:false, onclick: __game_increase_game_speed })

        scroll_speed_label : text({text[45, 3], pos[32, 102], font: FONT_SMALL_PLAIN})
        scroll_speed_value : text({pos[248, 102], font: FONT_SMALL_PLAIN})

        arrow_scroll_down  : arrowdown({pos[192, 96], tiny:false, onclick: __game_decrease_scroll_speed})
        arrow_scroll_up    : arrowup({pos[216, 96], tiny:false, onclick: __game_increase_scroll_speed})

        btn_ok             : button({margin{centerx: -96, bottom: -34}, size[192, 24], text[45, 4], font: FONT_NORMAL_BLACK_ON_DARK, onclick: window_go_back})
        btn_cancel         : button({margin{centerx: -96, bottom: -60}, size[192, 24], text[45, 1], font: FONT_NORMAL_BLACK_ON_DARK, onclick: speed_options_window_oncancel})
    }
}

[event=speed_options_window_cancel]
function speed_options_window_oncancel(p1, p2) {
    log_info("akhenaten: speed options window oncancel")
    game.game_speed = speed_options_window.original_game_speed
    game.scroll_speed = speed_options_window.original_scroll_speed
    log_info("akhenaten: speed options window init ${original_game_speed} ${original_scroll_speed}", speed_options_window)
    window_go_back()
}

[event=speed_options_window_draw]
function speed_options_window_update(window) {
    window.game_speed_value.text = game.game_speed + "%"
    window.scroll_speed_value.text = game.scroll_speed + "%"
}

[event=speed_options_window_init]
function speed_options_window_init(window) {
    log_info("akhenaten: speed options window init")
    speed_options_window.original_game_speed = game.game_speed
    speed_options_window.original_scroll_speed = game.scroll_speed
    log_info("akhenaten: speed options window init ${original_game_speed} ${original_scroll_speed}", speed_options_window)
}