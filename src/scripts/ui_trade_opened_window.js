log_info("akhenaten: ui trade opened window started")

[es=(trade_opened_window, init)]
function trade_opened_window_on_init(window) {
    var city = empire.get_city(empire_window.selected_city)
    var sea = !!city && city.is_sea_trade
    window.intro_sea.enabled = sea
    window.intro_land.enabled = !!city && !sea
    window.sea_body_extra.enabled = sea
}

[es=modal_window]
trade_opened_window {
    pos [(sw(0) - px(30)) / 2, (sh(0) - px(14)) / 2]
    allow_rmb_goback : true
    draw_underlying : true

    ui {
        background     : outer_panel({size[30, 14]})
        title          : header({pos[0, 16], size[px(30), 20], text[142, 0], align:"center"})
        intro_sea      : text({pos[32, 56], size[px(26), -1], text[142, 1], multiline:true, wrap:px(26), font: FONT_NORMAL_BLACK_ON_LIGHT, enabled:false})
        intro_land     : text({pos[32, 88], size[px(26), -1], text[142, 1], multiline:true, wrap:px(26), font: FONT_NORMAL_BLACK_ON_LIGHT, enabled:false})
        sea_body_extra : text({pos[32, 120], size[px(26), -1], text[142, 3], multiline:true, wrap:px(26), font: FONT_NORMAL_BLACK_ON_LIGHT, enabled:false})
        footer         : text({pos[48, 192], text[142, 2], align:"center", font: FONT_NORMAL_BLACK_ON_LIGHT})

        button_advisor : image_button({
                                        pos[12, 184]
                                        size[28, 28]
                                        pack:PACK_GENERAL, id:106, offset:12
                                        tooltip:[68, 41]
                                        onclick: function() { window_advisors_show_advisor(ADVISOR_TRADE) }
                                      })

        button_close   : image_button({pos[442, 188], size[24, 24], pack:PACK_GENERAL, id:134, offset:4, onclick: window_go_back })
    }
}
