log_info("akhenaten: ui difficulty options window started")


[es=(difficulty_options_window, toggle_gods)]
function difficulty_options_toggle_gods(window) {
    __game_settings.gods_enabled = !__game_settings.gods_enabled
    window.btn_gods.text = __game_settings.gods_enabled ? "ON" : "OFF"
}

[es=(difficulty_options_window, ui_draw_foreground)]
function difficulty_options_window_es_draw(window) {
    var difficulty_levels = ["very_easy", "easy", "normal", "hard", "very_hard"]
    window.difficulty_value.text = "${loc.difficulty_" + difficulty_levels[game.difficulty] + "}"
}

[es=(difficulty_options_window, init)]
function difficulty_options_window_es_draw_background(window) {
    window.btn_gods.text = __game_settings.gods_enabled ? "ON" : "OFF"
}

[es=modal_window]
difficulty_options_window {
    allow_rmb_goback : true
    draw_underlying : true
    pos [(sw(0) - px(24))/2, (sh(0) - px(12))/2]

    ui {
        background       : outer_panel({size[24, 12]})
        title            : header({pos[0, 16], size[px(24), 20], text:"#difficulty_settings", align:"center"})

        difficulty_label : text({text:"#difficulty_row_difficulty", pos[32, 50], font: FONT_SMALL_PLAIN})
        arrow_diff_down  : arrowdown({pos[168, 44], tiny:false, allow_repeat: true, onclick: __game_decrease_difficulty })
        arrow_diff_up    : arrowup({pos[192, 44], tiny:false, allow_repeat: true, onclick: __game_increase_difficulty })
        difficulty_value : text({pos[248, 50], font: FONT_SMALL_PLAIN})

        gods_label       : text({text:"#difficulty_row_gods", pos[32, 84], font: FONT_SMALL_PLAIN})
        btn_gods         : button({pos[168, 76], size[50, 22], font: FONT_NORMAL_BLACK_ON_DARK
                                   onclick_event: "toggle_gods"})

        footer           : text({pos[0, 166], size[px(24), 40], text[153, 8], font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"})
    }
}
