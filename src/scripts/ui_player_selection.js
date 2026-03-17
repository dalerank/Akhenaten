log_info("akhenaten: player selection started")

function player_selection_on_click_item(entry) {
    window_player_selection.dynasty_name_changed = entry.text
    game.dynasty_name = entry.text
}

function player_selection_on_double_click(entry) {
    player_selection_proceed()
}

function player_selection_btn_new() {
    window_show_by_id("window_new_career")
}

function player_selection_btn_delete() {
    if (game.dynasty_name == "") {
        ui.show_ok("#popup_dialog_no_dynasty")
        return
    }

    ui.show_yesno("#popup_dialog_delete_dynasty", function() {
        __game_delete_player(game.dynasty_name)
        window_player_selection.need_refresh_list = true
    })
}

function player_selection_proceed() {
    if (game.dynasty_name == "") {
        ui.show_ok("#popup_dialog_no_dynasty")
        return
    }

    window_show_by_id("window_dinasty_menu")
}

function player_selection_btn_back() {
    window_go_back()
}

[es=window]
window_player_selection {
    pos [(sw(0) - px(24))/2, (sh(0) - px(21))/2]
    allow_rmb_goback : true
    dynasty_name_changed : ""
    need_refresh_list : false
    ui {
        background_image : background({pack:PACK_UNLOADED, id:29})
        background       : outer_panel({size[24, 21]})

        title    : text_center({pos[0, 16], size[px(24), 20], font:FONT_LARGE_BLACK_ON_LIGHT, text[292, 3]})

        player_list : scrollable_list({
            margin{left:16, top:52}
            size[20, 13]
            dir:"Save/"
            file_ext:"folders"
            use_file_finder:true
            view_items:12
            draw_scrollbar_always:true
            onclick_item: player_selection_on_click_item
            ondoubleclick_item: player_selection_on_double_click
        })

        btn_new    : button({margin{left:16, top:266}, size[126, 25], text[292, 0], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: player_selection_btn_new })
        btn_delete : button({margin{left:146, top:266}, size[126, 25], text[292, 1], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: player_selection_btn_delete })
        btn_proceed: button({margin{left:278, top:266}, size[86, 25], text[292, 2], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: player_selection_proceed })
        btn_back   : button({margin{left:64, top:296}, size[256, 25], text[292, 4], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick: player_selection_btn_back })
    }
}

function update_player_list(window) {
    window.player_list.refresh_file_finder()
    if (game.dynasty_name !== "") {
        window.player_list.select_item(game.dynasty_name)
    }

    if (window.player_list.items_count == 1) {
        window.player_list.select_index(0)
        var name = window.player_list.selected_text(0)
        if (name !== "") {
            game.dynasty_name = name
        }
    } else {
        game.dynasty_name = ""
    }
    window_player_selection.need_refresh_list = false
}

[es=(window_player_selection, ui_draw_foreground)]
function window_player_selection_ui_draw_foreground(window) {
    if (window_player_selection.need_refresh_list) {
        update_player_list(window)
    }
}

[es=(window_player_selection, on_restore)]
function window_player_selection_on_restore(window) {
    window_player_selection.need_refresh_list = true
}

[es=(window_player_selection, init)]
function window_player_selection_on_init(window) {
   window_player_selection.need_refresh_list = true
}
