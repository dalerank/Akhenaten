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

        arrow_diff_down  : arrowdown({pos[240, 54], tiny:false, allow_repeat: true, onclick: __game_decrease_difficulty })
        arrow_diff_up    : arrowup({pos[264, 54], tiny:false, allow_repeat: true, onclick: __game_increase_difficulty })
        difficulty_value : text({pos[22, 62], size[244, 20], font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"})

        btn_gods         : button({pos[238, 102], size[50, 22], font: FONT_NORMAL_BLACK_ON_DARK, onclick_event: "toggle_gods"})
        gods_value       : text({pos[22, 110], size[244, 20], text:"#difficulty_row_gods", font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"})

        footer           : text({pos[0, 156], size[px(24), 20], text:"#difficulty_right_click_to_continue", font: FONT_NORMAL_BLACK_ON_LIGHT, align:"center"})
    }
}
