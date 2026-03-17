[es=window]
window_new_career {
    pos [(sw(0) - px(24))/2, (sh(0) - px(8))/2]
    allow_rmb_goback : true
    player_name_value : ""
    ui {
        background_image: background({pack:PACK_UNLOADED, id:31})
        background : outer_panel({size[24, 8]})
        title      : text_center({pos[0, 12], size[px(24), 20], font:FONT_LARGE_BLACK_ON_LIGHT, text[31, 0]})
        player_name: input({margin{left:32, top:48}, size[20, 2], font:FONT_NORMAL_WHITE_ON_DARK, max_length:31, allow_punctuation:1, oninput: new_career_on_input})
        btn_back   : button({margin{left:31, top:89}, size[px(9), 26], text[12, 0], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: new_career_btn_back})
        btn_ok     : button({margin{centerx:16, top:89}, size[px(9), 26], text[13, 5], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: new_career_btn_ok})
    }
}

function new_career_btn_back() {
    window_go_back()
}

function new_career_on_input(params) {
    window_new_career.player_name_value = params.value || ""
}

function new_career_btn_ok() {
    var name = window_new_career.player_name_value
    if (!name || name === "") {
        ui.show_ok("#popup_dialog_no_player_name")
        return
    }
    game.dynasty_name = name
    __game_player_data_new(name)
    window_go_back()
    window_show_by_id("window_player_selection")
}

[es=(window_new_career, init)]
function window_new_career_on_init(window) {
    __game_clear_personal_savings()
    __scenario_init()

    window.player_name.value = game.dynasty_name || "My Dynasty"
    window_new_career.player_name_value = window.player_name.value
}
