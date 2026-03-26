log_info("akhenaten: ui empire window common started")

empire_window {
    trade_column_spacing : 146
    trade_row_spacing : 20
    info_y_traded : -3
    trade_button_offset_x : 0
    info_y_footer_1 : 78
    info_y_city_desc : 28
    trade_resource_size : 18
    trade_resource_offset : 3
    trade_button_offset_y : 10
    start_pos : [16, 16]
    finish_pos : [32, 136]
    image : {pack:PACK_EMPIRE, id:1}
    bottom_image : {pack:PACK_GENERAL, id:172, offset:3}
    horizontal_bar : {pack:PACK_GENERAL, id:172, offset:1}
    vertical_bar : {pack:PACK_GENERAL, id:172, offset:0}
    cross_bar : {pack:PACK_GENERAL, id:172, offset:2}
    trade_amount : {pack:PACK_GENERAL, id:171}
    closed_trade_route_hl : {pack:PACK_GENERAL, id:149, offset:211}
    open_trade_route : {pack:PACK_GENERAL, id:149, offset:201}
    open_trade_route_hl : {pack:PACK_GENERAL, id:149, offset:186}

    ui {
        background           : dummy({size[sw(0), sh(0)]})
        city_name            : header({pos[0, -1], margin{bottom:-120}, size[sw(0), 20], align:"center"})
        button_help          : help_button({margin{centerx:575, bottom:-120}})
        button_close         : close_button({margin{centerx:575, bottom:-40}})
        button_advisor       : advisor_button({margin{centerx:-595, bottom:-120}})

        button_open_trade    : button({margin{centerx:-220, bottom:-40}, size:[440, 20]})
        info_tooltip         : text({margin{centerx:-200, bottom:-60}, size:[400, 20], font:FONT_NORMAL_BLACK_ON_LIGHT, align:"center"})

        city_sell_title      : text({text[47, 11], margin{centerx:250, bottom:-120}, font: FONT_NORMAL_BLACK_ON_LIGHT })
        city_sell_items      : dummy({pos[0, 100], size[200, 0], margin{centerx:100, bottom:-90}})
        city_sell_item       : dummy({size[120, 20], font:FONT_SMALL_PLAIN})

        city_buy_title       : text({text[47, 10], margin{centerx:-300, bottom:-120}, font: FONT_NORMAL_BLACK_ON_LIGHT })
        city_buy_items       : dummy({pos[0, 0], size[200, 0], margin{centerx:-430, bottom:-90}})
        city_buy_item        : dummy({size[120, 20], font:FONT_SMALL_PLAIN})

        city_want_sell_title : text({text[47, 5], margin{centerx:-220, bottom:-90}, font: FONT_NORMAL_BLACK_ON_LIGHT })
        city_want_sell_items : dummy({pos[0, 100], margin{centerx:-170, bottom:-90}})
        city_want_sell_item  : dummy({size[110, 0], font:FONT_SMALL_PLAIN})

        city_want_buy_title  : text({text[47, 4], margin{centerx:-220, bottom:-70}, font: FONT_NORMAL_BLACK_ON_LIGHT })
        city_want_buy_items  : dummy({pos[0, 0], margin{centerx:-170, bottom:-70}})
        city_want_buy_item   : dummy({size[110, 0], font:FONT_SMALL_PLAIN})
    }
}

function empire_window_screen_bounds() {
    var map_img = get_image(empire_window.image)
    var f = empire_window.finish_pos
    var fx = f.x !== undefined ? f.x : f[0]
    var fy = f.y !== undefined ? f.y : f[1]
    var bottom_extra = 20
    var ew = map_img ? (map_img.width + fx) : (1200 + 32)
    var eh = map_img ? (map_img.height + fy + bottom_extra) : (1600 + 136 + 20)
    var sw = game.screen.w
    var sh = game.screen.h
    var min_x = sw <= ew ? 0 : ((sw - ew) / 2) | 0
    var max_x = sw <= ew ? sw : min_x + ew
    var min_y = sh <= eh ? 0 : ((sh - eh) / 2) | 0
    var max_y = sh <= eh ? sh : min_y + eh
    return { min_pos: {x: min_x, y: min_y}, max_pos: {x: max_x, y: max_y} }
}

