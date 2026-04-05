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
            onclick      : resource_settings_cycle_trade_import
            pos[32, 92], size[px(16), 30], align:"left"
            ui {
                import_dec   : arrowdown({pos[px(16) - 51, 3], onclick: resource_settings_amount_import_dec})
                import_inc   : arrowup({pos[px(16) - 28, 3], onclick: resource_settings_amount_import_inc})
            }
        })

        could_export     : text_center({pos[98 + 216, 101], size[px(8), -1], font : FONT_NORMAL_BLACK_ON_LIGHT})
        export_status    : button({pos[px(36)/2, 92], size[px(16), 30], align:"left"
            onclick: resource_settings_cycle_trade_export
            ui {
                export_dec   : arrowdown({pos[px(16) - 51, 3], onclick: resource_settings_trading_amount_export_dec})
                export_inc   : arrowup({pos[px(16) - 28, 3], onclick: resource_settings_amount_export_inc})
            }
        })

        toggle_industry  : button({margin{centerx:-200}, pos[-1, 130], size[400, 30], onclick: resource_setting_stoggle_industry})
        stockpile_industry: button({margin{centerx:-200}, pos[-1, 168], size[400, 50], split:true, onclick: resource_settings_toggle_stockpiled})

        button_close     : close_button({onclick: window_go_back})
        button_help      : help_button({onclick: show_window_by_id("message_game_concept_industry")})
    }
}

function resource_settings_cycle_trade_import(ev) {
    city.resources.cycle_trade_import(trade_resource_settings_window.resource)
}

function resource_setting_stoggle_industry(ev) {
    emit event_toggle_industry_mothballed{ resource: trade_resource_settings_window.resource }
}

function resource_settings_amount_import_dec(ev) {
    city.resources.change_trading_amount(trade_resource_settings_window.resource, -100)
}

function resource_settings_amount_import_inc(ev) {
    city.resources.change_trading_amount(trade_resource_settings_window.resource, 100)
}

function resource_settings_cycle_trade_export(ev) {
    city.resources.cycle_trade_export(trade_resource_settings_window.resource)
}

function resource_settings_trading_amount_export_dec(ev) {
    city.resources.change_trading_amount(trade_resource_settings_window.resource, -100)
}

function resource_settings_amount_export_inc(ev) {
    city.resources.change_trading_amount(trade_resource_settings_window.resource, 100)
}

function resource_settings_toggle_stockpiled(ev) {
    city.resources.toggle_stockpiled(trade_resource_settings_window.resource)
}

[es=(trade_resource_settings_window, init)]
function trade_resource_settings_window_on_init(window) {
    trade_resource_settings_window.resource = window.resource

    window.icon.image = window.resource
    window.title.text = city.resources.get_name(window.resource)

    var stored = city.yards_stored(window.resource)
    window.production_store.text = fmt("${stored} ${unit} ${stored_in_city}", { stored: stored, unit: __loc(8, 10), stored_in_city: __loc(54, 15)})
}
