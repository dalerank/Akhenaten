log_info("akhenaten: dynasty menu started")

function dynasty_menu_btn_resume() {
    var last = game.last_autosave
    var to_begin = !last || last === "" || !__game_file_exists(last)
    if (to_begin) {
        __game_load_mission(SCENARIO_NUBT, 1)
        return
    }

    if (__game_load_savegame(last)) {
        ui.window_city_show()
    }
}

function dynasty_menu_btn_explore() { window_scenario_selection_show(MAP_SELECTION_CAMPAIGN) }
function dynasty_menu_btn_load() { window_file_dialog_load_show(FILE_TYPE_SAVED_GAME) }
function dynasty_menu_btn_custom() { window_scenario_selection_show(MAP_SELECTION_CUSTOM) }
function dynasty_menu_btn_back() {
    window_player_selection_init();
    window_player_selection_show()
}

window_dinasty_menu {
    pos [(sw(0) - px(24))/2, (sh(0) - px(21))/2]
    ui {
        background_image: background({pack:PACK_UNLOADED, id:31})
        background      : outer_panel({size[24, 19]})

        title       : text_center({pos[0, 20], size[px(24), 20], font:FONT_LARGE_BLACK_ON_LIGHT})
        btnresume   : button({margin{centerx: -135, top: 40 + 1 * 40}, size[270, 25], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: dynasty_menu_btn_resume })
        btnexplore  : button({margin{centerx: -135, top: 40 + 2 * 40}, size[270, 25], text[293, 6], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: dynasty_menu_btn_explore })
        btnload     : button({margin{centerx: -135, top: 40 + 3 * 40}, size[270, 25], text[293, 2], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: dynasty_menu_btn_load })
        btncustom   : button({margin{centerx: -135, top: 40 + 4 * 40}, size[270, 25], text[293, 3], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: dynasty_menu_btn_custom })
        btnback     : button({margin{centerx: -135, top: 40 + 5 * 40}, size[270, 25], text[293, 4], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: dynasty_menu_btn_back })
    }
}

[es=(window_dinasty_menu, go_back)]
function window_dinasty_menu_go_back(window) {
    window_player_selection_init();
    window_player_selection_show()
}

[es=(window_dinasty_menu, init)]
function window_dinasty_menu_on_init(window) {
    __game_load_player_data(game.dynasty_name)

    window.title.text = __loc(293, 5).replace("[player_name]", game.dynasty_name)
    var last = game.last_autosave
    var to_begin = !last || last === "" || !__game_file_exists(last)

    window.btnresume.text = __loc(293, to_begin ? 7 : 0)
}