[es=(empire_window, init)]
function empire_window_on_init(window) {
    window.button_help.onclick = function() { ui.window_message_dialog_show("message_world_map") }
    window.button_close.onclick = function() { ui.window_city_show() }
    window.button_advisor.onclick = function() { ui.show_advisor(ADVISOR_TRADE) }
    window.button_open_trade.onclick = function() {
        ui.show_yesno("#popup_dialog_open_trade", function() { empire_window_confirm_open_trade() })
    }
}

[es=(empire_window, draw_map)]
function empire_window_draw_distant_battle_icon(window) {
    if (!empire.has_distant_battle) {
        return
    }

    var ecity = empire.get_city(empire.active_battle.city)
    if (!ecity) {
        return
    }

    var battle_icon = get_image("pharaoh_general/empire_bits_00001")
    if (!battle_icon) {
        return
    }

    var battle_icon_pos = vec2i(window.draw_offset)
                            .add(ecity.empire_object.pos)
                            .add({x:-battle_icon.width / 2, y:-battle_icon.height / 2})

    ui.image(battle_icon, battle_icon_pos)
}

[es=(empire_window, draw_map)]
function empire_window_draw_dispatched_army_icon(window) {
    if (empire.dispatched_army.state <= 0) {
        return
    }

    var army_icon = get_image("pharaoh_general/empire_bits_00009")
    if (!army_icon) {
        return
    }

    var army_icon_pos = vec2i(window.draw_offset)
                            .add(empire.dispatched_army.pos)
                            .add({x:-army_icon.width / 2, y:-army_icon.height / 2})

    ui.image(army_icon, army_icon_pos)
}

[es=(empire_window, draw_paneling)]
function empire_window_draw_paneling(window) {
    var bounds = empire_window_screen_bounds()
    var min_pos = bounds.min_pos
    var max_pos = bounds.max_pos

    var bottom = get_image(empire_window.bottom_image)
    var hbar = get_image(empire_window.horizontal_bar)
    var vbar = get_image(empire_window.vertical_bar)
    var cross = get_image(empire_window.cross_bar)

    ui.set_clip_rectangle(min_pos, vec2i(max_pos).sub(min_pos))

    for (var x = min_pos.x; x < max_pos.x; x += 70) {
        ui.image(bottom, {x: x, y: max_pos.y - 140})
        ui.image(bottom, {x: x, y: max_pos.y - 100})
        ui.image(bottom, {x: x, y: max_pos.y - 60})
        ui.image(bottom, {x: x, y: max_pos.y - 20})
    }

    for (var x = min_pos.x; x < max_pos.x; x += 86) {
        ui.image(hbar, {x: x, y: min_pos.y})
        ui.image(hbar, {x: x, y: max_pos.y - 140})
        ui.image(hbar, {x: x, y: max_pos.y - 16})
    }

    for (var y = min_pos.y + 16; y < max_pos.y; y += 86) {
        ui.image(vbar, {x: min_pos.x, y: y})
        ui.image(vbar, {x: max_pos.x - 16, y: y})
    }

    ui.image(cross, {x: min_pos.x, y: min_pos.y})
    ui.image(cross, {x: min_pos.x, y: max_pos.y - 140})
    ui.image(cross, {x: min_pos.x, y: max_pos.y - 16})
    ui.image(cross, {x: max_pos.x - 16, y: min_pos.y})
    ui.image(cross, {x: max_pos.x - 16, y: max_pos.y - 140})
    ui.image(cross, {x: max_pos.x - 16, y: max_pos.y - 16})

    ui.reset_clip_rectangle()
}