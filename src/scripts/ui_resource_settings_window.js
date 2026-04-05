log_info("akhenaten: ui resource settings window started")

trade_resource_settings_window {
    resource : null
    pos [(sw(0) - px(36)) / 2, (sh(0) - px(15)) / 2]
    ui {
        background       : outer_panel({size [36, 15]})
        icon             : resource_icon({pos [16, 18] })
        title            : text_center({pos [0, 16], size[px(36), -1], font : FONT_LARGE_BLACK_ON_LIGHT})

        production_state : text_center({pos[48, 42], size[px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT})
        production_store : text_center({pos[48, 62], size[px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT})

        could_import     : text_center({pos[46, 92], size[px(10), 30], font : FONT_NORMAL_BLACK_ON_LIGHT})
        import_status    : button({
            onclick_event: "cycle_trade_import"
            pos[32, 92], size[px(16), 30], align:"left"
            ui {
                import_dec   : arrowdown({pos[px(16) - 51, 3]})
                import_inc   : arrowup({pos[px(16) - 28, 3]})
            }
        })

        could_export     : text_center({pos[98 + 216, 101], size[px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT})
        export_status    : button({pos[px(36)/2, 92], size[px(16), 30], align:"left"
            ui {
                export_dec   : arrowdown({pos[px(16) - 51, 3]})
                export_inc   : arrowup({pos[px(16) - 28, 3]})
            }
        })

        toggle_industry  : button({margin:{centerx:-200}, pos:[-1, 130], size:[400, 30], onclick_event: "toggle_industry"})
        stockpile_industry: button({margin:{centerx:-200}, pos:[-1, 168], size:[400, 50], split:true})

        button_close     : close_button({})
        button_help      : help_button({})
    }
}

[es=(trade_resource_settings_window, cycle_trade_import)]
function trade_resource_settings_window_on_cycle_trade_import(ev) {
    city.resources.cycle_trade_import(trade_resource_settings_window.resource)
}

[es=(trade_resource_settings_window, toggle_industry)]
function trade_resource_settings_window_on_toggle_industry(ev) {
    emit event_toggle_industry_mothballed{ resource: trade_resource_settings_window.resource }
}

[es=(trade_resource_settings_window, init)]
function trade_resource_settings_window_on_init(window) {
    trade_resource_settings_window.resource = window.resource

    var r = window.resource

    window.icon.image = r
    window.title.text = city.resources.get_name(r)

    var stored = city.yards_stored(r)
    window.production_store.text = String(stored) + " " + __loc(8, 10) + " " + __loc(54, 15)

    window.import_dec.onclick = function() { city.resources.change_trading_amount(r, -100) }
    window.import_inc.onclick = function() { city.resources.change_trading_amount(r, 100) }

    window.export_status.onclick = function() { city.resources.cycle_trade_export(r) }
    window.export_dec.onclick = function() { city.resources.change_trading_amount(r, -100) }
    window.export_inc.onclick = function() { city.resources.change_trading_amount(r, 100) }

    window.stockpile_industry.onclick = function() { city.resources.toggle_stockpiled(r) }

    window.button_help.onclick = function() { ui.window_message_dialog_show("message_game_concept_industry") }
    window.button_close.onclick = function() { window_go_back() }
}
