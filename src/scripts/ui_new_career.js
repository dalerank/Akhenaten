[es=window]
window_new_career {
    pos [(sw(0) - px(24))/2, (sh(0) - px(22))/2]
    allow_rmb_goback : true
    ui {
        background_image: background({pack:PACK_UNLOADED, id:31})
        background : outer_panel({size[24, 22]})
        title      : text_center({pos[0, 12], size[px(24), 20], font:FONT_LARGE_BLACK_ON_LIGHT, text[31, 0]})
        player_name: input({margin{left:32, top:48}, size[20, 2], font:FONT_NORMAL_WHITE_ON_DARK, max_length:31, allow_punctuation:1})
        names_title: text({pos[32, 84], text[13, 8], font:FONT_NORMAL_BLACK_ON_LIGHT})
        name_list  : scrollable_list({
            margin{left:16, top:104}
            size[20, 12]
            view_items:11
            draw_scrollbar_always:true
            draw_paneling:true
            onclick_event: "pick_name"
            ondoubleclick_event: "pick_name_ok"
        })
        btn_back   : button({margin{left:31, top:312}, size[px(9), 26], text[12, 0], font:FONT_NORMAL_BLACK_ON_LIGHT })
        btn_ok     : button({margin{centerx:16, top:312}, size[px(9), 26], text[13, 5], font:FONT_NORMAL_BLACK_ON_LIGHT, onclick_event: "ok"})
    }
}

function new_career_trim_name(name) {
    if (!name) {
        return ""
    }
    // Loc strings may include trailing spaces from the original language packs.
    while (name.length > 0 && name.charAt(name.length - 1) === " ") {
        name = name.substring(0, name.length - 1)
    }
    return name
}

function new_career_is_missing_loc(text) {
    if (!text || text === "") {
        return true
    }
    // lang_get_string placeholders are exactly "#<group>.<id>".
    if (text.charAt(0) !== "#") {
        return false
    }
    var i = 1
    var digits = 0
    while (i < text.length && text.charAt(i) >= "0" && text.charAt(i) <= "9") {
        digits++
        i++
    }
    if (digits === 0 || text.charAt(i) !== ".") {
        return false
    }
    i++
    digits = 0
    while (i < text.length && text.charAt(i) >= "0" && text.charAt(i) <= "9") {
        digits++
        i++
    }
    return digits > 0 && i === text.length
}

function new_career_fill_egyptian_names(window) {
    window.name_list.clear()
    var i
    for (i = 0; i < 256; i++) {
        var name = __loc(151, i)
        if (new_career_is_missing_loc(name)) {
            break
        }
        window.name_list.add_item(name, i)
    }
}

[es=(window_new_career, btn_back)]
function window_new_career_btn_back(window) {
    window_go_back()
}

[es=(window_new_career, pick_name)]
function new_career_on_pick_name(window) {
    var name = new_career_trim_name(window.text)
    if (!name) {
        return
    }
    window.player_name.value = name
}

function new_career_commit(window) {
    var name = new_career_trim_name(window.player_name.value || "")
    if (!name) {
        ui.show_ok(__loc("#popup_dialog_no_player_name"), __loc(5, 96))
        return
    }
    game.dynasty_name = name
    __game_player_data_new(name)
    // Opened from player selection — go_back restores it and refreshes the list.
    window_go_back()
}

[es=(window_new_career, pick_name_ok)]
function new_career_on_pick_name_ok(window) {
    var name = new_career_trim_name(window.text)
    if (name) {
        window.player_name.value = name
    }
    new_career_commit(window)
}

[es=(window_new_career, ok)]
function new_career_btn_ok(window) {
    new_career_commit(window)
}

[es=(window_new_career, init)]
function window_new_career_on_init(window) {
    __scenario_init()
    city.kingdome.campaign_carry_personal_savings = 0
    city.kingdome.personal_savings = 0
    __campaign_carry_clear()

    var default_name = __loc(9, 5)
    if (new_career_is_missing_loc(default_name)) {
        default_name = "Your Name Here"
    }
    window.player_name.value = game.dynasty_name || default_name
    new_career_fill_egyptian_names(window)
}
