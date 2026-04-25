log_info("akhenaten: ui speed options window started")

function speed_options_on_cancel() {
    var w = speed_options_window
    game_features.gameopt_game_speed = w.original_game_speed
    game_features.gameopt_scroll_speed = w.original_scroll_speed
    window_go_back()
}

[es=(speed_options_window, init)]
function speed_options_window_es_init(window) {
    var w = speed_options_window
    w.original_game_speed = Math.round(game_features.gameopt_game_speed)
    w.original_scroll_speed = Math.round(game_features.gameopt_scroll_speed)
}

[es=(speed_options_window, ui_draw_foreground)]
function speed_options_window_es_draw(window) {
    window.game_speed_value.text = Math.round(game_features.gameopt_game_speed) + "%"
    window.scroll_speed_value.text = Math.round(game_features.gameopt_scroll_speed) + "%"
}

[es=modal_window]
speed_options_window {
    allow_rmb_goback : true
    draw_underlying : true
    pos [(sw(0) - px(20))/2, (sh(0) - px(14))/2]

    original_game_speed : 0
    original_scroll_speed : 0

    ui {
        background         : outer_panel({size[20, 14]})
        title              : header({pos[0, 16], size[px(20), 20], text[45, 0], align:"center"})

        game_speed_label   : text({text[45, 2], pos[32, 66], font: FONT_SMALL_PLAIN})
        game_speed_value   : text({pos[248, 66], font: FONT_SMALL_PLAIN})

        arrow_game_down    : arrowdown({pos[192, 60], tiny:false, allow_repeat: true, onclick: function() { emit event_change_gamespeed{ increase: false } } })
        arrow_game_up      : arrowup({pos[216, 60], tiny:false, allow_repeat: true, onclick: function() { emit event_change_gamespeed{ increase: true } } })

        scroll_speed_label : text({text[45, 3], pos[32, 102], font: FONT_SMALL_PLAIN})
        scroll_speed_value : text({pos[248, 102], font: FONT_SMALL_PLAIN})

        arrow_scroll_down  : arrowdown({pos[192, 96], tiny:false, allow_repeat: true, onclick: function() { emit event_change_scroll_speed{ increase: false } } })
        arrow_scroll_up    : arrowup({pos[216, 96], tiny:false, allow_repeat: true, onclick: function() { emit event_change_scroll_speed{ increase: true } } })

        btnok              : ok_button({margin{left:px(20)/2 - 40, bottom:-40}, onclick: window_go_back })
        btncancel          : cancel_button({margin{left:px(20)/2 + 20, bottom:-40}, onclick: speed_options_on_cancel })
    }
}
