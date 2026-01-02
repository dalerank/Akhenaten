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

[event=empire_window_draw]
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